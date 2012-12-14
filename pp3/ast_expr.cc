/* File: ast_expr.cc
 * -----------------
 * Implementation of expression node classes.
 */

#include <string.h>
#include "ast_expr.h"
#include "ast_type.h"
#include "ast_decl.h"

ClassDecl* Expr::GetClassDecl(Scope *s) {
    while (s != NULL) {
        ClassDecl *c;
        if ((c = s->GetClassDecl()) != NULL)
            return c;
        s = s->GetParent();
    }
    return NULL;
}

Decl* Expr::GetFieldDecl(Identifier *f, Type *b) {
    NamedType *n = dynamic_cast<NamedType*>(b);

    while (n != NULL) {
        Decl *d = Program::newScope->table->Lookup(n->GetName());
		Decl *fd;
        ClassDecl *c = dynamic_cast<ClassDecl*>(d);
        InterfaceDecl *i = dynamic_cast<InterfaceDecl*>(d);

        if (c != NULL) {
            if ((fd = GetFieldDecl(f, c->GetScope())) != NULL)
                return fd;
            else n = c->GetExtends();
        } 
		else if (i != NULL) {
            if ((fd = GetFieldDecl(f, i->GetScope())) != NULL)
                return fd;
            else n = NULL;
        } 
		else { n = NULL;}
    }

    return GetFieldDecl(f, scope);
}

Decl* Expr::GetFieldDecl(Identifier *f, Scope *s) {
    while (s != NULL) {
        Decl *d;
        if ((d = s->table->Lookup(f->GetName())) != NULL)
            return d;
        s = s->GetParent();
    }
    return NULL;
}

Type* EmptyExpr::GetType() {
    return Type::errorType;
}

IntConstant::IntConstant(yyltype loc, int val) : Expr(loc) {
    value = val;
}

Type* IntConstant::GetType() {
    return Type::intType;
}

DoubleConstant::DoubleConstant(yyltype loc, double val) : Expr(loc) {
    value = val;
}

Type* DoubleConstant::GetType() {
    return Type::doubleType;
}

BoolConstant::BoolConstant(yyltype loc, bool val) : Expr(loc) {
    value = val;
}

Type* BoolConstant::GetType() {
    return Type::boolType;
}

StringConstant::StringConstant(yyltype loc, const char *val) : Expr(loc) {
    Assert(val != NULL);
    value = strdup(val);
}

Type* StringConstant::GetType() {
    return Type::stringType;
}

Type* NullConstant::GetType() {
    return Type::nullType;
}

Operator::Operator(yyltype loc, const char *tok) : Node(loc) {
    Assert(tok != NULL);
    strncpy(tokenString, tok, sizeof(tokenString));
}

CompoundExpr::CompoundExpr(Expr *l, Operator *o, Expr *r)
  : Expr(Join(l->GetLocation(), r->GetLocation())) {
    Assert(l != NULL && o != NULL && r != NULL);
    (op=o)->SetParent(this);
    (left=l)->SetParent(this);
    (right=r)->SetParent(this);
}

CompoundExpr::CompoundExpr(Operator *o, Expr *r)
  : Expr(Join(o->GetLocation(), r->GetLocation())) {
    Assert(o != NULL && r != NULL);
    left = NULL;
    (op=o)->SetParent(this);
    (right=r)->SetParent(this);
}

void CompoundExpr::SetScope(Scope *parent) {
    scope->SetParent(parent);
    if (left != NULL)  left->SetScope(scope);
    right->SetScope(scope);
}

void CompoundExpr::Check() {
    if (left != NULL)  left->Check();
    right->Check();
}

Type* ArithmeticExpr::GetType() {
    Type *r = right->GetType();

    if (left == NULL) {
        if (r->IsEquivalentTo(Type::intType) || r->IsEquivalentTo(Type::doubleType))
            return r;
        else return Type::errorType;
    }

    Type *l = left->GetType();

    if (l->IsEquivalentTo(Type::intType) && r->IsEquivalentTo(Type::intType))
        return l;

    if (l->IsEquivalentTo(Type::doubleType) && r->IsEquivalentTo(Type::doubleType))
        return l;

    return Type::errorType;
}

