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

#include <stdlib.h>

void initializeStack(void *data, int size, void (*entry)(), void **stackPointer)
{
    void* stackBottom = (char*)data + size;
    // align to 16 byte
    stackBottom = (void*)((size_t)stackBottom & ~0xF);
    
    void **p = (void**)stackBottom;

    //*(--p) = 0; // align to 16 bytes
    *(--p) = (void*)fn; // rip
    *(--p) = entry; // rbp
    *(--p) = 0; // rbx
    *(--p) = 0; // r12
    *(--p) = 0; // r13
    *(--p) = 0; // r14
    *(--p) = 0; // r15
    *(--p) = 0; // rsi
    *(--p) = 0; // rdi
    *(--p) = 0; // xmm6
    *(--p) = 0; // xmm6
    *(--p) = 0; // xmm7
    *(--p) = 0; // xmm7
    *(--p) = 0; // xmm8
    *(--p) = 0; // xmm8
    *(--p) = 0; // xmm9
    *(--p) = 0; // xmm9
    *(--p) = 0; // xmm10
    *(--p) = 0; // xmm10
    *(--p) = 0; // xmm11
    *(--p) = 0; // xmm11
    *(--p) = 0; // xmm12
    *(--p) = 0; // xmm12
    *(--p) = 0; // xmm13
    *(--p) = 0; // xmm13
    *(--p) = 0; // xmm14
    *(--p) = 0; // xmm14
    *(--p) = 0; // xmm15
    *(--p) = 0; // xmm15
    *(--p) = (void*)0x00001f800000033f; // SIMD and regular floating point control defaults
    
    *stackPointer = p;
}
