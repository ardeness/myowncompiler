#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ast.h"
#include "minic.tab.h"

int scope = 0;
StringBucket StringTable[STRING_BUCKET_SIZE];
Symbol SHT[SHT_BUCKET_SIZE];
Symbol currentFunction;

void Init()
{
	int i;

	for(i=0; i<STRING_BUCKET_SIZE; i++)
	{
		StringTable[i] = (StringBucket)malloc(sizeof(*StringTable[i]));
		StringTable[i]->string = NULL;
		StringTable[i]->next = NULL;
		StringTable[i]->prev = StringTable[i];
	}

	for(i=0; i<SHT_BUCKET_SIZE; i++)
	{
		SHT[i] = (Symbol)malloc(sizeof(*SHT[i]));
		SHT[i]->name = NULL;
		SHT[i]->scope = -1;
		SHT[i]->next = NULL;
		SHT[i]->prev = SHT[i];
	}
	currentFunction = NULL;
}
void S_program(A_program program)
{
	Init();
	S_declarationlist(program->u.declarationlist2program.declarationlist);
}
void S_declarationlist(A_declarationlist declarationlist)
{
	if(declarationlist->kind == Declarationlist2declarationlist)
	{
		S_declarationlist(declarationlist->u.declarationlist2declarationlist.declarationlist);
		S_declaration(declarationlist->u.declarationlist2declarationlist.declaration);
	}
	else if(declarationlist->kind == Declaration2declarationlist)
	{
		S_declaration(declarationlist->u.declaration2declarationlist.declaration);
	}
}
void S_declaration(A_declaration declaration)
{
	if(declaration->kind == Vardeclaration2declaration)
	{
		S_vardeclaration(declaration->u.vardeclaration2declaration.vardeclaration);
		free(declaration->u.vardeclaration2declaration.vardeclaration);
		declaration->u.vardeclaration2declaration.vardeclaration = NULL;
	}
	else if(declaration->kind = Fundeclaration2declaration)
	{
		S_fundeclaration(declaration->u.fundeclaration2declaration.fundeclaration);
	}
}
Ty_ty S_vardeclaration(A_vardeclaration vardeclaration)
{
	if(vardeclaration->kind == Typespecifier2vardeclaration)
	{
		Ty_ty t = S_typespecifier(vardeclaration->u.typespecifier2vardeclaration.typespecifier);
		S_insert(t, vardeclaration->u.typespecifier2vardeclaration.id.tokenvalue);
		free(vardeclaration->u.typespecifier2vardeclaration.typespecifier);
		vardeclaration->u.typespecifier2vardeclaration.typespecifier = NULL;
		free(vardeclaration->u.typespecifier2vardeclaration.id.tokenvalue);
	}
	else if(vardeclaration->kind == TypespecifierNUM2vardeclaration)
	{
		Ty_ty t = S_typespecifier(vardeclaration->u.typespecifierNUM2vardeclaration.typespecifier);
		t = Ty_Array(t);
		S_insert(t, vardeclaration->u.typespecifierNUM2vardeclaration.id.tokenvalue);
		free(vardeclaration->u.typespecifierNUM2vardeclaration.typespecifier);
		vardeclaration->u.typespecifierNUM2vardeclaration.typespecifier = NULL;
		free(vardeclaration->u.typespecifierNUM2vardeclaration.id.tokenvalue);
	}
}

Ty_ty S_typespecifier(A_typespecifier typespecifier)
{
	Ty_ty t;
	if(typespecifier->typespecifier.tokennumber == INT)
		t = Ty_Int();
	else if(typespecifier->typespecifier.tokennumber == VOID)
		t = Ty_Void();

	free(typespecifier->typespecifier.tokenvalue);
	return t;
}

void S_fundeclaration(A_fundeclaration fundeclaration)
{
	Symbol s;
	Ty_ty head;
	Ty_tyList tail;

	head = S_typespecifier(fundeclaration->u.typespecifier2fundeclaration.typespecifier);
	scope++;
	tail = S_params(fundeclaration->u.typespecifier2fundeclaration.params);
	tail = Ty_TyList(head, tail);
	scope--;
	s = S_insertfunction(tail, fundeclaration->u.typespecifier2fundeclaration.id.tokenvalue);

	if(s == NULL)
	{
		printf("Function %s allready declared\n", fundeclaration->u.typespecifier2fundeclaration.id.tokenvalue);
	}
	currentFunction = s;
	S_compoundstmt(fundeclaration->u.typespecifier2fundeclaration.compoundstmt);

	s->u.function.tl = tail;
	free(fundeclaration->u.typespecifier2fundeclaration.id.tokenvalue);
	free(fundeclaration->u.typespecifier2fundeclaration.typespecifier);
	fundeclaration->u.typespecifier2fundeclaration.typespecifier = NULL;
}

