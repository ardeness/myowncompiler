all : minic.tab.c lex.yy.c minic.tab.h
	gcc minic.tab.c lex.yy.c constructor.c -o compiler

debug : minic.tab.c lex.yy.c minic.tab.h
	gcc -g minic.tab.c lex.yy.c constructor.c -o compiler_debug

minic.tab.c : minic.y
	bison -d minic.y

minic.tab.h : minic.y
	bison -d minic.y

lex.yy.c : scanner.l
	flex scanner.l

clean:
	rm -f minic.tab.c minic.tab.h lex.yy.c compiler compiler_debug
