// Etapa 5 do trabalho de Compiladores do semestre 2024/2
// Por Matheus Rodrigues Fonseca e Thalles Fernandes Rezende

#ifndef AST_HPP
#define AST_HPP

#include "symbols.hpp"

enum TYPES {
	NENHUM = 0,
	IDENTIFICADOR = 1,
	FUNCTION = 2,
	
	ARIT_SOMA = 4,
	ARIT_SUB = 5,
	ARIT_MULT = 6,
	ARIT_DIV = 7,
	BOOL_NEGACAO = 8,
	BOOL_MENOR = 9,
	BOOL_MAIOR = 10,
	BOOL_IGUAL = 11,
	BOOL_AND = 12,
	BOOL_OR = 13,
	LIST_CMD = 14,
	
	CMD_IF = 15,
	CMD_WHILE = 16,
	CMD_READ = 17,
	CMD_PRINT = 18,
	CMD_PRINT_LIST = 3,
	CMD_RETURN = 19,
	CMD_ATTR = 20,
	DEC_VAR = 21,
	DEC_VAR_LIST = 22,
	DEC_FUN = 23,
	DEC_FUN_LIST = 24,
	CHAR = 25,
	INT = 26
};

struct AST {
	TYPES tipo;
	Symbol* id;
	AST* filho1;
	AST* filho2;
	AST* filho3;
	Symbol* id2;
};

void printCode(AST *ast);

void printAST(AST *ast, int level);

AST* createAST(TYPES tipo, Symbol* id, AST* filho1, AST* filho2, AST* filho3, Symbol* id2);



#endif