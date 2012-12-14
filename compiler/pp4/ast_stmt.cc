/* File: ast_stmt.cc
 * -----------------
 * Implementation of statement node classes.
 */

#include "ast_stmt.h"
#include "ast_type.h"
#include "ast_decl.h"
#include "ast_expr.h"
#include "codegen.h"
#include "hashtable.h"


Scope::Scope() : table(new Hashtable<Decl*>) {}

void Scope::AddDecl(Decl *d) {
    table->Enter(d->GetName(), d);
}

Scope *Program::newScope  = new Scope;
stack<const char*> *Program::breakLabel = new stack<const char*>;

Program::Program(List<Decl*> *d) : gen(new CodeGenerator) {
    Assert(d != NULL);
    (decls=d)->SetParentAll(this);
    scope = newScope ;
}

void Program::Check() {
    /* You can use your pp3 semantic analysis or leave it out if
     * you want to avoid the clutter.  We won't test pp4 against
     * semantically-invalid programs.
     */
	for (int i = 0; i < decls->NumElements(); i++){
        newScope ->AddDecl(decls->Nth(i));
        decls->Nth(i)->SetScope();
	}
}

void Program::Emit() {
    /* pp4: here is where the code generation is kicked off.
     *      The general idea is perform a tree traversal of the
     *      entire program, generating instructions as you go.
     *      Each node can have its own way of translating itself,
     *      which makes for a great use of inheritance and
     *      polymorphism in the node classes.
     */

    int offset = CodeGenerator::OffsetToFirstGlobal;

    for (int i = 0; i < decls->NumElements(); i++) {
        VarDecl *vd = dynamic_cast<VarDecl*>(decls->Nth(i));
        if (vd == NULL)
            continue;

        Location *loc = new Location(gpRelative, offset, vd->GetName());
        vd->SetLoc(loc);
        offset += vd->GetBytes();
    }

	for (int i = 0; i < decls->NumElements(); i++){
        decls->Nth(i)->Initialize();
        decls->Nth(i)->Emit(gen);
	}

    gen->DoFinalCodeGen();
}

Stmt::Stmt() : Node() {
    scope = new Scope;
}

Stmt::Stmt(yyltype loc) : Node(loc) {
    scope = new Scope;
}

StmtBlock::StmtBlock(List<VarDecl*> *d, List<Stmt*> *s) {
    Assert(d != NULL && s != NULL);
    (decls=d)->SetParentAll(this);
    (stmts=s)->SetParentAll(this);
}

void StmtBlock::SetScope() {
	for (int i = 0; i < decls->NumElements(); i++){
        scope->AddDecl(decls->Nth(i));
        decls->Nth(i)->SetScope();
	}

    for (int i = 0; i < stmts->NumElements(); i++)
        stmts->Nth(i)->SetScope();
}

Location* StmtBlock::Emit(CodeGenerator *cg) {
    for (int i = 0; i < decls->NumElements(); i++) {
        VarDecl *vd = dynamic_cast<VarDecl*>(decls->Nth(i));
        if (vd == NULL)   continue;
        Location *loc = cg->GenLocalVar(vd->GetName(), vd->GetBytes());
        vd->SetLoc(loc);
    }

    for (int i = 0; i < stmts->NumElements(); i++)
        stmts->Nth(i)->Emit(cg);

    return NULL;
}

int StmtBlock::GetBytes() {
    int bytes = 0;

    for (int i = 0; i < decls->NumElements(); i++)
        bytes += decls->Nth(i)->GetBytes();

    for (int i = 0; i < stmts->NumElements(); i++)
        bytes += stmts->Nth(i)->GetBytes();

    return bytes;
}

ConditionalStmt::ConditionalStmt(Expr *t, Stmt *b) {
    Assert(t != NULL && b != NULL);
    (test=t)->SetParent(this);
    (body=b)->SetParent(this);
}

void ConditionalStmt::SetScope() {
    test->SetScope();
    body->SetScope();
}

void LoopStmt::SetScope() {
    ConditionalStmt::SetScope();
}

