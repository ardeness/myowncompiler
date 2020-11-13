/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     NUM = 258,
     ID = 259,
     VOID = 260,
     INT = 261,
     COMMA = 262,
     SEMICOLON = 263,
     LPAREN = 264,
     RPAREN = 265,
     LBRACKET = 266,
     RBRACKET = 267,
     LBRACE = 268,
     RBRACE = 269,
     IF = 270,
     ELSE = 271,
     WHILE = 272,
     FOR = 273,
     ASSIGN = 274,
     RETURN = 275,
     ADD = 276,
     SUB = 277,
     MULT = 278,
     DIV = 279,
     LESS = 280,
     LESSEQUAL = 281,
     GREAT = 282,
     GREATEQUAL = 283,
     EQUAL = 284,
     NOTEQUAL = 285,
     UMINUS = 286
   };
#endif
/* Tokens.  */
#define NUM 258
#define ID 259
#define VOID 260
#define INT 261
#define COMMA 262
#define SEMICOLON 263
#define LPAREN 264
#define RPAREN 265
#define LBRACKET 266
#define RBRACKET 267
#define LBRACE 268
#define RBRACE 269
#define IF 270
#define ELSE 271
#define WHILE 272
#define FOR 273
#define ASSIGN 274
#define RETURN 275
#define ADD 276
#define SUB 277
#define MULT 278
#define DIV 279
#define LESS 280
#define LESSEQUAL 281
#define GREAT 282
#define GREATEQUAL 283
#define EQUAL 284
#define NOTEQUAL 285
#define UMINUS 286




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 14 "minic.y"
{
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
/* Line 1489 of yacc.c.  */
#line 145 "minic.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

