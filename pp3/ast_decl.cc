/* File: ast_decl.cc
 * -----------------
 * Implementation of Decl node classes.
 */
#include "ast_decl.h"
#include "ast_type.h"
#include "ast_stmt.h"

Decl::Decl(Identifier *n) : Node(*n->GetLocation()), scope(new Scope) {
    Assert(n != NULL);
    (id=n)->SetParent(this);
}

bool Decl::IsEquivalentTo(Decl *other) { return true;}

void Decl::SetScope(Scope *parent) {
    scope->SetParent(parent);
}

VarDecl::VarDecl(Identifier *n, Type *t) : Decl(n) {
    Assert(n != NULL && t != NULL);
    (type=t)->SetParent(this);
}

bool VarDecl::IsEquivalentTo(Decl *other) {
    VarDecl *k = dynamic_cast<VarDecl*>(other);
    if (k == NULL)  return false;
    return type->IsEquivalentTo(k->type);
}

void VarDecl::Check() {
    if (type->IsPrimitive())  return;
    Scope *s = scope;
    while (s != NULL) {
        Decl *d;
        if ((d = s->table->Lookup(type->GetName())) != NULL) {
            if (dynamic_cast<ClassDecl*>(d) == NULL && dynamic_cast<InterfaceDecl*>(d) == NULL)
                type->NotIdentifier(LookingForType);
            return;
        }
        s = s->GetParent();
    }
    type->NotIdentifier(LookingForType);
}

ClassDecl::ClassDecl(Identifier *n, NamedType *ex, List<NamedType*> *imp, List<Decl*> *m) : Decl(n) {
    // extends can be NULL, impl & mem may be empty lists but cannot be NULL
    Assert(n != NULL && imp != NULL && m != NULL);
    extends = ex;
    if (extends) extends->SetParent(this);
    (implements=imp)->SetParentAll(this);
    (members=m)->SetParentAll(this);
}

void ClassDecl::SetScope(Scope *parent) {
    scope->SetParent(parent);
    scope->SetClassDecl(this);
    for (int i = 0; i < members->NumElements(); i ++)
        scope->AddDecl(members->Nth(i));
    for (int i = 0; i < members->NumElements(); i ++)
        members->Nth(i)->SetScope(scope);
}

void ClassDecl::Check() {
    for (int i = 0; i < members->NumElements(); i ++)
        members->Nth(i)->Check();

    IsExtends();
    IsImplements();

    for (int i = 0; i < implements->NumElements(); i ++)
        ImplementsObject(implements->Nth(i));

    ExtendsObject(extends);
    IsInterfaces();
}

void ClassDecl::IsExtends() {
    if (extends == NULL)  return;
    Decl *d = scope->GetParent()->table->Lookup(extends->GetName());
    if (dynamic_cast<ClassDecl*>(d) == NULL)
        extends->NotIdentifier(LookingForClass);
}

void ClassDecl::IsImplements() {
    Scope *s = scope->GetParent();
    for (int i = 0; i < implements->NumElements(); i ++) {
        NamedType *n = implements->Nth(i);
        Decl *d = s->table->Lookup(implements->Nth(i)->GetName());
        if (dynamic_cast<InterfaceDecl*>(d) == NULL)
            n->NotIdentifier(LookingForInterface);
    }
}

void ClassDecl::ExtendsObject(NamedType *et) {
    if (et == NULL)  return;
    Decl *d = scope->GetParent()->table->Lookup(et->GetName());
    ClassDecl *extDecl = dynamic_cast<ClassDecl*>(d);
    if (extDecl == NULL)  return;
    ExtendsObject(extDecl->extends);
    IsScope(extDecl->scope);
}

void ClassDecl::ImplementsObject(NamedType *it) {
    Decl *d = scope->GetParent()->table->Lookup(it->GetName());
    InterfaceDecl *i = dynamic_cast<InterfaceDecl*>(d);
    if (i == NULL)  return;
    IsScope(i->GetScope());
}

