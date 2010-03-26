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
    Coroutine* c1 = Coroutine::build(&fnNoArg);
    QCOMPARE(fnCounter, -99);
    QCOMPARE(c1->cont(), true);
    QCOMPARE(fnCounter, 0);
    QCOMPARE(c1->cont(), true);
    QCOMPARE(fnCounter, 1);
    QCOMPARE(c1->cont(), false);
    QCOMPARE(fnCounter, 2);
    delete c1;

    Coroutine* c2 = Coroutine::build(&fnArg, 40);
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
