/****************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the Qt Toolkit.
**
****************************************************************************/

// Generated code, do not edit! Use generator at tools/generatebuild/
#ifndef COROUTINE_STOREDFUNCTIONCALL_H
#define COROUTINE_STOREDFUNCTIONCALL_H

#ifndef qdoc

template <typename FunctionPointer>
struct StoredFunctorCall0: public Coroutine
{
    inline StoredFunctorCall0(FunctionPointer function)
      : function(function) {}
protected:
    virtual void run() { function(); }
    FunctionPointer function;

};

template <typename FunctionPointer>
struct StoredFunctorPointerCall0: public Coroutine
{
    inline StoredFunctorPointerCall0(FunctionPointer * function)
      : function(function) {}
protected:
    virtual void run() { (*function)(); }
    FunctionPointer * function;

};

template <typename Class>
class StoredMemberFunctionCall0 : public Coroutine
{
public:
    StoredMemberFunctionCall0(void (Class::*fn)() , const Class &object)
    : fn(fn), object(object){ }
protected:
    virtual void run()
    {
        (object.*fn)();
    }
private:
    void (Class::*fn)();
    Class object;

};
template <typename Class>
class StoredConstMemberFunctionCall0 : public Coroutine
{
public:
    StoredConstMemberFunctionCall0(void (Class::*fn)() const, const Class &object)
    : fn(fn), object(object){ }
protected:
    virtual void run()
    {
        (object.*fn)();
    }
private:
    void (Class::*fn)()const;
    const Class object;

};
template <typename Class>
class StoredMemberFunctionPointerCall0 : public Coroutine
{
public:
    StoredMemberFunctionPointerCall0(void (Class::*fn)() , Class *object)
    : fn(fn), object(object){ }
protected:
    virtual void run()
    {
        (object->*fn)();
    }
private:
    void (Class::*fn)();
    Class *object;

};
template <typename Class>
class StoredConstMemberFunctionPointerCall0 : public Coroutine
{
public:
    StoredConstMemberFunctionPointerCall0(void (Class::*fn)() const, Class const *object)
    : fn(fn), object(object){ }
protected:
    virtual void run()
    {
        (object->*fn)();
    }
private:
    void (Class::*fn)()const;
    Class const *object;

};
template <typename FunctionPointer, typename Arg1>
struct StoredFunctorCall1: public Coroutine
{
    inline StoredFunctorCall1(FunctionPointer function, const Arg1 &arg1)
      : function(function), arg1(arg1) {}
protected:
    virtual void run() { function(arg1); }
    FunctionPointer function;
    Arg1 arg1;
};

template <typename FunctionPointer, typename Arg1>
struct StoredFunctorPointerCall1: public Coroutine
{
    inline StoredFunctorPointerCall1(FunctionPointer * function, const Arg1 &arg1)
      : function(function), arg1(arg1) {}
protected:
    virtual void run() { (*function)(arg1); }
    FunctionPointer * function;
    Arg1 arg1;
};

template <typename Class, typename Param1, typename Arg1>
class StoredMemberFunctionCall1 : public Coroutine
{
public:
    StoredMemberFunctionCall1(void (Class::*fn)(Param1) , const Class &object, const Arg1 &arg1)
    : fn(fn), object(object), arg1(arg1){ }
protected:
    virtual void run()
    {
        (object.*fn)(arg1);
    }
private:
    void (Class::*fn)(Param1);
    Class object;
    Arg1 arg1;
};
template <typename Class, typename Param1, typename Arg1>
class StoredConstMemberFunctionCall1 : public Coroutine
{
public:
    StoredConstMemberFunctionCall1(void (Class::*fn)(Param1) const, const Class &object, const Arg1 &arg1)
    : fn(fn), object(object), arg1(arg1){ }
protected:
    virtual void run()
    {
        (object.*fn)(arg1);
    }
private:
    void (Class::*fn)(Param1)const;
    const Class object;
    Arg1 arg1;
};
template <typename Class, typename Param1, typename Arg1>
class StoredMemberFunctionPointerCall1 : public Coroutine
{
public:
    StoredMemberFunctionPointerCall1(void (Class::*fn)(Param1) , Class *object, const Arg1 &arg1)
    : fn(fn), object(object), arg1(arg1){ }
protected:
    virtual void run()
    {
        (object->*fn)(arg1);
    }
private:
    void (Class::*fn)(Param1);
    Class *object;
    Arg1 arg1;
};
template <typename Class, typename Param1, typename Arg1>
class StoredConstMemberFunctionPointerCall1 : public Coroutine
{
public:
    StoredConstMemberFunctionPointerCall1(void (Class::*fn)(Param1) const, Class const *object, const Arg1 &arg1)
    : fn(fn), object(object), arg1(arg1){ }
protected:
    virtual void run()
    {
        (object->*fn)(arg1);
    }
private:
    void (Class::*fn)(Param1)const;
    Class const *object;
    Arg1 arg1;
};
template <typename FunctionPointer, typename Arg1, typename Arg2>
struct StoredFunctorCall2: public Coroutine
{
    inline StoredFunctorCall2(FunctionPointer function, const Arg1 &arg1, const Arg2 &arg2)
      : function(function), arg1(arg1), arg2(arg2) {}
protected:
    virtual void run() { function(arg1, arg2); }
    FunctionPointer function;
    Arg1 arg1; Arg2 arg2;
};

