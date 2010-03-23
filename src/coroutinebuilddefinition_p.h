/****************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the Qt Toolkit.
**
****************************************************************************/

// Generated code, do not edit! Use generator at tools/generatebuild/

#include "coroutinestoredfunctioncall_p.h"

#ifndef qdoc


Coroutine* Coroutine::build(void (*functionPointer)())
{
    return new StoredFunctorCall0<void (*)()>(functionPointer);
}
template <typename Param1, typename Arg1>
Coroutine* Coroutine::build(void (*functionPointer)(Param1), const Arg1 &arg1)
{
    return new StoredFunctorCall1<void (*)(Param1), Arg1>(functionPointer, arg1);
}
template <typename Param1, typename Arg1, typename Param2, typename Arg2>
Coroutine* Coroutine::build(void (*functionPointer)(Param1, Param2), const Arg1 &arg1, const Arg2 &arg2)
{
    return new StoredFunctorCall2<void (*)(Param1, Param2), Arg1, Arg2>(functionPointer, arg1, arg2);
}
template <typename Param1, typename Arg1, typename Param2, typename Arg2, typename Param3, typename Arg3>
Coroutine* Coroutine::build(void (*functionPointer)(Param1, Param2, Param3), const Arg1 &arg1, const Arg2 &arg2, const Arg3 &arg3)
{
    return new StoredFunctorCall3<void (*)(Param1, Param2, Param3), Arg1, Arg2, Arg3>(functionPointer, arg1, arg2, arg3);
}
template <typename Param1, typename Arg1, typename Param2, typename Arg2, typename Param3, typename Arg3, typename Param4, typename Arg4>
Coroutine* Coroutine::build(void (*functionPointer)(Param1, Param2, Param3, Param4), const Arg1 &arg1, const Arg2 &arg2, const Arg3 &arg3, const Arg4 &arg4)
{
    return new StoredFunctorCall4<void (*)(Param1, Param2, Param3, Param4), Arg1, Arg2, Arg3, Arg4>(functionPointer, arg1, arg2, arg3, arg4);
}
template <typename Param1, typename Arg1, typename Param2, typename Arg2, typename Param3, typename Arg3, typename Param4, typename Arg4, typename Param5, typename Arg5>
Coroutine* Coroutine::build(void (*functionPointer)(Param1, Param2, Param3, Param4, Param5), const Arg1 &arg1, const Arg2 &arg2, const Arg3 &arg3, const Arg4 &arg4, const Arg5 &arg5)
{
    return new StoredFunctorCall5<void (*)(Param1, Param2, Param3, Param4, Param5), Arg1, Arg2, Arg3, Arg4, Arg5>(functionPointer, arg1, arg2, arg3, arg4, arg5);
}

template <typename FunctionObject>
Coroutine* Coroutine::build(FunctionObject functionObject)
{
    return new StoredFunctorCall0<FunctionObject>(functionObject);
}
template <typename FunctionObject, typename Arg1>
Coroutine* Coroutine::build(FunctionObject functionObject, const Arg1 &arg1)
{
    return new StoredFunctorCall1<FunctionObject, Arg1>(functionObject, arg1);
}
template <typename FunctionObject, typename Arg1, typename Arg2>
Coroutine* Coroutine::build(FunctionObject functionObject, const Arg1 &arg1, const Arg2 &arg2)
{
    return new StoredFunctorCall2<FunctionObject, Arg1, Arg2>(functionObject, arg1, arg2);
}
template <typename FunctionObject, typename Arg1, typename Arg2, typename Arg3>
Coroutine* Coroutine::build(FunctionObject functionObject, const Arg1 &arg1, const Arg2 &arg2, const Arg3 &arg3)
{
    return new StoredFunctorCall3<FunctionObject, Arg1, Arg2, Arg3>(functionObject, arg1, arg2, arg3);
}
template <typename FunctionObject, typename Arg1, typename Arg2, typename Arg3, typename Arg4>
Coroutine* Coroutine::build(FunctionObject functionObject, const Arg1 &arg1, const Arg2 &arg2, const Arg3 &arg3, const Arg4 &arg4)
{
    return new StoredFunctorCall4<FunctionObject, Arg1, Arg2, Arg3, Arg4>(functionObject, arg1, arg2, arg3, arg4);
}
template <typename FunctionObject, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5>
Coroutine* Coroutine::build(FunctionObject functionObject, const Arg1 &arg1, const Arg2 &arg2, const Arg3 &arg3, const Arg4 &arg4, const Arg5 &arg5)
{
    return new StoredFunctorCall5<FunctionObject, Arg1, Arg2, Arg3, Arg4, Arg5>(functionObject, arg1, arg2, arg3, arg4, arg5);
}

