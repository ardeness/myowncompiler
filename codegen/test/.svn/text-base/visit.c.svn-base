#include "visit.h"
#include "minic.tab.h"
#include <stdio.h>
#include <stdlib.h>

int bottom;
int linenumber;
Symbol currentFunction;

void V_program(A_program program)
{
	Symbol main;
	if(program == NULL)
		return;

	linenumber = 0;
	bottom = 0;

	linenumber = 5;
	V_declarationlist(program->u.declarationlist2program.declarationlist);

	main = S_lookup("main");

	if(main == NULL)
	{
		printf("main 함수를 찾을 수 없습니다. 종료합니다. \n");
		exit(-1);
	}

	linenumber = 0;

	printf("* 프로그램 초기화 \n");
	printf("%d : LD %d, %d(%d)\n", linenumber, FP, 0, R0);	// 최대 주소값을 FP에 저장
	linenumber++;
	printf("%d : ST %d, %d(%d)\n", linenumber, R0, 0, R0);	// 0번지 값을 0으로 초기화
	linenumber++;
	printf("%d : LDA %d, %d(%d)\n", linenumber, R0, 1, PC);	// return 주소 R0에 저장
	linenumber++;
	printf("%d : LDA %d, %d(%d)\n", linenumber, PC, main->startlinenumber - (linenumber + 1), PC);	// main 함수 호출
	linenumber++;
	printf("%d : HALT %d, %d, %d\n", linenumber, 0, 0, 0);	// 프로그램 종료

}

void V_declarationlist(A_declarationlist declarationlist)
{
	if(declarationlist == NULL)
		return;

	if(declarationlist->kind == Declarationlist2declarationlist)
	{
		V_declarationlist(declarationlist->u.declarationlist2declarationlist.declarationlist);
		V_declaration(declarationlist->u.declarationlist2declarationlist.declaration);
	}
	else if(declarationlist->kind == Declaration2declarationlist)
	{
		V_declaration(declarationlist->u.declaration2declarationlist.declaration);
	}
}

void V_declaration(A_declaration declaration)
{
	if(declaration == NULL)
		return;
	
	if(declaration->kind == Fundeclaration2declaration)
	{
		V_fundeclaration(declaration->u.fundeclaration2declaration.fundeclaration);
	}
}

void V_vardeclaration(A_vardeclaration vardeclaration)
{
	if(vardeclaration == NULL)
		return;
}

void V_typespecifier(A_typespecifier typespecifier)
{
	if(typespecifier == NULL)
		return;
}

void V_fundeclaration(A_fundeclaration fundeclaration)
{
	if(fundeclaration == NULL)
		return;

	bottom = 0;

	if(fundeclaration->kind == Typespecifier2fundeclaration)
	{
		printf("* 함수 %s 시작 \n", fundeclaration->s->name);
		currentFunction = fundeclaration->s;
		fundeclaration->s->startlinenumber = linenumber;
		printf("%d : ST %d, %d(%d)\n", linenumber, R0, retFO, FP);
		linenumber++;

		V_compoundstmt(fundeclaration->u.typespecifier2fundeclaration.compoundstmt);

		printf("%d : LD %d, %d(%d)\n", linenumber, PC, retFO, FP);
		linenumber++;

		printf("* 함수 %s 끝 \n", fundeclaration->s->name);
	}
	
}

void V_params(A_params params)
{
	if(params == NULL)
		return;
}

void V_paramlist(A_paramlist paramlist)
{
	if(paramlist == NULL)
		return;
}

void V_param(A_param param)
{
	if(param == NULL)
		return;
}

void V_compoundstmt(A_compoundstmt compoundstmt)
{
	if(compoundstmt == NULL)
		return;

	if(compoundstmt->kind == Localdeclarations2compoundstmt)
	{
		V_statementlist(compoundstmt->u.localdeclarations2compoundstmt.statementlist);
	}
}

void V_localdeclarations(A_localdeclarations localdeclarations)
{
	if(localdeclarations == NULL)
		return;
}

void V_statementlist(A_statementlist statementlist)
{
	if(statementlist == NULL)
		return;

	if(statementlist->kind == Statementlist2statementlist)
	{
		V_statementlist(statementlist->u.statementlist2statementlist.statementlist);
		V_statement(statementlist->u.statementlist2statementlist.statement);
	}
}

void V_statement(A_statement statement)
{
	if(statement == NULL)
		return;

	if(statement->kind == Expressionstmt2statement)
	{
		V_expressionstmt(statement->u.expressionstmt2statement.expressionstmt);
	}
	else if(statement->kind == Compoundstmt2statement)
	{
		V_compoundstmt(statement->u.compoundstmt2statement.compoundstmt);
	}
	else if(statement->kind == Selectionstmt2statement)
	{
		V_selectionstmt(statement->u.selectionstmt2statement.selectionstmt);
	}
	else if(statement->kind == Iterationstmt2statement)
	{
		V_iterationstmt(statement->u.iterationstmt2statement.iterationstmt);
	}
	else if(statement->kind == Returnstmt2statement)
	{
		V_returnstmt(statement->u.returnstmt2statement.returnstmt);
	}
}

