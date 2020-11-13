#include "ast.h"
#include "minic.tab.h"
#include <stdio.h>
#include <stdlib.h>
extern int globalsize;
extern Symbol currentFunction;
extern int SP;
InstructionPair C_program(A_program program)
{
	Symbol main;
	InstructionPair temp;
	Instruction start;
	Instruction end;
	Instruction inst;

	if(program == NULL)
		return NULL;

	SP = 0;

	temp = C_declarationlist(program->u.declarationlist2program.declarationlist);

	if(temp == NULL)
	{
		free(inst);
		return NULL;
	}

	main = S_lookup("main");

	if(main==NULL)
	{
		printf("Can not find function main.\n");
		exit(0);		
	}

	// load max address from MEM(0)
	start = (Instruction)malloc(sizeof(*start));
	start->opcode = LD;
	start->r = GP;
	start->s = GP;
	start->t = 0;
	start->branchtarget = NULL;
	end = start;

	// copy gp to fp

	inst = (Instruction)malloc(sizeof(*inst));
	inst->opcode = LDA;
	inst->r = FP;
	inst->s = GP;
	inst->t = 0;
	inst->branchtarget = NULL;

	end->next = inst;
	inst->prev = end;
	end = inst;


	// set gp to 0
	inst = (Instruction)malloc(sizeof(*inst));
	inst->opcode = LDC;
	inst->r = GP;
	inst->s = R0;
	inst->t = 0;
	inst->branchtarget = NULL;

	end->next = inst;
	inst->prev = end;
	end = inst;


	// clear location 0
	inst = (Instruction)malloc(sizeof(*inst));
	inst->opcode = ST;
	inst->r = ZERO;
	inst->s = ZERO;
	inst->t = 0;
	inst->branchtarget = NULL;

	end->next = inst;
	inst->prev = end;
	end = inst;

	// store current FP
	inst = (Instruction)malloc(sizeof(*inst));
	inst->opcode = ST;
	inst->r = FP;
	inst->s = FP;
	inst->t = globalsize;
	inst->branchtarget = NULL;

	end->next = inst;
	inst->prev = end;
	end = inst;

	// push new FP
	inst = (Instruction)malloc(sizeof(*inst));
	inst->opcode = LDA;
	inst->r = FP;
	inst->s = FP;
	inst->t = -globalsize;
	inst->branchtarget = NULL;

	end->next = inst;
	inst->prev = end;
	end = inst;

	// save ret address in R0
	inst = (Instruction)malloc(sizeof(*inst));
	inst->opcode = LDA;
	inst->r = R0;
	inst->s = PC;
	inst->t = 1;
	inst->branchtarget = NULL;

	end->next = inst;
	inst->prev = end;
	end = inst;

	// call function
	inst = (Instruction)malloc(sizeof(*inst));
	inst->opcode = LDA;
	inst->r = PC;
	inst->s = PC;
	inst->t = 0;
	inst->branchtarget = main->head;

	end->next = inst;
	inst->prev = end;
	end = inst;

	// restore current FP
	inst = (Instruction)malloc(sizeof(*inst));
	inst->opcode = LD;
	inst->r = FP;
	inst->s = FP;
	inst->t = 0;
	inst->branchtarget = NULL;

	end->next = inst;
	inst->prev = end;
	end = inst;

	// halting program
	inst = (Instruction)malloc(sizeof(*inst));
	inst->opcode = HALT;
	inst->r = 0;
	inst->s = 0;
	inst->t = 0;
	inst->branchtarget = NULL;

	end->next = inst;
	inst->prev = end;
	end = inst;

	end->next = temp->head;
	temp->head->prev = end;
	temp->head = start;

	return temp;
}

InstructionPair C_declarationlist(A_declarationlist declarationlist)
{
	if(declarationlist == NULL)
		return NULL;

	InstructionPair temp1;
	InstructionPair temp2;
	if(declarationlist->kind == Declarationlist2declarationlist)
	{
		temp1 = C_declarationlist(declarationlist->u.declarationlist2declarationlist.declarationlist);
		temp2 = C_declaration(declarationlist->u.declarationlist2declarationlist.declaration);

		if(temp1 == NULL)
			return temp2;
		else if(temp2 == NULL)
			return temp1;
		else
		{
			temp1->tail->next = temp2->head;
			temp2->head->prev = temp1->tail;
			temp1->tail = temp2->tail;
			free(temp2);
			return temp1;
		}
	}
	else if(declarationlist->kind == Declaration2declarationlist)
	{
		return C_declaration(declarationlist->u.declaration2declarationlist.declaration);
	}
}