template <typename FunctionObject>
Coroutine* Coroutine::build(FunctionObject *functionObject)
{
    return new StoredFunctorPointerCall0<FunctionObject>(functionObject);
}
template <typename FunctionObject, typename Arg1>
Coroutine* Coroutine::build(FunctionObject *functionObject, const Arg1 &arg1)
{
    return new StoredFunctorPointerCall1<FunctionObject, Arg1>(functionObject, arg1);
}
template <typename FunctionObject, typename Arg1, typename Arg2>
Coroutine* Coroutine::build(FunctionObject *functionObject, const Arg1 &arg1, const Arg2 &arg2)
{
    return new StoredFunctorPointerCall2<FunctionObject, Arg1, Arg2>(functionObject, arg1, arg2);
}
template <typename FunctionObject, typename Arg1, typename Arg2, typename Arg3>
Coroutine* Coroutine::build(FunctionObject *functionObject, const Arg1 &arg1, const Arg2 &arg2, const Arg3 &arg3)
{
    return new StoredFunctorPointerCall3<FunctionObject, Arg1, Arg2, Arg3>(functionObject, arg1, arg2, arg3);
}
template <typename FunctionObject, typename Arg1, typename Arg2, typename Arg3, typename Arg4>
Coroutine* Coroutine::build(FunctionObject *functionObject, const Arg1 &arg1, const Arg2 &arg2, const Arg3 &arg3, const Arg4 &arg4)
{
    return new StoredFunctorPointerCall4<FunctionObject, Arg1, Arg2, Arg3, Arg4>(functionObject, arg1, arg2, arg3, arg4);
}
template <typename FunctionObject, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5>
Coroutine* Coroutine::build(FunctionObject *functionObject, const Arg1 &arg1, const Arg2 &arg2, const Arg3 &arg3, const Arg4 &arg4, const Arg5 &arg5)
{
    return new StoredFunctorPointerCall5<FunctionObject, Arg1, Arg2, Arg3, Arg4, Arg5>(functionObject, arg1, arg2, arg3, arg4, arg5);
}

template <typename Class>
Coroutine* Coroutine::build(const Class &object, void (Class::*fn)())
{
    return new StoredMemberFunctionCall0<Class>(fn, object);
}
template <typename Class, typename Param1, typename Arg1>
Coroutine* Coroutine::build(const Class &object, void (Class::*fn)(Param1), const Arg1 &arg1)
{
    return new StoredMemberFunctionCall1<Class, Param1, Arg1>(fn, object, arg1);
}
template <typename Class, typename Param1, typename Arg1, typename Param2, typename Arg2>
Coroutine* Coroutine::build(const Class &object, void (Class::*fn)(Param1, Param2), const Arg1 &arg1, const Arg2 &arg2)
{
    return new StoredMemberFunctionCall2<Class, Param1, Arg1, Param2, Arg2>(fn, object, arg1, arg2);
}
template <typename Class, typename Param1, typename Arg1, typename Param2, typename Arg2, typename Param3, typename Arg3>
Coroutine* Coroutine::build(const Class &object, void (Class::*fn)(Param1, Param2, Param3), const Arg1 &arg1, const Arg2 &arg2, const Arg3 &arg3)
{
    return new StoredMemberFunctionCall3<Class, Param1, Arg1, Param2, Arg2, Param3, Arg3>(fn, object, arg1, arg2, arg3);
}
template <typename Class, typename Param1, typename Arg1, typename Param2, typename Arg2, typename Param3, typename Arg3, typename Param4, typename Arg4>
Coroutine* Coroutine::build(const Class &object, void (Class::*fn)(Param1, Param2, Param3, Param4), const Arg1 &arg1, const Arg2 &arg2, const Arg3 &arg3, const Arg4 &arg4)
{
    return new StoredMemberFunctionCall4<Class, Param1, Arg1, Param2, Arg2, Param3, Arg3, Param4, Arg4>(fn, object, arg1, arg2, arg3, arg4);
}
template <typename Class, typename Param1, typename Arg1, typename Param2, typename Arg2, typename Param3, typename Arg3, typename Param4, typename Arg4, typename Param5, typename Arg5>
Coroutine* Coroutine::build(const Class &object, void (Class::*fn)(Param1, Param2, Param3, Param4, Param5), const Arg1 &arg1, const Arg2 &arg2, const Arg3 &arg3, const Arg4 &arg4, const Arg5 &arg5)
{
    return new StoredMemberFunctionCall5<Class, Param1, Arg1, Param2, Arg2, Param3, Arg3, Param4, Arg4, Param5, Arg5>(fn, object, arg1, arg2, arg3, arg4, arg5);
}