Ty_tyList S_params(A_params params)
{
	if(params == NULL)
		return NULL;
	if(params->kind == Void2params)
		return NULL;
	
	return S_paramlist(params->u.paramlist2params.paramlist);
}
Ty_tyList S_paramlist(A_paramlist paramlist)
{
	Ty_tyList h;
	Ty_tyList t;

	if(paramlist->kind == Paramlist2paramlist)
	{
		h = S_paramlist(paramlist->u.paramlist2paramlist.paramlist);
		t = h;

		while(t->tail != NULL)
			t = t->tail;

		t->tail = Ty_TyList(S_param(paramlist->u.paramlist2paramlist.param), NULL);
		return h;
	}
	else if(paramlist->kind == Param2paramlist)
	{
		return Ty_TyList(S_param(paramlist->u.param2paramlist.param), NULL);
	}
}
Ty_ty S_param(A_param param)
{
	Ty_ty t;

	if(param == NULL)
		return NULL;

	else if(param->kind == Typespecifier2param)
	{
		t = S_typespecifier(param->u.typespecifier2param.typespecifier);
		S_insert(t, param->u.typespecifier2param.id.tokenvalue);
	}
	else if(param->kind == TypespecifierArray2param)
	{
		t = S_typespecifier(param->u.typespecifierArray2param.typespecifier);
		t = Ty_Array(t);
		S_insert(t, param->u.typespecifierArray2param.id.tokenvalue);
	}
	return t;
}
void S_compoundstmt(A_compoundstmt compoundstmt)
{
	scope++;
	S_localdeclarations(compoundstmt->u.localdeclarations2compoundstmt.localdeclarations);
	S_statementlist(compoundstmt->u.localdeclarations2compoundstmt.statementlist);
	PopSymbolinScope(scope);
	scope--;
}
void S_localdeclarations(A_localdeclarations localdeclarations)
{
	if(localdeclarations == NULL)
		return;

	else if(localdeclarations->kind == Localdeclarations2localdeclarations)
	{
		S_localdeclarations(localdeclarations->u.localdeclarations2localdeclarations.localdeclarations);
		S_vardeclaration(localdeclarations->u.localdeclarations2localdeclarations.vardeclaration);
		free(localdeclarations->u.localdeclarations2localdeclarations.vardeclaration);
		localdeclarations->u.localdeclarations2localdeclarations.vardeclaration=NULL;
	}
}
void S_statementlist(A_statementlist statementlist)
{
	if(statementlist==NULL)
		return;

	else if(statementlist->kind == Statementlist2statementlist)
	{
		S_statementlist(statementlist->u.statementlist2statementlist.statementlist);
		S_statement(statementlist->u.statementlist2statementlist.statement);
	}
}
void S_statement(A_statement statement)
{
	switch(statement->kind)
	{
		case Expressionstmt2statement:
			S_expressionstmt(statement->u.expressionstmt2statement.expressionstmt);
			break;
		case Compoundstmt2statement:
			S_compoundstmt(statement->u.compoundstmt2statement.compoundstmt);
			break;
		case Selectionstmt2statement:
			S_selectionstmt(statement->u.selectionstmt2statement.selectionstmt);
			break;
		case Iterationstmt2statement:
			S_iterationstmt(statement->u.iterationstmt2statement.iterationstmt);
			break;
		case Returnstmt2statement:
			S_returnstmt(statement->u.returnstmt2statement.returnstmt);
			break;
		default:
			return;
	}
}
void S_expressionstmt(A_expressionstmt expressionstmt)
{
	if(expressionstmt == NULL)
		return;

	else if(expressionstmt->kind == Expression2expressionstmt)
		S_expression(expressionstmt->u.expression2expressionstmt.expression);
}
void S_selectionstmt(A_selectionstmt selectionstmt)
{
	if(selectionstmt->kind == If2selectionstmt)
	{
		S_expression(selectionstmt->u.if2selectionstmt.expression);
		S_statement(selectionstmt->u.if2selectionstmt.statement);
	}
	else if(selectionstmt->kind == Ifelse2selectionstmt)
	{
		S_expression(selectionstmt->u.ifelse2selectionstmt.expression);
		S_statement(selectionstmt->u.ifelse2selectionstmt.statement1);
		S_statement(selectionstmt->u.ifelse2selectionstmt.statement2);
	}
}