void V_expressionstmt(A_expressionstmt expressionstmt)
{
	if(expressionstmt == NULL)
		return;

	if(expressionstmt->kind == Expression2expressionstmt)
	{
		V_expression(expressionstmt->u.expression2expressionstmt.expression);
	}
}

void V_selectionstmt(A_selectionstmt selectionstmt)
{
	int temp_linenumber;
	int temp_linenumber1;
	if(selectionstmt == NULL)
		return;

	if(selectionstmt->kind == If2selectionstmt)
	{
		printf("* if 구문 \n");

		V_expression(selectionstmt->u.if2selectionstmt.expression);

		temp_linenumber = linenumber;
		linenumber++;
		
		V_statement(selectionstmt->u.if2selectionstmt.statement);

		printf("* expression이 참이면 아래 statment 수행, 그렇지 않다면 탈출 \n");
		printf("%d : JEQ %d, %d(%d)\n", temp_linenumber, R0, linenumber - (temp_linenumber + 1), PC);

	}
	else if(selectionstmt->kind == Ifelse2selectionstmt)
	{
		printf("*if else 구문 \n");

		V_expression(selectionstmt->u.ifelse2selectionstmt.expression);

		temp_linenumber = linenumber;
		linenumber++;

		V_statement(selectionstmt->u.ifelse2selectionstmt.statement1);

		temp_linenumber1 = linenumber;
		linenumber++;

		V_statement(selectionstmt->u.ifelse2selectionstmt.statement2);
		
		printf("* expression이 참이면 아래 statement 수행, 그렇지 않다면 else statement 탈출 \n");
		printf("%d : JEQ %d, %d(%d)\n", temp_linenumber, R0, temp_linenumber1 + 1 - (temp_linenumber - 1), PC);

		printf("* else statement는 실행하지 않음 \n");
		printf("%d : LDA %d, %d(%d)\n", temp_linenumber1, PC, linenumber - (temp_linenumber1 + 1), PC);
	}
}

void V_iterationstmt(A_iterationstmt iterationstmt)
{
	int exp_linenumber;
	int temp_linenumber;
	if(iterationstmt == NULL)
		return;

	if(iterationstmt->kind == While2iterationstmt)
	{
		printf("*while 구문 \n");
		exp_linenumber = linenumber;
		V_expression(iterationstmt->u.while2iterationstmt.expression);

		temp_linenumber = linenumber;
		linenumber++;

		V_statement(iterationstmt->u.while2iterationstmt.statement);
		printf("%d : LDA %d, %d(%d)\n", linenumber, PC, exp_linenumber - (linenumber + 1), PC);	// repeat
		linenumber++;

		printf("%d : JEQ %d, %d(%d)\n", temp_linenumber, R0, linenumber - (temp_linenumber + 1), PC);
	}
	else if(iterationstmt->kind == For2iterationstmt)
	{
		V_expression(iterationstmt->u.for2iterationstmt.expression1);

		exp_linenumber = linenumber;
		V_expression(iterationstmt->u.for2iterationstmt.expression2);

		temp_linenumber = linenumber;
		linenumber++;
		V_statement(iterationstmt->u.for2iterationstmt.statement);

		V_expression(iterationstmt->u.for2iterationstmt.expression3);

		printf("%d : LDA %d, %d(%d)\n", linenumber, PC, exp_linenumber - (linenumber + 1), PC); // repeat
		linenumber++;

		printf("%d : JEQ %d, %d(%d)\n", temp_linenumber, R0, linenumber - (temp_linenumber + 1), PC);
	}
}

void V_returnstmt(A_returnstmt returnstmt)
{
	if(returnstmt == NULL)
	{
		printf("%d : LD %d, %d(%d)\n", linenumber, PC, retFO, FP);
		linenumber++;
	}
	else if(returnstmt->kind == Expression2returnstmt)
	{
		V_expression(returnstmt->u.expression2returnstmt.expression);
		printf("%d : LD %d, %d(%d)\n", linenumber, PC, retFO, FP);
		linenumber++;
	}
}