InstructionPair C_declaration(A_declaration declaration)
{
	if(declaration == NULL)
		return NULL;
	InstructionPair temp;

	if(declaration->kind == Vardeclaration2declaration)
		temp = C_vardeclaration(declaration->u.vardeclaration2declaration.vardeclaration);
	else if(declaration->kind == Fundeclaration2declaration)
		temp = C_fundeclaration(declaration->u.fundeclaration2declaration.fundeclaration);
	
	return temp;
}

InstructionPair C_vardeclaration(A_vardeclaration vardeclaration)
{
	if(vardeclaration == NULL)
		return NULL;
	// do nothing. Vardeclaration is null after symbol table phase.
	return NULL;
}

InstructionPair C_typespecifier(A_typespecifier typespecifier)
{
	return NULL;
}

InstructionPair C_fundeclaration(A_fundeclaration fundeclaration)
{
	// determine stack size
	// calling convention
	// return
	// 
	if(fundeclaration == NULL)
		return NULL;

	currentFunction = fundeclaration->s;

	SP = 0;


	// save return address in stack
	InstructionPair temp = C_compoundstmt(fundeclaration->u.typespecifier2fundeclaration.compoundstmt);
	Instruction inst;

	if(temp == NULL)
		return NULL;

	// save return address on memory
	inst = (Instruction)malloc(sizeof(*inst));
	inst->opcode = ST;
	inst->r = R0;
	inst->s = FP;
	inst->t = retFO;
	inst->branchtarget = NULL;

	inst->next = temp->head;
	temp->head->prev = inst;
	temp->head = inst;

	// return to caller
	inst = (Instruction)malloc(sizeof(*inst));
	inst->opcode = LD;
	inst->r = PC;
	inst->s = FP;
	inst->t = retFO;
	inst->branchtarget = NULL;

	temp->tail->next = inst;
	inst->prev = temp->tail;
	temp->tail = inst;

	fundeclaration->s->head = temp->head;
	fundeclaration->s->tail = temp->tail;

	currentFunction = NULL;

	return temp;	
}

InstructionPair C_params(A_params params)
{
	// do nothing
	return NULL;
}

InstructionPair C_paramlist(A_paramlist paramlist)
{
	// do nothing
	return NULL;
}

InstructionPair C_param(A_param param)
{
	// do nothing
	return NULL;
}

InstructionPair C_compoundstmt(A_compoundstmt compoundstmt)
{
	if(compoundstmt == NULL)
		return NULL;

	InstructionPair temp = C_statementlist(compoundstmt->u.localdeclarations2compoundstmt.statementlist);
	return temp;
}

InstructionPair C_localdeclarations(A_localdeclarations localdeclarations)
{
	// do nothing
	return NULL;
}

InstructionPair C_statementlist(A_statementlist statementlist)
{
	if(statementlist == NULL)
		return NULL;

	InstructionPair temp1;
	InstructionPair temp2;

	temp1 = C_statementlist(statementlist->u.statementlist2statementlist.statementlist);
	temp2 = C_statement(statementlist->u.statementlist2statementlist.statement);

	if(temp1 == NULL)
		return temp2;
	else if(temp2 == NULL)
		return temp1;
	else
	{
		temp1->tail->next = temp2->head;
		temp2->head->prev = temp1->tail;
		temp1->tail = temp2->tail;
		free(temp2);
		return temp1;
	}
}


InstructionPair C_statement(A_statement statement)
{
	if(statement==NULL)
		return NULL;
	
	if(statement->kind == Expressionstmt2statement)
		return C_expressionstmt(statement->u.expressionstmt2statement.expressionstmt);
	else if(statement->kind == Compoundstmt2statement)
		return C_compoundstmt(statement->u.compoundstmt2statement.compoundstmt);
	else if(statement->kind == Selectionstmt2statement)
		return C_selectionstmt(statement->u.selectionstmt2statement.selectionstmt);
	else if(statement->kind == Iterationstmt2statement)
		return C_iterationstmt(statement->u.iterationstmt2statement.iterationstmt);
	else if(statement->kind == Returnstmt2statement)
		return C_returnstmt(statement->u.returnstmt2statement.returnstmt);
}
		
InstructionPair C_expressionstmt(A_expressionstmt expressionstmt)
{
	if(expressionstmt == NULL)
		return NULL;
	return C_expression(expressionstmt->u.expression2expressionstmt.expression);
}

