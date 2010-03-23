#include <QtTest/QtTest>
#include <coroutine.h>

class benchmark : public QObject
{
    Q_OBJECT
private slots:
    void switchToCoroutineAndBack();
};

static void yielder()
{
    forever
        Coroutine::yield();
}

void benchmark::switchToCoroutineAndBack()
{
    Coroutine *c = Coroutine::build(&yielder);
    c->createStack();
    QBENCHMARK {
        c->cont();
    }
    delete c;
}

QTEST_MAIN(benchmark)

#include "benchmarks.moc"
