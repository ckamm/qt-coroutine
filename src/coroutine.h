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

#endif // INCLUDE_COROUTINE_H
