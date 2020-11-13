%{
#include "ast.h"
#include "global.h"
#include <stdio.h>
extern char *yytext;
A_program program;
void print(int, char*);
int yylex(void);
void yyerror(char *s)
{
	printf("%s near line %d\n", s, linenumber);
}
%}
%union{
	char*			str;
	int				num;
	A_program		program;
	A_declarationlist	declarationlist;
	A_declaration		declaration;
	A_vardeclaration	vardeclaration;
	A_typespecifier		typespecifier;
	A_fundeclaration	fundeclaration;
	A_params		params;
	A_paramlist		paramlist;
	A_param			param;
	A_compoundstmt		compoundstmt;
	A_localdeclarations	localdeclarations;
	A_statementlist		statementlist;
	A_statement		statement;
	A_expressionstmt	expressionstmt;
	A_selectionstmt		selectionstmt;
	A_iterationstmt		iterationstmt;
	A_returnstmt		returnstmt;
	A_expression		expression;
	A_var			var;
	A_simpleexpression	simpleexpression;
	int			relop;
	A_additiveexpression	additiveexpression;
	int			addop;
	A_term			term;
	int			mulop;
	A_factor		factor;
	A_call			call;
	A_args			args;
	A_arglist		arglist;
}
%token <num>	NUM
%token <str>	ID
%token <str>	VOID INT
%token COMMA SEMICOLON LPAREN RPAREN LBRACKET RBRACKET LBRACE RBRACE IF ELSE WHILE FOR ASSIGN RETURN
%token <num>	ADD SUB MULT DIV
%token <num>	LESS LESSEQUAL GREAT GREATEQUAL EQUAL NOTEQUAL
%type <program> program
%type <declarationlist> declarationlist
%type <declaration> declaration
%type <vardeclaration> vardeclaration
%type <typespecifier> typespecifier
%type <fundeclaration> fundeclaration
%type <params> params
%type <paramlist> paramlist
%type <param> param
%type <compoundstmt> compoundstmt
%type <localdeclarations> localdeclarations
%type <statementlist> statementlist
%type <statement> statement
%type <expressionstmt> expressionstmt
%type <selectionstmt> selectionstmt
%type <iterationstmt> iterationstmt
%type <returnstmt> returnstmt
%type <expression> expression
%type <var> var
%type <simpleexpression> simpleexpression
%type <relop> relop
%type <additiveexpression> additiveexpression
%type <relop> addop
%type <term> term
%type <mulop> mulop
%type <factor> factor
%type <call> call
%type <args> args
%type <arglist> arglist
%left ADD SUB MULT DIV
%right UMINUS
%nonassoc EQUAL NOTEQUAL LESS LESSEQUAL GREAT GREATEQUAL
%start program
%%
program : declarationlist
		{ $$ = F_declarationlist2program($1); program = $$;}
	;

declarationlist : declarationlist declaration
			{ $$ = F_declarationlist2declarationlist($1, $2);}
		| declaration
			{ $$ = F_declaration2declarationlist($1);}
		;

declaration : vardeclaration
			{ $$= F_vardeclaration2declaration($1);}
	| fundeclaration
			{ $$ = F_fundeclaration2declaration($1);}
	;

vardeclaration : typespecifier ID SEMICOLON
			{ $$ = F_typespecifier2vardeclaration($1, $2);}
		| typespecifier ID LBRACKET NUM RBRACKET SEMICOLON
			{ $$ = F_typespecifierNUM2vardeclaration($1, $2, $4);}
		;

typespecifier : INT
		{ $$ = F_typespecifier("int", INT);}
		| VOID
		{ $$ = F_typespecifier("void", VOID);}
		;

fundeclaration : typespecifier ID LPAREN params RPAREN compoundstmt
		{ $$ = F_typespecifier2fundeclaration($1, $2, $4, $6);}
		;

params : paramlist
	{ $$ = F_paramlist2params($1);}
	| VOID
	{ $$ = F_void2params();}
	;

paramlist : paramlist COMMA param
	{ $$ = F_paramlist2paramlist($1, $3);}
	| param
	{ $$ = F_param2paramlist($1);}
	;

param : typespecifier ID
	{ $$ = F_typespecifier2param($1, $2);}
	| typespecifier ID LBRACKET RBRACKET
	{ $$ = F_typespecifierArray2param($1, $2);}
	|
	{ $$ = F_null2param();}
	;

