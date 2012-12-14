/* File: ast_type.cc
 * -----------------
 * Implementation of type node classes.
 */

#include <string.h>
#include "ast_type.h"
#include "ast_decl.h"

/* Class constants
 * ---------------
 * These are public constants for the built-in base types (int, double, etc.)
 * They can be accessed with the syntax Type::intType. This allows you to
 * directly access them and share the built-in types where needed rather that
 * creates lots of copies.
 */

Type *Type::intType    = new Type("int");
Type *Type::doubleType = new Type("double");
Type *Type::voidType   = new Type("void");
Type *Type::boolType   = new Type("bool");
Type *Type::nullType   = new Type("null");
Type *Type::stringType = new Type("string");
Type *Type::errorType  = new Type("error"); 

Type::Type(const char *n) {
    Assert(n);
    typeName = strdup(n);
}

bool Type::IsEquivalentTo(Type *other) {
    if (IsCompatibleWith(Type::errorType))  return true;
    if (IsCompatibleWith(Type::nullType) && dynamic_cast<NamedType*>(other))    return true;
    return IsCompatibleWith(other);
}

NamedType::NamedType(Identifier *i) : Type(*i->GetLocation()) {
    Assert(i != NULL);
    (id=i)->SetParent(this);
}

void NamedType::NotIdentifier(reasonT reason) {
    ReportError::IdentifierNotDeclared(id, reason);
}

bool NamedType::IsCompatibleWith(Type *other) {
    NamedType *n = dynamic_cast<NamedType*>(other);
    if (n == NULL)  return false;
	if(*id == *(n -> id)) return true;
    return false;
}

bool NamedType::IsEquivalentTo(Type *other) {
    if (IsCompatibleWith(other))  return true;
    NamedType *n = this;
    Decl *d;
    while ((d = Program::newScope -> table -> Lookup(n -> GetName())) != NULL) {
        ClassDecl *c = dynamic_cast<ClassDecl*>(d);
        if (c == NULL)  return false;

        List<NamedType*> *nL = c->GetImplements();
        for (int i = 0; i < nL->NumElements(); i ++) {
            if (nL->Nth(i)->IsCompatibleWith(other))
                return true;
        }
        n = c->GetExtends();
        if (n == NULL)  break;
        if (n->IsCompatibleWith(other))   return true;
    }
    return false;
}

ArrayType::ArrayType(yyltype loc, Type *et) : Type(loc) {
    Assert(et != NULL);
    (elemType=et)->SetParent(this);
}

ArrayType::ArrayType(Type *et) : Type() {
    Assert(et != NULL);
    (elemType=et)->SetParent(this);
}

void ArrayType::NotIdentifier(reasonT reason) {
    elemType->NotIdentifier(reason);
}

bool ArrayType::IsCompatibleWith(Type *other) {
    ArrayType *a = dynamic_cast<ArrayType*>(other);
    if (a == NULL)  return false;
    return elemType->IsCompatibleWith(a->elemType);
}

bool ArrayType::IsEquivalentTo(Type *other) {
    ArrayType *a = dynamic_cast<ArrayType*>(other);
    if (a == NULL) return false;
    return elemType->IsEquivalentTo(a->elemType);
}