void V_expression(A_expression expression)
{
	if(expression == NULL)
		return;

	if(expression->kind == Var2expression)
	{
		A_var var = expression->u.var2expression.var;
		Symbol s = expression->u.var2expression.var->s;
		V_expression(expression->u.var2expression.expression);

		if(var->kind == Array2var)
		{
			printf("* 배열일 경우의 처리 \n");
			printf("* 오른쪽 expression 결과인 R0를 메모리에 저장 \n");
			printf("%d : ST %d, %d(%d)\n", linenumber, R0, initFO - currentFunction->size - bottom, FP);
			linenumber++;
			bottom--;

			V_expression(var->u.array2var.expression);

			printf("* 메모리에 저장된 오른쪽 expression 결과를 R1에 로드 \n");
			bottom++;
			printf("%d : LD %d, %d(%d)\n", linenumber, R1, initFO - currentFunction->size - bottom, FP);
			linenumber++;

			printf("* 배열 변수의 시작 주소 오프셋을 R2에 설정 \n");
			printf("%d : LDC %d, %d(%d)\n", linenumber, R2, -1 * s->offset + initFO, FP);
			linenumber++;

			printf("* 배열 변수 시작 오프셋에서 [] 안의 값을 빼서 R2에 저장 \n");
			printf("%d : SUB %d, %d, %d\n", linenumber, R2, R2, R0);
			linenumber++;

			printf("* R2 에 FP - 배열 시작 주소 - 오프셋 주소 값을 저장 \n");
			printf("%d : ADD %d, %d, %d\n", linenumber, R2, R2, FP);
			linenumber++;

			printf("* 계산된 주소에 값을 저장 \n");
			printf("%d : ST %d, %d(%d)\n", linenumber, R1, 0, R2);
			linenumber++;

		}
		else if(var->kind == Id2var)
		{
			printf("* 단순 변수일 경우 \n");
			printf("%d : ST %d, %d(%d)\n", linenumber, R0, -1 * s->offset + initFO, FP);
			linenumber++;
		}
	}
	else if(expression->kind == Simpleexpression2expression)
	{
		V_simpleexpression(expression->u.simpleexpression2expression.simpleexpression);
	}
}

void V_var(A_var var)
{
	if(var == NULL)
		return;
	printf("* 변수 값을 R0에 저장 \n");
	printf("%d : LD %d, %d(%d)\n", linenumber, R0, initFO - var->s->offset, FP);
	linenumber++;
}

void V_simpleexpression(A_simpleexpression simpleexpression)
{
	if(simpleexpression == NULL)
		return;

	if(simpleexpression->kind == Additiveexpressionrelop2simpleexpression)
	{
		V_additiveexpression(simpleexpression->u.additiveexpressionrelop2simpleexpression.additiveexpression1);

		printf("* R0 대피\n");
		printf("%d : ST %d %d(%d)\n", linenumber, R0, initFO - currentFunction->size - bottom, FP);
		linenumber++;
		bottom++;

		V_additiveexpression(simpleexpression->u.additiveexpressionrelop2simpleexpression.additiveexpression2);

		printf("* 대피한 R0을 R1으로 복구 \n");
		bottom--;
		printf("%d : LD %d %d(%d)\n", linenumber, R1, initFO - currentFunction->size - bottom, FP);
		linenumber++;

		printf("%d : SUB %d, %d, %d\n", linenumber, R0, R1, R0);
		linenumber++;

		switch(simpleexpression->u.additiveexpressionrelop2simpleexpression.relop)
		{
		case LESS:
			printf("%d : JLT %d, 2(%d)\n", linenumber, R0, PC);
			linenumber++;
			break;
		case GREAT:
			printf("%d : JGT %d, 2(%d)\n", linenumber, R0, PC);
			linenumber++;
			break;
		case LESSEQUAL:
			printf("%d : JLE %d, 2(%d)\n", linenumber, R0, PC);
			linenumber++;
			break;
		case GREATEQUAL:
			printf("%d : JGE %d, 2(%d)\n", linenumber, R0, PC);
			linenumber++;
			break;
		case EQUAL:
			printf("%d : JEQ %d, 2(%d)\n", linenumber, R0, PC);
			linenumber++;
			break;
		case NOTEQUAL:
			printf("%d : JNE %d, 2(%d)\n", linenumber, R0, PC);
			linenumber++;
			break;
		default:
			break;
		}
		printf("%d : LDC 0, 0(0)\n", linenumber);
		linenumber++;
		printf("%d : LDA %d, 1(%d)\n", linenumber, PC);
		linenumber++;
		printf("%d : LDC 0, 1(0)\n", linenumber);
		linenumber++;

	}
	else if(simpleexpression->kind == Additiveexpression2simpleexpression)
	{
		V_additiveexpression(simpleexpression->u.additiveexpression2simpleexpression.additiveexpression);
	}
}