InstructionPair C_selectionstmt(A_selectionstmt selectionstmt)
{
	InstructionPair expression;
	InstructionPair statement1;
	InstructionPair statement2;
	Instruction inst;
	Instruction elseinst;

	if(selectionstmt == NULL)
		return NULL;

	if(selectionstmt->kind == If2selectionstmt)
	{
		expression = C_expression(selectionstmt->u.if2selectionstmt.expression);
		statement1 = C_statement(selectionstmt->u.if2selectionstmt.statement);
		if(expression == NULL)
			return statement1;
		else if(statement1 == NULL)
			return expression;

		inst = (Instruction)malloc(sizeof(*inst));
		inst->opcode = JEQ;
		inst->r = 0;
		inst->s = PC;
		inst->t = 1;
		inst->branchtarget = statement1->tail;

		expression->tail->next = inst;
		inst->prev = expression->tail;
		inst->next = statement1->head;
		statement1->head->prev = inst;
		expression->tail = statement1->tail;
		free(statement1);
		return expression;
	}
	else if(selectionstmt->kind == Ifelse2selectionstmt)
	{
		expression = C_expression(selectionstmt->u.ifelse2selectionstmt.expression);
		statement1 = C_statement(selectionstmt->u.ifelse2selectionstmt.statement1);
		statement2 = C_statement(selectionstmt->u.ifelse2selectionstmt.statement2);

		if(expression == NULL)
			if(statement1 == NULL)
				return statement2;
			else
				return statement1;

		else if(statement1 == NULL)
			return expression;

		elseinst = (Instruction)malloc(sizeof(*inst));
		elseinst->opcode = LDA;
		elseinst->r = PC;
		elseinst->s = PC;
		elseinst->t = 1;
		elseinst->branchtarget = statement2->tail;

		inst = (Instruction)malloc(sizeof(*inst));
		inst->opcode = JEQ;
		inst->r = 0;
		inst->s = PC;
		inst->t = 0;
		inst->branchtarget = statement2->head;

		expression->tail->next = inst;
		inst->prev = expression->tail;
		inst->next = statement1->head;
		statement1->head->prev = inst;

		statement1->tail->next = elseinst;
		elseinst->prev = statement1->tail;
		elseinst->next = statement2->head;
		statement2->head->prev = elseinst;

		expression->tail = statement2->tail;

		free(statement1);
		free(statement2);
		return expression;
	}
}

	
InstructionPair C_iterationstmt(A_iterationstmt iterationstmt)
{
	InstructionPair expression1;
	InstructionPair expression2;
	InstructionPair expression3;
	InstructionPair statement;

	Instruction branch;
	Instruction repeat;

	if(iterationstmt == NULL)
		return NULL;

	if(iterationstmt->kind == While2iterationstmt)
	{
		expression1 = C_expression(iterationstmt->u.while2iterationstmt.expression);
		statement = C_statement(iterationstmt->u.while2iterationstmt.statement);

		if(expression1 == NULL)
			return NULL;
		else if(statement == NULL)
			return NULL;

		repeat = (Instruction)malloc(sizeof(*repeat));
		repeat->opcode = LDA;
		repeat->r = PC;
		repeat->s = PC;
		repeat->t = 0;
		repeat->branchtarget = expression1->head;
		repeat->prev = statement->tail;
		statement->tail->next = repeat;
		statement->tail = repeat;

		branch = (Instruction)malloc(sizeof(*branch));
		branch->opcode = JEQ;
		branch->r = 0;
		branch->s = PC;
		branch->t = 1;
		branch->branchtarget = statement->tail;

		expression1->tail->next = branch;
		branch->prev = expression1->tail;
		branch->next = statement->head;
		statement->head->prev = branch;
		expression1->tail = statement->tail;

		free(statement);

		return expression1;
	}
	else if(iterationstmt->kind == For2iterationstmt)
	{
		expression1 = C_expression(iterationstmt->u.for2iterationstmt.expression1);
		expression2 = C_expression(iterationstmt->u.for2iterationstmt.expression2);
		expression3 = C_expression(iterationstmt->u.for2iterationstmt.expression3);
		statement = C_statement(iterationstmt->u.for2iterationstmt.statement);

		if(statement == NULL)
			return NULL;

		if(expression3 != NULL)
		{
			statement->tail->next = expression3->head;
			expression3->head->prev = statement->tail;
			statement->tail = expression3->tail;

			free(expression3);
		}
		if(expression2 == NULL)
			return statement;

		repeat = (Instruction)malloc(sizeof(*repeat));
		repeat->opcode = LDA;
		repeat->r = PC;
		repeat->s = PC;
		repeat->t = 0;
		repeat->branchtarget = expression2->head;
		repeat->prev = statement->tail;
		statement->tail->next = repeat;
		statement->tail = repeat;

		if(expression1 == NULL)
			return statement;

		branch = (Instruction)malloc(sizeof(*branch));
		branch->opcode = JEQ;
		branch->r = 0;
		branch->s = PC;
		branch->t = 1;
		branch->branchtarget = statement->tail;

		expression1->tail->next = expression2->head;
		expression2->head->prev = expression1->tail;
		expression2->tail->next = branch;
		branch->prev = expression2->tail;
		branch->next = statement->head;
		statement->head->prev = branch;
		expression1->tail = statement->tail;
		free(statement);
		return expression1;
	}
}

