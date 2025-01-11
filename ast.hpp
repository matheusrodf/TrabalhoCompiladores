// Etapa 6 do trabalho de Compiladores do semestre 2024/2
// Por Matheus Rodrigues Fonseca e Thalles Fernandes Rezende

#ifndef AST_HPP
#define AST_HPP

#include "symbols.hpp"

enum TYPES {
	NENHUM,
	IDENTIFICADOR,
	FUNCTION,
	FUN_PARAMS,
	
	ARIT_SOMA,
	ARIT_SUB,
	ARIT_MULT,
	ARIT_DIV,
	BOOL_NEGACAO,
	BOOL_MENOR,
	BOOL_MAIOR,
	BOOL_IGUAL,
	BOOL_AND,
	BOOL_OR,
	LIST_CMD,
	
	CMD_IF,
	CMD_WHILE,
	CMD_READ,
	CMD_PRINT,
	CMD_RETURN,
	CMD_ATTR,
	DEC_VAR,
	DEC_VEC,
	DEC_VEC_LIST,
	DEC_FUN,
	DEC_FUN_LIST,
	CHAR,
	INT
};

struct AST {
	DATATYPE datatype;
	TYPES type;
	int args;
	Symbol* id;
	AST* filho1;
	AST* filho2;
	AST* filho3;
	Symbol* id2;
};

void printCode(AST *ast);

void printAST(AST *ast, int level);

AST* createAST(TYPES type, Symbol* id, AST* filho1, AST* filho2, AST* filho3, Symbol* id2);

int semanticVerification(AST *ast, SymbolsTable *symbolsTable);

int getNumArgs(AST *ast);

AST* setReturnType(AST *ast, DATATYPE type);

bool checkDeclaration(AST *ast, SymbolsTable *symbolsTable, bool isError, AST* parent);

bool checkDataType(AST *ast, SymbolsTable *symbolsTable, bool isError);

#endif