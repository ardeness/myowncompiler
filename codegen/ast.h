#ifndef _AST_H_
#define _AST_H_

#define STRING_BUCKET_SIZE 203
#define SHT_BUCKET_SIZE 203

#define retFO -1
#define initFO -2
#define ofpFO 0

#define ZERO 3
#define AC 4
#define GP 5
#define FP 6
#define PC 7

#define R0 0
#define R1 1
#define R2 2
#define R3 3
#define R4 4
#define R5 5
#define R6 6

enum OPCODE {HALT, IN, OUT, CADD, CSUB, CMUL, CDIV, LD, LDA, LDC, ST, JLT, JLE, JGE, JGT, JEQ, JNE};
typedef struct _Instruction* Instruction;

struct _Instruction
{
	int offset;
	int opcode;
	int r;
	int s;
	int t;
	Instruction branchtarget;
	Instruction prev;
	Instruction next;
};

typedef struct _InstructionPair* InstructionPair;

struct _InstructionPair
{
	Instruction head;
	Instruction tail;
};

typedef struct Ty_ty_ *Ty_ty;
typedef struct Ty_tyList_ *Ty_tyList;

struct Ty_ty_
{
	enum
	{
		Ty_int,
		Ty_array,
		Ty_name,
		Ty_void
	} kind;

	union
	{
		Ty_ty array;
//		struct {
//			S_symbol sym;
//			Ty_ty ty;
//		} name;
	} u;
};

struct Ty_tyList_
{
	Ty_ty head;
	Ty_tyList tail;
};

typedef struct StringBucket_* StringBucket;
struct StringBucket_
{
	char *string;
	StringBucket prev;
	StringBucket next;
};

typedef struct Symbol_* Symbol;
struct Symbol_
{
	int ac_register;
	int offset;
	int index;
	int size;
	int scope;
	char *name;

	Instruction head;
	Instruction tail;
	enum
	{
		Var,
		Fun
	} kind;

	union
	{
		struct {
			Ty_tyList tl;
		} function;
		struct {
			Ty_ty t;
		} variable;
	} u;
	Symbol prev;
	Symbol next;
};


typedef struct SymbolContainer_* SymbolContainer;
struct SymbolContainer_
{
	Symbol s;
	SymbolContainer prev;
	SymbolContainer next;
};

struct tokentype
{
	int tokennumber;
	char *tokenvalue;
};

/*
typedef struct NodeType
{
	struct tokentype token;
	enum {terminal, nonterminal} noderep;
	struct nodeType *child;
	struct nodeType *brother;
} Node;
*/

typedef enum {TINT, TARRAY, TVOID, TBOOL, TUNKNOWN} TYPE;

typedef struct _A_program		*A_program;
typedef struct _A_declarationlist	*A_declarationlist;
typedef struct _A_declaration		*A_declaration;
typedef struct _A_vardeclaration	*A_vardeclaration;
typedef struct _A_typespecifier		*A_typespecifier;
typedef struct _A_fundeclaration	*A_fundeclaration;
typedef struct _A_params		*A_params;
typedef struct _A_paramlist		*A_paramlist;
typedef struct _A_param			*A_param;
typedef struct _A_compoundstmt		*A_compoundstmt;
typedef struct _A_localdeclarations	*A_localdeclarations;
typedef struct _A_statementlist		*A_statementlist;
typedef struct _A_statement		*A_statement;
typedef struct _A_expressionstmt	*A_expressionstmt;
typedef struct _A_selectionstmt		*A_selectionstmt;
typedef struct _A_iterationstmt		*A_iterationstmt;
typedef struct _A_returnstmt		*A_returnstmt;
typedef struct _A_expression		*A_expression;
typedef struct _A_var			*A_var;
typedef struct _A_simpleexpression	*A_simpleexpression;
typedef struct _A_additiveexpression	*A_additiveexpression;
typedef struct _A_term			*A_term;
typedef struct _A_factor		*A_factor;
typedef struct _A_call			*A_call;
typedef struct _A_args			*A_args;
typedef struct _A_arglist		*A_arglist;

