#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "ast.h"
#include "minic.tab.h"

A_program		F_declarationlist2program(A_declarationlist declarationlist)
{
	A_program s = malloc(sizeof(*s));

	s->kind = Declarationlist2program;
	s->u.declarationlist2program.declarationlist = declarationlist;

	S_program(s);

	V_program(s);


	return s;
}

A_declarationlist	F_declarationlist2declarationlist(A_declarationlist declarationlist, A_declaration declaration)
{
	A_declarationlist s = malloc(sizeof(*s));

	s->kind = Declarationlist2declarationlist;

	s->u.declarationlist2declarationlist.declarationlist = declarationlist;
	s->u.declarationlist2declarationlist.declaration = declaration;

	return s;
}

A_declarationlist	F_declaration2declarationlist(A_declaration declaration)
{
	A_declarationlist s = malloc(sizeof(*s));

	s->kind = Declaration2declarationlist;

	s->u.declaration2declarationlist.declaration = declaration;

	return s;
}


A_declaration		F_vardeclaration2declaration(A_vardeclaration vardeclaration)
{
	A_declaration s = malloc(sizeof(*s));

	s->kind = Vardeclaration2declaration;

	s->u.vardeclaration2declaration.vardeclaration = vardeclaration;

	return s;
}
A_declaration		F_fundeclaration2declaration(A_fundeclaration fundeclaration)
{
	A_declaration s = malloc(sizeof(*s));

	s->kind = Fundeclaration2declaration;

	s->u.fundeclaration2declaration.fundeclaration = fundeclaration;

	return s;
}

A_vardeclaration	F_typespecifier2vardeclaration(A_typespecifier typespecifier, char *id)
{
	A_vardeclaration s = malloc(sizeof(*s));

	s->kind = Typespecifier2vardeclaration;

	s->u.typespecifier2vardeclaration.typespecifier = typespecifier;
	s->u.typespecifier2vardeclaration.id.tokennumber = ID;
	s->u.typespecifier2vardeclaration.id.tokenvalue = malloc(sizeof(char) * (strlen(id) + 1));
	memset(s->u.typespecifier2vardeclaration.id.tokenvalue, 0, strlen(id) + 1);
	memcpy(s->u.typespecifier2vardeclaration.id.tokenvalue, id, strlen(id));

	return s;
}
A_vardeclaration	F_typespecifierNUM2vardeclaration(A_typespecifier typespecifier, char *id, int size)
{
	A_vardeclaration s = malloc(sizeof(*s));

	s->kind = TypespecifierNUM2vardeclaration;

	s->u.typespecifierNUM2vardeclaration.typespecifier = typespecifier;
	s->u.typespecifierNUM2vardeclaration.id.tokennumber = ID;
	s->u.typespecifierNUM2vardeclaration.id.tokenvalue = malloc(sizeof(char) * (strlen(id) + 1));
	memset(s->u.typespecifierNUM2vardeclaration.id.tokenvalue, 0, strlen(id) + 1);
	memcpy(s->u.typespecifierNUM2vardeclaration.id.tokenvalue, id, strlen(id));
	s->u.typespecifierNUM2vardeclaration.size = size;

	return s;
}

A_typespecifier		F_typespecifier(char *type, int tokennumber)
{
	A_typespecifier s = malloc(sizeof(*s));

	s->typespecifier.tokennumber = tokennumber;
	s->typespecifier.tokenvalue = malloc(sizeof(char) * (strlen(type)+1));
	memset(s->typespecifier.tokenvalue, 0, strlen(type) + 1);
	memcpy(s->typespecifier.tokenvalue, type, strlen(type));

	return s;
}

A_fundeclaration	F_typespecifier2fundeclaration(A_typespecifier typespecifier, char *id, A_params params, A_compoundstmt compoundstmt)
{
	A_fundeclaration s = malloc(sizeof(*s));

	s->kind = Typespecifier2fundeclaration;


	s->u.typespecifier2fundeclaration.id.tokennumber = ID;
	s->u.typespecifier2fundeclaration.id.tokenvalue = malloc(sizeof(char) * (strlen(id) + 1));
	memset(s->u.typespecifier2fundeclaration.id.tokenvalue, 0, strlen(id) + 1);
	memcpy(s->u.typespecifier2fundeclaration.id.tokenvalue, id, strlen(id));
	s->u.typespecifier2fundeclaration.typespecifier = typespecifier;
	s->u.typespecifier2fundeclaration.params = params;
	s->u.typespecifier2fundeclaration.compoundstmt = compoundstmt;

	return s;
}

