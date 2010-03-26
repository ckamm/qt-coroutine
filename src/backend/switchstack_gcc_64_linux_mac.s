##########################################################################
##
## This file is part of the Coroutine library
##
## Copyright (c) 2010 Nokia Corporation and/or its subsidiary(-ies).
##
## Contact: Nokia Corporation (qt-info@nokia.com)
##
## Commercial Usage
##
## Licensees holding valid Qt Commercial licenses may use this file in
## accordance with the Qt Commercial License Agreement provided with the
## Software or, alternatively, in accordance with the terms contained in
## a written agreement between you and Nokia.
##
## GNU Lesser General Public License Usage
##
## Alternatively, this file may be used under the terms of the GNU Lesser
## General Public License version 2.1 as published by the Free Software
## Foundation and appearing in the file LICENSE.LGPL included in the
## packaging of this file.  Please review the following information to
## ensure the GNU Lesser General Public License version 2.1 requirements
## will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
##
## If you are unsure which license is appropriate for your use, please
## contact the sales department at http://qt.nokia.com/contact.
##
##########################################################################

.text
.globl _switchStackInternal

_switchStackInternal:
    // save callee-saved registers
    push %rbp
    movq %rsp, %rbp
    push %rbx
    push %r12
    push %r13
    push %r14
    push %r15

    // store SIMD floating point control word
    sub $4, %rsp
    stmxcsr (%rsp)

    // store floating point control bytes
    sub $4, %rsp
    fstcw (%rsp)

    // save the old stack pointer (second arg in rsi)
    movq %rsp, (%rsi)
    // set the new stack pointer (first arg in rdi)
    movq %rdi, %rsp

    // restore floating point control bytes
    fnclex
    fldcw (%rsp)
    add $4, %rsp

    // restore SIMD floating point control word
    ldmxcsr (%rsp)
    add $4, %rsp

    // pop callee-saved registers
    pop %r15
    pop %r14
    pop %r13
    pop %r12
    pop %rbx
    pop %rbp

    retq
