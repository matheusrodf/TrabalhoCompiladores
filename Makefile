# Esse arquivo foi feito com base no Makefile disponibilizado no site do Marcelo Johann
# https://www.inf.ufrgs.br/~johann/comp/

OPTIONS = -std=c++11 -Wall

etapa1: lex.yy.o main.o symbols.o
	g++ $(OPTIONS) -o etapa1 lex.yy.o main.o symbols.o
%.o: %.cpp
	g++ $(OPTIONS) $< -c
lex.yy.cpp: scanner.l
	flex -o lex.yy.cpp scanner.l 
clean:
	rm *.o lex.yy.cpp etapa1