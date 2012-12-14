/* File: ast_stmt.h
 * ----------------
 * The Stmt class and its subclasses are used to represent
 * statements in the parse tree.  For each statment in the
 * language (for, if, return, etc.) there is a corresponding
 * node class for that construct.
 *
 * pp4: You will need to extend the Stmt classes to implement
 * code generation for statements.
 */

#ifndef _H_ast_stmt
#define _H_ast_stmt

#include "list.h"
#include "ast.h"
#include "hashtable.h"
#include <stack>

class Decl;
class VarDecl;
class Expr;
class CodeGenerator;
class Location;

class Scope
{
  public:
    Hashtable<Decl*> *table;

  public:
    Scope();
    void AddDecl(Decl *d);
};

class Program : public Node
{
  protected:
    List<Decl*> *decls;
    CodeGenerator *gen;

  public:
    Program(List<Decl*> *declList);
    void Check();
    void Emit();
    static Scope *newScope ;
    static stack<const char*> *breakLabel;

  private:
    void SetScope();
};

class Stmt : public Node
{
  public:
    Stmt();
    Stmt(yyltype loc);

    virtual void SetScope() = 0;
    virtual Location* Emit(CodeGenerator *cg) = 0;
    virtual int GetBytes() = 0;
};

class StmtBlock : public Stmt
{
  protected:
    List<VarDecl*> *decls;
    List<Stmt*> *stmts;

  public:
    StmtBlock(List<VarDecl*> *variableDeclarations, List<Stmt*> *statements);
    void SetScope();
    Location* Emit(CodeGenerator *cg);
    int GetBytes();
};

class ConditionalStmt : public Stmt
{
  protected:
    Expr *test;
    Stmt *body;

  public:
    ConditionalStmt(Expr *testExpr, Stmt *body);
    virtual void SetScope() = 0;
};

class LoopStmt : public ConditionalStmt
{
  public:
    LoopStmt(Expr *testExpr, Stmt *body)
            : ConditionalStmt(testExpr, body) {}
    virtual void SetScope() = 0;
};

class ForStmt : public LoopStmt
{
  protected:
    Expr *init, *step;

  public:
    ForStmt(Expr *init, Expr *test, Expr *step, Stmt *body);
    void SetScope();
    Location* Emit(CodeGenerator *cg);
    int GetBytes();
};

class WhileStmt : public LoopStmt
{
  public:
    WhileStmt(Expr *test, Stmt *body) : LoopStmt(test, body) {}
    void SetScope();
    Location* Emit(CodeGenerator *cg);
    int GetBytes();
};

class IfStmt : public ConditionalStmt
{
  protected:
    Stmt *elseBody;

  public:
    IfStmt(Expr *test, Stmt *thenBody, Stmt *elseBody);
    void SetScope();
    Location* Emit(CodeGenerator *cg);
    int GetBytes();
};

class BreakStmt : public Stmt
{
  public:
    BreakStmt(yyltype loc) : Stmt(loc) {}
    void SetScope() {}
    Location* Emit(CodeGenerator *cg);
    int GetBytes() { return 0; };
};

class ReturnStmt : public Stmt
{
  protected:
    Expr *expr;

  public:
    ReturnStmt(yyltype loc, Expr *expr);
    void SetScope();
    Location* Emit(CodeGenerator *cg);
    int GetBytes();
};

class PrintStmt : public Stmt
{
  protected:
    List<Expr*> *args;

  public:
    PrintStmt(List<Expr*> *arguments);
    void SetScope();
    Location* Emit(CodeGenerator *cg);
    int GetBytes();
};

#endif
