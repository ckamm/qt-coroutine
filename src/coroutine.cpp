#include <stdlib.h>
#include <QtCore/QtGlobal>
#include <QtCore/QThreadStorage>

#include "coroutine.h"

/*!
  \class Coroutine
  \brief The Coroutine class provides cooperatively scheduled stacks of execution.

  Coroutines, also known as fibers, allow managing multiple stacks in the same
  thread.

  \omit ### outdated \endomit
  To create a coroutine, subclass Coroutine and override the run() method. To run it,
  call cont(). This will execute the code in run() until it calls Coroutine::yield().
  At that point, the call to cont() returns. Subsequent calls to cont() will
  continue execution of the coroutine just after the yield().

  Example:
  void myCoroutine()
  {
      qDebug() << "1";
      Coroutine::yield();
      qDebug() << "2";
  }

  MyCoroutine c(&myCoroutine);
  qDebug() << "0.5";
  c.cont(); // prints 1
  qDebug() << "1.5";
  c.cont(); // prints 2
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

Coroutine::Coroutine(StartFunction startFunction, int stackSize)
    : _startFunction(startFunction)
    , _stackData(0)
    , _stackPointer(0)
    , _previousCoroutine(0)
    , _status(NotStarted)
{
    // establish starting coroutine context if necessary
    currentCoroutine();
    
    _stackData = malloc(stackSize);
    initializeStack(_stackData, stackSize, &entryPoint, &_stackPointer);
}

Coroutine::Coroutine()
    : _startFunction(0)
    , _stackData(0)
    , _stackPointer(0)
    , _previousCoroutine(0)
    , _status(Running)
{
}

Coroutine::~Coroutine()
{
    if (_stackData)
        free(_stackData);
}

static QThreadStorage<Coroutine *> qt_currentCoroutine;

Coroutine *Coroutine::currentCoroutine()
{
    Coroutine *current = qt_currentCoroutine.localData();
    if (current)
        return current;

    // establish a context for the starting coroutine
    current = new Coroutine;
    qt_currentCoroutine.setLocalData(current);
    return current;
}

void Coroutine::entryPoint()
{
    qt_currentCoroutine.localData()->_startFunction();
    yieldHelper(Terminated);
    Q_ASSERT(0); // unreachable
}

// returns whether it can be continued again
bool Coroutine::cont()
{    
    Q_ASSERT(_status == NotStarted || _status == Stopped);
    Q_ASSERT(!_previousCoroutine);
    
    _status = Running;

    _previousCoroutine = qt_currentCoroutine.localData();
    qt_currentCoroutine.setLocalData(this);
    switchStack(_stackPointer, &_previousCoroutine->_stackPointer);
    return _status != Terminated;
}

void Coroutine::yield()
{
    yieldHelper(Stopped);
}

void Coroutine::yieldHelper(Status stopStatus)
{
    Coroutine *stoppingCoroutine = qt_currentCoroutine.localData();
    Q_ASSERT(stoppingCoroutine);
    Q_ASSERT(stoppingCoroutine->_status == Running);
    stoppingCoroutine->_status = stopStatus;

    Coroutine *continuingCoroutine = stoppingCoroutine->_previousCoroutine;
    Q_ASSERT(continuingCoroutine);

    stoppingCoroutine->_previousCoroutine = 0;
    qt_currentCoroutine.setLocalData(continuingCoroutine);
    switchStack(continuingCoroutine, &stoppingCoroutine->_stackPointer);
}
