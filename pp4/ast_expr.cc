/* File: ast_expr.cc
 * -----------------
 * Implementation of expression node classes.
 */

#include <string.h>
#include "ast_expr.h"
#include "ast_type.h"
#include "ast_decl.h"
#include "codegen.h"
#include "errors.h"

Decl* Expr::GetFieldDecl(Identifier *field, Expr *b) {
    if (b != NULL)
        return GetFieldDecl(field, b->GetType());
    Decl *d = GetFieldDecl(field, static_cast<Node*>(this));
    if (d == NULL) {
        ClassDecl *classDecl = GetClassDecl();
        if (classDecl != NULL)
            d = GetFieldDecl(field, classDecl->GetType());
    }
    return d;
}

Decl* Expr::GetFieldDecl(Identifier *field, Node *n) {
    while (n != NULL) {
        Decl *d = n->GetScope()->table->Lookup(field->GetName());
        if (d != NULL)  return d;
        n = n->GetParent();
    }
    return NULL;
}

Decl* Expr::GetFieldDecl(Identifier *field, Type *t) {
    while (t != NULL) {
        Decl *tDecl = Program::newScope ->table->Lookup(t->GetName());
        Decl *d = tDecl->GetScope()->table->Lookup(field->GetName());
        if (d != NULL)  return d;
        if (dynamic_cast<ClassDecl*>(tDecl))
            t = static_cast<ClassDecl*>(tDecl)->GetExtends();
        else break;
    }
    return NULL;
}

ClassDecl* Expr::GetClassDecl() {
    Node *n = this;
    while (n != NULL) {
        if (dynamic_cast<ClassDecl*>(n))
            return static_cast<ClassDecl*>(n);
        n = n->GetParent();
    }
    return NULL;
}


IntConstant::IntConstant(yyltype loc, int val) : Expr(loc) {
    value = val;
}

Location* IntConstant::Emit(CodeGenerator *cg) {
    return cg->GenLoadConstant(value);
}


DoubleConstant::DoubleConstant(yyltype loc, double val) : Expr(loc) {
    value = val;
}


Location* DoubleConstant::Emit(CodeGenerator *cg) {
    Assert(0);
    return NULL;
}


BoolConstant::BoolConstant(yyltype loc, bool val) : Expr(loc) {
    value = val;
}


Location* BoolConstant::Emit(CodeGenerator *cg) {
    return cg->GenLoadConstant(value ? 1 : 0);
}


StringConstant::StringConstant(yyltype loc, const char *val) : Expr(loc) {
    Assert(val != NULL);
    value = strdup(val);
}


Location* StringConstant::Emit(CodeGenerator *cg) {
    return cg->GenLoadConstant(value);
}