template <typename FunctionPointer, typename Arg1, typename Arg2>
struct StoredFunctorPointerCall2: public Coroutine
{
    inline StoredFunctorPointerCall2(FunctionPointer * function, const Arg1 &arg1, const Arg2 &arg2)
      : function(function), arg1(arg1), arg2(arg2) {}
protected:
    virtual void run() { (*function)(arg1, arg2); }
    FunctionPointer * function;
    Arg1 arg1; Arg2 arg2;
};

template <typename Class, typename Param1, typename Arg1, typename Param2, typename Arg2>
class StoredMemberFunctionCall2 : public Coroutine
{
public:
    StoredMemberFunctionCall2(void (Class::*fn)(Param1, Param2) , const Class &object, const Arg1 &arg1, const Arg2 &arg2)
    : fn(fn), object(object), arg1(arg1), arg2(arg2){ }
protected:
    virtual void run()
    {
        (object.*fn)(arg1, arg2);
    }
private:
    void (Class::*fn)(Param1, Param2);
    Class object;
    Arg1 arg1; Arg2 arg2;
};
template <typename Class, typename Param1, typename Arg1, typename Param2, typename Arg2>
class StoredConstMemberFunctionCall2 : public Coroutine
{
public:
    StoredConstMemberFunctionCall2(void (Class::*fn)(Param1, Param2) const, const Class &object, const Arg1 &arg1, const Arg2 &arg2)
    : fn(fn), object(object), arg1(arg1), arg2(arg2){ }
protected:
    virtual void run()
    {
        (object.*fn)(arg1, arg2);
    }
private:
    void (Class::*fn)(Param1, Param2)const;
    const Class object;
    Arg1 arg1; Arg2 arg2;
};
template <typename Class, typename Param1, typename Arg1, typename Param2, typename Arg2>
class StoredMemberFunctionPointerCall2 : public Coroutine
{
public:
    StoredMemberFunctionPointerCall2(void (Class::*fn)(Param1, Param2) , Class *object, const Arg1 &arg1, const Arg2 &arg2)
    : fn(fn), object(object), arg1(arg1), arg2(arg2){ }
protected:
    virtual void run()
    {
        (object->*fn)(arg1, arg2);
    }
private:
    void (Class::*fn)(Param1, Param2);
    Class *object;
    Arg1 arg1; Arg2 arg2;
};
template <typename Class, typename Param1, typename Arg1, typename Param2, typename Arg2>
class StoredConstMemberFunctionPointerCall2 : public Coroutine
{
public:
    StoredConstMemberFunctionPointerCall2(void (Class::*fn)(Param1, Param2) const, Class const *object, const Arg1 &arg1, const Arg2 &arg2)
    : fn(fn), object(object), arg1(arg1), arg2(arg2){ }
protected:
    virtual void run()
    {
        (object->*fn)(arg1, arg2);
    }
private:
    void (Class::*fn)(Param1, Param2)const;
    Class const *object;
    Arg1 arg1; Arg2 arg2;
};
template <typename FunctionPointer, typename Arg1, typename Arg2, typename Arg3>
struct StoredFunctorCall3: public Coroutine
{
    inline StoredFunctorCall3(FunctionPointer function, const Arg1 &arg1, const Arg2 &arg2, const Arg3 &arg3)
      : function(function), arg1(arg1), arg2(arg2), arg3(arg3) {}
protected:
    virtual void run() { function(arg1, arg2, arg3); }
    FunctionPointer function;
    Arg1 arg1; Arg2 arg2; Arg3 arg3;
};

