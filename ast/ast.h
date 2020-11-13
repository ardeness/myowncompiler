#ifndef _AST_H_
#define _AST_H_
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
typedef struct _A_relop			*A_relop;
typedef struct _A_additiveexpression	*A_additiveexpression;
typedef struct _A_addop			*A_addop;
typedef struct _A_term			*A_term;
typedef struct _A_mulop			*A_mulop;
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
			struct tokentype size;
		} typespecifierNUM2vardeclaration;
	} u;
};

struct _A_typespecifier
{
	struct tokentype typespecifier;
};

struct _A_fundeclaration
{
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
			A_relop relop;
			A_additiveexpression additiveexpression2;
			} additiveexpressionrelop2simpleexpression;
		struct {
			A_additiveexpression additiveexpression;
			} additiveexpression2simpleexpression;
		} u;
};

struct _A_relop
{
	struct tokentype relop;
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
			A_addop addop;
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
			A_mulop mulop;
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

struct _A_mulop
{
	struct tokentype mulop;
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
			struct tokentype num;
			} num2factor;
		} u;
};

struct _A_call
{
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
A_vardeclaration	F_typespecifierNUM2vardeclaration(A_typespecifier typespecifier, char *id, char *size);

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

A_simpleexpression	F_additiveexpressionrelop2simpleexpression(A_additiveexpression additiveexpression1, A_relop relop, A_additiveexpression additiveexpression2);
A_simpleexpression	F_additiveexpression2simpleexpression(A_additiveexpression additiveexpression);

A_relop			F_relop(char *relop, int tokennumber);

A_additiveexpression	F_additiveexpression2additiveexpression(A_additiveexpression additiveexpression, A_addop addop, A_term term);
A_additiveexpression	F_term2additiveexpression(A_term term);

A_addop			F_addop(char *addop, int tokennumber);

A_term			F_term2term(A_term term, A_mulop mulop, A_factor factor);
A_term			F_factor2term(A_factor factor);
A_term			F_uminus2term(A_factor factor);

A_mulop			F_mulop(char *mulop, int tokennumber);

A_factor		F_expression2factor(A_expression expression);
A_factor		F_var2factor(A_var var);
A_factor		F_call2factor(A_call call);
A_factor		F_num2factor(char *num);

A_call			F_id2call(char *id, A_args args);

A_args			F_arglist2args(A_arglist arglist);
A_args			F_null2args();

A_arglist		F_arglist2arglist(A_arglist arglist, A_expression expression);
A_arglist		F_expression2arglist(A_expression expression);
#endif
