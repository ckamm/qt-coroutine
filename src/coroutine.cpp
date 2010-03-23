#include <stdlib.h>
#include <QtCore/QtGlobal>
#include <QtCore/QThreadStorage>

#include "coroutine.h"

/*!
  \class Coroutine
  \brief The Coroutine class provides cooperatively scheduled stacks of execution.

  Coroutines, also known as fibers, allow managing multiple stacks in the same
  thread.

  New coroutines are made from functions, functors, etc by invoking Coroutine::build
  on them. Alternatively, it's possible to derive from Coroutine and overriding
  the run() method.

  A coroutine doesn't start execution when it is built. Call cont() to run it.
  This will execute the coroutine's code until it calls Coroutine::yield().
  At that point, the call to cont() returns. Subsequent calls to cont() will
  continue execution of the coroutine just after the yield().

  Example:
  void myCoroutine()
  {
      qDebug() << "1";
      Coroutine::yield();
      qDebug() << "2";
  }

  Coroutine *c = Coroutine::build(32000, &myCoroutine);
  qDebug() << "0.5";
  c.cont(); // prints 1
  qDebug() << "1.5";
  c.cont(); // prints 2
*/

/*!
  \fn Coroutine *Coroutine::build(int stackSize, Function function, ...)
  \brief Creates a new Coroutine from a callable object.

  The callable object, Function, can be a function pointer, functor or
  pointer to functor, object and member function pointer, or pointer to object
  and member function pointer. In the case of passing functor pointers or
  object pointers, the Coroutine object doesn't take ownership.

  The stackSize value denotes the size of the stack the coroutine will allocate
  for execution.
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

Coroutine::Coroutine(int stackSize)
    : _stackData(0)
    , _stackPointer(0)
    , _previousCoroutine(0)
    , _status(NotStarted)
{
    // establish starting coroutine context if necessary
    currentCoroutine();
    
    _stackData = malloc(stackSize);
    initializeStack(_stackData, stackSize, &entryPoint, &_stackPointer);
}

Coroutine::Coroutine(bool)
    : _stackData(0)
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

static QThreadStorage<Coroutine **> qt_currentCoroutine;

Coroutine *Coroutine::currentCoroutine()
{
    // establish a context for the starting coroutine
    if (!qt_currentCoroutine.hasLocalData()) {
        Coroutine *current = new Coroutine(true);
        qt_currentCoroutine.setLocalData(new Coroutine*(current));
        return current;
    }

    return *qt_currentCoroutine.localData();
}

void Coroutine::entryPoint()
{
    (*qt_currentCoroutine.localData())->run();
    yieldHelper(Terminated);
    Q_ASSERT(0); // unreachable
}

// returns whether it can be continued again
bool Coroutine::cont()
{    
    Q_ASSERT(_status == NotStarted || _status == Stopped);
    Q_ASSERT(!_previousCoroutine);
    
    _status = Running;

    _previousCoroutine = *qt_currentCoroutine.localData();
    *qt_currentCoroutine.localData() = this;
    switchStack(_stackPointer, &_previousCoroutine->_stackPointer);
    return _status != Terminated;
}

void Coroutine::yield()
{
    yieldHelper(Stopped);
}

void Coroutine::yieldHelper(Status stopStatus)
{
    Coroutine *stoppingCoroutine = *qt_currentCoroutine.localData();
    Q_ASSERT(stoppingCoroutine);
    Q_ASSERT(stoppingCoroutine->_status == Running);
    stoppingCoroutine->_status = stopStatus;

    Coroutine *continuingCoroutine = stoppingCoroutine->_previousCoroutine;
    Q_ASSERT(continuingCoroutine);

    stoppingCoroutine->_previousCoroutine = 0;
    *qt_currentCoroutine.localData() = continuingCoroutine;
    switchStack(continuingCoroutine->_stackPointer, &stoppingCoroutine->_stackPointer);
}