template <typename FunctionPointer, typename Arg1, typename Arg2, typename Arg3>
struct StoredFunctorPointerCall3: public Coroutine
{
    inline StoredFunctorPointerCall3(FunctionPointer * function, const Arg1 &arg1, const Arg2 &arg2, const Arg3 &arg3)
      : function(function), arg1(arg1), arg2(arg2), arg3(arg3) {}
protected:
    virtual void run() { (*function)(arg1, arg2, arg3); }
    FunctionPointer * function;
    Arg1 arg1; Arg2 arg2; Arg3 arg3;
};

template <typename Class, typename Param1, typename Arg1, typename Param2, typename Arg2, typename Param3, typename Arg3>
class StoredMemberFunctionCall3 : public Coroutine
{
public:
    StoredMemberFunctionCall3(void (Class::*fn)(Param1, Param2, Param3) , const Class &object, const Arg1 &arg1, const Arg2 &arg2, const Arg3 &arg3)
    : fn(fn), object(object), arg1(arg1), arg2(arg2), arg3(arg3){ }
protected:
    virtual void run()
    {
        (object.*fn)(arg1, arg2, arg3);
    }
private:
    void (Class::*fn)(Param1, Param2, Param3);
    Class object;
    Arg1 arg1; Arg2 arg2; Arg3 arg3;
};
template <typename Class, typename Param1, typename Arg1, typename Param2, typename Arg2, typename Param3, typename Arg3>
class StoredConstMemberFunctionCall3 : public Coroutine
{
public:
    StoredConstMemberFunctionCall3(void (Class::*fn)(Param1, Param2, Param3) const, const Class &object, const Arg1 &arg1, const Arg2 &arg2, const Arg3 &arg3)
    : fn(fn), object(object), arg1(arg1), arg2(arg2), arg3(arg3){ }
protected:
    virtual void run()
    {
        (object.*fn)(arg1, arg2, arg3);
    }
private:
    void (Class::*fn)(Param1, Param2, Param3)const;
    const Class object;
    Arg1 arg1; Arg2 arg2; Arg3 arg3;
};
template <typename Class, typename Param1, typename Arg1, typename Param2, typename Arg2, typename Param3, typename Arg3>
class StoredMemberFunctionPointerCall3 : public Coroutine
{
public:
    StoredMemberFunctionPointerCall3(void (Class::*fn)(Param1, Param2, Param3) , Class *object, const Arg1 &arg1, const Arg2 &arg2, const Arg3 &arg3)
    : fn(fn), object(object), arg1(arg1), arg2(arg2), arg3(arg3){ }
protected:
    virtual void run()
    {
        (object->*fn)(arg1, arg2, arg3);
    }
private:
    void (Class::*fn)(Param1, Param2, Param3);
    Class *object;
    Arg1 arg1; Arg2 arg2; Arg3 arg3;
};
template <typename Class, typename Param1, typename Arg1, typename Param2, typename Arg2, typename Param3, typename Arg3>
class StoredConstMemberFunctionPointerCall3 : public Coroutine
{
public:
    StoredConstMemberFunctionPointerCall3(void (Class::*fn)(Param1, Param2, Param3) const, Class const *object, const Arg1 &arg1, const Arg2 &arg2, const Arg3 &arg3)
    : fn(fn), object(object), arg1(arg1), arg2(arg2), arg3(arg3){ }
protected:
    virtual void run()
    {
        (object->*fn)(arg1, arg2, arg3);
    }
private:
    void (Class::*fn)(Param1, Param2, Param3)const;
    Class const *object;
    Arg1 arg1; Arg2 arg2; Arg3 arg3;
};
template <typename FunctionPointer, typename Arg1, typename Arg2, typename Arg3, typename Arg4>
struct StoredFunctorCall4: public Coroutine
{
    inline StoredFunctorCall4(FunctionPointer function, const Arg1 &arg1, const Arg2 &arg2, const Arg3 &arg3, const Arg4 &arg4)
      : function(function), arg1(arg1), arg2(arg2), arg3(arg3), arg4(arg4) {}
protected:
    virtual void run() { function(arg1, arg2, arg3, arg4); }
    FunctionPointer function;
    Arg1 arg1; Arg2 arg2; Arg3 arg3; Arg4 arg4;
};

template <typename FunctionPointer, typename Arg1, typename Arg2, typename Arg3, typename Arg4>
struct StoredFunctorPointerCall4: public Coroutine
{
    inline StoredFunctorPointerCall4(FunctionPointer * function, const Arg1 &arg1, const Arg2 &arg2, const Arg3 &arg3, const Arg4 &arg4)
      : function(function), arg1(arg1), arg2(arg2), arg3(arg3), arg4(arg4) {}
protected:
    virtual void run() { (*function)(arg1, arg2, arg3, arg4); }
    FunctionPointer * function;
    Arg1 arg1; Arg2 arg2; Arg3 arg3; Arg4 arg4;
};