void S_iterationstmt(A_iterationstmt iterationstmt)
{
	if(iterationstmt->kind == While2iterationstmt)
	{
		S_expression(iterationstmt->u.while2iterationstmt.expression);
		S_statement(iterationstmt->u.while2iterationstmt.statement);
	}
	else if(iterationstmt->kind == For2iterationstmt)
	{
		S_expression(iterationstmt->u.for2iterationstmt.expression1);
		S_expression(iterationstmt->u.for2iterationstmt.expression2);
		S_expression(iterationstmt->u.for2iterationstmt.expression3);
		S_statement(iterationstmt->u.for2iterationstmt.statement);
	}
}
void S_returnstmt(A_returnstmt returnstmt)
{
	Ty_ty t;
	if(returnstmt == NULL)
		return;
	else if(returnstmt->kind == Expression2returnstmt)
	{
		t = S_expression(returnstmt->u.expression2returnstmt.expression);
	}
	if(currentFunction != NULL && currentFunction->u.function.tl->head->kind != t->kind)
	{
		printf("Function %s type is %s but return %s.\n", currentFunction->name, Ty_print(currentFunction->u.function.tl->head), Ty_print(t));
	}
}
Ty_ty S_expression(A_expression expression)
{
	Ty_ty t1;
	Ty_ty t2;
	if(expression->kind == Var2expression)
	{
		t1 = S_var(expression->u.var2expression.var);
		t2 = S_expression(expression->u.var2expression.expression);

		if(t1->kind != t2->kind)
		{
			printf("Conversion from %s to %s.\n", Ty_print(t2), Ty_print(t1));
		}
		return t1;
	}
	else if(expression->kind == Simpleexpression2expression)
	{
		t1 = S_simpleexpression(expression->u.simpleexpression2expression.simpleexpression);
		return t1;
	}
}
Ty_ty S_var(A_var var)
{
	char *name;
	if(var->kind == Id2var)
	{
		name = var->u.id2var.id.tokenvalue;
		var->s = S_lookup(var->u.id2var.id.tokenvalue);
	}
	else if(var->kind == Array2var)
	{
		name = var->u.array2var.id.tokenvalue;
		var->s = S_lookup(var->u.array2var.id.tokenvalue);
		S_expression(var->u.array2var.expression);
	}
	if(var->s == NULL)
	{
		printf("Can't find symbol %s\n", name);
		return NULL;
	}
	return var->s->u.variable.t;
}
Ty_ty S_simpleexpression(A_simpleexpression simpleexpression)
{
	Ty_ty t1;
	Ty_ty t2;
	if(simpleexpression->kind == Additiveexpressionrelop2simpleexpression)
	{
		t1 = S_additiveexpression(simpleexpression->u.additiveexpressionrelop2simpleexpression.additiveexpression1);
		S_relop(simpleexpression->u.additiveexpressionrelop2simpleexpression.relop);
		t2 = S_additiveexpression(simpleexpression->u.additiveexpressionrelop2simpleexpression.additiveexpression2);
//		t = Ty_Int();	// boolean value
		if(t1->kind != t2->kind)
		{
			printf("Compare %s and %s.\n", Ty_print(t1), Ty_print(t2));
		}
		return t1;
	}
	else if(simpleexpression->kind == Additiveexpression2simpleexpression)
	{
		t1 = S_additiveexpression(simpleexpression->u.additiveexpression2simpleexpression.additiveexpression);
		return t1;
	}
}
void S_relop(A_relop relop)
{
	// do nothing
	return;
}
Ty_ty S_additiveexpression(A_additiveexpression additiveexpression)
{
	Ty_ty t1, t2;
	if(additiveexpression->kind == Additiveexpression2additiveexpression)
	{
		t1 = S_additiveexpression(additiveexpression->u.additiveexpression2additiveexpression.additiveexpression);
		S_addop(additiveexpression->u.additiveexpression2additiveexpression.addop);
		t2 = S_term(additiveexpression->u.additiveexpression2additiveexpression.term);

		if(t1->kind != t2->kind)
		{
			printf("Additive operation with %s and %s.\n", Ty_print(t1), Ty_print(t2));
		}
		return t1;
	}
	else if(additiveexpression->kind == Term2additiveexpression)
	{
		t1 = S_term(additiveexpression->u.term2additiveexpression.term);
		return t1;
	}
}
void S_addop(A_addop addop)
{
	// do nothing
	return;
}
Ty_ty S_term(A_term term)
{
	Ty_ty t1, t2;
	if(term->kind == Term2term)
	{
		t1 = S_term(term->u.term2term.term);
		S_mulop(term->u.term2term.mulop);
		t2 = S_factor(term->u.term2term.factor);

		if(t1->kind != t2->kind)
		{
			printf("Multiple operation with %s and %s.\n", Ty_print(t1), Ty_print(t2));
		}
		return t1;
	}
	else if(term->kind == Factor2term)
	{
		t1 = S_factor(term->u.factor2term.factor);
		return t1;
	}
	else if(term->kind == Uminus2term);
	{
		t1 = S_factor(term->u.uminus2term.factor);
		return t1;
	}
}
void S_mulop(A_mulop mulop)
{
	// do nothing
	return;
}
Ty_ty S_factor(A_factor factor)
{
	Ty_ty t;
	if(factor->kind == Expression2factor)
	{
		t = S_expression(factor->u.expression2factor.expression);
	}
	else if(factor->kind == Var2factor)
	{
		t = S_var(factor->u.var2factor.var);
	}
	else if(factor->kind == Call2factor)
	{
		t = S_call(factor->u.call2factor.call);
	}
	else if(factor->kind == Num2factor)
	{
		// do nothing
		t = Ty_Int();
	}
	return t;
}
Ty_ty S_call(A_call call)
{
	Ty_tyList tl;
	call->s = S_lookup(call->u.id2call.id.tokenvalue);
	tl = S_args(call->u.id2call.args);

	if(call->s == NULL)
	{
		printf("Can't find symbol %s\n", call->u.id2call.id.tokenvalue);
		return NULL;
	}
	if(!TyList_compare(call->s->u.function.tl->tail, tl))
	{
		printf("Function %s argument type check fail.\n", call->s->name);
	}
	return call->s->u.function.tl->head;
}
Ty_tyList S_args(A_args args)
{
	Ty_tyList tl;
	if(args == NULL)
		return NULL;

	if(args->kind == Arglist2args)
	{
		tl = S_arglist(args->u.arglist2args.arglist);
		return tl;
	}
	else if(args->kind == Null2args)
		return NULL;
}
Ty_tyList S_arglist(A_arglist arglist)
{
	Ty_tyList tl;
	Ty_tyList tail;
	Ty_tyList temp;
	Ty_ty t;
	if(arglist->kind == Expression2arglist)
	{
		t = S_expression(arglist->u.expression2arglist.expression);
		tl = Ty_TyList(t, NULL);
		return tl;
	}
	else if(arglist->kind == Arglist2arglist)
	{
		tl = S_arglist(arglist->u.arglist2arglist.arglist);
		tail = tl;

		while(tail->tail != NULL)
			tail  = tail->tail;
		temp = Ty_TyList(S_expression(arglist->u.arglist2arglist.expression), NULL);
		tail->tail = temp;
		return tl;
	}
}

