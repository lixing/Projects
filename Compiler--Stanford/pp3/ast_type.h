/* File: ast_type.h
 * ----------------
 * In our parse tree, Type nodes are used to represent and
 * store type information. The base Type class is used
 * for built-in types, the NamedType for classes and interfaces,
 * and the ArrayType for arrays of other types.
 *
 * pp3: You will need to extend the Type classes to implement
 * the type system and rules for type equivalency and compatibility.
 */

#ifndef _H_ast_type
#define _H_ast_type

#include "ast.h"
#include "list.h"
#include <iostream>
#include "errors.h"
using namespace std;

class Type : public Node
{
  protected:
    char *typeName;

  public :
    static Type *intType, *doubleType, *boolType, *voidType,
                *nullType, *stringType, *errorType;

    Type(yyltype loc) : Node(loc) {}
    Type() : Node() {}
    Type(const char *str);
    virtual void PrintToStream(ostream& out) { out << typeName; }
    friend ostream& operator<<(ostream& out, Type *t) { t->PrintToStream(out); return out; }
    virtual bool IsEquivalentTo(Type *other);
    virtual void NotIdentifier(reasonT reason){ return; }
    virtual bool IsCompatibleWith(Type *other) { return this == other; }
    virtual bool IsPrimitive() { return true; }
    virtual const char* GetName() { return typeName; }
};

class NamedType : public Type
{
  protected:
    Identifier *id;

  public:
    NamedType(Identifier *i);
    void PrintToStream(ostream& out) { out << id; }
    void NotIdentifier(reasonT reason);
    bool IsEquivalentTo(Type *other);
    bool IsCompatibleWith(Type *other);
    bool IsPrimitive() { return false; }
    Identifier* GetId() { return id; }
	const char* GetName() { return id->GetName(); }
};

class ArrayType : public Type
{
  protected:
    Type *elemType;

  public:
    ArrayType(yyltype loc, Type *elemType);
    ArrayType(Type *elemType);
    void PrintToStream(ostream& out) { out << elemType << "[]"; }
    void NotIdentifier(reasonT reason);
    bool IsEquivalentTo(Type *other);
    bool IsCompatibleWith(Type *other);
    bool IsPrimitive() { return false; }
    Type* GetElemType() { return elemType; }
    const char* GetName() { return elemType->GetName(); }
};

#endif
