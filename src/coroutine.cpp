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
  on them. Alternatively, it is possible to derive from Coroutine and overriding
  the run() method.

  After creation it is necessary to set up the coroutine's stack. Call either
  createStack() or setStack() to do so. createStack() will make the coroutine allocate
  some stack space that it will release on destruction. Using setStack() allows
  passing in memory that the coroutine will not take ownership of. The latter
  is useful if you have a lot of coroutines and want to reuse their stack memory.

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

  Coroutine *c = Coroutine::build(&myCoroutine);
  c->createStack();
  qDebug() << "0.5";
  c.cont(); // prints 1
  qDebug() << "1.5";
  c.cont(); // prints 2
*/

/*!
  \fn Coroutine *Coroutine::build(Function function, ...)
  \brief Creates a new Coroutine from a callable object.

  The callable object, Function, can be a function pointer, functor or
  pointer to functor, object and member function pointer, or pointer to object
  and member function pointer. In the case of passing functor pointers or
  object pointers, the Coroutine object doesn't take ownership.

  The coroutine will be ready for use after it's stack has been set up.
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

Coroutine::Coroutine()
    : _stackData(0)
    , _stackPointer(0)
    , _previousCoroutine(0)
    , _status(NotStarted)
{
    // establish starting coroutine context if necessary
    currentCoroutine();
}

Coroutine::~Coroutine()
{
    if (_stackData)
        free(_stackData);
}

void Coroutine::createStack(int size)
{
    if (_stackData)
        free(_stackData);

    _stackData = malloc(size);
    initializeStack(_stackData, size, &entryPoint, &_stackPointer);
}

void Coroutine::setStack(void *memory, int size)
{
    initializeStack(memory, size, &entryPoint, &_stackPointer);
}

static QThreadStorage<Coroutine **> qt_currentCoroutine;

Coroutine *Coroutine::currentCoroutine()
{
    // establish a context for the starting coroutine
    if (!qt_currentCoroutine.hasLocalData()) {
        Coroutine **currentPtr = new Coroutine*;
        qt_currentCoroutine.setLocalData(currentPtr);
        *currentPtr = new Coroutine;
        (*currentPtr)->_status = Running;
        return *currentPtr;
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
    Q_ASSERT(_stackPointer);

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