struct _A_program
{

	enum {
		Declarationlist2program
		} kind;

	union {
		struct {
			A_declarationlist	declarationlist;
		} declarationlist2program;
	} u;
};

struct _A_declarationlist
{

	enum {
		Declarationlist2declarationlist,
		Declaration2declarationlist
		} kind;

	union {
		struct {
			A_declarationlist	declarationlist;
			A_declaration		declaration;
		} declarationlist2declarationlist;
		struct {
			A_declaration	declaration;
		} declaration2declarationlist;
	} u;
};

struct _A_declaration
{

	enum {
		Vardeclaration2declaration,
		Fundeclaration2declaration
		} kind;

	union {
		struct {
			A_vardeclaration vardeclaration;
		} vardeclaration2declaration;
		struct {
			A_fundeclaration fundeclaration;
		} fundeclaration2declaration;
	} u;
};

struct _A_vardeclaration
{

	enum {
		Typespecifier2vardeclaration,
		TypespecifierNUM2vardeclaration
		} kind;

	union {
		struct {
			A_typespecifier typespecifier;
			struct tokentype id;
		} typespecifier2vardeclaration;
		struct {
			A_typespecifier typespecifier;
			struct tokentype id;
			int size;
		} typespecifierNUM2vardeclaration;
	} u;
};

struct _A_typespecifier
{
	struct tokentype typespecifier;
};

struct _A_fundeclaration
{
	Symbol s;
	int stacksize;
	enum {
		Typespecifier2fundeclaration
	} kind;

	union {
		struct {
			A_typespecifier typespecifier;
			struct tokentype id;
			A_params params;
			A_compoundstmt compoundstmt;
		} typespecifier2fundeclaration;
	} u;
};

struct _A_params
{

	enum {
		Paramlist2params,
		Void2params
		} kind;

	union {
		struct {
			A_paramlist paramlist;
			} paramlist2params;
		} u;
};

struct _A_paramlist
{

	enum {
		Paramlist2paramlist,
		Param2paramlist
		} kind;

	union {
		struct {
			A_paramlist paramlist;
			A_param param;
			} paramlist2paramlist;
		struct {
			A_param param;
			} param2paramlist;
		} u;
};

struct _A_param
{

	enum {
		Typespecifier2param,
		TypespecifierArray2param,
		Null2param
		} kind;

	union {
		struct {
			A_typespecifier typespecifier;
			struct tokentype id;
			} typespecifier2param;
		struct {
			A_typespecifier typespecifier;
			struct tokentype id;
			} typespecifierArray2param;
		} u;
};

struct _A_compoundstmt
{

	enum {
		Localdeclarations2compoundstmt
		} kind;

	union {
		struct {
			A_localdeclarations localdeclarations;
			A_statementlist statementlist;
			} localdeclarations2compoundstmt;
		} u;
};

struct _A_localdeclarations
{

	enum {
		Localdeclarations2localdeclarations,
		Null2localdeclarations
		} kind;

	union {
		struct {
			A_localdeclarations localdeclarations;
			A_vardeclaration vardeclaration;
			} localdeclarations2localdeclarations;
		} u;
};

struct _A_statementlist
{

	enum {
		Statementlist2statementlist,
		Null2statementlist
		} kind;

	union {
		struct {
			A_statementlist statementlist;
			A_statement statement;
			} statementlist2statementlist;
		} u;
};

struct _A_statement
{

	enum {
		Expressionstmt2statement,
		Compoundstmt2statement,
		Selectionstmt2statement,
		Iterationstmt2statement,
		Returnstmt2statement
		} kind;

	union {
		struct {
			A_expressionstmt expressionstmt;
			} expressionstmt2statement;
		struct {
			A_compoundstmt compoundstmt;
			} compoundstmt2statement;
		struct {
			A_selectionstmt selectionstmt;
			} selectionstmt2statement;
		struct {
			A_iterationstmt iterationstmt;
			} iterationstmt2statement;
		struct {
			A_returnstmt returnstmt;
			} returnstmt2statement;
		} u;
};

