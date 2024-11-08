
#include "ast.hpp"


void printAST(AST ast) {
	
	printf("a");
}

AST* createAST(TYPES tipo, Symbol* id, AST* filho1, AST* filho2, AST* filho3, AST* filho4) {
	AST *ast = new AST();
	ast->tipo = tipo;
	ast->id = id;
	ast->filho1 = filho1;
	ast->filho2 = filho2;
	ast->filho3 = filho3;
	ast->filho4 = filho4;
	return ast;
}