template <typename Class, typename Param1, typename Arg1, typename Param2, typename Arg2, typename Param3, typename Arg3, typename Param4, typename Arg4>
class StoredMemberFunctionCall4 : public Coroutine
{
public:
    StoredMemberFunctionCall4(void (Class::*fn)(Param1, Param2, Param3, Param4) , const Class &object, const Arg1 &arg1, const Arg2 &arg2, const Arg3 &arg3, const Arg4 &arg4)
    : fn(fn), object(object), arg1(arg1), arg2(arg2), arg3(arg3), arg4(arg4){ }
protected:
    virtual void run()
    {
        (object.*fn)(arg1, arg2, arg3, arg4);
    }
private:
    void (Class::*fn)(Param1, Param2, Param3, Param4);
    Class object;
    Arg1 arg1; Arg2 arg2; Arg3 arg3; Arg4 arg4;
};
template <typename Class, typename Param1, typename Arg1, typename Param2, typename Arg2, typename Param3, typename Arg3, typename Param4, typename Arg4>
class StoredConstMemberFunctionCall4 : public Coroutine
{
public:
    StoredConstMemberFunctionCall4(void (Class::*fn)(Param1, Param2, Param3, Param4) const, const Class &object, const Arg1 &arg1, const Arg2 &arg2, const Arg3 &arg3, const Arg4 &arg4)
    : fn(fn), object(object), arg1(arg1), arg2(arg2), arg3(arg3), arg4(arg4){ }
protected:
    virtual void run()
    {
        (object.*fn)(arg1, arg2, arg3, arg4);
    }
private:
    void (Class::*fn)(Param1, Param2, Param3, Param4)const;
    const Class object;
    Arg1 arg1; Arg2 arg2; Arg3 arg3; Arg4 arg4;
};
template <typename Class, typename Param1, typename Arg1, typename Param2, typename Arg2, typename Param3, typename Arg3, typename Param4, typename Arg4>
class StoredMemberFunctionPointerCall4 : public Coroutine
{
public:
    StoredMemberFunctionPointerCall4(void (Class::*fn)(Param1, Param2, Param3, Param4) , Class *object, const Arg1 &arg1, const Arg2 &arg2, const Arg3 &arg3, const Arg4 &arg4)
    : fn(fn), object(object), arg1(arg1), arg2(arg2), arg3(arg3), arg4(arg4){ }
protected:
    virtual void run()
    {
        (object->*fn)(arg1, arg2, arg3, arg4);
    }
private:
    void (Class::*fn)(Param1, Param2, Param3, Param4);
    Class *object;
    Arg1 arg1; Arg2 arg2; Arg3 arg3; Arg4 arg4;
};
template <typename Class, typename Param1, typename Arg1, typename Param2, typename Arg2, typename Param3, typename Arg3, typename Param4, typename Arg4>
class StoredConstMemberFunctionPointerCall4 : public Coroutine
{
public:
    StoredConstMemberFunctionPointerCall4(void (Class::*fn)(Param1, Param2, Param3, Param4) const, Class const *object, const Arg1 &arg1, const Arg2 &arg2, const Arg3 &arg3, const Arg4 &arg4)
    : fn(fn), object(object), arg1(arg1), arg2(arg2), arg3(arg3), arg4(arg4){ }
protected:
    virtual void run()
    {
        (object->*fn)(arg1, arg2, arg3, arg4);
    }
private:
    void (Class::*fn)(Param1, Param2, Param3, Param4)const;
    Class const *object;
    Arg1 arg1; Arg2 arg2; Arg3 arg3; Arg4 arg4;
};
template <typename FunctionPointer, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5>
struct StoredFunctorCall5: public Coroutine
{
    inline StoredFunctorCall5(FunctionPointer function, const Arg1 &arg1, const Arg2 &arg2, const Arg3 &arg3, const Arg4 &arg4, const Arg5 &arg5)
      : function(function), arg1(arg1), arg2(arg2), arg3(arg3), arg4(arg4), arg5(arg5) {}
protected:
    virtual void run() { function(arg1, arg2, arg3, arg4, arg5); }
    FunctionPointer function;
    Arg1 arg1; Arg2 arg2; Arg3 arg3; Arg4 arg4; Arg5 arg5;
};