InstructionPair C_returnstmt(A_returnstmt returnstmt)
{
	InstructionPair temp;
	Instruction inst;
	inst = (Instruction)malloc(sizeof(*inst));
	inst->opcode = LD;
	inst->r = PC;
	inst->s = FP;
	inst->t = retFO;
	inst->branchtarget = NULL;

	if(returnstmt != NULL)
	{
		temp = C_expression(returnstmt->u.expression2returnstmt.expression);
		temp->tail->next = inst;
		inst->prev = temp->tail;
		temp->tail = inst;
	}
	else
	{
		temp = (InstructionPair)malloc(sizeof(*temp));
		temp->head = inst;
		temp->tail = inst;
		inst->next = inst;
		inst->prev = inst;
	}
	return temp;
}
		
InstructionPair C_expression(A_expression expression)
{
	InstructionPair temp;
	InstructionPair temp1;
	Instruction inst;
	Symbol s;

	if(expression == NULL)
		return NULL;

	if(expression->kind == Var2expression)	// assignment
	{
		A_var var = expression->u.var2expression.var;
		temp = C_expression(expression->u.var2expression.expression);

		if(var->kind == Id2var)	// normal variable
		{
			s = var->s;
			inst = (Instruction)malloc(sizeof(*inst));
			inst->opcode = ST;
			inst->r = R0;
			if(s->scope == 0)
			{
				inst->s = GP;
				inst->t = s->offset;
			}
			else
			{
				inst->s = FP;
				inst->t = initFO - s->offset;
			}
			inst->branchtarget = NULL;

			temp->tail->next = inst;
			inst->prev = temp->tail;
			temp->tail = inst;
			return temp;
		}
		else if(var->kind = Array2var)	// array
		{
			s = var->s;

			// save expression result in R0 to memory
			inst = (Instruction)malloc(sizeof(*inst));
			inst->opcode = ST;
			inst->r = R0;
			inst->s = FP;
			inst->t = initFO - currentFunction->size - SP;
			inst->branchtarget = NULL;
			SP++;
			temp->tail->next = inst;
			inst->prev = temp->tail;
			temp->tail = inst;

			// get array index
			temp1 = C_expression(var->u.array2var.expression);

			// array offset : R2 = FP - expression value
			inst = (Instruction)malloc(sizeof(*inst));
			inst->opcode = CSUB;
			inst->r = R2;
			inst->s = FP;
			inst->t = R0;
			inst->branchtarget = NULL;

			temp1->tail->next = inst;
			inst->prev = temp1->tail;
			temp1->tail = inst;

			// load saved R0
			SP--;
			inst = (Instruction)malloc(sizeof(*inst));
			inst->opcode = LD;
			inst->r = R1;
			inst->s = FP;
			inst->t = initFO - currentFunction->size - SP;
			inst->branchtarget = NULL;

			temp1->tail->next = inst;
			inst->prev = temp1->tail;
			temp1->tail = inst;

			// store R0 in memory FP - expression_value - symbol_offset - initFO
			inst = (Instruction)malloc(sizeof(*inst));
			inst->opcode = ST;
			inst->r = R1;
			inst->s = R2;
			inst->t = initFO - s->offset;
			inst->branchtarget = NULL;

			temp1->tail->next = inst;
			inst->prev = temp1->tail;
			temp1->tail = inst;

			temp->tail->next = temp1->head;
			temp1->head->prev = temp->tail;
			temp->tail = temp1->tail;
			free(temp1);
			return temp;
		}
	}
	else if(expression->kind == Simpleexpression2expression)
		return C_simpleexpression(expression->u.simpleexpression2expression.simpleexpression);
}

InstructionPair C_var(A_var var)
{
	// do nothing
	return NULL;
}

