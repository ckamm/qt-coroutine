#include <stdlib.h>
#include <QtCore/QtGlobal>
#include <QtCore/QThreadStorage>

#include "coroutine.h"

/*!
  \class Coroutine
  \brief The Coroutine class provides cooperatively scheduled stacks of execution.

  Coroutines, also known as fibers, allow managing multiple stacks in the same
  thread.

  New coroutines are made from functions, functors, etc by invoking Coroutine::build()
  on them. Alternatively, it is possible to derive from Coroutine and overriding
  the run() method.

  A coroutine doesn't start execution when it is built. Call cont() to run it.
  This will execute the coroutine's code until it calls Coroutine::yield().
  At that point, the call to cont() returns. Subsequent calls to cont() will
  continue execution of the coroutine just after the yield().

  \code
  void myCoroutine()
  {
      qDebug() << "1";
      Coroutine::yield();
      qDebug() << "2";
  }

  Coroutine *c = Coroutine::build(&myCoroutine);
  qDebug() << "0.5";
  c.cont(); // prints 1
  qDebug() << "1.5";
  c.cont(); // prints 2
  \endcode

  By default, a Coroutine will create its own stack space using createStack()
  with the default argument. To manage the stack memory manually or to use
  a stack of a different size, use createStack() or setStack() before starting
  execution.
*/

/*!
  \fn static Coroutine *Coroutine::build(Function function, ...)

  Creates a new Coroutine from a callable object.

  The callable object, \a function, can be a function pointer, functor or
  pointer to functor, object and member function pointer, or pointer to object
  and member function pointer. In the case of passing functor pointers or
  object pointers, the Coroutine object doesn't take ownership.
*/

/*!
  \enum Coroutine::Status

  Specifies the current state of a coroutine.

  \value NotStarted  Before the first call to cont()
  \value Running     The coroutine is currently running. Note that if a coroutine
                     starts another coroutine, both will be in the Running state. Use
                     currentCoroutine() to get the active one.
  \value Stopped     The coroutine has called yield() at least once but can still be
                     continued with cont().
  \value Terminated  The coroutine has finished executing.

  \sa Coroutine::status()
*/

/*!
  \fn Coroutine::Status Coroutine::status() const

  Returns the status of the coroutine.
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

/*!
  Creates a stack of the given \a size for the coroutine.
  The memory is owned by the Coroutine object and will be deleted on destruction.

  Calling this function is only valid when in the NotStarted state.

  \sa setStack()
*/
void Coroutine::createStack(int size)
{
    Q_ASSERT(_status == NotStarted);

    if (_stackData)
        free(_stackData);

    _stackData = malloc(size);
    initializeStack(_stackData, size, &entryPoint, &_stackPointer);
}

/*!
  Initializes the area given by \a memory and \a size to serve as the stack
  for the coroutine. The Coroutine object does not take ownership.

  Calling this function is only valid when in the NotStarted state.

  \sa createStack()
*/
void Coroutine::setStack(void *memory, int size)
{
    Q_ASSERT(_status == NotStarted);

    if (_stackData) {
        free(_stackData);
        _stackData = 0;
    }

    initializeStack(memory, size, &entryPoint, &_stackPointer);
}

static QThreadStorage<Coroutine **> qt_currentCoroutine;

/*!
  Returns the currently running Coroutine.
*/
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

/*!
  Passes control to the coroutine.
  The coroutine will run until it terminates or is stopped by a call to yield().

  Returns whether it can be continued again.

  Calling this function is only valid if in the NotStarted or Stopped state.

  \sa yield()
*/
bool Coroutine::cont()
{    
    Q_ASSERT(_status == NotStarted || _status == Stopped);
    Q_ASSERT(!_previousCoroutine);

    if (!_stackPointer)
        createStack();

    _status = Running;

    _previousCoroutine = *qt_currentCoroutine.localData();
    *qt_currentCoroutine.localData() = this;
    switchStack(_stackPointer, &_previousCoroutine->_stackPointer);
    return _status != Terminated;
}

/*!
  Stops the currently running coroutine and passes control back to the caller of cont().

  \sa cont()
*/
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
