# Esse arquivo foi feito com base no Makefile disponibilizado no site do Marcelo Johann
# https://www.inf.ufrgs.br/~johann/comp/

OPTIONS = -std=c++11 -Wall
ETAPA = etapa5

target: %$(ETAPA)

%$(ETAPA): symbols.o ast.o parser.tab.o lex.yy.o TAC.o
	g++ $(OPTIONS) -o $(ETAPA) symbols.o ast.o parser.tab.o lex.yy.o TAC.o
%.o: %.cpp %.hpp
	g++ $(OPTIONS) $< -c
	
parser.tab.cpp: parser.ypp
	bison parser.ypp -d

lex.yy.cpp: scanner.l
	flex -o lex.yy.cpp scanner.l
clean:
	rm *.o lex.yy.cpp parser.tab.cpp parser.tab.hpp $(ETAPA)