InstructionPair C_simpleexpression(A_simpleexpression simpleexpression)
{
	InstructionPair additive1;
	InstructionPair additive2;
	Instruction inst;
	Instruction i1;
	Instruction i2;
	Instruction i3;
	Instruction i4;
	if(simpleexpression == NULL)
		return NULL;

	if(simpleexpression->kind == Additiveexpressionrelop2simpleexpression)
	{
		// generator relop code
		additive1 = C_additiveexpression(simpleexpression->u.additiveexpressionrelop2simpleexpression.additiveexpression1);
		additive2 = C_additiveexpression(simpleexpression->u.additiveexpressionrelop2simpleexpression.additiveexpression2);

		// save addtivie1 result(R0) to memory(R0)
		inst = (Instruction)malloc(sizeof(*inst));
		inst->opcode = ST;
		inst->r = R0;
		inst->s = FP;
		inst->t = initFO - currentFunction->size - SP;
		inst->branchtarget = NULL;
		SP++;
		additive1->tail->next = inst;
		inst->prev = additive1->tail;
		additive1->tail = inst;

		// load additive1 result(R1) from memory(R0)
		SP--;
		inst = (Instruction)malloc(sizeof(*inst));
		inst->opcode = LD;
		inst->r = R1;
		inst->s = FP;
		inst->t = initFO - currentFunction->size - SP;
		inst->branchtarget = NULL;
		additive2->tail->next = inst;
		inst->prev = additive2->tail;
		additive2->tail = inst;

		// merge two instruction pair
		additive1->tail->next = additive2->head;
		additive2->head->prev = additive1->tail;
		additive1->tail = additive2->tail;
		free(additive2);

		inst = (Instruction)malloc(sizeof(*inst));
		i1 = (Instruction)malloc(sizeof(*i1));
		i2 = (Instruction)malloc(sizeof(*i2));
		i3 = (Instruction)malloc(sizeof(*i3));
		i4 = (Instruction)malloc(sizeof(*i4));

		inst->opcode = CSUB;
		inst->r = R0;
		inst->s = R1;
		inst->t = R0;
		inst->branchtarget = NULL;

//		i1->opcode = JLE;
		i1->r = R0;
		i1->s = PC;
		i1->t = 0;
		i1->branchtarget = i4;

		i2->opcode = LDC;
		i2->r = R0;
		i2->s = 0;
		i2->t = 0;
		i2->branchtarget = NULL;

		i3->opcode = LDA;
		i3->r = PC;
		i3->s = PC;
		i3->t = 1;
		i3->branchtarget = i4;

		i4->opcode = LDC;
		i4->r = R0;
		i4->s = 1;
		i4->t = 1;
		i4->branchtarget = NULL;

		inst->next = i1;
		i1->next = i2;
		i2->next = i3;
		i3->next = i4;
		i4->prev = i3;
		i3->prev = i2;
		i2->prev = i1;
		i1->prev = inst;

		additive1->tail->next = inst;
		inst->prev = additive1->tail;
		additive1->tail = i4;

		switch(simpleexpression->u.additiveexpressionrelop2simpleexpression.relop)
		{
			// R1 : left, R0 : right
			case LESSEQUAL:
				i1->opcode = JLE;
				break;

			case LESS:
				i1->opcode = JLT;
				break;

			case GREAT:
				i1->opcode = JGT;
				break;

			case GREATEQUAL:
				i1->opcode = JGE;
				break;

			case EQUAL:
				i1->opcode = JEQ;
				break;

			case NOTEQUAL:
				i1->opcode = JNE;
				break;

			default:
				break;
		}

		return additive1;

	}
	else if(simpleexpression->kind == Additiveexpression2simpleexpression)
		return C_additiveexpression(simpleexpression->u.additiveexpression2simpleexpression.additiveexpression);
}


InstructionPair C_additiveexpression(A_additiveexpression additiveexpression)
{
	InstructionPair additive1;
	InstructionPair additive2;

	Instruction inst;

	if(additiveexpression == NULL)
		return NULL;

	if(additiveexpression->kind == Additiveexpression2additiveexpression)
	{
		additive1 = C_additiveexpression(additiveexpression->u.additiveexpression2additiveexpression.additiveexpression);
		additive2 = C_term(additiveexpression->u.additiveexpression2additiveexpression.term);

		// save additive1 result(R0) to memory
		inst = (Instruction)malloc(sizeof(*inst));
		inst->opcode = ST;
		inst->r = R0;
		inst->s = FP;
		inst->t = initFO - currentFunction->size - SP;
		inst->branchtarget = NULL;
		SP++;
		additive1->tail->next = inst;
		inst->prev = additive1->tail;
		additive1->tail = inst;

		// merge two instruction pair

		additive1->tail->next = additive2->head;
		additive2->head->prev = additive1->tail;
		additive1->tail = additive2->tail;
		free(additive2);

		// load additive1 result from memory
		SP--;
		inst = (Instruction)malloc(sizeof(*inst));
		inst->opcode = LD;
		inst->r = R1;
		inst->s = FP;
		inst->t = initFO - currentFunction->size - SP;
		inst->branchtarget = NULL;

		additive1->tail->next = inst;
		inst->prev = additive1->tail;
		additive1->tail = inst;

		// generate additive operation code
		inst = (Instruction)malloc(sizeof(*inst));
		inst->r = R0;
		inst->s = R1;
		inst->t = R0;
		inst->branchtarget = NULL;

		switch(additiveexpression->u.additiveexpression2additiveexpression.addop)
		{
			case ADD:
				inst->opcode = CADD;
				break;

			case SUB:
				inst->opcode = CSUB;

			default:
				break;
		}
		additive1->tail->next = inst;
		inst->prev = additive1->tail;
		additive1->tail = inst;
		return additive1;
	}
	else if(additiveexpression->kind == Term2additiveexpression)
		return C_term(additiveexpression->u.term2additiveexpression.term);

}


