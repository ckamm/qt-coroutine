#ifndef INCLUDE_FIBER_H
#define INCLUDE_FIBER_H

class Fiber
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
    explicit Fiber(int stackSize = 32768);
    virtual ~Fiber();
    
    bool cont();
    static void yield();
    
    static Fiber *currentFiber();
    
    Status status()
    { return _status; }
    
protected:
    // could be abstract if subclassing for start fiber
    virtual void run() {}
    
private:
    // for the original fiber
    Fiber(bool);

    static void yieldHelper(Status stopStatus);
    
    void *_stackData;
    void *_stackPointer;
    Fiber *_previousFiber;
    Status _status;
    
    // should be thread local
    static Fiber *_currentFiber;
    
    static void entryPoint();
};

#endif // INCLUDE_FIBER_H
