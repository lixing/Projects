/* File: parser.y
 * --------------
 * Bison input file to generate the parser for the compiler.
 *
 * pp2: your job is to write a parser that will construct the parse tree
 *      and if no parse errors were found, print it.  The parser should 
 *      accept the language as described in specification, and as augmented 
 *      in the pp2 handout.
 */

%{

/* Just like lex, the text within this first region delimited by %{ and %}
 * is assumed to be C/C++ code and will be copied verbatim to the y.tab.c
 * file ahead of the definitions of the yyparse() function. Add other header
 * file inclusions or C++ variable declarations/prototypes that are needed
 * by your code here.
 */
#include "scanner.h" // for yylex
#include "parser.h"
#include "errors.h"

void yyerror(const char *msg); // standard error-handling routine

%}

/* The section before the first %% is the Definitions section of the yacc
 * input file. Here is where you declare tokens and types, add precedence
 * and associativity options, and so on.
 */
 
/* yylval 
 * ------
 * Here we define the type of the yylval global variable that is used by
 * the scanner to store attibute information about the token just scanned
 * and thus communicate that information to the parser. 
 *
 * pp2: You will need to add new fields to this union as you add different 
 *      attributes to your non-terminal symbols.
 */
%union {
    int integerConstant;
    bool boolConstant;
    char *stringConstant;
    double doubleConstant;
    char identifier[MaxIdentLen+1]; // +1 for terminating null
    Decl *decl;
    List<Decl*> *declList;

    Type *type;
    NamedType *nameType;
    List<NamedType*> *nameTypeList;
    FnDecl *fDecl;
    VarDecl *var;
    List<VarDecl*> *varList;
    Expr *expr;
    List<Expr*> *exprList;
    Stmt *stmt;
    List<Stmt*> *stmtList;
    LValue *lvalue;
    Case *caseX;
    List<Case*> *caseList;
    DefaultStmt *defaultStmt;
      


}


/* Tokens
 * ------
 * Here we tell yacc about all the token types that we are using.
 * Bison will assign unique numbers to these and export the #define
 * in the generated y.tab.h header file.
 */
%token   T_Void T_Bool T_Int T_Double T_String T_Class 
%token   T_LessEqual T_GreaterEqual T_Equal T_NotEqual T_Dims
%token   T_And T_Or T_Null T_Extends T_This T_Interface T_Implements
%token   T_While T_For T_If T_Else T_Return T_Break
%token   T_New T_NewArray T_Print T_ReadInteger T_ReadLine
%token   T_Increm T_Decrem T_Switch T_Case T_Default 


%token   <identifier> T_Identifier
%token   <stringConstant> T_StringConstant 
%token   <integerConstant> T_IntConstant
%token   <doubleConstant> T_DoubleConstant
%token   <boolConstant> T_BoolConstant


/* Non-terminal types
 * ------------------
 * In order for yacc to assign/access the correct field of $$, $1, we
 * must to declare which field is appropriate for the non-terminal.
 * As an example, this first type declaration establishes that the DeclList
 * non-terminal uses the field named "declList" in the yylval union. This
 * means that when we are setting $$ for a reduction for DeclList ore reading
 * $n which corresponds to a DeclList nonterminal we are accessing the field
 * of the union named "declList" which is of type List<Decl*>.
 * pp2: You'll need to add many of these of your own.
 */



%type <decl>         ClassDecl Decl Field InterfaceDecl
%type <declList>     FieldList DeclList InterfaceList
%type <expr>         Expr ExprX Constant Call
%type <lvalue>       LValue
%type <type>         Type 
%type <nameType>     NameType
%type <nameTypeList> Implement NameTypeList
%type <fDecl>        FnDecl FnHeader
%type <var>          Variable VarDecl
%type <varList>      VarDeclList Formals FormalList
%type <exprList>     Actuals ExprList
%type <stmt>         Stmt StmtBlock Else SwitchStmt
%type <stmtList>     StmtList
%type <caseX>        Case 
%type <caseList>     CaseList
%type <defaultStmt>  DefaultStmt