void ArithmeticExpr::Check() {
    if (left != NULL)  left->Check();
    right->Check();
    Type *r = right->GetType();

    if (left == NULL) {
        if (r->IsEquivalentTo(Type::intType) || r->IsEquivalentTo(Type::doubleType))
            return;
        else ReportError::IncompatibleOperand(op, r);

        return;
    }

    Type *l = left->GetType();

    if (l->IsEquivalentTo(Type::intType) && r->IsEquivalentTo(Type::intType))
        return;

    if (l->IsEquivalentTo(Type::doubleType) && r->IsEquivalentTo(Type::doubleType))
        return;

    ReportError::IncompatibleOperands(op, l, r);
}

Type* RelationalExpr::GetType() {
    Type *r = right->GetType();
    Type *l = left->GetType();

    if (l->IsEquivalentTo(Type::intType) && r->IsEquivalentTo(Type::intType))
        return Type::errorType;

    if (l->IsEquivalentTo(Type::doubleType) && r->IsEquivalentTo(Type::doubleType))
        return Type::errorType;

    return Type::boolType;
}

void RelationalExpr::Check() {
    Type *r = right->GetType();
    Type *l = left->GetType();

    if (l->IsEquivalentTo(Type::intType) && r->IsEquivalentTo(Type::intType))
        return;

    if (l->IsEquivalentTo(Type::doubleType) && r->IsEquivalentTo(Type::doubleType))
        return;

    ReportError::IncompatibleOperands(op, l, r);
}

Type* EqualityExpr::GetType() {
    Type *r = right->GetType();
    Type *l = left->GetType();

    if (!l->IsEquivalentTo(r) && !r->IsEquivalentTo(l))
        return Type::errorType;

   return Type::boolType;
}

void EqualityExpr::Check() {
    left->Check();
    right->Check();

    Type *r = right->GetType();
    Type *l = left->GetType();

    if (!r->IsEquivalentTo(l) && !l->IsEquivalentTo(r))
        ReportError::IncompatibleOperands(op, l, r);
}

Type* LogicalExpr::GetType() {
    Type *r = right->GetType();

    if (left == NULL) {
        if (r->IsEquivalentTo(Type::boolType))
            return Type::boolType;
        else
            return Type::errorType;
    }

    Type *l = left->GetType();

    if (l->IsEquivalentTo(Type::boolType) && r->IsEquivalentTo(Type::boolType))
        return Type::boolType;

    return Type::errorType;
}

void LogicalExpr::Check() {
    if (left != NULL)
        left->Check();

    right->Check();
    Type *r = right->GetType();

    if (left == NULL) {
        if (r->IsEquivalentTo(Type::boolType))
            return;
        else  ReportError::IncompatibleOperand(op, r);

        return;
    }
    Type *l = left->GetType();
    if (l->IsEquivalentTo(Type::boolType) &&  r->IsEquivalentTo(Type::boolType))
        return;

    ReportError::IncompatibleOperands(op, l, r);
}

Type* AssignExpr::GetType() {
    Type *l = left->GetType();
    Type *r = right->GetType();
    if (!r->IsEquivalentTo(l))
        return Type::errorType;
    return l;
}

void AssignExpr::Check() {
    left->Check();
    right->Check();

    Type *l = left->GetType();
    Type *r = right->GetType();

    if (!r->IsEquivalentTo(l) && !l->IsCompatibleWith(Type::errorType))
        ReportError::IncompatibleOperands(op, l, r);
}

Type* This::GetType() {
    ClassDecl *d = GetClassDecl(scope);
    if (d == NULL)
        return Type::errorType;

    return d->GetType();
}

void This::Check() {
    if (GetClassDecl(scope) == NULL)
        ReportError::ThisOutsideClassScope(this);
}

ArrayAccess::ArrayAccess(yyltype loc, Expr *b, Expr *s) : LValue(loc) {
    (base=b)->SetParent(this);
    (subscript=s)->SetParent(this);
}