ForStmt::ForStmt(Expr *i, Expr *t, Expr *s, Stmt *b): LoopStmt(t, b) {
    Assert(i != NULL && t != NULL && s != NULL && b != NULL);
    (init=i)->SetParent(this);
    (step=s)->SetParent(this);
}

void ForStmt::SetScope() {
    LoopStmt::SetScope();

    init->SetScope();
    step->SetScope();
}

Location* ForStmt::Emit(CodeGenerator *cg) {
    const char* top = cg->NewLabel();
    const char* bot = cg->NewLabel();

    Program::breakLabel->push(bot);

    init->Emit(cg);
    cg->GenLabel(top);
    Location *t = test->Emit(cg);
    cg->GenIfZ(t, bot);
    body->Emit(cg);
    step->Emit(cg);
    cg->GenGoto(top);
    cg->GenLabel(bot);

    Program::breakLabel->pop();

    return NULL;

}

int ForStmt::GetBytes() {
    return init->GetBytes() + test->GetBytes() + body->GetBytes() + step->GetBytes();
}

void WhileStmt::SetScope() {
    LoopStmt::SetScope();
}

Location* WhileStmt::Emit(CodeGenerator *cg) {
    const char* top = cg->NewLabel();
    const char* bot = cg->NewLabel();

    Program::breakLabel->push(bot);

    cg->GenLabel(top);
    Location *t = test->Emit(cg);
    cg->GenIfZ(t, bot);
    body->Emit(cg);
    cg->GenGoto(top);
    cg->GenLabel(bot);

    Program::breakLabel->pop();

    return NULL;
}

int WhileStmt::GetBytes() {
    return test->GetBytes() + body->GetBytes();
}


IfStmt::IfStmt(Expr *t, Stmt *tb, Stmt *eb): ConditionalStmt(t, tb) {
    Assert(t != NULL && tb != NULL); // else can be NULL
    elseBody = eb;
    if (elseBody) elseBody->SetParent(this);
}

void IfStmt::SetScope() {
    ConditionalStmt::SetScope();
    if (elseBody) elseBody->SetScope();
}


Location* IfStmt::Emit(CodeGenerator *cg) {
    const char* els = cg->NewLabel();
    const char* bot = cg->NewLabel();

    Location *t = test->Emit(cg);
    cg->GenIfZ(t, els);
    body->Emit(cg);
    cg->GenGoto(bot);
    cg->GenLabel(els);
    if (elseBody) elseBody->Emit(cg);
    cg->GenLabel(bot);

    return NULL;
}


int IfStmt::GetBytes() {
    int bytes = test->GetBytes() + body->GetBytes();
    if (elseBody) bytes += elseBody->GetBytes();
    return bytes;
}

Location* BreakStmt::Emit(CodeGenerator *cg) {
    cg->GenGoto(Program::breakLabel->top());
    return NULL;
}

ReturnStmt::ReturnStmt(yyltype loc, Expr *e) : Stmt(loc) {
    Assert(e != NULL);
    (expr=e)->SetParent(this);
}

void ReturnStmt::SetScope() {
    expr->SetScope();
}

Location* ReturnStmt::Emit(CodeGenerator *cg) {
    if (expr == NULL)  cg->GenReturn();
    else  cg->GenReturn(expr->Emit(cg));

    return NULL;
}

int ReturnStmt::GetBytes() {
    if (expr == NULL)   return 0;
    else  return expr->GetBytes();
}

PrintStmt::PrintStmt(List<Expr*> *a) {
    Assert(a != NULL);
    (args=a)->SetParentAll(this);
}

void PrintStmt::SetScope() {
   for (int i = 0; i < args->NumElements(); i++)
        args->Nth(i)->SetScope();
}

Location* PrintStmt::Emit(CodeGenerator *cg) {
    for (int i = 0; i < args->NumElements(); i++) {
        Expr *e = args->Nth(i);
        BuiltIn b = e->GetType()->GetPrint();
        Assert(b != NumBuiltIns);
        cg->GenBuiltInCall(b, e->Emit(cg));
    }

    return NULL;
}

int PrintStmt::GetBytes() {
    int bytes = 0;
    for (int i = 0; i < args->NumElements(); i++)
        bytes += args->Nth(i)->GetBytes();
   return bytes;
}
