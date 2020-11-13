%{
/* lex source for Mini C*/
#include "minic.tab.h"
#include "global.h"
#define ERROR -1
%}
%%
"for"			return(FOR);
"else"			return(ELSE);
"if"			return(IF);
"int"			return(INT);
"return"		return(RETURN);
"void"			return(VOID);
"while"			return(WHILE);
"+"			return(ADD);
"-"			return(SUB);
"*"			return(MULT);
"/"			return(DIV);
"="			return(ASSIGN);
"=="			return(EQUAL);
"!="			return(NOTEQUAL);
"<"			return(LESS);
">"			return(GREAT);
"<="			return(LESSEQUAL);
">="			return(GREATEQUAL);
"{"			return(LBRACE);
"}"			return(RBRACE);
"("			return(LPAREN);
")"			return(RPAREN);
"["			return(LBRACKET);
"]"			return(RBRACKET);
";"			return(SEMICOLON);
","			return(COMMA);
[A-Za-z_][A-Za-z0-9_]*					return(ID);
[1-9][0-9]*|0([0-7]+|(x|X)[0-9A-Fa-f]*)?		return(NUM);
"/*"([^*]|\*+[^*/])*\**"*/"				;
"//".*							;
[ \t]							{}
[\n\r]							{linenumber++;}
.							{printf("Scanning error at line %d\n", linenumber); return ERROR;}
%%
int yywrap()
{
	return 1;
}