Location* NullConstant::Emit(CodeGenerator *cg) {
    return cg->GenLoadConstant(0);
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


Location* ArithmeticExpr::Emit(CodeGenerator *cg) {
    if (left == NULL)  return EmitUnary(cg);
    else  return EmitBinary(cg);
}

int ArithmeticExpr::GetBytes() {
    if (left == NULL)  return GetBytesUnary();
    else  return GetBytesBinary();
}

Location* ArithmeticExpr::EmitUnary(CodeGenerator *cg) {
    Location *rightLocation = right->Emit(cg);
    Location *zero = cg->GenLoadConstant(0);
    return cg->GenBinaryOp(op->GetTokenString(), zero, rightLocation);
}


Location* ArithmeticExpr::EmitBinary(CodeGenerator *cg) {
    Location *leftLocation = left->Emit(cg);
    Location *rightLocation = right->Emit(cg);
    return cg->GenBinaryOp(op->GetTokenString(), leftLocation, rightLocation);
}


Location* RelationalExpr::Emit(CodeGenerator *cg) {
    const char *tok = op->GetTokenString();

    if (strcmp("<", tok) == 0)
        return EmitLess(cg, left, right);
    else if (strcmp("<=", tok) == 0)
        return EmitLessEqual(cg, left, right);
    else if (strcmp(">", tok) == 0)
        return EmitLess(cg, right, left);
    else if (strcmp(">=", tok) == 0)
        return EmitLessEqual(cg, right, left);
    else  Assert(0);

    return NULL;
}

int RelationalExpr::GetBytes() {
    const char *tok = op->GetTokenString();

    if (strcmp("<", tok) == 0)
        return GetBytesLess(left, right);
    else if (strcmp("<=", tok) == 0)
        return GetBytesLessEqual(left, right);
    else if (strcmp(">", tok) == 0)
        return GetBytesLess(right, left);
    else if (strcmp(">=", tok) == 0)
        return GetBytesLessEqual(right, left);
    else  Assert(0); 

    return 0;
}

Location* RelationalExpr::EmitLess(CodeGenerator *cg, Expr *l, Expr *r) {
    Location *leftLocation = l->Emit(cg);
    Location *rightLocation = r->Emit(cg);
    return cg->GenBinaryOp("<", leftLocation, rightLocation);
}

int RelationalExpr::GetBytesLess(Expr *l, Expr *r) {
    return l->GetBytes() + r->GetBytes() + CodeGenerator::VarSize;
}

Location* RelationalExpr::EmitLessEqual(CodeGenerator *cg, Expr *l, Expr *r) {
    Location *leftLocation = l->Emit(cg);
    Location *rightLocation = r->Emit(cg);

    Location *less = cg->GenBinaryOp("<", leftLocation, rightLocation);
    Location *equal = cg->GenBinaryOp("==", leftLocation, rightLocation);

    return cg->GenBinaryOp("||", less, equal);
}


Location* EqualityExpr::Emit(CodeGenerator *cg) {
    const char *tok = op->GetTokenString();

    if (strcmp("==", tok) == 0)
        return EmitEqual(cg);
    else if (strcmp("!=", tok) == 0)
        return EmitNotEqual(cg);
    else  Assert(0); 

    return NULL;
}

int EqualityExpr::GetBytes() {
    const char *tok = op->GetTokenString();

    if (strcmp("==", tok) == 0)
        return GetBytesEqual();
    else if (strcmp("!=", tok) == 0)
        return GetBytesNotEqual();
    else  Assert(0); 
    return 0;
}

Location* EqualityExpr::EmitEqual(CodeGenerator *cg) {
    Location *leftLocation = left->Emit(cg);
    Location *rightLocation = right->Emit(cg);

    if (left->GetType()->IsEquivalentTo(Type::stringType))
        return cg->GenBuiltInCall(StringEqual, leftLocation, rightLocation);
    else  return cg->GenBinaryOp("==", leftLocation, rightLocation);
}


Location* EqualityExpr::EmitNotEqual(CodeGenerator *cg) {
    const char* temp_a = cg->NewLabel();
    const char* temp_b = cg->NewLabel();
    Location *l = cg->GenTempVar();

    Location *leftLocation = left->Emit(cg);
    Location *rightLocation = right->Emit(cg);

    Location *equal;
    if (left->GetType()->IsEquivalentTo(Type::stringType))
        equal = cg->GenBuiltInCall(StringEqual, leftLocation, rightLocation);
    else
        equal = cg->GenBinaryOp("==", leftLocation, rightLocation);

    cg->GenIfZ(equal, temp_b);
    cg->GenAssign(l, cg->GenLoadConstant(0));
    cg->GenGoto(temp_a);
    cg->GenLabel(temp_b);
    cg->GenAssign(l, cg->GenLoadConstant(1));
    cg->GenLabel(temp_a);

    return l;
}


Location* LogicalExpr::Emit(CodeGenerator *cg) {
    const char *tok = op->GetTokenString();

    if (strcmp("&&", tok) == 0)
        return EmitAnd(cg);
    else if (strcmp("||", tok) == 0)
        return EmitOr(cg);
    else if (strcmp("!", tok) == 0)
        return EmitNot(cg);
    else  Assert(0); 

    return 0;
}

int LogicalExpr::GetBytes() {
    const char *tok = op->GetTokenString();

    if (strcmp("&&", tok) == 0)
        return GetBytesAnd();
    else if (strcmp("||", tok) == 0)
        return GetBytesOr();
    else if (strcmp("!", tok) == 0)
        return GetBytesNot();
    else  Assert(0); 

    return 0;
}

Location* LogicalExpr::EmitAnd(CodeGenerator *cg) {
    Location *leftLocation = left->Emit(cg);
    Location *rightLocation = right->Emit(cg);

    return cg->GenBinaryOp("&&", leftLocation, rightLocation);
}


Location* LogicalExpr::EmitOr(CodeGenerator *cg) {
    Location *leftLocation = left->Emit(cg);
    Location *rightLocation = right->Emit(cg);
    return cg->GenBinaryOp("||", leftLocation, rightLocation);
}


Location* LogicalExpr::EmitNot(CodeGenerator *cg) {
    const char* temp_a = cg->NewLabel();
    const char* temp_b = cg->NewLabel();
    Location *l = cg->GenTempVar();

    Location *rightLocation = right->Emit(cg);

    cg->GenIfZ(rightLocation, temp_b);
    cg->GenAssign(l, cg->GenLoadConstant(0));
    cg->GenGoto(temp_a);
    cg->GenLabel(temp_b);
    cg->GenAssign(l, cg->GenLoadConstant(1));
    cg->GenLabel(temp_a);

    return l;
}


Location* AssignExpr::Emit(CodeGenerator *cg) {
    Location *rightLocation = right->Emit(cg);
    LValue *lval = dynamic_cast<LValue*>(left);

    if (lval != NULL)
        return lval->EmitStore(cg, rightLocation);

    Location *leftLocation = left->Emit(cg);
    cg->GenAssign(leftLocation, rightLocation);
    return leftLocation;
}

int AssignExpr::GetBytes() {
    LValue *l = dynamic_cast<LValue*>(left);
    if (l != NULL)
        return right->GetBytes() + l->GetBytesStore();
    return right->GetBytes() + left->GetBytes();
}

Type* This::GetType() {
    ClassDecl *d = GetClassDecl();
    Assert(d != NULL);
    return d->GetType();
}

Location* This::Emit(CodeGenerator *cg) {
    Location *result = new Location(fpRelative, CodeGenerator::OffsetToFirstParam, "this");
	return result;
}


ArrayAccess::ArrayAccess(yyltype loc, Expr *b, Expr *s) : LValue(loc) {
    (base=b)->SetParent(this);
    (subscript=s)->SetParent(this);
}


Location* ArrayAccess::Emit(CodeGenerator *cg) {
    return cg->GenLoad(EmitAddr(cg));
}


Location* ArrayAccess::EmitStore(CodeGenerator *cg, Location *val) {
    Location *addr = EmitAddr(cg);
    cg->GenStore(addr, val);
    return cg->GenLoad(addr);
}


Location* ArrayAccess::EmitAddr(CodeGenerator *cg) {
    Location *b = base->Emit(cg);
    Location *s = subscript->Emit(cg);

    EmitRuntime(cg, b, s);

    Location *con = cg->GenLoadConstant(CodeGenerator::VarSize);
    Location *num = cg->GenBinaryOp("*", s, con);
    Location *off = cg->GenBinaryOp("+", num, con);

    return cg->GenBinaryOp("+", b, off);
}


Location* ArrayAccess::EmitRuntime(CodeGenerator *cg,
                                                 Location *arr,
                                                 Location *sub) {
    Location *zro = cg->GenLoadConstant(0);
    Location *siz = cg->GenLoad(arr);

    Location *lessZro = cg->GenBinaryOp("<", sub, zro);
    Location *gratSiz = cg->GenBinaryOp("<", siz, sub);
    Location *equlSiz = cg->GenBinaryOp("==", siz, sub);
    Location *gratEqulSiz = cg->GenBinaryOp("||", gratSiz, equlSiz);
    Location *gratEqulSizLessZro = cg->GenBinaryOp("||", gratEqulSiz, lessZro);

    const char *passCheck = cg->NewLabel();
    cg->GenIfZ(gratEqulSizLessZro, passCheck);
    cg->GenBuiltInCall(PrintString, cg->GenLoadConstant(err_arr_out_of_bounds));
    cg->GenBuiltInCall(Halt);
    cg->GenLabel(passCheck);

    return NULL;
}


FieldAccess::FieldAccess(Expr *b, Identifier *f)
  : LValue(b? Join(b->GetLocation(), f->GetLocation()) : *f->GetLocation()) {
    Assert(f != NULL); // b can be be NULL (just means no explicit base)
    base = b;
    if (base) base->SetParent(this);
    (field=f)->SetParent(this);
}

Type* FieldAccess::GetType() {
    VarDecl *d = GetDecl();
    Assert(d != NULL);
    return d->GetType();
}

Location* FieldAccess::Emit(CodeGenerator *cg) {
    FieldAccess *baseAccess = dynamic_cast<FieldAccess*>(base);
    VarDecl *fieldDecl = GetDecl();
    Assert(fieldDecl != NULL);

    if (baseAccess == NULL)
        return Emit(cg, fieldDecl);

    VarDecl *baseDecl = baseAccess->GetDecl();
    Assert(baseDecl != NULL);
    int fieldOffset = fieldDecl->GetOffset();
    return cg->GenLoad(baseDecl->GetLoc(), fieldOffset);
}

int FieldAccess::GetBytes() {
    FieldAccess *baseAccess = dynamic_cast<FieldAccess*>(base);
    VarDecl *fieldDecl = GetDecl();
    Assert(fieldDecl != NULL);

    if (baseAccess == NULL)
        return GetBytes(fieldDecl);

    return CodeGenerator::VarSize;
}

Location* FieldAccess::EmitStore(CodeGenerator *cg, Location *val) {
    FieldAccess *baseAccess = dynamic_cast<FieldAccess*>(base);
    VarDecl *fieldDecl = GetDecl();
    Assert(fieldDecl != NULL);

    if (baseAccess == NULL) {
        return EmitStore(cg, val, fieldDecl);
    }

    VarDecl *baseDecl = baseAccess->GetDecl();
    Assert(baseDecl != NULL);
    int fieldOffset = fieldDecl->GetOffset();
    Location *leftLocation = baseDecl->GetLoc();
    cg->GenStore(leftLocation, val, fieldOffset);
    return leftLocation;
}

int FieldAccess::GetBytesStore() {
    FieldAccess *baseAccess = dynamic_cast<FieldAccess*>(base);
    VarDecl *fieldDecl = GetDecl();
    Assert(fieldDecl != NULL);

    if (baseAccess == NULL)
        return GetBytesStore(fieldDecl);

    return 0;
}

VarDecl* FieldAccess::GetDecl() {
    Decl *d = GetFieldDecl(field, base);
    return dynamic_cast<VarDecl*>(d);
}

Location* FieldAccess::Emit(CodeGenerator *cg, VarDecl *fieldDecl) {
    Location *loc = fieldDecl->GetLoc();
    if (loc != NULL)  return loc;
    Location *l = new Location(fpRelative, CodeGenerator::OffsetToFirstParam, "this");
    return cg->GenLoad(l, fieldDecl->GetOffset());
}

int FieldAccess::GetBytes(VarDecl *fieldDecl) {
    Location *loc = fieldDecl->GetLoc();
    if (loc != NULL)
        return 0;
    return CodeGenerator::VarSize;
}

Location* FieldAccess::EmitStore(CodeGenerator *cg, Location *val,VarDecl *fieldDecl) {
    Location *loc = fieldDecl->GetLoc();
    if (loc != NULL) {
        cg->GenAssign(loc, val);
        return loc;
    }
    Location *l = new Location(fpRelative, CodeGenerator::OffsetToFirstParam, "this");
    cg->GenStore(l, val, fieldDecl->GetOffset());
    return l;
}

Call::Call(yyltype loc, Expr *b, Identifier *f, List<Expr*> *a) : Expr(loc)  {
    Assert(f != NULL && a != NULL); // b can be be NULL (just means no explicit base)
    base = b;
    if (base) base->SetParent(this);
    (field=f)->SetParent(this);
    (actuals=a)->SetParentAll(this);
}

Type* Call::GetType() {
    if (IsArrayLengthCall())
        return Type::intType;

    FnDecl *d = GetDecl();
    Assert(d != NULL);
    return d->GetType();
}

Location* Call::Emit(CodeGenerator *cg) {
    if (IsArrayLengthCall())
        return EmitArrayLength(cg);
    return EmitLabel(cg);
}

int Call::GetBytes() {
    if (IsArrayLengthCall())
        return GetBytesArrayLength();
    return GetBytesLabel();
}

Location* Call::EmitLabel(CodeGenerator *cg) {
    List<Location*> *params = new List<Location*>;
    for (int i = 0; i < actuals->NumElements(); i++)
        params->Append(actuals->Nth(i)->Emit(cg));

    int n = params->NumElements();
    for (int i = n-1; i >= 0; i--)
        cg->GenPushParam(params->Nth(i));

    Location *l;
    if (!IsMethodCall()) {
        FnDecl *d = GetDecl();
        l = cg->GenLCall(d->GetLabel(), d->HasReturnVal());
        cg->GenPopParams(n * CodeGenerator::VarSize);
    } else {
        Location *b;
        if (base != NULL)
            b = base->Emit(cg);
        else
            b = new Location(fpRelative, CodeGenerator::OffsetToFirstParam, "this");;

        cg->GenPushParam(b);
        l = EmitDynamicDispatch(cg, b);
        cg->GenPopParams((n+1) * CodeGenerator::VarSize);
    }

    return l;
}

int Call::GetBytesLabel() {
    int bytes = 0;
    for (int i = 0, n = actuals->NumElements(); i < n; ++i)
        bytes += actuals->Nth(i)->GetBytes();

    if (IsMethodCall()) {
        if (base != NULL)
            bytes += base->GetBytes();
        bytes += GetBytesDynamicDispatch();
    }

    if (GetDecl()->HasReturnVal())
        bytes += CodeGenerator::VarSize;

    return bytes;
}

Location* Call::EmitArrayLength(CodeGenerator *cg) {
    return cg->GenLoad(base->Emit(cg));
}


Location* Call::EmitDynamicDispatch(CodeGenerator *cg, Location *b) {
    Location *vtable = cg->GenLoad(b);
    int methodOffset = GetDecl()->GetVTblOffset();
    Location *faddr = cg->GenLoad(vtable, methodOffset);
    return cg->GenACall(faddr, GetDecl()->HasReturnVal());
}


FnDecl* Call::GetDecl() {
    Decl *d = GetFieldDecl(field, base);
    return dynamic_cast<FnDecl*>(d);
}

bool Call::IsArrayLengthCall() {
    if (base == NULL)
        return false;

    if (dynamic_cast<ArrayType*>(base->GetType()) == NULL)
        return false;

    if (strcmp("length", field->GetName()) != 0)
        return false;

    return true;
}

bool Call::IsMethodCall() {
    if (base != NULL)
        return true;

    ClassDecl *c = GetClassDecl();
    if (c == NULL)
        return false;

    FnDecl *f = dynamic_cast<FnDecl*>(GetFieldDecl(field, c->GetType()));
    if (f == NULL)
        return false;

    return true;
}

NewExpr::NewExpr(yyltype loc, NamedType *c) : Expr(loc) {
  Assert(c != NULL);
  (cType=c)->SetParent(this);
}

Type* NewExpr::GetType() {
    Decl *d = Program::newScope ->table->Lookup(cType->GetName());
    ClassDecl *c = dynamic_cast<ClassDecl*>(d);
    Assert(c != NULL);
    return c->GetType();
}

Location* NewExpr::Emit(CodeGenerator *cg) {
    const char *name = cType->GetName();

    Decl *d = Program::newScope ->table->Lookup(name);
    Assert(d != NULL);

    Location *s = cg->GenLoadConstant(d->GetBytes());
    Location *c = cg->GenLoadConstant(CodeGenerator::VarSize);

    Location *mem = cg->GenBuiltInCall(Alloc, cg->GenBinaryOp("+", c, s));
    cg->GenStore(mem, cg->GenLoadLabel(name));

    return mem;
}


NewArrayExpr::NewArrayExpr(yyltype loc, Expr *sz, Type *et) : Expr(loc) {
    Assert(sz != NULL && et != NULL);
    (size=sz)->SetParent(this);
    (elemType=et)->SetParent(this);
}


Location* NewArrayExpr::Emit(CodeGenerator *cg) {
    Location *s = size->Emit(cg);
    Location *c = cg->GenLoadConstant(CodeGenerator::VarSize);

    EmitRuntimeSizeCheck(cg, s);

    Location *n = cg->GenBinaryOp("*", s, c);
    Location *mem = cg->GenBuiltInCall(Alloc, cg->GenBinaryOp("+", c, n));
    cg->GenStore(mem, s);

    return mem;
}

Location* NewArrayExpr::EmitRuntimeSizeCheck(CodeGenerator *cg, Location *siz) {
    Location *zro = cg->GenLoadConstant(0);

    Location *lessZro = cg->GenBinaryOp("<", siz, zro);
    Location *equlZro = cg->GenBinaryOp("==", siz, zro);
    Location *lessEqulZro = cg->GenBinaryOp("||", lessZro, equlZro);

    const char *passCheck = cg->NewLabel();
    cg->GenIfZ(lessEqulZro, passCheck);
    cg->GenBuiltInCall(PrintString, cg->GenLoadConstant(err_arr_bad_size));
    cg->GenBuiltInCall(Halt);
    cg->GenLabel(passCheck);

    return NULL;
}


Location* ReadIntegerExpr::Emit(CodeGenerator *cg) {
    return cg->GenBuiltInCall(ReadInteger);
}

Location* ReadLineExpr::Emit(CodeGenerator *cg) {
    return cg->GenBuiltInCall(ReadLine);
}


