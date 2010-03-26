/**************************************************************************
**
** This file is part of the Coroutine library
**
** Copyright (c) 2010 Nokia Corporation and/or its subsidiary(-ies).
**
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** Commercial Usage
**
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Nokia.
**
** GNU Lesser General Public License Usage
**
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** If you are unsure which license is appropriate for your use, please
** contact the sales department at http://qt.nokia.com/contact.
**
**************************************************************************/

#include <QtTest/QtTest>
#include <coroutine.h>

class tst_basic : public QObject
{
Q_OBJECT

private slots:
    void noYield();
    void coroutineStartingCoroutine();
    void smallStack();
    void reuseStack();
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

    delete c1;
    delete base;
}

namespace StackTests {
    static int counter = 0;
    static void simpleCoroutine()
    {
        while(true) {
            counter++;
            Coroutine::yield();
        }
    }
}

void tst_basic::smallStack()
{
    using namespace StackTests;

    Coroutine *c = Coroutine::build(&simpleCoroutine);
    c->createStack(1000);
    counter = 0;
    QCOMPARE(c->cont(), true);
    QCOMPARE(counter, 1);
    QCOMPARE(c->cont(), true);
    QCOMPARE(counter, 2);
    delete c;
}

void tst_basic::reuseStack()
{
    using namespace StackTests;

    char* p = new char[10000];

    Coroutine *c1 = Coroutine::build(&simpleCoroutine);
    c1->setStack(p, 10000);
    counter = 0;
    QCOMPARE(c1->cont(), true);
    QCOMPARE(counter, 1);
    QCOMPARE(c1->cont(), true);
    QCOMPARE(counter, 2);
    delete c1;

    Coroutine *c2 = Coroutine::build(&simpleCoroutine);
    c2->setStack(p, 10000);
    counter = 0;
    QCOMPARE(c2->cont(), true);
    QCOMPARE(counter, 1);
    QCOMPARE(c2->cont(), true);
    QCOMPARE(counter, 2);
    delete c2;

    delete [] p;
}

QTEST_MAIN(tst_basic)
#include "tst_basic.moc"