struct _A_expressionstmt
{

	enum {
		Expression2expressionstmt,
		Null2expressionstmt
		} kind;

	union {
		struct {
			A_expression expression;
			} expression2expressionstmt;
		} u;
};

struct _A_selectionstmt
{

	enum {
		If2selectionstmt,
		Ifelse2selectionstmt
		} kind;

	union {
		struct {
			A_expression expression;
			A_statement statement;
			} if2selectionstmt;
		struct {
			A_expression expression;
			A_statement statement1;
			A_statement statement2;
			} ifelse2selectionstmt;
		} u;
};

struct _A_iterationstmt
{

	enum {
		While2iterationstmt,
		For2iterationstmt
		} kind;

	union {
		struct {
			A_expression expression;
			A_statement statement;
			} while2iterationstmt;
		struct {
			A_expression expression1;
			A_expression expression2;
			A_expression expression3;
			A_statement statement;
			} for2iterationstmt;
		} u;
};

struct _A_returnstmt
{

	enum {
		Null2returnstmt,
		Expression2returnstmt
		} kind;

	union {
		struct {
			A_expression expression;
			} expression2returnstmt;
		} u;
};

struct _A_expression
{

	enum {
		Var2expression,
		Simpleexpression2expression
		} kind;

	union {
		struct {
			A_var var;
			A_expression expression;
			} var2expression;
		struct {
			A_simpleexpression simpleexpression;
			} simpleexpression2expression;
		} u;
};

struct _A_var
{
	Symbol s;
	enum {
		Id2var,
		Array2var
		} kind;

	union {
		struct {
			struct tokentype id;
			} id2var;
		struct {
			struct tokentype id;
			A_expression expression;
			} array2var;
		} u;
};

struct _A_simpleexpression
{

	enum {
		Additiveexpressionrelop2simpleexpression,
		Additiveexpression2simpleexpression
		} kind;

	union {
		struct {
			A_additiveexpression additiveexpression1;
			int relop;
			A_additiveexpression additiveexpression2;
			} additiveexpressionrelop2simpleexpression;
		struct {
			A_additiveexpression additiveexpression;
			} additiveexpression2simpleexpression;
		} u;
};

struct _A_additiveexpression
{

	enum {
		Additiveexpression2additiveexpression,
		Term2additiveexpression
		} kind;

	union {
		struct {
			A_additiveexpression additiveexpression;
			int addop;
			A_term term;
			} additiveexpression2additiveexpression;
		struct {
			A_term term;
			} term2additiveexpression;
		} u;
};

struct _A_addop
{

	struct tokentype addop;
};

struct _A_term
{

	enum {
		Term2term,
		Factor2term,
		Uminus2term
		} kind;

	union {
		struct {
			A_term term;
			int mulop;
			A_factor factor;
			} term2term;
		struct {
			A_factor factor;
			} factor2term;
		struct {
			A_factor factor;
			} uminus2term;
		} u;
};

struct _A_factor
{

	enum {
		Expression2factor,
		Var2factor,
		Call2factor,
		Num2factor
		} kind;

	union {
		struct {
			A_expression expression;
			} expression2factor;
		struct {
			A_var var;
			} var2factor;
		struct {
			A_call call;
			} call2factor;
		struct {
			int num;
			} num2factor;
		} u;
};

struct _A_call
{
	Symbol s;
	enum {
		Id2call
		} kind;

	union {
		struct {
			struct tokentype id;
			A_args args;
			} id2call;
		} u;
};

struct _A_args
{

	enum {
		Arglist2args,
		Null2args
		} kind;

	union {
		struct {
			A_arglist arglist;
			} arglist2args;
		} u;
};

struct _A_arglist
{

	enum {
		Arglist2arglist,
		Expression2arglist
		} kind;

	union {
		struct {
			A_arglist arglist;
			A_expression expression;
			} arglist2arglist;
		struct {
			A_expression expression;
			} expression2arglist;
		} u;
};

