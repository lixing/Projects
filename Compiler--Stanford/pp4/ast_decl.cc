/* File: ast_decl.cc
 * -----------------
 * Implementation of Decl node classes.
 */
#include "ast_decl.h"
#include "ast_type.h"
#include "ast_stmt.h"
#include "codegen.h"


Decl::Decl(Identifier *n) : Node(*n->GetLocation()) {
    Assert(n != NULL);
    (id=n)->SetParent(this);
    scope = new Scope;
}

VarDecl::VarDecl(Identifier *n, Type *t) : Decl(n) {
    Assert(n != NULL && t != NULL);
    (type=t)->SetParent(this);
}


ClassDecl::ClassDecl(Identifier *n, NamedType *ex, List<NamedType*> *imp, List<Decl*> *m) : Decl(n) {
    // extends can be NULL, impl & mem may be empty lists but cannot be NULL
    Assert(n != NULL && imp != NULL && m != NULL);
    extends = ex;
    if (extends) extends->SetParent(this);
    (implements=imp)->SetParentAll(this);
    (members=m)->SetParentAll(this);
}


void ClassDecl::SetScope() {
	for (int i = 0; i < members->NumElements(); i ++){
        scope->AddDecl(members->Nth(i));
        members->Nth(i)->SetScope();
	}
}

void ClassDecl::Initialize() {
    int memOffset = CodeGenerator::OffsetToFirstField;
    int vtblOffset = CodeGenerator::OffsetToFirstMethod;

    if (extends != NULL) {
        Decl *d = Program::newScope ->table->Lookup(extends->GetName());
        Assert(d != NULL);
        memOffset += d->GetBytes();
        vtblOffset += d->GetVTblBytes();
    }

    for (int i = 0; i < members->NumElements(); i ++){
        VarDecl *vd = dynamic_cast<VarDecl*>(members->Nth(i));
        if (vd == NULL)  continue;
        vd->SetOffset(memOffset);
        memOffset += vd->GetBytes();
    }

    for (int i = 0; i < members->NumElements(); i ++){
        FnDecl *fd = dynamic_cast<FnDecl*>(members->Nth(i));
        if (fd == NULL)  continue;
        fd->SetIsMethod(true);
        fd->SetVTblOffset(vtblOffset);
        vtblOffset += CodeGenerator::VarSize;
    }

    for (int i = 0; i < members->NumElements(); i ++) {
        std::string prefix;
        prefix += GetName();
        prefix += ".";
        members->Nth(i)->AddPrefix(prefix.c_str());
    }
}

Location* ClassDecl::Emit(CodeGenerator *cg) {
    for (int i = 0; i < members->NumElements(); i ++)
        members->Nth(i)->Emit(cg);

    List<FnDecl*> *decls = GetMethodDecls();
    List<const char*> *labels = new List<const char*>;
    for (int i = 0, n = decls->NumElements(); i < n; ++i)
        labels->Append(decls->Nth(i)->GetLabel());

    cg->GenVTable(GetName(), labels);

    return NULL;
}

int ClassDecl::GetBytes() {
    int bytes = 0;

    if (extends != NULL) {
        Decl *d = Program::newScope ->table->Lookup(extends->GetName());
        Assert(d != NULL);
        bytes += d->GetBytes();
    }

    for (int i = 0; i < members->NumElements(); i ++)
        bytes += members->Nth(i)->GetBytes();

    return bytes;
}

int ClassDecl::GetVTblBytes() {
    int vtblBytes = 0;

    if (extends != NULL) {
        Decl *d = Program::newScope ->table->Lookup(extends->GetName());
        Assert(d != NULL);
        vtblBytes += d->GetVTblBytes();
    }

    for (int i = 0; i < members->NumElements(); i ++)
        vtblBytes += members->Nth(i)->GetVTblBytes();

    return vtblBytes;
}

List<FnDecl*>* ClassDecl::GetMethodDecls() {
    List<FnDecl*> *decls = new List<FnDecl*>;

    if (extends != NULL) {
        Decl *d = Program::newScope ->table->Lookup(extends->GetName());
        ClassDecl *cd = dynamic_cast<ClassDecl*>(d);
        Assert(cd != NULL);
        List<FnDecl*> *extDecls = cd->GetMethodDecls();
        for (int i = 0; i < extDecls->NumElements(); i++)
            decls->Append(extDecls->Nth(i));
    }


    for (int i = 0; i < members->NumElements(); i ++) {
        FnDecl *fd = dynamic_cast<FnDecl*>(members->Nth(i));
        if (fd == NULL)
            continue;

        for (int j = 0; j < decls->NumElements(); j++) {
            if (strcmp(decls->Nth(j)->GetName(), fd->GetName()) == 0) {
                decls->RemoveAt(j);
                decls->InsertAt(fd, j);
            }
        }
    }


    for (int i = 0; i < members->NumElements(); i ++) {
        FnDecl *fd = dynamic_cast<FnDecl*>(members->Nth(i));
        if (fd == NULL)
            continue;
        decls->Append(fd);
    }

    return decls;
}

InterfaceDecl::InterfaceDecl(Identifier *n, List<Decl*> *m) : Decl(n) {
    Assert(n != NULL && m != NULL);
    (members=m)->SetParentAll(this);
}

void InterfaceDecl::SetScope() {
	for (int i = 0; i < members->NumElements(); i ++){
        scope->AddDecl(members->Nth(i));
        members->Nth(i)->SetScope();
	}
}

FnDecl::FnDecl(Identifier *n, Type *r, List<VarDecl*> *d) : Decl(n) {
    Assert(n != NULL && r!= NULL && d != NULL);
    (returnType=r)->SetParent(this);
    (formals=d)->SetParentAll(this);
    body = NULL;
    label = new std::string(GetName());
    if (*label != "main")
        label->insert(0, "labelPrefix"); 
    isMethod = false;
}

void FnDecl::SetFunctionBody(Stmt *b) {
    (body=b)->SetParent(this);
}


void FnDecl::SetScope() {
	for (int i = 0; i < formals->NumElements(); i++){
        scope->AddDecl(formals->Nth(i));
        formals->Nth(i)->SetScope();
	}

    if (body) 
		body->SetScope();
}

Location* FnDecl::Emit(CodeGenerator *cg) {
    int offset = CodeGenerator::OffsetToFirstParam;

    if (isMethod)
        offset += CodeGenerator::VarSize;

    for (int i = 0; i < formals->NumElements(); i++) {
        VarDecl *vd = formals->Nth(i);
        Location *loc = new Location(fpRelative, offset, vd->GetName());
        vd->SetLoc(loc);
        offset += vd->GetBytes();
    }

    if (body != NULL) {
        cg->GenLabel(GetLabel());
        cg->GenBeginFunc()->SetFrameSize(body->GetBytes());
        body->Emit(cg);
        cg->GenEndFunc();
    }
    return NULL;
}