InstructionPair C_term(A_term term)
{
	InstructionPair term1;
	InstructionPair term2;
	Instruction inst;

	if(term == NULL)
		return NULL;

	if(term->kind == Term2term)
	{
		term1 = C_term(term->u.term2term.term);
		term2 = C_factor(term->u.term2term.factor);

		// save term1 result(R0) to memory
		inst = (Instruction)malloc(sizeof(*inst));
		inst->opcode = ST;
		inst->r = R0;
		inst->s = FP;
		inst->t = initFO - currentFunction->size - SP;
		inst->branchtarget = NULL;
		SP++;

		// merge two instruction pair
		term1->tail->next = inst;
		inst->prev = term1->tail;
		inst->next = term2->head;
		term2->head->prev = inst;
		term1->tail = term2->tail;
		free(term2);

		// load term1 result from memory
		SP--;
		inst = (Instruction)malloc(sizeof(*inst));
		inst->opcode = LD;
		inst->r = R1;
		inst->s = FP;
		inst->t = initFO - currentFunction->size - SP;
		inst->branchtarget = NULL;
		term1->tail->next = inst;
		inst->prev = term1->tail;
		term1->tail = inst;

		// generate mulop code
		inst = (Instruction)malloc(sizeof(*inst));
		inst->r = R0;
		inst->s = R1;
		inst->t = R0;
		inst->branchtarget = NULL;
		term1->tail->next = inst;
		inst->prev = term1->tail;
		term1->tail = inst;

		switch(term->u.term2term.mulop)
		{
			case MULT:
				inst->opcode = CMUL;
				break;

			case DIV:
				inst->opcode = CDIV;
				break;

			default:
				break;
		}
		return term1;
	}
	else if(term->kind == Factor2term)
		return C_factor(term->u.factor2term.factor);

	else if(term->kind == Uminus2term)
	{
		term1 = C_factor(term->u.uminus2term.factor);
		inst = (Instruction)malloc(sizeof(*inst));
		inst->opcode = LDC;
		inst->r = R1;
		inst->s = 0;
		inst->t = -1;
		inst->branchtarget = NULL;
		term1->tail->next = inst;
		inst->prev = term1->tail;
		term1->tail = inst;

		inst = (Instruction)malloc(sizeof(*inst));
		inst->opcode = CMUL;
		inst->r = R0;
		inst->s = R0;
		inst->t = R1;
		inst->branchtarget = NULL;
		term1->tail->next = inst;
		inst->prev = term1->tail;
		term1->tail = inst;

		return term1;
	}
}

InstructionPair C_factor(A_factor factor)
{
	InstructionPair temp;
	Instruction inst;
	A_var var;
	Symbol s;

	if(factor->kind == Expression2factor)
		return C_expression(factor->u.expression2factor.expression);
	else if(factor->kind == Var2factor)
	{
		// load memory value to register R0
		var = factor->u.var2factor.var;
		s = var->s;

		if(var->kind == Id2var)
		{
			inst = (Instruction)malloc(sizeof(*inst));
			inst->opcode = LD;
			inst->r = R0;
			if(s->scope == 0)
			{
				inst->s = GP;
				inst->t = var->s->offset;
			}
			else
			{
				inst->s = FP;
				inst->t = initFO - var->s->offset;
			}
			inst->branchtarget = NULL;
			temp = (InstructionPair)malloc(sizeof(*temp));
			temp->head = inst;
			temp->tail = inst;
			inst->prev = inst;
			inst->next = inst;
			return temp;
		}
		else if(var->kind == Array2var)
		{
			temp = C_expression(var->u.array2var.expression);
			inst = (Instruction)malloc(sizeof(*inst));
			inst->opcode = LDA;
			inst->r = R1;
			if(s->scope == 0)
			{
				inst->s = GP;
				inst->t = var->s->offset;
			}
			else
			{
				inst->s = FP;
				inst->t = initFO - var->s->offset;
			}
			inst->branchtarget = NULL;

			temp->tail->next = inst;
			inst->prev = temp->tail;
			temp->tail = inst;

			inst = (Instruction)malloc(sizeof(*inst));
			inst->opcode = CSUB;
			inst->r = R1;
			inst->s = R1;
			inst->t = R0;
			inst->branchtarget = NULL;

			temp->tail->next = inst;
			inst->prev = temp->tail;
			temp->tail = inst;

			inst = (Instruction)malloc(sizeof(*inst));
			inst->opcode = LD;
			inst->r = R0;
			inst->s = R1;
			inst->t = 0;
			inst->branchtarget = NULL;

			temp->tail->next = inst;
			inst->prev = temp->tail;
			temp->tail = inst;

			return temp;

		}
	}
	else if(factor->kind == Call2factor)
	{
		return C_call(factor->u.call2factor.call);
	}
	else if(factor->kind == Num2factor)
	{
		temp = (InstructionPair)malloc(sizeof(*temp));
		inst = (Instruction)malloc(sizeof(*inst));
		inst->opcode = LDC;
		inst->r = R0;
		inst->s = 0;
		inst->t = factor->u.num2factor.num;
		inst->branchtarget = NULL;
		inst->next = inst;
		inst->prev = inst;
		temp->head = inst;
		temp->tail = inst;
		return temp;
	}
}

