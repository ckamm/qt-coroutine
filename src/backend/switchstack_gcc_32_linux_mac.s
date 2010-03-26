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
    push %ebp
    movl %esp, %ebp
    push %ebx
    push %esi
    push %edi

    // store SIMD floating point control word
    sub $4, %esp
    stmxcsr (%esp)

    // store floating point control bytes
    sub $4, %esp
    fstcw (%esp)

    // save the old stack pointer
    movl 0xc(%ebp), %edx
    movl %esp, (%edx)
    // set the new stack pointer
    movl 0x8(%ebp), %esp

    // restore floating point control bytes
    fnclex
    fldcw (%esp)
    add $4, %esp

    // restore SIMD floating point control word
    ldmxcsr (%esp)
    add $4, %esp

    // pop callee-saved registers
    pop %edi
    pop %esi
    pop %ebx
    pop %ebp

    ret