void ClassDecl::IsScope(Scope *other) {
	Decl *d;
    Iterator<Decl*> iter = scope->table->GetIterator();
    while ((d = iter.GetNextValue()) != NULL) {
        Decl *de = other->table->Lookup(d->GetName());
        if (de == NULL) continue;
        if (dynamic_cast<VarDecl*>(de) != NULL)
            ReportError::DeclConflict(d, de);
        if (dynamic_cast<FnDecl*>(de) != NULL &&
            !d->IsEquivalentTo(de))
            ReportError::OverrideMismatch(d);
    }
}

void ClassDecl::IsInterfaces() {
 Scope *s = scope->GetParent();
    for (int i = 0; i < implements->NumElements(); i ++) {
        NamedType *n = implements->Nth(i);
        Decl *d = s->table->Lookup(implements->Nth(i)->GetName());
        InterfaceDecl *iDecl = dynamic_cast<InterfaceDecl*>(d);
        if (iDecl == NULL)  continue;

        List<Decl*> *intMembers = iDecl->GetMembers();
        for (int i = 0; i< intMembers->NumElements(); i ++) {
            Decl *d2 = intMembers->Nth(i);
            ClassDecl *classDecl = this;
            Decl *classLookup;
            while (classDecl != NULL) {
                classLookup = classDecl->GetScope()->table->Lookup(d2->GetName());
                if (classLookup != NULL) break;
                if (classDecl->GetExtends() == NULL) {
                    classDecl = NULL;
                } 
				else {
                    const char *extName = classDecl->GetExtends()->GetName();
                    Decl *ext = Program::newScope->table->Lookup(extName);
                    classDecl = dynamic_cast<ClassDecl*>(ext);
                }
            }
            if (classLookup == NULL) {
                ReportError::InterfaceNotImplemented(this, n);
                return;
            }
        }
    }
}

InterfaceDecl::InterfaceDecl(Identifier *n, List<Decl*> *m) : Decl(n) {
    Assert(n != NULL && m != NULL);
    (members=m)->SetParentAll(this);
}

void InterfaceDecl::SetScope(Scope *parent) {
    scope->SetParent(parent);
    for (int i = 0; i< members->NumElements(); i ++)
        scope->AddDecl(members->Nth(i));
    for (int i = 0; i< members->NumElements(); i ++)
        members->Nth(i)->SetScope(scope);
}

void InterfaceDecl::Check() {
    for (int i = 0; i< members->NumElements(); i ++)
        members->Nth(i)->Check();
}

FnDecl::FnDecl(Identifier *n, Type *r, List<VarDecl*> *d) : Decl(n) {
    Assert(n != NULL && r!= NULL && d != NULL);
    (returnType=r)->SetParent(this);
    (formals=d)->SetParentAll(this);
    body = NULL;
}

void FnDecl::SetFunctionBody(Stmt *b) {
    (body=b)->SetParent(this);
}

bool FnDecl::IsEquivalentTo(Decl *other) {
    FnDecl *f = dynamic_cast<FnDecl*>(other);

    if (f == NULL)    return false;
    if (!returnType->IsEquivalentTo(f->returnType))   return false;
    if (formals->NumElements() != f->formals->NumElements())  return false;

	for (int i = 0; i < formals->NumElements(); i ++){
        if (!formals->Nth(i)->IsEquivalentTo(f->formals->Nth(i)))
            return false;
	}
    return true;
}

void FnDecl::SetScope(Scope *parent) {
    scope->SetParent(parent);
    scope->SetFnDecl(this);

    for (int i = 0; i < formals->NumElements(); i ++)
        scope->AddDecl(formals->Nth(i));

    for (int i = 0; i < formals->NumElements(); i ++)
        formals->Nth(i)->SetScope(scope);

    if (body)
        body->SetScope(scope);
}

void FnDecl::Check() {
    for (int i = 0; i < formals->NumElements(); i ++)
        formals->Nth(i)->Check();

    if (body)
        body->Check();
}
