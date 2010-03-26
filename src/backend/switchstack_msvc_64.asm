comment */*
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
*/*

.model flat, c
.code

_switchStackInternal PROC to:QWORD, from:QWORD
    ; save callee-saved registers
    PUSH RBP
    MOV RBP, RSP
    PUSH RBX
    PUSH ESI
    PUSH EDI

    PUSH R12
    PUSH R13
    PUSH R14
    PUSH R15

    PUSH RSI
    PUSH RDI

    SUB RSP, 0x10
    MOVUPD [RSP], XMM6
    SUB RSP, 0x10
    MOVUPD [RSP], XMM7
    SUB RSP, 0x10
    MOVUPD [RSP], XMM8
    SUB RSP, 0x10
    MOVUPD [RSP], XMM9
    SUB RSP, 0x10
    MOVUPD [RSP], XMM10
    SUB RSP, 0x10
    MOVUPD [RSP], XMM11
    SUB RSP, 0x10
    MOVUPD [RSP], XMM12
    SUB RSP, 0x10
    MOVUPD [RSP], XMM13
    SUB RSP, 0x10
    MOVUPD [RSP], XMM14
    SUB RSP, 0x10
    MOVUPD [RSP], XMM15

    ; store SIMD floating point control word
    SUB RSP, 4
    STMXCSR [RSP]

    ; store floating point control bytes
    SUB RSP, 4
    FSTCW [RSP]

    ; save the old stack pointer
    MOV [from], RSP
    ; set the new stack pointer
    MOV RSP, to

    ; restore floating point control bytes
    FNCLEX
    FLDCW [RSP]
    ADD RSP, 4

    ; restore SIMD floating point control word
    LDMXCSR [RSP]
    ADD RSP, 4

    ; pop callee-saved registers
    MOVUPD XMM15, [RSP]
    ADD RSP, 0x10
    MOVUPD XMM14, [RSP]
    ADD RSP, 0x10
    MOVUPD XMM13, [RSP]
    ADD RSP, 0x10
    MOVUPD XMM12, [RSP]
    ADD RSP, 0x10
    MOVUPD XMM11, [RSP]
    ADD RSP, 0x10
    MOVUPD XMM10, [RSP]
    ADD RSP, 0x10
    MOVUPD XMM9, [RSP]
    ADD RSP, 0x10
    MOVUPD XMM8, [RSP]
    ADD RSP, 0x10
    MOVUPD XMM7, [RSP]
    ADD RSP, 0x10
    MOVUPD XMM6, [RSP]
    ADD RSP, 0x10

    POP RDI
    POP RSI

    POP R15
    POP R14
    POP R13
    POP R12
    POP RBX
    POP RBP

    RET
_switchStackInternal ENDP

end