%left      ','
%left      '='
%left      ':'
%left      T_Or
%left      T_And 
%nonassoc  T_Equal T_NotEqual
%nonassoc  '<' '>' T_LessEqual T_GreaterEqual
%left      '+' '-'
%left      '*' '/' '%'  
%nonassoc  '!' T_UnaryMinus T_Increm T_Decrem
%nonassoc  '.' '['
%nonassoc  T_Lower_Than_Else
%nonassoc  T_Else

%%
/* Rules
 * -----
 * All productions and actions should be placed between the start and stop
 * %% markers which delimit the Rules section.
	 
 */
Program   :    DeclList            { 
                                      @1; 
                                      /* pp2: The @1 is needed to convince 
                                       * yacc to set up yylloc. You can remove 
                                       * it once you have other uses of @n*/
                                      Program *program = new Program($1);
                                      // if no errors, advance to next phase
                                      if (ReportError::NumErrors() == 0) 
                                          program->Print(0);
                                    }
          ;

DeclList  :    DeclList Decl        { ($$=$1)->Append($2); }
          |    Decl                 { ($$ = new List<Decl*>)->Append($1); }
          ;


Decl      :    ClassDecl
          |    FnDecl               { $$=$1; }
          |    VarDecl              { $$=$1; }
          |    InterfaceDecl 
          ;

VarDecl   :    Variable ';' 
          ;

VarDeclList  :    VarDeclList VarDecl     { ($$=$1)->Append($2); }
             |                            { $$ = new List<VarDecl*>; }
             ;

Variable  :    Type T_Identifier    { $$ = new VarDecl(new Identifier(@2, $2), $1); }
          ;

Type      :    T_Int                { $$ = Type::intType; }
          |    T_Bool               { $$ = Type::boolType; }
          |    T_String             { $$ = Type::stringType; }
          |    T_Double             { $$ = Type::doubleType; }
          |    T_Identifier         { $$ = new NamedType(new Identifier(@1,$1)); }
          |    Type T_Dims          { $$ = new ArrayType(Join(@1, @2), $1); }
          ;

InterfaceDecl  :    T_Interface T_Identifier '{' InterfaceList '}'     { $$ = new InterfaceDecl(new Identifier(@2, $2), $4); }
               ; 

InterfaceList  :    InterfaceList FnHeader ';'     { ($$=$1)->Append($2); }
               |                                   { $$ = new List<Decl*>(); }
               ;

ClassDecl  :    T_Class T_Identifier NameType Implement '{' FieldList '}'      { $$ = new ClassDecl(new Identifier(@2, $2), $3, $4, $6); }
           ; 
                
NameType    :    T_Extends T_Identifier       { $$ = new NamedType(new Identifier(@2, $2)); }
            |                                 { $$ = NULL; }
            ;

Implement   :    T_Implements NameTypeList      { $$ = $2; }
            |                                   { $$ = new List<NamedType*>; }
            ;

NameTypeList   :    NameTypeList ',' T_Identifier        { ($$=$1)->Append(new NamedType(new Identifier(@3, $3))); }
               |    T_Identifier                         { ($$=new List<NamedType*>)->Append(new NamedType(new Identifier(@1, $1))); }
               ;

FieldList  :    FieldList Field      { ($$=$1)->Append($2); }
           |                         { $$ = new List<Decl*>(); }
           ;

Field     :    VarDecl              { $$ = $1; }
          |    FnDecl               { $$ = $1; }
          ;
          

FnHeader  :    Type T_Identifier '(' Formals ')'      { $$ = new FnDecl(new Identifier(@2, $2), $1, $4); }
          |    T_Void T_Identifier '(' Formals ')'    { $$ = new FnDecl(new Identifier(@2, $2), Type::voidType, $4); }
          ;

Formals   :    FormalList           { $$ = $1; }
          |                         { $$ = new List<VarDecl*>; }
          ;

FormalList  :    FormalList ',' Variable       { ($$=$1)->Append($3); }
            |    Variable                      { ($$ = new List<VarDecl*>)->Append($1); }
            ;

