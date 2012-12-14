/* File: ast_decl.h
 * ----------------
 * In our parse tree, Decl nodes are used to represent and
 * manage declarations. There are 4 subclasses of the base class,
 * specialized for declarations of variables, functions, classes,
 * and interfaces.
 *
 * pp4: You will need to extend the Decl classes to implement
 * code generation for declarations.
 */

#ifndef _H_ast_decl
#define _H_ast_decl

#include "ast.h"
#include "list.h"
#include "ast_type.h"
#include "codegen.h"

class Type;
class NamedType;
class Identifier;
class Stmt;
class CodeGenerator;
class Location;
class FnDecl;

class Decl : public Node
{
  protected:
    Identifier *id;

  public:
    Decl(Identifier *name);
    friend ostream& operator<<(ostream& out, Decl *d) { return out << d->id; }

    virtual void SetScope() = 0;
    virtual void Initialize() = 0;
    virtual Location* Emit(CodeGenerator *cg) = 0;
    virtual int GetBytes() = 0;
    virtual int GetVTblBytes() = 0;
    const char* GetName() { return id->GetName(); }
    virtual void AddPrefix(const char *prefix) = 0;
};

class VarDecl : public Decl
{
  protected:
    Type *type;
    Location *memLoc;
    int memOffset;

  public:
    VarDecl(Identifier *name, Type *type);

    void SetScope() {}
    void Initialize() {}
    Location* Emit(CodeGenerator *cg) { return NULL; }
    Type* GetType() { return type; }
    int GetBytes() { return CodeGenerator::VarSize; };
    int GetVTblBytes() { return 0; }
    void AddPrefix(const char *prefix) {}
    Location* GetLoc() { return memLoc; }
    void SetLoc(Location *m) { memLoc = m; }
    int GetOffset() { return memOffset; }
    void SetOffset(int m) { memOffset = m; }
};

class ClassDecl : public Decl
{
  protected:
    List<Decl*> *members;
    NamedType *extends;
    List<NamedType*> *implements;

  public:
    ClassDecl(Identifier *name, NamedType *extends,
              List<NamedType*> *implements, List<Decl*> *members);

    void SetScope();
    void Initialize();
    Location* Emit(CodeGenerator *cg);
    int GetBytes();
    int GetVTblBytes();
    void AddPrefix(const char *prefix) {}
    NamedType* GetType() { return new NamedType(id); };
    NamedType* GetExtends() { return extends; }

  private:
    List<FnDecl*>* GetMethodDecls();
};

class InterfaceDecl : public Decl
{
  protected:
    List<Decl*> *members;

  public:
    InterfaceDecl(Identifier *name, List<Decl*> *members);

    void SetScope();
    void Initialize() {}
    Location* Emit(CodeGenerator *cg) { return NULL; }
    int GetBytes() { return 0; }
    int GetVTblBytes() { return 0; }
    void AddPrefix(const char *prefix) { }
};

class FnDecl : public Decl
{
  protected:
    List<VarDecl*> *formals;
    Type *returnType;
    Stmt *body;
    std::string *label;
    int vtblOffset;
    bool isMethod;

  public:
    FnDecl(Identifier *name, Type *returnType, List<VarDecl*> *formals);
    void SetFunctionBody(Stmt *b);

    void SetScope();
    void Initialize() {}
    Location* Emit(CodeGenerator *cg);
    Type* GetType() { return returnType; }
    const char* GetLabel() { return label->c_str(); };
    bool HasReturnVal() {  return returnType == Type::voidType ? 0 : 1; };
    int GetBytes() { return 0; }
    int GetVTblBytes() { return CodeGenerator::VarSize; };
    void AddPrefix(const char *prefix) { label->insert(0, prefix); };
    int GetVTblOffset() { return vtblOffset; }
    void SetVTblOffset(int v) { vtblOffset = v; }
    void SetIsMethod(bool b) { isMethod = b; }
};

#endif
