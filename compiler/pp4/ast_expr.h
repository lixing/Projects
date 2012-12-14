/* File: ast_expr.h
 * ----------------
 * The Expr class and its subclasses are used to represent
 * expressions in the parse tree.  For each expression in the
 * language (add, call, New, etc.) there is a corresponding
 * node class for that construct.
 *
 * pp4: You will need to extend the Expr classes to implement
 * code generation for expressions.
 */

#ifndef _H_ast_expr
#define _H_ast_expr

#include "ast.h"
#include "ast_stmt.h"
#include "ast_type.h"
#include "list.h"
#include "codegen.h"

class NamedType; // for new
class Type; // for NewArray
class CodeGenerator;
class ClassDecl;
class FnDecl;

class Expr : public Stmt
{
  public:
    Expr(yyltype loc) : Stmt(loc) {}
    Expr() : Stmt() {}

    virtual Type* GetType() = 0;
    void SetScope() {}
    virtual Location* Emit(CodeGenerator *cg) = 0;
    virtual int GetBytes() = 0;

  protected:
    Decl* GetFieldDecl(Identifier *field, Expr *b);
    Decl* GetFieldDecl(Identifier *field, Node *n);
    Decl* GetFieldDecl(Identifier *field, Type *t);
    ClassDecl* GetClassDecl();
};

/* This node type is used for those places where an expression is optional.
 * We could use a NULL pointer, but then it adds a lot of checking for
 * NULL. By using a valid, but no-op, node, we save that trouble */
class EmptyExpr : public Expr
{
  public:
    Type* GetType() { return NULL; }
    Location* Emit(CodeGenerator *cg) { return NULL; }
    int GetBytes() { return 0; }
};

class IntConstant : public Expr
{
  protected:
    int value;

  public:
    IntConstant(yyltype loc, int val);
    Type* GetType() {  return Type::intType; };
    Location* Emit(CodeGenerator *cg);
    int GetBytes() { return 4; };
};

class DoubleConstant : public Expr
{
  protected:
    double value;

  public:
    DoubleConstant(yyltype loc, double val);
    Type* GetType() {  return Type::doubleType; };
    Location* Emit(CodeGenerator *cg);
    int GetBytes() { return 4; };
};

class BoolConstant : public Expr
{
  protected:
    bool value;

  public:
    BoolConstant(yyltype loc, bool val);
    Type* GetType() { return Type::boolType; };
    Location* Emit(CodeGenerator *cg);
    int GetBytes() { return 4; };
};

class StringConstant : public Expr
{
  protected:
    char *value;

  public:
    StringConstant(yyltype loc, const char *val);
    Type* GetType() {  return Type::stringType; };
    Location* Emit(CodeGenerator *cg);
    int GetBytes() { return 4; };
};

class NullConstant: public Expr
{
  public:
    NullConstant(yyltype loc) : Expr(loc) {}
    Type* GetType() {  return Type::nullType; };
    Location* Emit(CodeGenerator *cg);
    int GetBytes() { return 4; };
};

class Operator : public Node
{
  protected:
    char tokenString[4];

  public:
    Operator(yyltype loc, const char *tok);
    friend ostream& operator<<(ostream& out, Operator *o) { return out << o->tokenString; }
    const char *GetTokenString() { return tokenString; }
};

class CompoundExpr : public Expr
{
  protected:
    Operator *op;
    Expr *left, *right; // left will be NULL if unary

  public:
    CompoundExpr(Expr *lhs, Operator *op, Expr *rhs); // for binary
    CompoundExpr(Operator *op, Expr *rhs);             // for unary

    virtual Type* GetType() = 0;
    virtual Location* Emit(CodeGenerator *cg) = 0;
    virtual int GetBytes() = 0;
};

class ArithmeticExpr : public CompoundExpr
{
  public:
    ArithmeticExpr(Expr *lhs, Operator *op, Expr *rhs) : CompoundExpr(lhs,op,rhs) {}
    ArithmeticExpr(Operator *op, Expr *rhs) : CompoundExpr(op,rhs) {}

    Type* GetType() { return right->GetType(); }
    Location* Emit(CodeGenerator *cg);
    int GetBytes();

