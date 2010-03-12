#include <stdlib.h>
#include <QtCore/QtGlobal>

#include "fiber.h"

/*!
  \class Fiber
  \brief The Fiber class provides cooperatively scheduled stacks of execution.

  Fibers, also known as coroutines, allow managing multiple stacks in the same
  thread.

  To create a fiber, subclass Fiber and override the run() method. To run it,
  call cont(). This will execute the code in run() until it calls Fiber::yield().
  At that point, the call to cont() returns. Subsequent calls to cont() will
  continue execution of the fiber just after the yield().

  Example:
  class MyFiber : public Fiber
  {
      virtual void run()
      {
          qDebug() << "1";
          Fiber::yield();
          qDebug() << "2";
      }
  }

  MyFiber fib;
  qDebug() << "0.5";
  fib.cont(); // prints 1
  qDebug() << "1.5";
  fib.cont(); // prints 2
*/

#ifdef Q_OS_MAC
extern "C" void switchStackInternal(void* to, void** from);
void initializeStack(void *data, int size, void (*entry)(), void **stackPointer);
void switchStack(void* to, void** from) { switchStackInternal(to, from); }
#else
extern "C" void _switchStackInternal(void* to, void** from);
void initializeStack(void *data, int size, void (*entry)(), void **stackPointer);
void switchStack(void* to, void** from) { _switchStackInternal(to, from); }
#endif

Fiber *Fiber::_currentFiber = 0;

Fiber::Fiber(int stackSize)
    : _stackData(0)
    , _stackPointer(0)
    , _previousFiber(0)
    , _status(NotStarted)
{
    // establish starting fiber context if necessary
    currentFiber();
    
    _stackData = malloc(stackSize);
    initializeStack(_stackData, stackSize, &entryPoint, &_stackPointer);
}

Fiber::Fiber(bool)
    : _stackData(0)
    , _stackPointer(0)
    , _previousFiber(0)
    , _status(Running)
{
}

Fiber::~Fiber()
{
    if (_stackData)
        free(_stackData);
}

Fiber *Fiber::currentFiber()
{
    // establish a context for the starting fiber
    if (!_currentFiber)
        _currentFiber = new Fiber(true);
    
    return _currentFiber;
}

void Fiber::entryPoint()
{
    _currentFiber->run();
    yieldHelper(Terminated);
    Q_ASSERT(0); // unreachable
}

// returns whether it can be continued again
bool Fiber::cont()
{    
    Q_ASSERT(_status == NotStarted || _status == Stopped);
    Q_ASSERT(!_previousFiber);
    
    _previousFiber = _currentFiber;
    _currentFiber = this;
    _status = Running;
    switchStack(_stackPointer, &_previousFiber->_stackPointer);
    return _status != Terminated;
}

void Fiber::yield()
{
    yieldHelper(Stopped);
}

void Fiber::yieldHelper(Status stopStatus)
{
    Fiber *stoppingFiber = _currentFiber;
    Q_ASSERT(stoppingFiber);
    Q_ASSERT(stoppingFiber->_previousFiber);
    Q_ASSERT(stoppingFiber->_status == Running);

    _currentFiber = stoppingFiber->_previousFiber;
    stoppingFiber->_previousFiber = 0;
    stoppingFiber->_status = stopStatus;
    switchStack(_currentFiber->_stackPointer, &stoppingFiber->_stackPointer);
}