A_params		F_paramlist2params(A_paramlist paramlist)
{
	A_params s = malloc(sizeof(*s));

	s->kind = Paramlist2params;

	s->u.paramlist2params.paramlist = paramlist;

	return s;
}
A_params		F_void2params()
{
	// no params
	return NULL;
}

A_paramlist		F_paramlist2paramlist(A_paramlist paramlist, A_param param)
{
	A_paramlist s = malloc(sizeof(*s));

	s->kind = Paramlist2paramlist;

	s->u.paramlist2paramlist.paramlist = paramlist;
	s->u.paramlist2paramlist.param = param;

	return s;
}
A_paramlist		F_param2paramlist(A_param param)
{
	A_paramlist s = malloc(sizeof(*s));

	s->kind = Param2paramlist;

	s->u.param2paramlist.param = param;

	return s;
}

A_param			F_typespecifier2param(A_typespecifier typespecifier, char *id)
{
	A_param s = malloc(sizeof(*s));

	s->kind = Typespecifier2param;

	s->u.typespecifier2param.typespecifier = typespecifier;
	s->u.typespecifier2param.id.tokennumber = ID;
	s->u.typespecifier2param.id.tokenvalue = malloc(sizeof(char) * (strlen(id) + 1));
	memset(s->u.typespecifier2param.id.tokenvalue, 0, strlen(id)+1);
	memcpy(s->u.typespecifier2param.id.tokenvalue, id, strlen(id));

	return s;
}
A_param			F_typespecifierArray2param(A_typespecifier typespecifier, char *id)
{
	A_param s = malloc(sizeof(*s));

	s->kind = TypespecifierArray2param;

	s->u.typespecifierArray2param.typespecifier = typespecifier;
	s->u.typespecifierArray2param.id.tokennumber = ID;
	s->u.typespecifierArray2param.id.tokenvalue = malloc(sizeof(char) * (strlen(id) + 1));
	memset(s->u.typespecifierArray2param.id.tokenvalue, 0, strlen(id)+1);
	memcpy(s->u.typespecifierArray2param.id.tokenvalue, id, strlen(id));

	return s;
}
A_param			F_null2param()
{
	// no param
	return NULL;
}

A_compoundstmt		F_localdeclarations2compoundstmt(A_localdeclarations localdeclarations, A_statementlist statementlist)
{
	A_compoundstmt s = malloc(sizeof(*s));

	s->kind = Localdeclarations2compoundstmt;

	s->u.localdeclarations2compoundstmt.localdeclarations = localdeclarations;
	s->u.localdeclarations2compoundstmt.statementlist = statementlist;

	return s;
}

A_localdeclarations	F_localdeclarations2localdeclarations(A_localdeclarations localdeclarations, A_vardeclaration vardeclaration)
{
	A_localdeclarations s = malloc(sizeof(*s));

	s->kind = Localdeclarations2localdeclarations;

	s->u.localdeclarations2localdeclarations.localdeclarations = localdeclarations;
	s->u.localdeclarations2localdeclarations.vardeclaration = vardeclaration;

	return s;
}
A_localdeclarations	F_null2localdeclaration()
{
	// no localdeclarations
	return NULL;
}

A_statementlist		F_statementlist2statementlist(A_statementlist statementlist, A_statement statement)
{
	A_statementlist s = malloc(sizeof(*s));

	s->kind = Statementlist2statementlist;

	s->u.statementlist2statementlist.statementlist = statementlist;
	s->u.statementlist2statementlist.statement = statement;

	return s;
}
A_statementlist		F_null2statementlist()
{
	// no statementlist
	return NULL;
}

A_statement		F_expressionstmt2statement(A_expressionstmt expressionstmt)
{
	A_statement s = malloc(sizeof(*s));

	s->kind = Expressionstmt2statement;

	s->u.expressionstmt2statement.expressionstmt = expressionstmt;

	return s;
}
A_statement		F_compoundstmt2statement(A_compoundstmt compoundstmt)
{
	A_statement s = malloc(sizeof(*s));

	s->kind = Compoundstmt2statement;

	s->u.compoundstmt2statement.compoundstmt = compoundstmt;

	return s;
}
A_statement		F_selectionstmt2statement(A_selectionstmt selectionstmt)
{
	A_statement s = malloc(sizeof(*s));

	s->kind = Selectionstmt2statement;

	s->u.selectionstmt2statement.selectionstmt = selectionstmt;

	return s;
}
A_statement		F_iterationstmt2statement(A_iterationstmt iterationstmt)
{
	A_statement s = malloc(sizeof(*s));

	s->kind = Iterationstmt2statement;

	s->u.iterationstmt2statement.iterationstmt = iterationstmt;

	return s;
}
A_statement		F_returnstmt2statement(A_returnstmt returnstmt)
{
	A_statement s = malloc(sizeof(*s));

	s->kind = Returnstmt2statement;

	s->u.returnstmt2statement.returnstmt = returnstmt;

	return s;
}

