%{
#include "global.h"
#include <stdio.h>
void print(int, char*);
int yylex(void);
void yyerror(char *s)
{
	printf("%s near line %d\n", s, linenumber);
}
%}
%token COMMA SEMICOLON LPAREN RPAREN LBRACKET RBRACKET LBRACE RBRACE INT VOID ID NUM IF ELSE WHILE FOR ASSIGN RETURN
%token ADD SUB MULT DIV
%token LESS LESSEQUAL GREAT GREATEQUAL EQUAL NOTEQUAL
%left ADD SUB MULT DIV
%right UMINUS
%nonassoc EQUAL NOTEQUAL LESS LESSEQUAL GREAT GREATEQUAL
%start program
%%
program : declarationlist
		{ print(1, "declarationlist to program"); }
	;

declarationlist : declarationlist declaration
			{ print(2, "declarationlist declaration to declarationlist"); }
		| declaration
			{ print(3, "declaration to declarationlist"); }
		;

declaration : vardeclaration
			{ print(4, "vardeclaration to declaration"); }
	| fundeclaration
			{ print(5, "fundeclaration to declaration"); }
	;

vardeclaration : typespecifier ID SEMICOLON
			{ print(6, "typespecifier ID SEMICOLON to vardeclaration"); }
		| typespecifier ID LBRACKET NUM RBRACKET SEMICOLON
			{ print(7, "typespecifier ID LBRACKET NUM RBRACKET SEMICOLON"); }
		;

typespecifier : INT
		{ print(7, "INT to typespecifier"); }
		| VOID
		{ print(8, "VOID to typespecifire"); }
		;

fundeclaration : typespecifier ID LPAREN params RPAREN compoundstmt
		{ print(9, "typespecifier ID LPAREN params RPAREN compoundstmt to fundeclaration");}
		;

params : paramlist
	{ print(10, "paramlist to params");}
	| VOID
	{ print(11, "VOID to params");}
	;

paramlist : paramlist COMMA param
	{ print(12, "paramlist COMMA param to paramlist");}
	| param
	{ print(13, "param to paramlist");}
	;

param : typespecifier ID
	{ print(14, "typespecifier ID to param");}
	| typespecifier ID LBRACKET RBRACKET
	{ print(15, "typespecifier ID LBRACKET RBRACKET to param"); }
	|
	{ print(16, "empty to param"); }
	;

compoundstmt : LBRACE localdeclarations statementlist RBRACE
		{ print(17, "LBRACE localdeclarations statementlist RBRACE to compoundstmt"); }
		;

localdeclarations : localdeclarations vardeclaration
			{ print(18, "localdeclarations vardeclaration to localdeclarations"); }
	|
	{ print(19, "empty to localdeclarations"); }
	;

statementlist : statementlist statement
		{ print(19, "statementlist statement to statementlist");}
		|
		{ print(20, "empty to statementlist");}
		;

statement : expressionstmt
		{ print(21, "expressionstmt to statement");}
	| compoundstmt
	{ print(22, "compoundstmt to statement");}
	| selectionstmt
	{ print(23, "selectionstmt to statement");}
	| iterationstmt
	{ print(23, "iterationstmt to statement");}
	| returnstmt
	{ print(24, "returnstmt to statement");}
	;

expressionstmt : expression SEMICOLON
		{ print(25, "expression SEMICOLON to expressionstmt");}
		| SEMICOLON
		{ print(26, "SEMICOLON to expressionstmt");}
		;

selectionstmt : IF LPAREN expression RPAREN statement
		{ print(27, "IF LPAREN expression RPAREN statement to selectionstmt");}
		| IF LPAREN expression RPAREN statement ELSE statement
		{ print(28, "IF LPAREN expression RPAREN statement ELSE statement to selectionstmt");}
		;

iterationstmt : WHILE LPAREN expression RPAREN statement
		{ print(29, "WHILE LPAREN expression RPAREN statement to iterationstmt");}
		| FOR LPAREN expression SEMICOLON expression SEMICOLON expression RPAREN
		{ print(30, "FOR LPAREN expression COMMA expression COMMA expression RPAREN to iterationstmt");}
		;

returnstmt : RETURN SEMICOLON
		{ print(31, "RETURN SEMICOLON to returnstmt");}
		| RETURN expression SEMICOLON
		{ print(32, "RETURN expression SEMICOLON to returnstmt");}
		;

expression : var ASSIGN expression
		{ print(33, "var ASSIGN expression to expression");}
		| simpleexpression
		{ print(34, "simpleexpression to expression");}
		;

var : ID
	{ print(35, "ID to var");}
	| ID LBRACKET expression RBRACKET
	{ print(36, "ID LBRACKET expression RBRACKET to var");}
	;

simpleexpression : additiveexpression relop additiveexpression
			{ print(37, "additiveexpression relop additiveexpression to simpleexpression"); }
		| additiveexpression
		{ print(38, "additiveexpression to simpleexpression");}
		;

relop : LESSEQUAL
	{ print(39, "LESSEQUAL to relop");}
	| LESS
	{ print(40, "LESS to relop");}
	| GREAT
	{ print(41, "GREAT to relop"); }
	| GREATEQUAL
	{ print(42, "GREATEQUAL to relop"); }
	| EQUAL
	{ print(43, "EQUAL to relop"); }
	| NOTEQUAL
	{ print(44, "NOTEQUAL to relop"); }
	;

additiveexpression : additiveexpression addop term
		{ print(45, "additiveexpression addop term to additiveexpression");}
	| term
	{ print(46, "term to additiveexpression");}
	;

addop : ADD
	{ print(47, "ADD to addop");}
	| SUB
	{ print(48, "SUB to addop");}
	;

term : term mulop factor
	{ print(49, "term mulop factor to term");}
	| factor
	{ print(50, "factor to term");}
	| SUB factor	%prec UMINUS
	{ print(100, "UMINUS factor to additiveexpression");}
	;

mulop : MULT
	{ print(51, "MULT to mulop");}
	| DIV
	{ print(52, "DIV to mulop");}
	;

factor : LPAREN expression RPAREN
	{ print(53, "LPAREN expression RPAREN to factor");}
	| var
	{ print(54, "var to factor");}
	| call
	{ print(55, "call to factor");}
	| NUM
	{ print(56, "NUM to factor");}
	;

call : ID LPAREN args RPAREN
	{ print(57, "ID LPAREN args RPAREN to call");}
	;

args : arglist
	{ print(58, "arglist to args");}
	|
	{ print(59, "empty to args");}
	;

arglist : arglist COMMA expression
	{ print(60, "arglist COMMA expression to arglist");}
	| expression
	{ print(61, "expression to arglist");}
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