  private:
    Location* EmitUnary(CodeGenerator *cg);
    int GetBytesUnary(){ return right->GetBytes() + 2 * CodeGenerator::VarSize; };

    Location* EmitBinary(CodeGenerator *cg);
    int GetBytesBinary() { return right->GetBytes() + left->GetBytes() + CodeGenerator::VarSize; }
};

class RelationalExpr : public CompoundExpr
{
  public:
    RelationalExpr(Expr *lhs, Operator *op, Expr *rhs) : CompoundExpr(lhs,op,rhs) {}

    Type* GetType() { return Type::boolType; };
    Location* Emit(CodeGenerator *cg);
    int GetBytes();

  private:
    Location* EmitLess(CodeGenerator *cg, Expr *l, Expr *r);
    int GetBytesLess(Expr *l, Expr *r);

    Location* EmitLessEqual(CodeGenerator *cg, Expr *l, Expr *r);
    int GetBytesLessEqual(Expr *l, Expr *r) { return l->GetBytes() + r->GetBytes() + 3 * CodeGenerator::VarSize; };
};

class EqualityExpr : public CompoundExpr
{
  public:
    EqualityExpr(Expr *lhs, Operator *op, Expr *rhs) : CompoundExpr(lhs,op,rhs) {}
    const char *GetPrintNameForNode() { return "EqualityExpr"; }

    Type* GetType() { return Type::boolType; };
    Location* Emit(CodeGenerator *cg);
    int GetBytes();

  private:
    Location* EmitEqual(CodeGenerator *cg);
    int GetBytesEqual() {  return left->GetBytes() + right->GetBytes() + CodeGenerator::VarSize; };

    Location* EmitNotEqual(CodeGenerator *cg);
    int GetBytesNotEqual() {  return left->GetBytes() + right->GetBytes() + 4 * CodeGenerator::VarSize; };
};

class LogicalExpr : public CompoundExpr
{
  public:
    LogicalExpr(Expr *lhs, Operator *op, Expr *rhs) : CompoundExpr(lhs,op,rhs) {}
    LogicalExpr(Operator *op, Expr *rhs) : CompoundExpr(op,rhs) {}
    const char *GetPrintNameForNode() { return "LogicalExpr"; }

    Type* GetType() { return Type::boolType; };
    Location* Emit(CodeGenerator *cg);
    int GetBytes();

  private:
    Location* EmitAnd(CodeGenerator *cg);
    int GetBytesAnd() {  return left->GetBytes() + right->GetBytes() + CodeGenerator::VarSize; };

    Location* EmitOr(CodeGenerator *cg);
    int GetBytesOr() { return left->GetBytes() + right->GetBytes() + CodeGenerator::VarSize; };

    Location* EmitNot(CodeGenerator *cg);
    int GetBytesNot() {  return right->GetBytes() + 3 * CodeGenerator::VarSize; };
};

class AssignExpr : public CompoundExpr
{
  public:
    AssignExpr(Expr *lhs, Operator *op, Expr *rhs) : CompoundExpr(lhs,op,rhs) {}
    const char *GetPrintNameForNode() { return "AssignExpr"; }

    Type* GetType() { return left->GetType(); };
    Location* Emit(CodeGenerator *cg);
    int GetBytes();
};

class LValue : public Expr
{
  public:
    LValue(yyltype loc) : Expr(loc) {}
    virtual Type* GetType() = 0;
    virtual Location* Emit(CodeGenerator *cg) = 0;
    virtual int GetBytes() = 0;
    virtual Location* EmitStore(CodeGenerator *cg, Location *val) = 0;
    virtual int GetBytesStore() = 0;
};

class This : public Expr
{
  public:
    This(yyltype loc) : Expr(loc) {}
    Type* GetType();
    Location* Emit(CodeGenerator *cg);
    int GetBytes() { return 0; };
};

class ArrayAccess : public LValue
{
  protected:
    Expr *base, *subscript;

  public:
    ArrayAccess(yyltype loc, Expr *base, Expr *subscript);

    Type* GetType() { return base->GetType(); };
    Location* Emit(CodeGenerator *cg);
    int GetBytes() { return GetBytesAddr() + CodeGenerator::VarSize; };

