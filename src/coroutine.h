#ifndef INCLUDE_COROUTINE_H
#define INCLUDE_COROUTINE_H

class Coroutine
{
public:
    typedef void(*StartFunction)();

    enum Status
    {
        NotStarted,
        Running,
        Stopped,
        Terminated
    };

public:
    explicit Coroutine(StartFunction startFunction, int stackSize = 32768);
    ~Coroutine();
    
    bool cont();
    static void yield();
    
    Status status()
    { return _status; }

    static Coroutine *currentCoroutine();

private:
    // for the original coroutine
    Coroutine();

    static void yieldHelper(Status stopStatus);
    static void entryPoint();

    StartFunction _startFunction;
    void *_stackData;
    void *_stackPointer;
    Coroutine *_previousCoroutine;
    Status _status;
};

#endif // INCLUDE_COROUTINE_H
