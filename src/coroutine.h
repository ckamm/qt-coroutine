#ifndef INCLUDE_COROUTINE_H
#define INCLUDE_COROUTINE_H

#include "coroutine_global.h"

class COROUTINE_EXPORT Coroutine
{
public:
    enum Status
    {
        NotStarted,
        Running,
        Stopped,
        Terminated
    };

public:
    Coroutine();
    virtual ~Coroutine();

    void createStack(int size = 32768);
    void setStack(void *memory, int size);
    
    bool cont();
    static void yield();
    
    Status status() const
    { return _status; }

    static Coroutine *currentCoroutine();

#ifdef qdoc
    static Coroutine *build(Function function, ...);
#endif
// add declarations for static build(...) function
#include "coroutinebuilddeclaration_p.h"

protected:
    virtual void run() {}

private: // not copyable
    Coroutine(const Coroutine &);
    Coroutine &operator=(const Coroutine &);

private:
    static void yieldHelper(Status stopStatus);
    static void entryPoint();

    void *_stackData;
    void *_stackPointer;
    Coroutine *_caller;
    Status _status;
};

// add definitions for static build(...) function
#include "coroutinebuilddefinition_p.h"

#endif // INCLUDE_COROUTINE_H
