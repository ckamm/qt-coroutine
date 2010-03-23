#include <QtTest/QtTest>
#include <coroutine.h>

class tst_basic : public QObject
{
Q_OBJECT

private slots:
    void noYield();
    void coroutineStartingCoroutine();
};

class NoYieldCoro : public Coroutine
{
public:
    virtual void run()
    {
        i++;
        QCOMPARE(status(), Running);
        QCOMPARE(currentCoroutine(), this);
    }

    int i;
};

void tst_basic::noYield()
{
    NoYieldCoro coro;
    coro.i = 0;
    QCOMPARE(coro.status(), Coroutine::NotStarted);
    QCOMPARE(coro.cont(), false);
    QCOMPARE(coro.i, 1);
    QCOMPARE(coro.status(), Coroutine::Terminated);
    Q_ASSERT(Coroutine::currentCoroutine() != &coro);
}

namespace CoroutineStartingCoroutine {
    static Coroutine *base = 0;
    static Coroutine *c1 = 0;

    static void c1code()
    {
        QCOMPARE(base->status(), Coroutine::Running);
        QCOMPARE(c1->status(), Coroutine::Running);
        QCOMPARE(Coroutine::currentCoroutine(), c1);

        Coroutine::yield();

        QCOMPARE(base->status(), Coroutine::Stopped);
        QCOMPARE(c1->status(), Coroutine::Running);
        QCOMPARE(Coroutine::currentCoroutine(), c1);
    }

    static void startCoroutines()
    {
        QCOMPARE(base->status(), Coroutine::Running);
        QCOMPARE(Coroutine::currentCoroutine(), base);

        c1 = Coroutine::build(&c1code);
        Q_ASSERT(c1);
        QCOMPARE(c1->status(), Coroutine::NotStarted);

        Coroutine::yield();

        QCOMPARE(base->status(), Coroutine::Running);
        QCOMPARE(c1->status(), Coroutine::NotStarted);
        QCOMPARE(Coroutine::currentCoroutine(), base);

        QCOMPARE(c1->cont(), true);

        QCOMPARE(base->status(), Coroutine::Running);
        QCOMPARE(c1->status(), Coroutine::Stopped);
        QCOMPARE(Coroutine::currentCoroutine(), base);

        Coroutine::yield();

        QCOMPARE(base->status(), Coroutine::Running);
        QCOMPARE(c1->status(), Coroutine::Terminated);
        QCOMPARE(Coroutine::currentCoroutine(), base);
    }
}

void tst_basic::coroutineStartingCoroutine()
{
    using namespace CoroutineStartingCoroutine;

    Coroutine *start = Coroutine::currentCoroutine();

    base = Coroutine::build(&startCoroutines);
    Q_ASSERT(base);

    QCOMPARE(base->cont(), true);

    Q_ASSERT(c1);
    QCOMPARE(base->status(), Coroutine::Stopped);
    QCOMPARE(c1->status(), Coroutine::NotStarted);
    QCOMPARE(Coroutine::currentCoroutine(), start);

    QCOMPARE(base->cont(), true);

    QCOMPARE(base->status(), Coroutine::Stopped);
    QCOMPARE(c1->status(), Coroutine::Stopped);
    QCOMPARE(Coroutine::currentCoroutine(), start);

    QCOMPARE(c1->cont(), false);

    QCOMPARE(base->status(), Coroutine::Stopped);
    QCOMPARE(c1->status(), Coroutine::Terminated);
    QCOMPARE(Coroutine::currentCoroutine(), start);

    QCOMPARE(base->cont(), false);

    QCOMPARE(base->status(), Coroutine::Terminated);
    QCOMPARE(c1->status(), Coroutine::Terminated);
    QCOMPARE(Coroutine::currentCoroutine(), start);
}

QTEST_MAIN(tst_basic)
#include "tst_basic.moc"
