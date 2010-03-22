/****************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the tools applications of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** No Commercial Usage
** This file contains pre-release code and may not be distributed.
** You may use this file in accordance with the terms and conditions
** contained in the Technology Preview License Agreement accompanying
** this package.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights.  These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
**
**
**
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/
#include <QApplication>
#include <QDebug>
#include <QFile>

#include "codegenerator.h"
using namespace CodeGenerator;

const Item argument = "arg" + Counter();
const Item argumentRef = "&arg" + Counter();
const Item argumentType  = "Arg" + Counter();
const Item constArgumentType  = "const Arg" + Counter();
const Item parameterType  = "Param" + Counter();

Group argumentTypes(argumentType);          // expands to ",Arg1, Arg2, ..."
Group argumentTypesNoPrefix(argumentType);  // expands to "Arg1, Arg2, ..."
Group arguments(argument);                  // expands to ",arg1, arg2, ..."
Group argumentsNoPrefix(argument);          // expands to "arg1, arg2, ..."
Group parameterTypes(parameterType);        // expands to ",Param1, Param2, ..."
Group parameterTypesNoPrefix(parameterType); // expands to "Param1, Param2, ..."
Group typenameTypes("typename " + parameterType + ", typename " + argumentType); // expands to " ,typename Param1, typename Arg1, ..."
Group typenameTypesWithTemplate("typename " + parameterType + ", typename " + argumentType); // expands to "typename Param1, typename Arg1, ..."
Group types(parameterType + ", " + argumentType); // expands to ", Param1, Arg1, ..."
Group functionParameters(constArgumentType + " " + argumentRef);
Group typenameArgumentTypes("typename " + argumentType);

Group initializers(argument + "(" + argument + ")");
Group classData(argumentType +" "  + argument + ";");
Group arglist(argument);
Group typeList(argumentTypes);

void init()
{
    argumentTypes.setPrefix(", ");
    arguments.setPrefix(", ");
    parameterTypes.setPrefix(", ");
    typenameTypes.setPrefix(", ");
    typenameTypesWithTemplate.setPrefix("template <");
    typenameTypesWithTemplate.setPostfix(">");
    types.setPrefix(", ");
    functionParameters.setPrefix(", ");
    typenameArgumentTypes.setPrefix(", ");

    initializers.setPrefix(", ");
    classData.setSeparator(" ");
    classData.setPrefix("    ");
    arglist.setPrefix(", ");
    typeList.setPrefix(", ");
}


Item Line(Item item)
{
    return item + "\n";
}

Item generateBuildFunctions(int repeats)
{
    Item functionPointerType = "void (*)(" + parameterTypesNoPrefix + ")";

    Item functionPointerParameter = "void (*functionPointer)(" + parameterTypesNoPrefix + ")";

    Item stackSizeParameter = "int stackSize, ";
    Item stackSizeArgument = "stackSize, ";



    // plain functions
    Repeater functions = Line (typenameTypesWithTemplate) +
                         Line ("Coroutine* build(" + stackSizeParameter + functionPointerParameter + functionParameters + ")")  +
                         Line("{") +
                         Line("    return new StoredFunctorCall" + Counter() + "<" +
                                   functionPointerType + argumentTypes + ">(" + stackSizeArgument + "functionPointer" + arguments + ");") +
                         Line("}");
    functions.setRepeatCount(repeats);

    // function objects by value
    Repeater functionObjects =  Line ("template <typename FunctionObject" + typenameArgumentTypes + ">") +
                                Line ("Coroutine* build(" + stackSizeParameter + "FunctionObject functionObject" + functionParameters + ")") +
                                Line("{") +
                                Line("    return new StoredFunctorCall" + Counter() +
                                     "<FunctionObject" +
                                     argumentTypes + ">(" + stackSizeArgument + "functionObject" + arguments + ");") +
                                Line("}");
    functionObjects.setRepeatCount(repeats);

    // function objects by pointer
    Repeater functionObjectsPointer =  Line ("template <typename FunctionObject" + typenameArgumentTypes + ">") +
                                Line ("Coroutine* build(" + stackSizeParameter + "FunctionObject *functionObject" + functionParameters + ")") +
                                Line("{") +
                                Line("    return new StoredFunctorPointerCall" + Counter() +
                                     "<FunctionObject" +
                                     argumentTypes + ">(" + stackSizeArgument + "functionObject" + arguments + ");") +
                                Line("}");
    functionObjectsPointer.setRepeatCount(repeats);

    // member functions by value
    Repeater memberFunction =  Line ("template <typename Class" + typenameTypes + ">") +
                                Line ("Coroutine* build(" + stackSizeParameter + "const Class &object, void (Class::*fn)(" + parameterTypesNoPrefix  + ")" + functionParameters + ")") +
                                Line("{") +
                                Line("    return new StoredMemberFunctionCall" + Counter() +
                                     "<Class" +
                                     types + ">(" + stackSizeArgument + "fn, object" + arguments + ");") +
                                Line("}");
    memberFunction.setRepeatCount(repeats);

    // const member functions by value
    Repeater constMemberFunction =  Line ("template <typename Class" + typenameTypes + ">") +
                                Line ("Coroutine *build(" + stackSizeParameter + "const Class &object, void (Class::*fn)(" + parameterTypesNoPrefix  + ") const" + functionParameters + ")") +
                                Line("{") +
                                Line("    return new StoredConstMemberFunctionCall" + Counter() +
                                     "<Class" +
                                     types + ">(" + stackSizeArgument + "fn, object" + arguments + ");") +
                                Line("}");
    constMemberFunction.setRepeatCount(repeats);

    // member functions by class pointer
    Repeater memberFunctionPointer =  Line ("template <typename Class" + typenameTypes + ">") +
                                Line ("Coroutine* build(" + stackSizeParameter + "Class *object, void (Class::*fn)(" + parameterTypesNoPrefix  + ")" + functionParameters + ")") +
                                Line("{") +
                                Line("    return new StoredMemberFunctionPointerCall" + Counter() +
                                     "<Class" +
                                     types + ">(" + stackSizeArgument + "fn, object" + arguments + ");") +
                                Line("}");
    memberFunctionPointer.setRepeatCount(repeats);

    // const member functions by class pointer
    Repeater constMemberFunctionPointer =  Line ("template <typename Class" + typenameTypes + ">") +
                                Line ("Coroutine* build(" + stackSizeParameter + "const Class *object, void (Class::*fn)(" + parameterTypesNoPrefix  + ") const" + functionParameters + ")") +
                                Line("{") +
                                Line("    return new StoredConstMemberFunctionPointerCall" + Counter() +
                                     "<Class" +
                                     types + ">(" + stackSizeArgument + "fn, object" + arguments + ");") +
                                Line("}");
    constMemberFunctionPointer.setRepeatCount(repeats);


    return functions + Line("") + functionObjects + Line("") + functionObjectsPointer + Line("")
          + memberFunction + Line("") + constMemberFunction + Line("")
          + memberFunctionPointer + Line("") + constMemberFunctionPointer + Line("")
    ;
}


Item functions(Item className, Item functorType, Item callLine)
{
    return
    Line("template <typename FunctionPointer" +  typenameArgumentTypes + ">") +
    Line("struct " + className +  Counter() +": public Coroutine") +
    Line("{") +
    Line("    inline " + className + Counter() + "(int stackSize, " + functorType + " function" + functionParameters +")") +
    Line("      : Coroutine(stackSize), function(function)" + initializers + " {}") +
    Line("protected:") +
    Line("    virtual void run() { " + callLine + argumentsNoPrefix + "); }") +
    Line("    " + functorType + " function;") +
    Line(       classData) +
    Line("};") +
    Line("");
}

Item memberFunctions(Item className, Item constFunction, Item objectArgument, Item objectMember, Item callLine)
{
    return
    Line("template <typename Class"  + typenameTypes + ">") +
    Line("class " + className + Counter() + " : public Coroutine") +
    Line("{") +
    Line("public:")+
    Line("    " + className + Counter() + "(int stackSize, void (Class::*fn)(" + parameterTypesNoPrefix  + ") " + constFunction + ", " + objectArgument + functionParameters + ")") +
    Line("    : Coroutine(stackSize), fn(fn), object(object)" + initializers + "{ }" ) +
    Line("protected:") +
    Line("    virtual void run()")+
    Line("    {")+
    Line("        " + callLine + argumentsNoPrefix +  ");")+
    Line("    }")+
    Line("private:")+
    Line("    void (Class::*fn)(" + parameterTypesNoPrefix  + ")" + constFunction + ";")+
    Line("    " + objectMember + ";") +
    Line(        classData) +
    Line("};");
}

Item generateSFCs(int repeats)
{

    Item functionPointerTypedef = "typedef void (*FunctionPointer)(" + argumentTypesNoPrefix + ");";

    Repeater dataStructures =

    // Function objects by value
    functions(Item("StoredFunctorCall"), Item("FunctionPointer"), Item("function(")) +

    // Function objects by pointer
    functions(Item("StoredFunctorPointerCall"), Item("FunctionPointer *"), Item("(*function)(")) +

    // Member functions by value
    memberFunctions(Item("StoredMemberFunctionCall"), Item(""), Item("const Class &object"), Item("Class object"), Item("(object.*fn)(")) +

    // Const Member functions by value
    memberFunctions(Item("StoredConstMemberFunctionCall"), Item("const"), Item("const Class &object"), Item("const Class object"), Item("(object.*fn)(")) +

    // Member functions by pointer
    memberFunctions(Item("StoredMemberFunctionPointerCall"), Item(""), Item("Class *object"), Item("Class *object"), Item("(object->*fn)(")) +

    // const member functions by pointer
    memberFunctions(Item("StoredConstMemberFunctionPointerCall"), Item("const"), Item("Class const *object"), Item("Class const *object"), Item("(object->*fn)("));

    dataStructures.setRepeatCount(repeats);
    return dataStructures;
}

void writeFile(QString fileName, QByteArray contents)
{
    QFile runFile(fileName);
    if (runFile.open(QIODevice::WriteOnly) == false) {
        qDebug() << "Write to" << fileName << "failed";
        return;
    }

    runFile.write(contents);
    runFile.close();
    qDebug() << "Write to" << fileName << "Ok";
}

Item dollarQuote(Item item)
{
    return Item("$") + item + Item("$");
}

int main()
{
    const int repeats = 6;
    init();
    Item run =  (
                       Line("/****************************************************************************") +
                       Line("**") +
                       Line("** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).") +
                       Line("** Contact: Nokia Corporation (qt-info@nokia.com)") +
                       Line("**") +
                       Line("** This file is part of the Qt Toolkit.") +
                       Line("**") +
                       Line("****************************************************************************/") +
                       Line("") +
                       Line("// Generated code, do not edit! Use generator at tools/generatebuild/") +
                       Line("#ifndef COROUTINE_MAKE_H") +
                       Line("#define COROUTINE_MAKE_H") +
                       Line("") +
                       Line("#include \"coroutine.h\"") +
                       Line("#include \"coroutinestoredfunctioncall.h\"") +