template <typename FunctionPointer, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5>
struct StoredFunctorPointerCall5: public Coroutine
{
    inline StoredFunctorPointerCall5(FunctionPointer * function, const Arg1 &arg1, const Arg2 &arg2, const Arg3 &arg3, const Arg4 &arg4, const Arg5 &arg5)
      : function(function), arg1(arg1), arg2(arg2), arg3(arg3), arg4(arg4), arg5(arg5) {}
protected:
    virtual void run() { (*function)(arg1, arg2, arg3, arg4, arg5); }
    FunctionPointer * function;
    Arg1 arg1; Arg2 arg2; Arg3 arg3; Arg4 arg4; Arg5 arg5;
};

template <typename Class, typename Param1, typename Arg1, typename Param2, typename Arg2, typename Param3, typename Arg3, typename Param4, typename Arg4, typename Param5, typename Arg5>
class StoredMemberFunctionCall5 : public Coroutine
{
public:
    StoredMemberFunctionCall5(void (Class::*fn)(Param1, Param2, Param3, Param4, Param5) , const Class &object, const Arg1 &arg1, const Arg2 &arg2, const Arg3 &arg3, const Arg4 &arg4, const Arg5 &arg5)
    : fn(fn), object(object), arg1(arg1), arg2(arg2), arg3(arg3), arg4(arg4), arg5(arg5){ }
protected:
    virtual void run()
    {
        (object.*fn)(arg1, arg2, arg3, arg4, arg5);
    }
private:
    void (Class::*fn)(Param1, Param2, Param3, Param4, Param5);
    Class object;
    Arg1 arg1; Arg2 arg2; Arg3 arg3; Arg4 arg4; Arg5 arg5;
};
template <typename Class, typename Param1, typename Arg1, typename Param2, typename Arg2, typename Param3, typename Arg3, typename Param4, typename Arg4, typename Param5, typename Arg5>
class StoredConstMemberFunctionCall5 : public Coroutine
{
public:
    StoredConstMemberFunctionCall5(void (Class::*fn)(Param1, Param2, Param3, Param4, Param5) const, const Class &object, const Arg1 &arg1, const Arg2 &arg2, const Arg3 &arg3, const Arg4 &arg4, const Arg5 &arg5)
    : fn(fn), object(object), arg1(arg1), arg2(arg2), arg3(arg3), arg4(arg4), arg5(arg5){ }
protected:
    virtual void run()
    {
        (object.*fn)(arg1, arg2, arg3, arg4, arg5);
    }
private:
    void (Class::*fn)(Param1, Param2, Param3, Param4, Param5)const;
    const Class object;
    Arg1 arg1; Arg2 arg2; Arg3 arg3; Arg4 arg4; Arg5 arg5;
};
template <typename Class, typename Param1, typename Arg1, typename Param2, typename Arg2, typename Param3, typename Arg3, typename Param4, typename Arg4, typename Param5, typename Arg5>
class StoredMemberFunctionPointerCall5 : public Coroutine
{
public:
    StoredMemberFunctionPointerCall5(void (Class::*fn)(Param1, Param2, Param3, Param4, Param5) , Class *object, const Arg1 &arg1, const Arg2 &arg2, const Arg3 &arg3, const Arg4 &arg4, const Arg5 &arg5)
    : fn(fn), object(object), arg1(arg1), arg2(arg2), arg3(arg3), arg4(arg4), arg5(arg5){ }
protected:
    virtual void run()
    {
        (object->*fn)(arg1, arg2, arg3, arg4, arg5);
    }
private:
    void (Class::*fn)(Param1, Param2, Param3, Param4, Param5);
    Class *object;
    Arg1 arg1; Arg2 arg2; Arg3 arg3; Arg4 arg4; Arg5 arg5;
};
template <typename Class, typename Param1, typename Arg1, typename Param2, typename Arg2, typename Param3, typename Arg3, typename Param4, typename Arg4, typename Param5, typename Arg5>
class StoredConstMemberFunctionPointerCall5 : public Coroutine
{
public:
    StoredConstMemberFunctionPointerCall5(void (Class::*fn)(Param1, Param2, Param3, Param4, Param5) const, Class const *object, const Arg1 &arg1, const Arg2 &arg2, const Arg3 &arg3, const Arg4 &arg4, const Arg5 &arg5)
    : fn(fn), object(object), arg1(arg1), arg2(arg2), arg3(arg3), arg4(arg4), arg5(arg5){ }
protected:
    virtual void run()
    {
        (object->*fn)(arg1, arg2, arg3, arg4, arg5);
    }
private:
    void (Class::*fn)(Param1, Param2, Param3, Param4, Param5)const;
    Class const *object;
    Arg1 arg1; Arg2 arg2; Arg3 arg3; Arg4 arg4; Arg5 arg5;
};

#endif // qdoc

#endif