FnDecl    :    FnHeader StmtBlock   { ($$=$1)->SetFunctionBody($2); }
          ;

StmtBlock   :    '{' VarDeclList StmtList '}'     { $$ = new StmtBlock($2, $3); }
            ;

StmtList  :    Stmt StmtList        { $$ = $2; $$->InsertAt($1, 0); }
          |                         { $$ = new List<Stmt*>; }
          ;

Stmt      :    ExprX ';'                                            { $$ = $1; }
          |    T_For '(' ExprX ';' Expr ';' ExprX ')' Stmt        { $$ = new ForStmt($3, $5, $7, $9); }
          |    T_If '(' Expr ')' Stmt Else                          { $$ = new IfStmt($3, $5, $6); }
          |    T_While '(' Expr ')' Stmt                            { $$ = new WhileStmt($3, $5); }
          |    T_Return Expr ';'                                    { $$ = new ReturnStmt(@2, $2); }
          |    T_Return ';'                                         { $$ = new ReturnStmt(@1, new EmptyExpr()); }
          |    T_Break ';'                                          { $$ = new BreakStmt(@1); }
          |    T_Print '(' ExprList ')' ';'                         { $$ = new PrintStmt($3); }
          |    StmtBlock
          |    SwitchStmt           
          ;

ExprX     :    Expr                 { $$ = $1; }
          |                         { $$ = new EmptyExpr(); }
          ;

Expr      :    Expr '+' Expr                         { $$ = new ArithmeticExpr($1, new Operator(@2, "+"), $3); }
          |    Expr '-' Expr                         { $$ = new ArithmeticExpr($1, new Operator(@2, "-"), $3); }
          |    Expr '*' Expr                         { $$ = new ArithmeticExpr($1, new Operator(@2,"*"), $3); }
          |    Expr '/' Expr                         { $$ = new ArithmeticExpr($1, new Operator(@2,"/"), $3); }
          |    Expr '%' Expr                         { $$ = new ArithmeticExpr($1, new Operator(@2,"%"), $3); }
          |    Expr '<' Expr                         { $$ = new RelationalExpr($1, new Operator(@2,"<"), $3); }
          |    Expr '>' Expr                         { $$ = new RelationalExpr($1, new Operator(@2,">"), $3); }
          |    Expr T_Equal Expr                     { $$ = new EqualityExpr($1, new Operator(@2,"=="), $3); }
          |    Expr T_NotEqual Expr                  { $$ = new EqualityExpr($1, new Operator(@2,"!="), $3); }
          |    Expr T_LessEqual Expr                 { $$ = new RelationalExpr($1, new Operator(@2,"<="), $3); }
          |    Expr T_GreaterEqual Expr              { $$ = new RelationalExpr($1, new Operator(@2,">="), $3); }
          |    Expr T_And Expr                       { $$ = new LogicalExpr($1, new Operator(@2,"&&"), $3); }
          |    Expr T_Or Expr                        { $$ = new LogicalExpr($1, new Operator(@2,"||"), $3); }
          |    '(' Expr ')'                          { $$ = $2; }
          |    '-' Expr  %prec T_UnaryMinus          { $$ = new ArithmeticExpr(new Operator(@1,"-"), $2); }
          |    '!' Expr                              { $$ = new LogicalExpr(new Operator(@1,"!"), $2); }
          |    T_ReadInteger '(' ')'                 { $$ = new ReadIntegerExpr(Join(@1,@3)); }
          |    T_ReadLine '(' ')'                    { $$ = new ReadLineExpr(Join(@1,@3)); }
          |    T_New '(' T_Identifier ')'            { $$ = new NewExpr(Join(@1,@4),new NamedType(new Identifier(@3,$3))); }
          |    T_New T_Identifier                    { $$ = new NewExpr(Join(@1,@2),new NamedType(new Identifier(@2,$2))); }
          |    T_NewArray '(' Expr ',' Type ')'      { $$ = new NewArrayExpr(Join(@1,@6),$3, $5); }
          |    T_This                                { $$ = new This(@1); }
          |    LValue                                { $$ = $1; }
          |    Call
          |    Constant
          |    LValue '=' Expr                       { $$ = new AssignExpr($1, new Operator(@2,"="), $3); }
          |    Expr T_Increm                         { $$ = new PostfixExpr($1, new Operator(@2, "++")); }
          |    Expr T_Decrem                         { $$ = new PostfixExpr($1, new Operator(@2, "--")); }
          ;

