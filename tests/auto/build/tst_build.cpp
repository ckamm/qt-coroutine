#include <QtTest/QtTest>
#include <coroutine.h>
#include <coroutinebuild.h>

class tst_build: public QObject
{
Q_OBJECT

private slots:
    void staticFn();
};

static int fnCounter = -99;
static void fnNoArg()
{
    fnCounter = 0;
    Coroutine::yield();
    fnCounter++;
    Coroutine::yield();
    fnCounter++;

}

static void fnArg(int start)
{
    fnCounter = start;
    Coroutine::yield();
    fnCounter++;
    Coroutine::yield();
    fnCounter++;
}


void tst_build::staticFn()
{
    Coroutine* c1 = build(32000, &fnNoArg);
    QCOMPARE(fnCounter, -99);
    QCOMPARE(c1->cont(), true);
    QCOMPARE(fnCounter, 0);
    QCOMPARE(c1->cont(), true);
    QCOMPARE(fnCounter, 1);
    QCOMPARE(c1->cont(), false);
    QCOMPARE(fnCounter, 2);
    delete c1;

    Coroutine* c2 = build(32000, &fnArg, 40);
    QCOMPARE(c2->cont(), true);
    QCOMPARE(fnCounter, 40);
    QCOMPARE(c2->cont(), true);
    QCOMPARE(fnCounter, 41);
    QCOMPARE(c2->cont(), false);
    QCOMPARE(fnCounter, 42);
    delete c2;
}


QTEST_MAIN(tst_build)
#include "tst_build.moc"
