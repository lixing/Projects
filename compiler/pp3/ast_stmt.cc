/* File: ast_stmt.cc
 * -----------------
 * Implementation of statement node classes.
 */
#ifdef _DEBUG
#include <iostream>
using namespace std;
#endif

#include "ast_stmt.h"
#include "ast_type.h"
#include "ast_decl.h"
#include "ast_expr.h"
#include "errors.h"

bool Scope::AddDecl(Decl *d) {
    Decl *lookup = table->Lookup(d->GetName());
    if (lookup != NULL) {
            ReportError::DeclConflict(d, lookup);
            return true;
    }
    table->Enter(d->GetName(), d);
    return false;
}

Scope *Program::newScope = new Scope();

Program::Program(List<Decl*> *d) {
    Assert(d != NULL);
    (decls=d)->SetParentAll(this);
}

void Program::Check() {
    /* pp3: here is where the semantic analyzer is kicked off.
     *      The general idea is perform a tree traversal of the
     *      entire program, examining all constructs for compliance
     *      with the semantic rules.  Each node can have its own way of
     *      checking itself, which makes for a great use of inheritance
     *      and polymorphism in the node classes.
     */
    Decl* d;
    SetScope();
	for (int i = 0; i < decls->NumElements(); i ++){
        d = decls->Nth(i);
		d->Check();
	}
#ifdef _DEBUG
	Iterator<Decl*> it=symbol_table.GetIterator();
	Decl* entry;
	while(entry=it.GetNextValue()) {
		cout << entry->get_name() << endl;
	}
#endif
}

void Program::SetScope() {
	Decl* d;
    for (int i = 0; i < decls->NumElements(); i ++)
        newScope->AddDecl(decls->Nth(i));

	for (int i = 0; i < decls->NumElements(); i ++){
        d = decls->Nth(i);
	    d -> SetScope(newScope);
	}
}

void Stmt::SetScope(Scope *parent) {
    scope->SetParent(parent);
}

void Stmt::Check() {}

StmtBlock::StmtBlock(List<VarDecl*> *d, List<Stmt*> *s) {
    Assert(d != NULL && s != NULL);
    (decls=d)->SetParentAll(this);
    (stmts=s)->SetParentAll(this);
}

void StmtBlock::SetScope(Scope *parent) {
    scope->SetParent(parent);

    for (int i = 0; i < decls->NumElements(); i ++)
        scope->AddDecl(decls->Nth(i));

    for (int i = 0; i < decls->NumElements(); i ++)
        decls->Nth(i)->SetScope(scope);

    for (int i = 0; i < stmts->NumElements(); i ++)
        stmts->Nth(i)->SetScope(scope);
}

void StmtBlock::Check() {
    for (int i = 0; i < decls->NumElements(); i ++)
        decls->Nth(i)->Check();

    for (int i = 0; i < stmts->NumElements(); i ++)
        stmts->Nth(i)->Check();
}

ConditionalStmt::ConditionalStmt(Expr *t, Stmt *b) {
    Assert(t != NULL && b != NULL);
    (test=t)->SetParent(this);
    (body=b)->SetParent(this);
}

void ConditionalStmt::SetScope(Scope *parent) {
    scope->SetParent(parent);
    test->SetScope(scope);
    body->SetScope(scope);
}

void ConditionalStmt::Check() {
    test->Check();
    body->Check();

    if (!test->GetType()->IsEquivalentTo(Type::boolType))
        ReportError::TestNotBoolean(test);
}

void LoopStmt::SetScope(Scope *parent) {
    scope->SetParent(parent);
    scope->SetLoopStmt(this);
    test->SetScope(scope);
    body->SetScope(scope);
}

ForStmt::ForStmt(Expr *i, Expr *t, Expr *s, Stmt *b): LoopStmt(t, b) {
    Assert(i != NULL && t != NULL && s != NULL && b != NULL);
    (init=i)->SetParent(this);
    (step=s)->SetParent(this);
}

IfStmt::IfStmt(Expr *t, Stmt *tb, Stmt *eb): ConditionalStmt(t, tb) {
    Assert(t != NULL && tb != NULL); // else can be NULL
    elseBody = eb;
    if (elseBody) elseBody->SetParent(this);
}

void IfStmt::SetScope(Scope *parent) {
    scope->SetParent(parent);
    test->SetScope(scope);
    body->SetScope(scope);
    if (elseBody != NULL)
        elseBody->SetScope(scope);
}

void IfStmt::Check() {
    test->Check();
    body->Check();

    if (!test->GetType()->IsEquivalentTo(Type::boolType))
        ReportError::TestNotBoolean(test);

    if (elseBody != NULL)
        elseBody->Check();
}

void BreakStmt::Check() {
    Scope *s = scope;
    while (s != NULL) {
        if (s->GetLoopStmt() != NULL)
            return;
        s = s->GetParent();
    }
    ReportError::BreakOutsideLoop(this);
}

ReturnStmt::ReturnStmt(yyltype loc, Expr *e) : Stmt(loc) {
    Assert(e != NULL);
    (expr=e)->SetParent(this);
}

void ReturnStmt::SetScope(Scope *parent) {
    scope->SetParent(parent);
    expr->SetScope(scope);
}

void ReturnStmt::Check() {
    expr->Check();

    FnDecl *d = NULL;
    Scope *s = scope;
    while (s != NULL) {
        if ((d = s->GetFnDecl()) != NULL)
            break;
        s = s->GetParent();
    }

    Type *got = expr->GetType();
    Type *expected = d->GetReturnType();
    if (!got->IsEquivalentTo(expected))
        ReportError::ReturnMismatch(this, got, expected);
}

PrintStmt::PrintStmt(List<Expr*> *a) {
    Assert(a != NULL);
    (args=a)->SetParentAll(this);
}

void PrintStmt::SetScope(Scope *parent) {
    scope->SetParent(parent);
    for (int i = 0; i <  args->NumElements(); i++)
        args->Nth(i)->SetScope(scope);
}

void PrintStmt::Check() {
    for (int i = 0; i< args->NumElements(); i++) {
        Type *t = args->Nth(i)->GetType();
		if (t->IsEquivalentTo(Type::errorType)) continue;
        if (!(t->IsEquivalentTo(Type::intType) || t->IsEquivalentTo(Type::boolType) ||  t->IsEquivalentTo(Type::stringType)))
            ReportError::PrintArgMismatch(args->Nth(i), i+1, t);
    }
    for (int i = 0; i < args->NumElements(); i++)
        args->Nth(i)->Check();
}
