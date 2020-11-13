%{
#include "ast.h"
#include "global.h"
#include <stdio.h>
extern char *yytext;
void print(int, char*);
int yylex(void);
void yyerror(char *s)
{
	printf("%s near line %d\n", s, linenumber);
}
%}
%union{
	char*			str;
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
	A_relop			relop;
	A_additiveexpression	additiveexpression;
	A_addop			addop;
	A_term			term;
	A_mulop			mulop;
	A_factor		factor;
	A_call			call;
	A_args			args;
	A_arglist		arglist;
}
%token <str>	NUM
%token <str>	ID
%token <str>	VOID INT
%token COMMA SEMICOLON LPAREN RPAREN LBRACKET RBRACKET LBRACE RBRACE IF ELSE WHILE FOR ASSIGN RETURN
%token <str>	ADD SUB MULT DIV
%token <str>	LESS LESSEQUAL GREAT GREATEQUAL EQUAL NOTEQUAL
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
%type <addop> addop
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
		{ print(1, "declarationlist to program"); $$ = F_declarationlist2program($1); }
	;

declarationlist : declarationlist declaration
			{ print(2, "declarationlist declaration to declarationlist"); $$ = F_declarationlist2declarationlist($1, $2);}
		| declaration
			{ print(3, "declaration to declarationlist"); $$ = F_declaration2declarationlist($1);}
		;

declaration : vardeclaration
			{ print(4, "vardeclaration to declaration"); $$= F_vardeclaration2declaration($1);}
	| fundeclaration
			{ print(5, "fundeclaration to declaration"); $$ = F_fundeclaration2declaration($1);}
	;

vardeclaration : typespecifier ID SEMICOLON
			{ print(6, "typespecifier ID SEMICOLON to vardeclaration"); $$ = F_typespecifier2vardeclaration($1, $2);}
		| typespecifier ID LBRACKET NUM RBRACKET SEMICOLON
			{ print(7, "typespecifier ID LBRACKET NUM RBRACKET SEMICOLON"); $$ = F_typespecifierNUM2vardeclaration($1, yytext, yytext);}
		;

typespecifier : INT
		{ print(7, "INT to typespecifier"); $$ = F_typespecifier("int", INT);}
		| VOID
		{ print(8, "VOID to typespecifire"); $$ = F_typespecifier("void", VOID);}
		;

fundeclaration : typespecifier ID LPAREN params RPAREN compoundstmt
		{ print(9, "typespecifier ID LPAREN params RPAREN compoundstmt to fundeclaration"); $$ = F_typespecifier2fundeclaration($1, $2, $4, $6);}
		;

params : paramlist
	{ print(10, "paramlist to params"); $$ = F_paramlist2params($1);}
	| VOID
	{ print(11, "VOID to params"); $$ = F_void2params();}
	;

paramlist : paramlist COMMA param
	{ print(12, "paramlist COMMA param to paramlist"); $$ = F_paramlist2paramlist($1, $3);}
	| param
	{ print(13, "param to paramlist"); $$ = F_param2paramlist($1);}
	;

param : typespecifier ID
	{ print(14, "typespecifier ID to param"); $$ = F_typespecifier2param($1, $2);}
	| typespecifier ID LBRACKET RBRACKET
	{ print(15, "typespecifier ID LBRACKET RBRACKET to param"); $$ = F_typespecifierArray2param($1, $2);}
	|
	{ print(16, "empty to param"); $$ = F_null2param();}
	;

compoundstmt : LBRACE localdeclarations statementlist RBRACE
		{ print(17, "LBRACE localdeclarations statementlist RBRACE to compoundstmt"); $$ = F_localdeclarations2compoundstmt($2, $3);}
		;

localdeclarations : localdeclarations vardeclaration
			{ print(18, "localdeclarations vardeclaration to localdeclarations"); $$ = F_localdeclarations2localdeclarations($1, $2);}
	|
	{ print(19, "empty to localdeclarations"); $$ = F_null2localdeclaration();}
	;

statementlist : statementlist statement
		{ print(19, "statementlist statement to statementlist"); $$ = F_statementlist2statementlist($1, $2);}
		|
		{ print(20, "empty to statementlist"); $$ = F_null2statementlist();}
		;

statement : expressionstmt
		{ print(21, "expressionstmt to statement"); $$ = F_expressionstmt2statement($1);}
	| compoundstmt
	{ print(22, "compoundstmt to statement"); $$ = F_compoundstmt2statement($1);}
	| selectionstmt
	{ print(23, "selectionstmt to statement"); $$ = F_selectionstmt2statement($1);}
	| iterationstmt
	{ print(23, "iterationstmt to statement"); $$ = F_iterationstmt2statement($1);}
	| returnstmt
	{ print(24, "returnstmt to statement"); $$ = F_returnstmt2statement($1);}
	;

expressionstmt : expression SEMICOLON
		{ print(25, "expression SEMICOLON to expressionstmt"); $$ = F_expression2expressionstmt($1);}
		| SEMICOLON
		{ print(26, "SEMICOLON to expressionstmt"); $$ = F_null2expressionstmt();}
		;