void V_additiveexpression(A_additiveexpression additiveexpression)
{
	if(additiveexpression == NULL)
		return;

	if(additiveexpression->kind == Additiveexpression2additiveexpression)
	{
		V_additiveexpression(additiveexpression->u.additiveexpression2additiveexpression.additiveexpression);

		printf("* R0 대피\n");
		printf("%d : ST %d %d(%d)\n", linenumber, R0, initFO - currentFunction->size - bottom, FP);
		linenumber++;
		bottom++;

		V_term(additiveexpression->u.additiveexpression2additiveexpression.term);

		printf("* 대피한 R0을 R1으로 복구 \n");
		bottom--;
		printf("%d : LD %d %d(%d)\n", linenumber, R1, initFO - currentFunction->size - bottom, FP);
		linenumber++;

		switch(additiveexpression->u.additiveexpression2additiveexpression.addop)
		{
		case ADD:
			printf("%d : ADD %d, %d, %d\n", linenumber, R0, R1, R0);
			linenumber++;
			break;
		case SUB:
			printf("%d : SUB %d, %d, %d\n", linenumber, R0, R1, R0);
			linenumber++;
			break;
		default:
			break;
		}
	}
	else if(additiveexpression->kind == Term2additiveexpression)
	{
		V_term(additiveexpression->u.term2additiveexpression.term);
	}
}


void V_term(A_term term)
{
	if(term == NULL)
		return;

	if(term->kind == Term2term)
	{
		V_term(term->u.term2term.term);

		printf("* R0 대피\n");
		printf("%d : ST %d %d(%d)\n", linenumber, R0, initFO - currentFunction->size - bottom, FP);
		linenumber++;
		bottom++;

		V_factor(term->u.term2term.factor);

		printf("* 대피한 R0을 R1으로 복구 \n");
		bottom--;
		printf("%d : LD %d %d(%d)\n", linenumber, R1, initFO - currentFunction->size - bottom, FP);
		linenumber++;

		switch(term->u.term2term.mulop)
		{
		case MULT:
			printf("%d : MUL %d, %d, %d\n", linenumber, R0, R1, R0);
			linenumber++;
			break;
		case DIV:
			printf("%d : DIV %d, %d, %d\n", linenumber, R0, R1, R0);
			linenumber++;
			break;
		default:
			break;
		}
	}
	else if(term->kind == Factor2term)
	{
		V_factor(term->u.factor2term.factor);
	}
	else if(term->kind == Uminus2term)
	{
		V_factor(term->u.uminus2term.factor);
	}
}


void V_factor(A_factor factor)
{
	if(factor == NULL)
		return;

	if(factor->kind == Expression2factor)
	{
		V_expression(factor->u.expression2factor.expression);
	}
	else if(factor->kind == Var2factor)
	{
		V_var(factor->u.var2factor.var);
	}
	else if(factor->kind == Call2factor)
	{
		V_call(factor->u.call2factor.call);
	}
	else if(factor->kind == Num2factor)
	{
		// 상수 읽는 코드 생성
		printf("* 상수를 읽어서 R0에 저장\n");
		printf("%d : LDC %d, %d(%d)\n", linenumber, R0, factor->u.num2factor.num, FP);
		linenumber++;
	}
}

void V_call(A_call call)
{
	int temp_bottom;

	if(call == NULL)
		return;

	if(call->kind == Id2call)
	{
		temp_bottom = bottom;
		bottom = bottom + 2;
		printf("* %s 함수 호출\n", call->s->name);
		printf("* 인자 전달 시작\n");
		V_args(call->u.id2call.args);
		printf("* 인자 전달 끝\n");

		printf("%d : ST %d, %d(%d)\n", linenumber, FP, ofpFO - currentFunction->size - temp_bottom , FP);
		linenumber++;

		printf("%d : LDA %d, %d(%d)\n", linenumber, FP, ofpFO - currentFunction->size - temp_bottom, FP);
		linenumber++;

		printf("%d : LDA %d, %d(%d)\n", linenumber, R0, 1, PC);
		linenumber++;

		printf("%d : LDA %d, %d(%d)\n", linenumber, PC, call->s->startlinenumber - (linenumber + 1), PC);
		linenumber++;
		printf("*%s 함수 호출 끝\n", call->s->name);
		bottom = temp_bottom;
	}
}

void V_args(A_args args)
{
	if(args == NULL)
		return;

	if(args->kind == Arglist2args)
	{
		V_arglist(args->u.arglist2args.arglist);
	}
}

void V_arglist(A_arglist arglist)
{
	if(arglist == NULL)
		return;
	
	if(arglist->kind == Arglist2arglist)
	{
		V_arglist(arglist->u.arglist2arglist.arglist);
		V_expression(arglist->u.arglist2arglist.expression);
		printf("%d : ST %d, %d(%d)\n", linenumber, R0, initFO - currentFunction->size - bottom, FP);
		linenumber++;
		bottom++;
	}
	else if(arglist->kind == Expression2arglist)
	{
		V_expression(arglist->u.expression2arglist.expression);
		printf("%d : ST %d, %d(%d)\n", linenumber, R0, initFO - currentFunction->size - bottom, FP);
		linenumber++;
		bottom++;
	}
}