char* String_insert(char* name)
{
	StringBucket head;
	StringBucket temp;
	unsigned int hash_value = 0;
	int i;
	if(name == NULL)
		return NULL;

	for(i=0; name[i]!='\0'; i++)
		hash_value += (unsigned int)name[i];

	hash_value = hash_value%STRING_BUCKET_SIZE;
	head = StringTable[hash_value];

	if(head->next == NULL)	// bucket list empty
	{
		temp = (StringBucket)malloc(sizeof(*temp));
		temp->string = (char *)malloc(sizeof(char) * (strlen(name)+1));
		memset(temp->string, 0, sizeof(char) * (strlen(name)+1));
		memcpy(temp->string, name, strlen(name));
		head->next = temp;
		temp->prev = head;
		temp->next = NULL;
		return temp->string;
	}

	head = head->next;

	while(head->next != NULL)
	{
		if(!strcmp(name, head->string))
			return head->string;
		head = head->next;
	}
	if(!strcmp(name, head->string))
		return head->string;

	temp = (StringBucket)malloc(sizeof(*temp));
	temp->string = (char *)malloc(sizeof(char) * (strlen(name)+1));
	memset(temp->string, 0, sizeof(char) * (strlen(name) + 1));
	memcpy(temp->string, name, strlen(name));
	head->next = temp;
	temp->prev = head;
	temp->next = NULL;
	return temp->string;
}