ExprList  :    ExprList ',' Expr    { ($$=$1)->Append($3); }
          |    Expr                 { ($$ = new List<Expr*>)->Append($1); }
          ;

Constant  :    T_IntConstant        { $$ = new IntConstant(@1,$1); }
          |    T_BoolConstant       { $$ = new BoolConstant(@1,$1); }
          |    T_DoubleConstant     { $$ = new DoubleConstant(@1,$1); }
          |    T_StringConstant     { $$ = new StringConstant(@1,$1); }
          |    T_Null               { $$ = new NullConstant(@1); }
          ;

Actuals   :    ExprList             { $$ = $1; }
          |                         { $$ = new List<Expr*>; }
          ;

Else      :    T_Else Stmt          { $$ = $2; }
          |    %prec T_Lower_Than_Else   { $$ = NULL; }
          ;

LValue    :    T_Identifier          { $$ = new FieldAccess(NULL, new Identifier(@1, $1)); }
          |    Expr '.' T_Identifier { $$ = new FieldAccess($1, new Identifier(@3, $3)); }
          |    Expr '[' Expr ']'     { $$ = new ArrayAccess(Join(@1, @4), $1, $3); }
          ;

Call      :    T_Identifier '(' Actuals ')'              { $$ = new Call(Join(@1,@4), NULL, new Identifier(@1,$1), $3); }
          |    Expr '.' T_Identifier '(' Actuals ')'     { $$ = new Call(Join(@1,@6), $1, new Identifier(@3,$3), $5); }
          ;


SwitchStmt  :    T_Switch '(' Expr ')' '{' CaseList DefaultStmt '}'    	{ $$ = new SwitchStmt($3,$6,$7);}
            | T_Switch '(' Expr ')' '{' CaseList '}'       	        { $$ = new SwitchStmt($3,$6,NULL);}  
            |  T_Switch '(' Expr ')' '{' DefaultStmt '}'	        { List<Case*> *emptyCL = new List<Case*>;
		                                                          $$ = new SwitchStmt($3,emptyCL,$6);}
	    | T_Switch '(' Expr ')' '{' '}'	                	{List<Case*> *emptyCL = new List<Case*>;
                                                                         $$ = new SwitchStmt($3,emptyCL,NULL);}
            ;

CaseList  :    CaseList Case        { ($$=$1)->Append($2); }
          |    Case                 { ($$ = new List<Case*>)->Append($1); }
          ;


Case      :    T_Case T_IntConstant ':' StmtList     { $$ = new Case(new IntConstant(@2, $2), $4); }
          ;

DefaultStmt	:  T_Default ':' StmtList		{ $$ = new DefaultStmt($3);}
                ;


%%

/* The closing %% above marks the end of the Rules section and the beginning
 * of the User Subroutines section. All text from here to the end of the
 * file is copied verbatim to the end of the generated y.tab.c file.
 * This section is where you put definitions of helper functions.
 */

/* Function: InitParser
 * --------------------
 * This function will be called before any calls to yyparse().  It is designed
 * to give you an opportunity to do anything that must be done to initialize
 * the parser (set global variables, configure starting state, etc.). One
 * thing it already does for you is assign the value of the global variable
 * yydebug that controls whether yacc prints debugging information about
 * parser actions (shift/reduce) and contents of state stack during parser.
 * If set to false, no information is printed. Setting it to true will give
 * you a running trail that might be helpful when debugging your parser.
 * Please be sure the variable is set to false when submitting your final
 * version.
 */
void InitParser()
{
   PrintDebug("parser", "Initializing parser");
   yydebug = false;
}
