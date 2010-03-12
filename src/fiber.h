#ifndef INCLUDE_FIBER_H
#define INCLUDE_FIBER_H

class Fiber
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
    explicit Fiber(StartFunction startFunction, int stackSize = 32768);
    ~Fiber();
    
    bool cont();
    static void yield();
    
    Status status()
    { return _status; }

    static Fiber *currentFiber();

private:
    // for the original fiber
    Fiber();

    static void yieldHelper(Status stopStatus);
    static void entryPoint();

    StartFunction _startFunction;
    void *_stackData;
    void *_stackPointer;
    Fiber *_previousFiber;
    Status _status;
};

#endif // INCLUDE_FIBER_H