selectionstmt : IF LPAREN expression RPAREN statement
		{ print(27, "IF LPAREN expression RPAREN statement to selectionstmt"); $$ = F_if2selectionstmt($3, $5);}
		| IF LPAREN expression RPAREN statement ELSE statement
		{ print(28, "IF LPAREN expression RPAREN statement ELSE statement to selectionstmt"); $$ = F_ifelse2selectionstmt($3, $5, $7);}
		;

iterationstmt : WHILE LPAREN expression RPAREN statement
		{ print(29, "WHILE LPAREN expression RPAREN statement to iterationstmt"); $$ = F_while2iterationstmt($3, $5);}
		| FOR LPAREN expression SEMICOLON expression SEMICOLON expression RPAREN statement
		{ print(30, "FOR LPAREN expression COMMA expression COMMA expression RPAREN to iterationstmt"); $$ = F_for2iterationstmt($3, $5, $7, $9);}
		;

returnstmt : RETURN SEMICOLON
		{ print(31, "RETURN SEMICOLON to returnstmt"); $$ = F_null2returnstmt();}
		| RETURN expression SEMICOLON
		{ print(32, "RETURN expression SEMICOLON to returnstmt"); $$ = F_expression2returnstmt($2);}
		;

expression : var ASSIGN expression
		{ print(33, "var ASSIGN expression to expression"); $$ = F_var2expression($1, $3);}
		| simpleexpression
		{ print(34, "simpleexpression to expression"); $$ = F_simpleexpression2expression($1);}
		;

var : ID
	{ print(35, "ID to var"); $$ = F_id2var($1);}
	| ID LBRACKET expression RBRACKET
	{ print(36, "ID LBRACKET expression RBRACKET to var"); $$ = F_array2var($1, $3);}
	;

simpleexpression : additiveexpression relop additiveexpression
			{ print(37, "additiveexpression relop additiveexpression to simpleexpression"); $$ = F_additiveexpressionrelop2simpleexpression($1, $2, $3);}
		| additiveexpression
		{ print(38, "additiveexpression to simpleexpression"); $$ = F_additiveexpression2simpleexpression($1);}
		;

relop : LESSEQUAL
	{ print(39, "LESSEQUAL to relop"); $$ = F_relop("<=", LESSEQUAL);}
	| LESS
	{ print(40, "LESS to relop"); $$ = F_relop("<", LESS);}
	| GREAT
	{ print(41, "GREAT to relop"); $$ = F_relop(">", GREAT);}
	| GREATEQUAL
	{ print(42, "GREATEQUAL to relop"); $$ = F_relop(">=", GREATEQUAL);}
	| EQUAL
	{ print(43, "EQUAL to relop"); $$ = F_relop("==", EQUAL);}
	| NOTEQUAL
	{ print(44, "NOTEQUAL to relop"); $$ = F_relop("!=", NOTEQUAL);}
	;

additiveexpression : additiveexpression addop term
		{ print(45, "additiveexpression addop term to additiveexpression"); $$ = F_additiveexpression2additiveexpression($1, $2, $3);}
	| term
	{ print(46, "term to additiveexpression"); $$ = F_term2additiveexpression($1);}
	;

addop : ADD
	{ print(47, "ADD to addop"); $$ = F_addop("+", ADD);}
	| SUB
	{ print(48, "SUB to addop"); $$ = F_addop("-", SUB);}
	;

term : term mulop factor
	{ print(49, "term mulop factor to term"); $$ = F_term2term($1, $2, $3);}
	| factor
	{ print(50, "factor to term"); $$ = F_factor2term($1);}
	| SUB factor	%prec UMINUS
	{ print(100, "UMINUS factor to additiveexpression"); $$ = F_uminus2term($2);}
	;

mulop : MULT
	{ print(51, "MULT to mulop"); $$ = F_mulop("*", MULT);}
	| DIV
	{ print(52, "DIV to mulop"); $$ = F_mulop("/", DIV);}
	;

factor : LPAREN expression RPAREN
	{ print(53, "LPAREN expression RPAREN to factor"); $$ = F_expression2factor($2);}
	| var
	{ print(54, "var to factor"); $$ = F_var2factor($1);}
	| call
	{ print(55, "call to factor"); $$ = F_call2factor($1);}
	| NUM
	{ print(56, "NUM to factor"); $$ = F_num2factor($1);}
	;

call : ID LPAREN args RPAREN
	{ print(57, "ID LPAREN args RPAREN to call"); $$ = F_id2call($1, $3); }
	;

args : arglist
	{ print(58, "arglist to args"); $$ = F_arglist2args($1);}
	|
	{ print(59, "empty to args"); $$ = F_null2args();}
	;

arglist : arglist COMMA expression
	{ print(60, "arglist COMMA expression to arglist"); $$ = F_arglist2arglist($1, $3);}
	| expression
	{ print(61, "expression to arglist"); $$ = F_expression2arglist($1);}
	;
%%
int main()
{
	linenumber = 1;
	yyparse();
	return 0;
}

void print(int rulenumber, char *s)
{
	printf("rulenumber %d : %s\n", rulenumber, s);
}