InstructionPair C_call(A_call call)
{
	InstructionPair temp;
	Instruction inst;
	int savedsp = SP;

	SP += 2;

	temp = C_args(call->u.id2call.args);

	if(temp!=NULL)
	{
		// store current FP
		inst = (Instruction)malloc(sizeof(*inst));
		inst->opcode = ST;
		inst->r = FP;
		inst->s = FP;
		inst->t = initFO - currentFunction->size - savedsp;
		inst->branchtarget = NULL;

		temp->tail->next = inst;
		inst->prev = temp->tail;
		temp->tail = inst;

		// push new FP
		inst = (Instruction)malloc(sizeof(*inst));
		inst->opcode = LDA;
		inst->r = FP;
		inst->s = FP;
		inst->t = initFO - currentFunction->size - savedsp;
		inst->branchtarget = NULL;

		temp->tail->next = inst;
		inst->prev = temp->tail;
		temp->tail = inst;

		// save ret address in R0
		inst = (Instruction)malloc(sizeof(*inst));
		inst->opcode = LDA;
		inst->r = R0;
		inst->s = PC;
		inst->t = 1;
		inst->branchtarget = NULL;

		temp->tail->next = inst;
		inst->prev = temp->tail;
		temp->tail = inst;

		// call function
		inst = (Instruction)malloc(sizeof(*inst));
		inst->opcode = LDA;
		inst->r = PC;
		inst->s = PC;
		inst->t = 0;
		inst->branchtarget = call->s->head;

		temp->tail->next = inst;
		inst->prev = temp->tail;
		temp->tail = inst;

		// restore current FP
		inst = (Instruction)malloc(sizeof(*inst));
		inst->opcode = LD;
		inst->r = FP;
		inst->s = FP;
		inst->t = 0;
		inst->branchtarget = NULL;

		temp->tail->next = inst;
		inst->prev = temp->tail;
		temp->tail = inst;

		SP = savedsp;

		return temp;
	}
	else if(temp == NULL)
	{
		temp = (InstructionPair)malloc(sizeof(*temp));
		// store current FP
		inst = (Instruction)malloc(sizeof(*inst));
		inst->opcode = ST;
		inst->r = FP;
		inst->s = FP;
		inst->t = initFO - currentFunction->size - savedsp;
		inst->branchtarget = NULL;

		inst->prev = inst;
		inst->next = inst;
		temp->head = inst;
		temp->tail = inst;

		// push new FP
		inst = (Instruction)malloc(sizeof(*inst));
		inst->opcode = LDA;
		inst->r = FP;
		inst->s = FP;
		inst->t = initFO - currentFunction->size - savedsp;
		inst->branchtarget = NULL;

		temp->tail->next = inst;
		inst->prev = temp->tail;
		temp->tail = inst;

		// save ret address in R0
		inst = (Instruction)malloc(sizeof(*inst));
		inst->opcode = LDA;
		inst->r = R0;
		inst->s = PC;
		inst->t = 1;
		inst->branchtarget = NULL;

		temp->tail->next = inst;
		inst->prev = temp->tail;
		temp->tail = inst;

		// call function
		inst = (Instruction)malloc(sizeof(*inst));
		inst->opcode = LDA;
		inst->r = PC;
		inst->s = PC;
		inst->t = 0;
		inst->branchtarget = call->s->head;

		temp->tail->next = inst;
		inst->prev = temp->tail;
		temp->tail = inst;

		// restore current FP
		inst = (Instruction)malloc(sizeof(*inst));
		inst->opcode = LD;
		inst->r = FP;
		inst->s = FP;
		inst->t = ofpFO;
		inst->branchtarget = NULL;

		temp->tail->next = inst;
		inst->prev = temp->tail;
		temp->tail = inst;

		SP = savedsp;
		return temp;
	}

}
InstructionPair C_args(A_args args)
{
	if(args == NULL)
		return NULL;
	else if(args->kind == Arglist2args)
		return C_arglist(args->u.arglist2args.arglist);
}

