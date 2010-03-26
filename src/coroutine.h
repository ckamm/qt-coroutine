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

#ifndef INCLUDE_COROUTINE_H
#define INCLUDE_COROUTINE_H

#include "coroutine_global.h"

class COROUTINE_EXPORT Coroutine
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
    Coroutine();
    virtual ~Coroutine();

    void createStack(int size = 32768);
    void setStack(void *memory, int size);
    
    bool cont();
    static void yield();
    
    Status status() const
    { return _status; }

    static Coroutine *currentCoroutine();

#ifdef qdoc
    static Coroutine *build(Function function, ...);
#endif
// add declarations for static build(...) function
#include "coroutinebuilddeclaration_p.h"

protected:
    virtual void run() {}

private: // not copyable
    Coroutine(const Coroutine &);
    Coroutine &operator=(const Coroutine &);

private:
    static void yieldHelper(Status stopStatus);
    static void entryPoint();

    void *_stackData;
    void *_stackPointer;
    Coroutine *_caller;
    Status _status;
};

// add definitions for static build(...) function
#include "coroutinebuilddefinition_p.h"

#endif // INCLUDE_COROUTINE_H
