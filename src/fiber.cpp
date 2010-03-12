#include <stdlib.h>
#include <QtCore/QtGlobal>
#include <QtCore/QThreadStorage>

#include "fiber.h"

/*!
  \class Fiber
  \brief The Fiber class provides cooperatively scheduled stacks of execution.

  Fibers, also known as coroutines, allow managing multiple stacks in the same
  thread.

  \omit ### outdated \endomit
  To create a fiber, subclass Fiber and override the run() method. To run it,
  call cont(). This will execute the code in run() until it calls Fiber::yield().
  At that point, the call to cont() returns. Subsequent calls to cont() will
  continue execution of the fiber just after the yield().

  Example:
  void myFiber()
  {
      qDebug() << "1";
      Fiber::yield();
      qDebug() << "2";
  }

  MyFiber fib(&myFiber);
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

Fiber::Fiber(StartFunction startFunction, int stackSize)
    : _startFunction(startFunction)
    , _stackData(0)
    , _stackPointer(0)
    , _previousFiber(0)
    , _status(NotStarted)
{
    // establish starting fiber context if necessary
    currentFiber();
    
    _stackData = malloc(stackSize);
    initializeStack(_stackData, stackSize, &entryPoint, &_stackPointer);
}

Fiber::Fiber()
    : _startFunction(0)
    , _stackData(0)
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

static QThreadStorage<Fiber *> qt_currentFiber;

Fiber *Fiber::currentFiber()
{
    Fiber *current = qt_currentFiber.localData();
    if (current)
        return current;

    // establish a context for the starting fiber
    current = new Fiber;
    qt_currentFiber.setLocalData(current);
    return current;
}

void Fiber::entryPoint()
{
    qt_currentFiber.localData()->_startFunction();
    yieldHelper(Terminated);
    Q_ASSERT(0); // unreachable
}

// returns whether it can be continued again
bool Fiber::cont()
{    
    Q_ASSERT(_status == NotStarted || _status == Stopped);
    Q_ASSERT(!_previousFiber);
    
    _status = Running;

    _previousFiber = qt_currentFiber.localData();
    qt_currentFiber.setLocalData(this);
    switchStack(_stackPointer, &_previousFiber->_stackPointer);
    return _status != Terminated;
}

void Fiber::yield()
{
    yieldHelper(Stopped);
}

void Fiber::yieldHelper(Status stopStatus)
{
    Fiber *stoppingFiber = qt_currentFiber.localData();
    Q_ASSERT(stoppingFiber);
    Q_ASSERT(stoppingFiber->_status == Running);
    stoppingFiber->_status = stopStatus;

    Fiber *continuingFiber = stoppingFiber->_previousFiber;
    Q_ASSERT(continuingFiber);

    stoppingFiber->_previousFiber = 0;
    qt_currentFiber.setLocalData(continuingFiber);
    switchStack(continuingFiber, &stoppingFiber->_stackPointer);
}