compoundstmt : LBRACE localdeclarations statementlist RBRACE
		{ $$ = F_localdeclarations2compoundstmt($2, $3);}
		;

localdeclarations : localdeclarations vardeclaration
			{ $$ = F_localdeclarations2localdeclarations($1, $2);}
	|
	{ $$ = F_null2localdeclaration();}
	;

statementlist : statementlist statement
		{ $$ = F_statementlist2statementlist($1, $2);}
		|
		{ $$ = F_null2statementlist();}
		;

statement : expressionstmt
		{ $$ = F_expressionstmt2statement($1);}
	| compoundstmt
	{ $$ = F_compoundstmt2statement($1);}
	| selectionstmt
	{ $$ = F_selectionstmt2statement($1);}
	| iterationstmt
	{ $$ = F_iterationstmt2statement($1);}
	| returnstmt
	{ $$ = F_returnstmt2statement($1);}
	;

expressionstmt : expression SEMICOLON
		{ $$ = F_expression2expressionstmt($1);}
		| SEMICOLON
		{ $$ = F_null2expressionstmt();}
		;

selectionstmt : IF LPAREN expression RPAREN statement
		{ $$ = F_if2selectionstmt($3, $5);}
		| IF LPAREN expression RPAREN statement ELSE statement
		{ $$ = F_ifelse2selectionstmt($3, $5, $7);}
		;

iterationstmt : WHILE LPAREN expression RPAREN statement
		{ $$ = F_while2iterationstmt($3, $5);}
		| FOR LPAREN expression SEMICOLON expression SEMICOLON expression RPAREN statement
		{ $$ = F_for2iterationstmt($3, $5, $7, $9);}
		;

returnstmt : RETURN SEMICOLON
		{ $$ = F_null2returnstmt();}
		| RETURN expression SEMICOLON
		{ $$ = F_expression2returnstmt($2);}
		;

expression : var ASSIGN expression
		{ $$ = F_var2expression($1, $3);}
		| simpleexpression
		{ $$ = F_simpleexpression2expression($1);}
		;

var : ID
	{ $$ = F_id2var($1);}
	| ID LBRACKET expression RBRACKET
	{ $$ = F_array2var($1, $3);}
	;

simpleexpression : additiveexpression relop additiveexpression
			{ $$ = F_additiveexpressionrelop2simpleexpression($1, $2, $3);}
		| additiveexpression
		{ $$ = F_additiveexpression2simpleexpression($1);}
		;

relop : LESSEQUAL
	{ $$ = LESSEQUAL;}
	| LESS
	{ $$ = LESS;}
	| GREAT
	{ $$ = GREAT;}
	| GREATEQUAL
	{ $$ = GREATEQUAL;}
	| EQUAL
	{ $$ = EQUAL;}
	| NOTEQUAL
	{ $$ = NOTEQUAL;}
	;

additiveexpression : additiveexpression addop term
		{ $$ = F_additiveexpression2additiveexpression($1, $2, $3);}
	| term
	{ $$ = F_term2additiveexpression($1);}
	;

addop : ADD
	{ $$ = ADD;}
	| SUB
	{ $$ = SUB;}
	;

term : term mulop factor
	{ $$ = F_term2term($1, $2, $3);}
	| factor
	{ $$ = F_factor2term($1);}
	| SUB factor	%prec UMINUS
	{ $$ = F_uminus2term($2);}
	;

mulop : MULT
	{ $$ = MULT;}
	| DIV
	{ $$ = DIV;}
	;

factor : LPAREN expression RPAREN
	{ $$ = F_expression2factor($2);}
	| var
	{ $$ = F_var2factor($1);}
	| call
	{ $$ = F_call2factor($1);}
	| NUM
	{ $$ = F_num2factor($1);}
	;

call : ID LPAREN args RPAREN
	{ $$ = F_id2call($1, $3); }
	;

args : arglist
	{ $$ = F_arglist2args($1);}
	|
	{ $$ = F_null2args();}
	;

arglist : arglist COMMA expression
	{ $$ = F_arglist2arglist($1, $3);}
	| expression
	{ $$ = F_expression2arglist($1);}
	;
%%
int main()
{
	linenumber = 1;
	yyparse();
	//S_program(program);
	return 0;
}

void print(int rulenumber, char *s)
{
	printf("rulenumber %d : %s\n", rulenumber, s);
}