template <typename Class>
Coroutine* Coroutine::build(const Class &object, void (Class::*fn)() const)
{
    return new StoredConstMemberFunctionCall0<Class>(fn, object);
}
template <typename Class, typename Param1, typename Arg1>
Coroutine* Coroutine::build(const Class &object, void (Class::*fn)(Param1) const, const Arg1 &arg1)
{
    return new StoredConstMemberFunctionCall1<Class, Param1, Arg1>(fn, object, arg1);
}
template <typename Class, typename Param1, typename Arg1, typename Param2, typename Arg2>
Coroutine* Coroutine::build(const Class &object, void (Class::*fn)(Param1, Param2) const, const Arg1 &arg1, const Arg2 &arg2)
{
    return new StoredConstMemberFunctionCall2<Class, Param1, Arg1, Param2, Arg2>(fn, object, arg1, arg2);
}
template <typename Class, typename Param1, typename Arg1, typename Param2, typename Arg2, typename Param3, typename Arg3>
Coroutine* Coroutine::build(const Class &object, void (Class::*fn)(Param1, Param2, Param3) const, const Arg1 &arg1, const Arg2 &arg2, const Arg3 &arg3)
{
    return new StoredConstMemberFunctionCall3<Class, Param1, Arg1, Param2, Arg2, Param3, Arg3>(fn, object, arg1, arg2, arg3);
}
template <typename Class, typename Param1, typename Arg1, typename Param2, typename Arg2, typename Param3, typename Arg3, typename Param4, typename Arg4>
Coroutine* Coroutine::build(const Class &object, void (Class::*fn)(Param1, Param2, Param3, Param4) const, const Arg1 &arg1, const Arg2 &arg2, const Arg3 &arg3, const Arg4 &arg4)
{
    return new StoredConstMemberFunctionCall4<Class, Param1, Arg1, Param2, Arg2, Param3, Arg3, Param4, Arg4>(fn, object, arg1, arg2, arg3, arg4);
}
template <typename Class, typename Param1, typename Arg1, typename Param2, typename Arg2, typename Param3, typename Arg3, typename Param4, typename Arg4, typename Param5, typename Arg5>
Coroutine* Coroutine::build(const Class &object, void (Class::*fn)(Param1, Param2, Param3, Param4, Param5) const, const Arg1 &arg1, const Arg2 &arg2, const Arg3 &arg3, const Arg4 &arg4, const Arg5 &arg5)
{
    return new StoredConstMemberFunctionCall5<Class, Param1, Arg1, Param2, Arg2, Param3, Arg3, Param4, Arg4, Param5, Arg5>(fn, object, arg1, arg2, arg3, arg4, arg5);
}

