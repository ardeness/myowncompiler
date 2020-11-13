%{
/* lex source for Mini C*/
#include "ast.h"
#include "minic.tab.h"
#include "global.h"
#include <stdlib.h>
#include <string.h>
#define ERROR -1
char *getString(char *s);
int evaluate(char *s);
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
[A-Za-z_][A-Za-z0-9_]*					{ yylval.str = getString(yytext); return(ID);}
[1-9][0-9]*|0([0-7]+|(x|X)[0-9A-Fa-f]*)?		{ yylval.num = evaluate(yytext); return(NUM);}
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
char *getString(char *s)
{
	char *temp = malloc(sizeof(char) * (strlen(s) + 1));
	memset(temp, 0, strlen(s) + 1);
	memcpy(temp, s, strlen(s));
	return temp;
}
int evaluate(char *s)
{
	int val = 0;
	char *n = s;

	while(*n != '\0')
	{
		val = val * 10;
		val += (*n - '0');
		n++;
	}
	return val;
}