    Location* EmitStore(CodeGenerator *cg, Location *val);
    int GetBytesStore() { return GetBytesAddr() + CodeGenerator::VarSize; };

  private:
    Location* EmitAddr(CodeGenerator *cg);
    int GetBytesAddr() { return base->GetBytes() + subscript->GetBytes() + 4 * CodeGenerator::VarSize + GetBytesRuntime(); };

    Location* EmitRuntime(CodeGenerator *cg, Location *siz,Location *sub);
    int GetBytesRuntime() { return 8 * CodeGenerator::VarSize; };
};

/* Note that field access is used both for qualified names
 * base.field and just field without qualification. We don't
 * know for sure whether there is an implicit "this." in
 * front until later on, so we use one node type for either
 * and sort it out later. */
class FieldAccess : public LValue
{
  protected:
    Expr *base;	// will be NULL if no explicit base
    Identifier *field;

  public:
    FieldAccess(Expr *base, Identifier *field); //ok to pass NULL base

    Type* GetType();
    Location* Emit(CodeGenerator *cg);
    int GetBytes();
    Location* EmitStore(CodeGenerator *cg, Location *val);
    int GetBytesStore();

  private:
    VarDecl* GetDecl();

    Location* Emit(CodeGenerator *cg, VarDecl *fieldDecl);
    int GetBytes(VarDecl *fieldDecl);
    Location* EmitStore(CodeGenerator *cg, Location *val,VarDecl *fieldDecl);
    int GetBytesStore(VarDecl *fieldDecl) { return 0; };
};

/* Like field access, call is used both for qualified base.field()
 * and unqualified field().  We won't figure out until later
 * whether we need implicit "this." so we use one node type for either
 * and sort it out later. */
class Call : public Expr
{
  protected:
    Expr *base;	// will be NULL if no explicit base
    Identifier *field;
    List<Expr*> *actuals;

  public:
    Call(yyltype loc, Expr *base, Identifier *field, List<Expr*> *args);

    Type* GetType();
    Location* Emit(CodeGenerator *cg);
    int GetBytes();

  private:
    Location* EmitLabel(CodeGenerator *cg);
    int GetBytesLabel();

    Location* EmitArrayLength(CodeGenerator *cg);
    int GetBytesArrayLength() { return base->GetBytes() + CodeGenerator::VarSize; };

    Location* EmitDynamicDispatch(CodeGenerator *cg, Location *b);
    int GetBytesDynamicDispatch() { return 2 * CodeGenerator::VarSize; };

    FnDecl* GetDecl();
    bool IsArrayLengthCall();
    bool IsMethodCall();
};

class NewExpr : public Expr
{
  protected:
    NamedType *cType;

  public:
    NewExpr(yyltype loc, NamedType *clsType);

    Type* GetType();
    Location* Emit(CodeGenerator *cg);
    int GetBytes() { return 5 * CodeGenerator::VarSize; };
};

class NewArrayExpr : public Expr
{
  protected:
    Expr *size;
    Type *elemType;

  public:
    NewArrayExpr(yyltype loc, Expr *sizeExpr, Type *elemType);

    Type* GetType() { return new ArrayType(elemType); };
    Location* Emit(CodeGenerator *cg);
    int GetBytes() { return size->GetBytes() + 4 * CodeGenerator::VarSize + GetBytesRuntimeSizeCheck(); };

  private:
    Location* EmitRuntimeSizeCheck(CodeGenerator *cg, Location *siz);
    int GetBytesRuntimeSizeCheck() { return 5 * CodeGenerator::VarSize; };
};

class ReadIntegerExpr : public Expr
{
  public:
    ReadIntegerExpr(yyltype loc) : Expr(loc) {}

    Type* GetType() { return Type::intType; };
    Location* Emit(CodeGenerator *cg);
    int GetBytes() { return CodeGenerator::VarSize; };
};

class ReadLineExpr : public Expr
{
  public:
    ReadLineExpr(yyltype loc) : Expr (loc) {}

    Type* GetType() {  return Type::stringType; };
    Location* Emit(CodeGenerator *cg);
    int GetBytes() {  return CodeGenerator::VarSize; };
};

#endif
