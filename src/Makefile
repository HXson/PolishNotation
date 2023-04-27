CC=gcc
CFLAGS=-c

all: graph


graph: stack.o printer.o parser.o calc.o graph.o
	$(CC) stack.o printer.o parser.o calc.o graph.o -o ../build/graph

stack.o:
	$(CC) $(CFLAGS) stack.c

printer.o:
	$(CC) $(CFLAGS) printer.c

parser.o:
	$(CC) $(CFLAGS) parser.c

calc.o:
	$(CC) $(CFLAGS) calc.c

graph.o:
	$(CC) $(CFLAGS) graph.c

clean:
	rm -rf *.o ../build/*

rb: clean all

style:
	cp ../materials/linters/CPPLINT.CFG ./
	python3 ../materials/linters/cpplint.py --extensions=c ./*.c
	python3 ../materials/linters/cpplint.py --extensions=c ./*.h
	rm ./CPPLINT.CFG

mem:
	leaks -atExit -- ../build/graph


cpp:
	cppcheck --enable=all --suppress=missingIncludeSystem ./
