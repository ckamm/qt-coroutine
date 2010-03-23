#include <QtTest/QtTest>
#include <coroutine.h>

class tst_basic : public QObject
{
Q_OBJECT

private slots:
    void noYield();
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
    coro.createStack();
    coro.i = 0;
    QCOMPARE(coro.status(), Coroutine::NotStarted);
    QCOMPARE(coro.cont(), false);
    QCOMPARE(coro.i, 1);
    QCOMPARE(coro.status(), Coroutine::Terminated);
    Q_ASSERT(Coroutine::currentCoroutine() != &coro);
}

QTEST_MAIN(tst_basic)
#include "tst_basic.moc"