A_expressionstmt	F_expression2expressionstmt(A_expression expression)
{
	A_expressionstmt s = malloc(sizeof(*s));

	s->kind = Expression2expressionstmt;

	s->u.expression2expressionstmt.expression = expression;

	return s;
}
A_expressionstmt	F_null2expressionstmt()
{
	// no expressionstmt
	return NULL;
}

A_selectionstmt		F_if2selectionstmt(A_expression expression, A_statement statement)
{
	A_selectionstmt s = malloc(sizeof(*s));

	s->kind = If2selectionstmt;

	s->u.if2selectionstmt.expression = expression;
	s->u.if2selectionstmt.statement = statement;

	return s;
}
A_selectionstmt		F_ifelse2selectionstmt(A_expression expression, A_statement statement1, A_statement statement2)
{
	A_selectionstmt s = malloc(sizeof(*s));

	s->kind = Ifelse2selectionstmt;

	s->u.ifelse2selectionstmt.expression = expression;
	s->u.ifelse2selectionstmt.statement1 = statement1;
	s->u.ifelse2selectionstmt.statement2 = statement2;

	return s;
}

A_iterationstmt		F_while2iterationstmt(A_expression expression, A_statement statement)
{
	A_iterationstmt s = malloc(sizeof(*s));

	s->kind = While2iterationstmt;

	s->u.while2iterationstmt.expression = expression;
	s->u.while2iterationstmt.statement = statement;

	return s;
}
A_iterationstmt		F_for2iterationstmt(A_expression expression1, A_expression expression2, A_expression expression3, A_statement statement)
{
	A_iterationstmt s = malloc(sizeof(*s));

	s->kind = For2iterationstmt;

	s->u.for2iterationstmt.expression1 = expression1;
	s->u.for2iterationstmt.expression2 = expression2;
	s->u.for2iterationstmt.expression3 = expression3;
	s->u.for2iterationstmt.statement = statement;

	return s;
}

A_returnstmt		F_null2returnstmt()
{
	// no returnstmt
	return NULL;
}
A_returnstmt		F_expression2returnstmt(A_expression expression)
{
	A_returnstmt s = malloc(sizeof(*s));

	s->kind = Expression2returnstmt;

	s->u.expression2returnstmt.expression = expression;

	return s;
}

A_expression		F_var2expression(A_var var, A_expression expression)
{
	A_expression s = malloc(sizeof(*s));

	s->kind = Var2expression;

	s->u.var2expression.var = var;
	s->u.var2expression.expression = expression;

	return s;
}
A_expression		F_simpleexpression2expression(A_simpleexpression simpleexpression)
{
	A_expression s = malloc(sizeof(*s));

	s->kind = Simpleexpression2expression;

	s->u.simpleexpression2expression.simpleexpression = simpleexpression;

	return s;
}

A_var			F_id2var(char *id)
{
	A_var s = malloc(sizeof(*s));

	s->kind = Id2var;

	s->u.id2var.id.tokennumber = ID;
	s->u.id2var.id.tokenvalue = malloc(sizeof(char) * (strlen(id) + 1));
	memset(s->u.id2var.id.tokenvalue, 0, strlen(id)+1);
	memcpy(s->u.id2var.id.tokenvalue, id, strlen(id));

	return s;
}
A_var			F_array2var(char *id, A_expression expression)
{
	A_var s = malloc(sizeof(*s));

	s->kind = Array2var;

	s->u.array2var.id.tokennumber = ID;
	s->u.array2var.id.tokenvalue = malloc(sizeof(char) * (strlen(id) + 1));
	memset(s->u.array2var.id.tokenvalue, 0, strlen(id)+1);
	memcpy(s->u.array2var.id.tokenvalue, id, strlen(id));
	s->u.array2var.expression = expression;

	return s;
}