// function declarations
A_program		F_declarationlist2program(A_declarationlist declarationlist);
A_declarationlist	F_declarationlist2declarationlist(A_declarationlist declarationlist, A_declaration declaration);
A_declarationlist	F_declaration2declarationlist(A_declaration declaration);

A_declaration		F_vardeclaration2declaration(A_vardeclaration vardeclaration);
A_declaration		F_fundeclaration2declaration(A_fundeclaration fundeclaration);

A_vardeclaration	F_typespecifier2vardeclaration(A_typespecifier typespecifier, char *id);
A_vardeclaration	F_typespecifierNUM2vardeclaration(A_typespecifier typespecifier, char *id, int size);

A_typespecifier		F_typespecifier(char *type, int tokennumber);

A_fundeclaration	F_typespecifier2fundeclaration(A_typespecifier typespecifier, char *id, A_params params, A_compoundstmt compoundstmt);

A_params		F_paramlist2params(A_paramlist paramlist);
A_params		F_void2params();

A_paramlist		F_paramlist2paramlist(A_paramlist paramlist, A_param param);
A_paramlist		F_param2paramlist(A_param param);

A_param			F_typespecifier2param(A_typespecifier typespecifier, char *id);
A_param			F_typespecifierArray2param(A_typespecifier typespecifier, char *id);
A_param			F_null2param();

A_compoundstmt		F_localdeclarations2compoundstmt(A_localdeclarations localdeclarations, A_statementlist statementlist);

A_localdeclarations	F_localdeclarations2localdeclarations(A_localdeclarations localdeclarations, A_vardeclaration vardeclaration);
A_localdeclarations	F_null2localdeclaration();

A_statementlist		F_statementlist2statementlist(A_statementlist statementlist, A_statement statement);
A_statementlist		F_null2statementlist();

A_statement		F_expressionstmt2statement(A_expressionstmt expressionstmt);
A_statement		F_compoundstmt2statement(A_compoundstmt compoundstmt);
A_statement		F_selectionstmt2statement(A_selectionstmt selectionstmt);
A_statement		F_iterationstmt2statement(A_iterationstmt iterationstmt);
A_statement		F_returnstmt2statement(A_returnstmt returnstmt);

A_expressionstmt	F_expression2expressionstmt(A_expression expression);
A_expressionstmt	F_null2expressionstmt();

A_selectionstmt		F_if2selectionstmt(A_expression expression, A_statement statement);
A_selectionstmt		F_ifelse2selectionstmt(A_expression expression, A_statement statement1, A_statement statement2);

A_iterationstmt		F_while2iterationstmt(A_expression expression, A_statement statement);
A_iterationstmt		F_for2iterationstmt(A_expression expression1, A_expression expression2, A_expression expression3, A_statement statement);

A_returnstmt		F_null2returnstmt();
A_returnstmt		F_expression2returnstmt(A_expression expression);

A_expression		F_var2expression(A_var var, A_expression expression);
A_expression		F_simpleexpression2expression(A_simpleexpression simpleexpression);

A_var			F_id2var(char *id);
A_var			F_array2var(char *id, A_expression expression);

A_simpleexpression	F_additiveexpressionrelop2simpleexpression(A_additiveexpression additiveexpression1, int relop, A_additiveexpression additiveexpression2);
A_simpleexpression	F_additiveexpression2simpleexpression(A_additiveexpression additiveexpression);


A_additiveexpression	F_additiveexpression2additiveexpression(A_additiveexpression additiveexpression, int addop, A_term term);
A_additiveexpression	F_term2additiveexpression(A_term term);


A_term			F_term2term(A_term term, int mulop, A_factor factor);
A_term			F_factor2term(A_factor factor);
A_term			F_uminus2term(A_factor factor);


A_factor		F_expression2factor(A_expression expression);
A_factor		F_var2factor(A_var var);
A_factor		F_call2factor(A_call call);
A_factor		F_num2factor(int num);

A_call			F_id2call(char *id, A_args args);

A_args			F_arglist2args(A_arglist arglist);
A_args			F_null2args();