Type* ArrayAccess::GetType() {
    ArrayType *a = dynamic_cast<ArrayType*>(base->GetType());
    if (a == NULL)  return Type::errorType;
    return a->GetElemType();
}

void ArrayAccess::SetScope(Scope *parent) {
    scope->SetParent(parent);
    base->SetScope(scope);
    subscript->SetScope(scope);
}

void ArrayAccess::Check() {
    base->Check();
    subscript->Check();

    ArrayType *a = dynamic_cast<ArrayType*>(base->GetType());
    if (a == NULL)
		ReportError::BracketsOnNonArray(base);

    if (!subscript->GetType()->IsCompatibleWith(Type::intType))
        ReportError::SubscriptNotInteger(subscript);
}

FieldAccess::FieldAccess(Expr *b, Identifier *f)
  : LValue(b? Join(b->GetLocation(), f->GetLocation()) : *f->GetLocation()) {
    Assert(f != NULL); // b can be be NULL (just means no explicit base)
    base = b;
    if (base) base->SetParent(this);
    (field=f)->SetParent(this);
}

Type* FieldAccess::GetType() {
    Decl *d;
    ClassDecl *c;
    Type *t;

    c = GetClassDecl(scope);

    if (base == NULL) {
        if (c == NULL) {
            d = GetFieldDecl(field, scope);
        } 
		else {
            t = c->GetType();
            d = GetFieldDecl(field, t);
        }
    } 
	else {
        t = base->GetType();
        d = GetFieldDecl(field, t);
    }

    if (d == NULL)  return Type::errorType;

    if (dynamic_cast<VarDecl*>(d) == NULL)
        return Type::errorType;

    return static_cast<VarDecl*>(d)->GetType();
}

void FieldAccess::SetScope(Scope *parent) {
    scope->SetParent(parent);
    if (base != NULL)
        base->SetScope(scope);
}

void FieldAccess::Check() {
    if (base != NULL)
        base->Check();

    Decl *d;
    Type *t;

    if (base == NULL) {
        ClassDecl *c = GetClassDecl(scope);
        if (c == NULL) {
            if ((d = GetFieldDecl(field, scope)) == NULL) {
                ReportError::IdentifierNotDeclared(field, LookingForVariable);
                return;
            }
        } else {
            t = c->GetType();
            if ((d = GetFieldDecl(field, t)) == NULL) {
                ReportError::FieldNotFoundInBase(field, t);
                return;
            }
        }
    } else {
        t = base->GetType();
        if ((d = GetFieldDecl(field, t)) == NULL) {
            ReportError::FieldNotFoundInBase(field, t);
            return;
        }
        else if (GetClassDecl(scope) == NULL) {
            ReportError::InaccessibleField(field, t);
            return;
        }
    }

    if (dynamic_cast<VarDecl*>(d) == NULL)
        ReportError::IdentifierNotDeclared(field, LookingForVariable);
}

Call::Call(yyltype loc, Expr *b, Identifier *f, List<Expr*> *a) : Expr(loc)  {
    Assert(f != NULL && a != NULL); // b can be be NULL (just means no explicit base)
    base = b;
    if (base) base->SetParent(this);
    (field=f)->SetParent(this);
    (actuals=a)->SetParentAll(this);
}

Type* Call::GetType() {
    Decl *d;

    if (base == NULL) {
        ClassDecl *c = GetClassDecl(scope);
        if (c == NULL) {
            if ((d = GetFieldDecl(field, scope)) == NULL)
                return Type::errorType;
        } else {
            if ((d = GetFieldDecl(field, c->GetType())) == NULL)
                return Type::errorType;
        }
    } else {
        Type *t = base->GetType();
        if ((d = GetFieldDecl(field, t)) == NULL) {

            if (dynamic_cast<ArrayType*>(t) != NULL &&
                strcmp("length", field->GetName()) == 0)
                return Type::intType;

            return Type::errorType;
        }
    }

    if (dynamic_cast<FnDecl*>(d) == NULL)
        return Type::errorType;

    return static_cast<FnDecl*>(d)->GetReturnType();
}