Symbol SHT_lookup(Symbol s)
{
	Symbol head;

	unsigned int hash_value = 0;
	int i;

	if(s == NULL)
		return NULL;

	if(s->name == NULL)
		return NULL;

	for(i=0; s->name[i] != '\0'; i++)
		hash_value += (unsigned int)(s->name[i]);

	hash_value %= SHT_BUCKET_SIZE;
	head = SHT[hash_value];

	if(head->next == NULL)
		return NULL;

	head = head->next;

	while(head!=NULL)
	{
		if(s->name == head->name)
			return head;
		head = head->next;
	}
	
	return NULL;
}
void SHT_insert(Symbol s)
{
	Symbol head;
	unsigned int hash_value = 0;
	int i;

	if(s == NULL)
		return;

	for(i=0; s->name[i] != '\0'; i++)
		hash_value += (unsigned int)(s->name[i]);

	hash_value %= SHT_BUCKET_SIZE;
	head = SHT[hash_value];

	if(head->next != NULL)
		head->next->prev = s;

	s->next = head->next;
	head->next = s;
	s->prev = head;
}

Symbol S_lookup(char *name)
{
	Symbol s = (Symbol)malloc(sizeof(*s));
	Symbol t;
	s->scope = scope;
	s->name = String_insert(name);

	t = SHT_lookup(s);
	free(s);
	return t;
}
Symbol S_insert(Ty_ty t, char *name)
{
	Symbol temp;
	Symbol s = (Symbol)malloc(sizeof(*s));
	s->scope = scope;
	s->kind = Var;
	s->name = String_insert(name);
	s->u.variable.t = t;

	temp = SHT_lookup(s);
	if(temp == NULL)
		SHT_insert(s);
	else if(temp->scope != s->scope)
		SHT_insert(s);
	else
	{
		printf("Multiple definition of symbol %s.\n", name);
		free(s);
		return NULL;
	}
	return s;
}

Symbol S_insertfunction(Ty_tyList tl, char *name)
{
	Symbol temp;
	Symbol s = (Symbol)malloc(sizeof(*s));
	s->scope = scope;
	s->kind = Fun;
	s->name = String_insert(name);
	s->u.function.tl = tl;

	temp = SHT_lookup(s);
	if(temp == NULL)
		SHT_insert(s);
	else if(temp->scope != s->scope)
		SHT_insert(s);
	else
	{
		printf("Multiple definition of symbol %s.\n", name);
		free(s);
		return NULL;
	}
	return s;
}

Ty_ty Ty_Int()
{
	Ty_ty t = (Ty_ty)malloc(sizeof(*t));
	t->kind = Ty_int;
	return t;
}

Ty_ty Ty_Void()
{
	Ty_ty t = (Ty_ty)malloc(sizeof(*t));
	t->kind = Ty_void;
	return t;
}
Ty_ty Ty_Array(Ty_ty ty)
{
	Ty_ty t = (Ty_ty)malloc(sizeof(*t));
	t->kind = Ty_array;
	t->u.array = ty;
	return t;
}
/*
Ty_ty Ty_Name(S_symbol sym, Ty_ty ty)
{
	Ty_ty t = (Ty_ty)malloc(sizeof(*t));
	t->kind = Ty_name;
	t->name.sym = sym;
	t->name.ty = ty;
	return ty;
}
*/
Ty_tyList Ty_TyList(Ty_ty head, Ty_tyList tail)
{
	Ty_tyList t = (Ty_tyList)malloc(sizeof(*t));
	t->head = head;
	t->tail = tail;
	return t;
}

char* Ty_print(Ty_ty t)
{
	switch(t->kind)
	{
		case Ty_int:
			return "type INT";
		case Ty_array:
			return "type ARRAY";
		case Ty_name:
			return "type NAME";
		case Ty_void:
			return "type VOID";
		default:
			return "unknown type";
	}
}

int TyList_compare(Ty_tyList list1, Ty_tyList list2)
{
	int i = 0;
	Ty_tyList t1 = list1;
	Ty_tyList t2 = list2;

	while(t1 != NULL && t2 != NULL)
	{
		if(t1->head->kind != t2->head->kind)
		{
			printf("Conversion from %s to %s.\n", Ty_print(t2->head), Ty_print(t1->head));
			return 0;
		}
		t1 = t1->tail;
		t2 = t2->tail;
		i++;
	}
	if((t1 == NULL && t2 != NULL) || (t1 != NULL && t2 == NULL))
	{
		printf("Type list length is not equal.\n");
		return 0;
	}
	return 1;
}

void PopSymbolinScope(int scope)
{
	Symbol s;
	int i;

	for(i=0; i<SHT_BUCKET_SIZE; i++)
	{
		s = SHT[i]->next;

		while(s!=NULL)
		{
			if(s->scope == scope)
			{
				if(s->next != NULL)
				{
					s->next->prev = s->prev;
				}
				s->prev->next = s->next;
				free(s);
			}
			s = s->next;
		}
	}
}