//                       Line("") +
//                       Line("QT_BEGIN_HEADER") +
//                       Line("QT_BEGIN_NAMESPACE") +
//                       Line("") +
//                       Line("QT_MODULE(Core)") +
                       Line("") +
                       Line("#ifdef qdoc") +
//                       Line("") +
//                       Line("namespace Coroutine {") +
                       Line("") +
                       Line("    Coroutine* build(Function function, ...);") +
//                       Line("") +
//                       Line("} // namespace Coroutine") +
                       Line("") +
                       Line("#else") +
//                       Line("") +
//                       Line("namespace Coroutine {") +
                       Line("") +
                       generateBuildFunctions(repeats) +
//                       Line("") +
//                       Line("} //namespace Coroutine") +
                       Line("") +
                       Line("#endif // qdoc") +
                       Line("") +
//                       Line("QT_END_NAMESPACE") +
//                       Line("QT_END_HEADER") +
//                       Line("") +
                       Line("#endif")
                      );

    writeFile("../../src/coroutinebuild.h", run.generate());

    Item storedFunctionCall = (
                                     Line("/****************************************************************************") +
                                     Line("**") +
                                     Line("** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).") +
                                     Line("** Contact: Nokia Corporation (qt-info@nokia.com)") +
                                     Line("**") +
                                     Line("** This file is part of the Qt Toolkit.") +
                                     Line("**") +
                                     Line("****************************************************************************/") +
                                     Line("") +
                                     Line("// Generated code, do not edit! Use generator at tools/generatebuild/") +
                                     Line("#ifndef COROUTINE_STOREDFUNCTIONCALL_H") +
                                     Line("#define COROUTINE_STOREDFUNCTIONCALL_H") +
                                     Line("") +
                                     Line("#include \"coroutine.h\"") +
//                                     Line("#include <QtCore/qtconcurrentrunbase.h>") +
//                                     Line("") +
//                                     Line("QT_BEGIN_HEADER") +
//                                     Line("QT_BEGIN_NAMESPACE") +
//                                     Line("") +
//                                     Line("QT_MODULE(Core)") +
//                                     Line("") +
                                     Line("#ifndef qdoc") +
                                     Line("") +
//                                     Line("namespace Coroutine {") +
                                     generateSFCs(repeats) +
//                                     Line("} //namespace Coroutine") +
                                     Line("") +
                                     Line("#endif // qdoc") +
                                     Line("") +
//                                     Line("QT_END_NAMESPACE") +
//                                     Line("QT_END_HEADER") +
//                                     Line("") +
                                     Line("#endif")
                                    );

    writeFile("../../src/coroutinestoredfunctioncall.h", storedFunctionCall.generate());
}