void Call::SetScope(Scope *parent) {
    scope->SetParent(parent);

    if (base != NULL)
        base->SetScope(scope);

    for (int i = 0, n = actuals->NumElements(); i < n; ++i)
        actuals->Nth(i)->SetScope(scope);
}

void Call::Check() {
    if (base != NULL)
        base->Check();

    Decl *d;
    Type *t;

    if (base == NULL) {
        ClassDecl *c = GetClassDecl(scope);
        if (c == NULL) {
            if ((d = GetFieldDecl(field, scope)) == NULL) {
                CheckActuals(d);
                ReportError::IdentifierNotDeclared(field, LookingForFunction);
                return;
            }
        } 
		else {
            t = c->GetType();
            if ((d = GetFieldDecl(field, t)) == NULL) {
                CheckActuals(d);
                ReportError::IdentifierNotDeclared(field, LookingForFunction);
                return;
            }
        }
    } 
	else {
        t = base->GetType();
        if ((d = GetFieldDecl(field, t)) == NULL) {
            CheckActuals(d);

            if (dynamic_cast<ArrayType*>(t) == NULL ||
                strcmp("length", field->GetName()) != 0)
                ReportError::FieldNotFoundInBase(field, t);

            return;
        }
    }

    CheckActuals(d);
}

void Call::CheckActuals(Decl *d) {
    for (int i = 0, n = actuals->NumElements(); i < n; ++i)
        actuals->Nth(i)->Check();

    FnDecl *fnDecl = dynamic_cast<FnDecl*>(d);
    if (fnDecl == NULL)
        return;

    List<VarDecl*> *formals = fnDecl->GetFormals();

    int numExpected = formals->NumElements();
    int numGiven = actuals->NumElements();
    if (numExpected != numGiven) {
        ReportError::NumArgsMismatch(field, numExpected, numGiven);
        return;
    }

    for (int i = 0, n = actuals->NumElements(); i < n; ++i) {
        Type *given = actuals->Nth(i)->GetType();
        Type *expected = formals->Nth(i)->GetType();
        if (!given->IsEquivalentTo(expected))
            ReportError::ArgMismatch(actuals->Nth(i), i+1, given, expected);
    }
}

NewExpr::NewExpr(yyltype loc, NamedType *c) : Expr(loc) {
  Assert(c != NULL);
  (cType=c)->SetParent(this);
}

Type* NewExpr::GetType() {
    Decl *d = Program::newScope->table->Lookup(cType->GetName());
    ClassDecl *c = dynamic_cast<ClassDecl*>(d);

    if (c == NULL)
        return Type::errorType;

    return c->GetType();
}

void NewExpr::Check() {
    Decl *d = Program::newScope->table->Lookup(cType->GetName());
    ClassDecl *c = dynamic_cast<ClassDecl*>(d);

    if (c == NULL)
        ReportError::IdentifierNotDeclared(cType->GetId(), LookingForClass);
}

NewArrayExpr::NewArrayExpr(yyltype loc, Expr *sz, Type *et) : Expr(loc) {
    Assert(sz != NULL && et != NULL);
    (size=sz)->SetParent(this);
    (elemType=et)->SetParent(this);
}

Type* NewArrayExpr::GetType() {
    return new ArrayType(elemType);
}

void NewArrayExpr::SetScope(Scope *parent) {
    scope->SetParent(parent);

    size->SetScope(scope);
}

void NewArrayExpr::Check() {
    size->Check();

    if (!size->GetType()->IsCompatibleWith(Type::intType))
        ReportError::NewArraySizeNotInteger(size);

    if (elemType->IsPrimitive() && !elemType->IsEquivalentTo(Type::voidType))
        return;

    Decl *d = Program::newScope->table->Lookup(elemType->GetName());
    if (dynamic_cast<ClassDecl*>(d) == NULL)
        elemType->NotIdentifier(LookingForType);
}

Type* ReadIntegerExpr::GetType() {
    return Type::intType;
}

Type* ReadLineExpr::GetType() {
    return Type::stringType;
}
