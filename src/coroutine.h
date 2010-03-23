#ifndef INCLUDE_COROUTINE_H
#define INCLUDE_COROUTINE_H

class Coroutine
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
    explicit Coroutine(int stackSize = 32768);
    virtual ~Coroutine();
    
    bool cont();
    static void yield();
    
    Status status()
    { return _status; }

    static Coroutine *currentCoroutine();

// add declarations for static build(...) function
#include "coroutinebuilddeclaration_p.h"

protected:
    virtual void run() {}

private:
    // for the original coroutine
    Coroutine(bool);

    static void yieldHelper(Status stopStatus);
    static void entryPoint();

    void *_stackData;
    void *_stackPointer;
    Coroutine *_previousCoroutine;
    Status _status;
};

// add definitions for static build(...) function
#include "coroutinebuilddefinition_p.h"

#endif // INCLUDE_COROUTINE_H