InstructionPair C_arglist(A_arglist arglist)
{
	InstructionPair arg1;
	InstructionPair arg2;
	Instruction inst;

	if(arglist == NULL)
		return NULL;

	if(arglist->kind == Arglist2arglist)
	{
		arg1 = C_arglist(arglist->u.arglist2arglist.arglist);
		arg2 = C_expression(arglist->u.arglist2arglist.expression);
		inst = (Instruction)malloc(sizeof(*inst));
		inst->opcode = ST;
		inst->r = R0;
		inst->s = FP;
		inst->t = initFO - currentFunction->size - SP;
		inst->branchtarget = NULL;
		SP++;

		// merge two instruction pair and instruction
		arg1->tail->next = arg2->head;
		arg2->head->prev = arg1->tail;
		arg2->tail->next = inst;
		inst->prev = arg2->tail;
		arg1->tail = inst;
		free(arg2);
		
		return arg1;
	}
	else if(arglist->kind == Expression2arglist)
	{
		arg1 = C_expression(arglist->u.expression2arglist.expression);
		inst = (Instruction)malloc(sizeof(*inst));
		inst->opcode = ST;
		inst->r = R0;
		inst->s = FP;
		inst->t = initFO - currentFunction->size - SP;
		inst->branchtarget = NULL;
		SP++;

		// merge instruction pair and instruction
		arg1->tail->next = inst;
		inst->prev = arg1->tail;
		arg1->tail = inst;

		return arg1;
	}
}

void AdjustInstruction(InstructionPair program)
{
	int offset = 0;
	Instruction currentInst = program->head;

	while(currentInst!=NULL)
	{
		currentInst->offset = offset;
		offset++;
		currentInst = currentInst->next;
	}

	currentInst = program->head;

	while(currentInst!=NULL)
	{
		if(currentInst->branchtarget != NULL)
		{
			currentInst->t = currentInst->branchtarget->offset - currentInst->offset + currentInst->t -1;
		}
		currentInst = currentInst->next;
	}
}

void PrintCode(InstructionPair program)
{
	Instruction currentInst = program->head;

	while(currentInst != NULL)
	{
		PrintInstruction(currentInst);
		currentInst = currentInst->next;
	}
}

void PrintInstruction(Instruction inst)
{
	printf("%2d:  ", inst->offset);
	
	switch(inst->opcode)
	{
		case HALT:
			printf("HALT  ");
			printf("%d, %d, %d\n", inst->r, inst->s, inst->t);
			break;

		case IN:
			printf("IN  ");
			printf("%d, %d, %d\n", inst->r, inst->s, inst->t);
			break;

		case OUT:
			printf("OUT  ");
			printf("%d, %d, %d\n", inst->r, inst->s, inst->t);
			break;

		case CADD:
			printf("ADD  ");
			printf("%d, %d, %d\n", inst->r, inst->s, inst->t);
			break;

		case CSUB:
			printf("SUB  ");
			printf("%d, %d, %d\n", inst->r, inst->s, inst->t);
			break;

		case CMUL:
			printf("MUL  ");
			printf("%d, %d, %d\n", inst->r, inst->s, inst->t);
			break;

		case CDIV:
			printf("DIV  ");
			printf("%d, %d, %d\n", inst->r, inst->s, inst->t);
			break;

		case LD:
			printf("LD  ");
			printf("%d, %d(%d)\n", inst->r, inst->t, inst->s);
			break;

		case LDA:
			printf("LDA  ");
			printf("%d, %d(%d)\n", inst->r, inst->t, inst->s);
			break;

		case LDC:
			printf("LDC  ");
			printf("%d, %d, %d\n", inst->r, inst->t, inst->s);
			break;

		case ST:
			printf("ST  ");
			printf("%d, %d(%d)\n", inst->r, inst->t, inst->s);
			break;

		case JLT:
			printf("JLT  ");
			printf("%d, %d(%d)\n", inst->r, inst->t, inst->s);
			break;

		case JLE:
			printf("JLE  ");
			printf("%d, %d(%d)\n", inst->r, inst->t, inst->s);
			break;

		case JGE:
			printf("JGE  ");
			printf("%d, %d(%d)\n", inst->r, inst->t, inst->s);
			break;

		case JGT:
			printf("JGT  ");
			printf("%d, %d(%d)\n", inst->r, inst->t, inst->s);
			break;

		case JEQ:
			printf("JEQ  ");
			printf("%d, %d(%d)\n", inst->r, inst->t, inst->s);
			break;

		case JNE:
			printf("JNE  ");
			printf("%d, %d(%d)\n", inst->r, inst->t, inst->s);
			break;

		default:
			break;
	}
}
