#ifndef AST_HPP
#define AST_HPP

#include "symbols.hpp"


enum TYPES {
	NENHUM = 0,
	IDENTIFICADOR = 1,
	COMANDO = 2,
	ASSINALAMENTO = 3,
	ARIT_SOMA = 4,
	ARIT_SUB = 5,
	ARIT_MULT = 6,
	ARIT_DIV = 7,
	BOOL_NEGACAO = 8,
	BOOL_MENOR = 9,
	BOOL_MAIOR = 10,
	BOOL_IGUAL = 11,
	BOOL_AND = 12,
	BOOL_OR = 13
};

struct AST {
	TYPES tipo;
	Symbol* id;
	AST* filho1;
	AST* filho2;
	AST* filho3;
	AST* filho4;
};

void printAST(AST ast);

AST* createAST(TYPES tipo, Symbol* id, AST* filho1, AST* filho2, AST* filho3, AST* filho4);



#endif