template <typename Class>
Coroutine* Coroutine::build(Class *object, void (Class::*fn)())
{
    return new StoredMemberFunctionPointerCall0<Class>(fn, object);
}
template <typename Class, typename Param1, typename Arg1>
Coroutine* Coroutine::build(Class *object, void (Class::*fn)(Param1), const Arg1 &arg1)
{
    return new StoredMemberFunctionPointerCall1<Class, Param1, Arg1>(fn, object, arg1);
}
template <typename Class, typename Param1, typename Arg1, typename Param2, typename Arg2>
Coroutine* Coroutine::build(Class *object, void (Class::*fn)(Param1, Param2), const Arg1 &arg1, const Arg2 &arg2)
{
    return new StoredMemberFunctionPointerCall2<Class, Param1, Arg1, Param2, Arg2>(fn, object, arg1, arg2);
}
template <typename Class, typename Param1, typename Arg1, typename Param2, typename Arg2, typename Param3, typename Arg3>
Coroutine* Coroutine::build(Class *object, void (Class::*fn)(Param1, Param2, Param3), const Arg1 &arg1, const Arg2 &arg2, const Arg3 &arg3)
{
    return new StoredMemberFunctionPointerCall3<Class, Param1, Arg1, Param2, Arg2, Param3, Arg3>(fn, object, arg1, arg2, arg3);
}
template <typename Class, typename Param1, typename Arg1, typename Param2, typename Arg2, typename Param3, typename Arg3, typename Param4, typename Arg4>
Coroutine* Coroutine::build(Class *object, void (Class::*fn)(Param1, Param2, Param3, Param4), const Arg1 &arg1, const Arg2 &arg2, const Arg3 &arg3, const Arg4 &arg4)
{
    return new StoredMemberFunctionPointerCall4<Class, Param1, Arg1, Param2, Arg2, Param3, Arg3, Param4, Arg4>(fn, object, arg1, arg2, arg3, arg4);
}
template <typename Class, typename Param1, typename Arg1, typename Param2, typename Arg2, typename Param3, typename Arg3, typename Param4, typename Arg4, typename Param5, typename Arg5>
Coroutine* Coroutine::build(Class *object, void (Class::*fn)(Param1, Param2, Param3, Param4, Param5), const Arg1 &arg1, const Arg2 &arg2, const Arg3 &arg3, const Arg4 &arg4, const Arg5 &arg5)
{
    return new StoredMemberFunctionPointerCall5<Class, Param1, Arg1, Param2, Arg2, Param3, Arg3, Param4, Arg4, Param5, Arg5>(fn, object, arg1, arg2, arg3, arg4, arg5);
}

template <typename Class>
Coroutine* Coroutine::build(const Class *object, void (Class::*fn)() const)
{
    return new StoredConstMemberFunctionPointerCall0<Class>(fn, object);
}
template <typename Class, typename Param1, typename Arg1>
Coroutine* Coroutine::build(const Class *object, void (Class::*fn)(Param1) const, const Arg1 &arg1)
{
    return new StoredConstMemberFunctionPointerCall1<Class, Param1, Arg1>(fn, object, arg1);
}
template <typename Class, typename Param1, typename Arg1, typename Param2, typename Arg2>
Coroutine* Coroutine::build(const Class *object, void (Class::*fn)(Param1, Param2) const, const Arg1 &arg1, const Arg2 &arg2)
{
    return new StoredConstMemberFunctionPointerCall2<Class, Param1, Arg1, Param2, Arg2>(fn, object, arg1, arg2);
}
template <typename Class, typename Param1, typename Arg1, typename Param2, typename Arg2, typename Param3, typename Arg3>
Coroutine* Coroutine::build(const Class *object, void (Class::*fn)(Param1, Param2, Param3) const, const Arg1 &arg1, const Arg2 &arg2, const Arg3 &arg3)
{
    return new StoredConstMemberFunctionPointerCall3<Class, Param1, Arg1, Param2, Arg2, Param3, Arg3>(fn, object, arg1, arg2, arg3);
}
template <typename Class, typename Param1, typename Arg1, typename Param2, typename Arg2, typename Param3, typename Arg3, typename Param4, typename Arg4>
Coroutine* Coroutine::build(const Class *object, void (Class::*fn)(Param1, Param2, Param3, Param4) const, const Arg1 &arg1, const Arg2 &arg2, const Arg3 &arg3, const Arg4 &arg4)
{
    return new StoredConstMemberFunctionPointerCall4<Class, Param1, Arg1, Param2, Arg2, Param3, Arg3, Param4, Arg4>(fn, object, arg1, arg2, arg3, arg4);
}
template <typename Class, typename Param1, typename Arg1, typename Param2, typename Arg2, typename Param3, typename Arg3, typename Param4, typename Arg4, typename Param5, typename Arg5>
Coroutine* Coroutine::build(const Class *object, void (Class::*fn)(Param1, Param2, Param3, Param4, Param5) const, const Arg1 &arg1, const Arg2 &arg2, const Arg3 &arg3, const Arg4 &arg4, const Arg5 &arg5)
{
    return new StoredConstMemberFunctionPointerCall5<Class, Param1, Arg1, Param2, Arg2, Param3, Arg3, Param4, Arg4, Param5, Arg5>(fn, object, arg1, arg2, arg3, arg4, arg5);
}


#endif // qdoc