A_arglist		F_arglist2arglist(A_arglist arglist, A_expression expression);
A_arglist		F_expression2arglist(A_expression expression);

Ty_ty Ty_Int();
Ty_ty Ty_Void();

Ty_ty Ty_Array(Ty_ty ty);
//Ty_ty Ty_Name(S_symbol sym, Ty_ty ty);
Ty_tyList Ty_TyList(Ty_ty head, Ty_tyList tail);

char* Ty_print(Ty_ty t);
int TyList_compare(Ty_tyList list1, Ty_tyList list2);

void S_program(A_program program);
void S_declarationlist(A_declarationlist declarationlist);
void S_declaration(A_declaration declaration);
Ty_ty S_vardeclaration(A_vardeclaration vardeclaration);
Ty_ty S_typespecifier(A_typespecifier typespecifier);
void S_fundeclaration(A_fundeclaration fundeclaration);
Ty_tyList S_params(A_params params);
Ty_tyList S_paramlist(A_paramlist paramlist);
Ty_ty S_param(A_param param);
void S_compoundstmt(A_compoundstmt compoundstmt);
void S_localdeclarations(A_localdeclarations localdeclarations);
void S_statementlist(A_statementlist statementlist);
void S_statement(A_statement statement);
void S_expressionstmt(A_expressionstmt expressionstmt);
void S_selectionstmt(A_selectionstmt selectionstmt);
void S_iterationstmt(A_iterationstmt iterationstmt);
void S_returnstmt(A_returnstmt returnstmt);
Ty_ty S_expression(A_expression expression);
Ty_ty S_var(A_var var);
Ty_ty S_simpleexpression(A_simpleexpression simpleexpression);
void S_relop(int relop);
Ty_ty S_additiveexpression(A_additiveexpression additiveexpression);
void S_addop(int addop);
Ty_ty S_term(A_term term);
void S_mulop(int mulop);
Ty_ty S_factor(A_factor factor);
Ty_ty S_call(A_call call);
Ty_tyList S_args(A_args args);
Ty_tyList S_arglist(A_arglist arglist);
char* String_insert(char* name);
Symbol S_lookup(char *name);
Symbol S_insert(Ty_ty t, char *name);
Symbol S_insertfunction(Ty_tyList tl, char *name);
void PopSymbolinScope(int scope);

InstructionPair C_program(A_program program);
InstructionPair C_declarationlist(A_declarationlist declarationlist);
InstructionPair C_declaration(A_declaration declaration);
InstructionPair C_vardeclaration(A_vardeclaration vardeclaration);
InstructionPair C_typespecifier(A_typespecifier typespecifier);
InstructionPair C_fundeclaration(A_fundeclaration fundeclaration);
InstructionPair C_params(A_params params);
InstructionPair C_paramlist(A_paramlist paramlist);
InstructionPair C_param(A_param param);
InstructionPair C_compoundstmt(A_compoundstmt compoundstmt);
InstructionPair C_localdeclarations(A_localdeclarations localdeclarations);
InstructionPair C_statementlist(A_statementlist statementlist);
InstructionPair C_statement(A_statement statement);
InstructionPair C_expressionstmt(A_expressionstmt expressionstmt);
InstructionPair C_selectionstmt(A_selectionstmt selectionstmt);
InstructionPair C_iterationstmt(A_iterationstmt iterationstmt);
InstructionPair C_returnstmt(A_returnstmt returnstmt);
InstructionPair C_expression(A_expression expression);
InstructionPair C_var(A_var var);
InstructionPair C_simpleexpression(A_simpleexpression simpleexpression);
InstructionPair C_additiveexpression(A_additiveexpression additiveexpression);
InstructionPair C_term(A_term term);
InstructionPair C_factor(A_factor factor);
InstructionPair C_call(A_call call);
InstructionPair C_args(A_args args);
InstructionPair C_arglist(A_arglist arglist);

void AdjustInstruction(InstructionPair program);
void PrintCode(InstructionPair program);
void PrintInstruction(Instruction inst);
#endif
