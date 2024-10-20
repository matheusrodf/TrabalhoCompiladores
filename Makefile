# Esse arquivo foi feito com base no Makefile disponibilizado no site do Marcelo Johann
# https://www.inf.ufrgs.br/~johann/comp/

OPTIONS = -std=c++11 -Wall
ETAPA = etapa2

target: %$(ETAPA)

%$(ETAPA): lex.yy.o symbols.o parser.tab.o
	g++ $(OPTIONS) -o $(ETAPA) lex.yy.o symbols.o parser.tab.o
%.o: %.cpp %.hpp
	g++ $(OPTIONS) $< -c
	
parser.tab.cpp: parser.ypp
	bison parser.ypp -d


lex.yy.cpp: scanner.l
	flex -o lex.yy.cpp scanner.l
clean:
	rm *.o lex.yy.cpp parser.tab.cpp parser.tab.hpp $(ETAPA)