A_simpleexpression	F_additiveexpressionrelop2simpleexpression(A_additiveexpression additiveexpression1, int relop, A_additiveexpression additiveexpression2)
{
	A_simpleexpression s = malloc(sizeof(*s));

	s->kind = Additiveexpressionrelop2simpleexpression;

	s->u.additiveexpressionrelop2simpleexpression.additiveexpression1 = additiveexpression1;
	s->u.additiveexpressionrelop2simpleexpression.relop = relop;
	s->u.additiveexpressionrelop2simpleexpression.additiveexpression2 = additiveexpression2;

	return s;
}
A_simpleexpression	F_additiveexpression2simpleexpression(A_additiveexpression additiveexpression)
{
	A_simpleexpression s = malloc(sizeof(*s));

	s->kind = Additiveexpression2simpleexpression;

	s->u.additiveexpression2simpleexpression.additiveexpression = additiveexpression;

	return s;
}

A_additiveexpression	F_additiveexpression2additiveexpression(A_additiveexpression additiveexpression, int addop, A_term term)
{
	A_additiveexpression s = malloc(sizeof(*s));

	s->kind = Additiveexpression2additiveexpression;

	s->u.additiveexpression2additiveexpression.additiveexpression = additiveexpression;
	s->u.additiveexpression2additiveexpression.addop = addop;
	s->u.additiveexpression2additiveexpression.term = term;

	return s;
}
A_additiveexpression	F_term2additiveexpression(A_term term)
{
	A_additiveexpression s = malloc(sizeof(*s));

	s->kind = Term2additiveexpression;

	s->u.term2additiveexpression.term = term;

	return s;
}

A_term			F_term2term(A_term term, int mulop, A_factor factor)
{
	A_term s = malloc(sizeof(*s));

	s->kind = Term2term;

	s->u.term2term.term = term;
	s->u.term2term.mulop = mulop;
	s->u.term2term.factor = factor;

	return s;
}

A_term			F_factor2term(A_factor factor)
{
	A_term s = malloc(sizeof(*s));

	s->kind = Factor2term;

	s->u.factor2term.factor = factor;

	return s;
}

A_term			F_uminus2term(A_factor factor)
{
	A_term s = malloc(sizeof(*s));

	s->kind = Uminus2term;

	s->u.uminus2term.factor = factor;

	return s;
}

A_factor		F_expression2factor(A_expression expression)
{
	A_factor s = malloc(sizeof(*s));

	s->kind = Expression2factor;

	s->u.expression2factor.expression = expression;

	return s;
}
A_factor		F_var2factor(A_var var)
{

	A_factor s = malloc(sizeof(*s));

	s->kind = Var2factor;

	s->u.var2factor.var = var;

	return s;
}
A_factor		F_call2factor(A_call call)
{

	A_factor s = malloc(sizeof(*s));

	s->kind = Call2factor;

	s->u.call2factor.call = call;

	return s;
}
A_factor		F_num2factor(int num)
{

	A_factor s = malloc(sizeof(*s));

	s->kind = Num2factor;

	s->u.num2factor.num = num;

	return s;
}

A_call			F_id2call(char *id, A_args args)
{
	A_call s = malloc(sizeof(*s));

	s->kind = Id2call;

	s->u.id2call.id.tokennumber = ID;
	s->u.id2call.id.tokenvalue = malloc(sizeof(char) * (strlen(id) + 1));
	memset(s->u.id2call.id.tokenvalue, 0, strlen(id) + 1);
	memcpy(s->u.id2call.id.tokenvalue, id, strlen(id));
	s->u.id2call.args = args;

	return s;
}

A_args			F_arglist2args(A_arglist arglist)
{
	A_args s = malloc(sizeof(*s));

	s->kind = Arglist2args;

	s->u.arglist2args.arglist = arglist;

	return s;
}
A_args			F_null2args()
{
	// no args
	return NULL;
}

A_arglist		F_arglist2arglist(A_arglist arglist, A_expression expression)
{
	A_arglist s = malloc(sizeof(*s));

	s->kind = Arglist2arglist;
	s->u.arglist2arglist.arglist = arglist;
	s->u.arglist2arglist.expression = expression;

	return s;
}
A_arglist		F_expression2arglist(A_expression expression)
{
	A_arglist s = malloc(sizeof(*s));

	s->kind = Expression2arglist;
	s->u.expression2arglist.expression = expression;

	return s;
}
