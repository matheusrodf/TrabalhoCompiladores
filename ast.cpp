
#include "ast.hpp"


void printAST(AST *ast) {
	
	if (ast != NULL) {
		switch (ast->tipo) {
	case NENHUM 	  :
	break;
	case IDENTIFICADOR:
		std::cout << " " << ast->id->name << " ";
	break;
	case COMANDO      :
	break;
	case ASSINALAMENTO:
	break;
	case ARIT_SOMA    :
		if (ast->filho1 != NULL)
			printAST(ast->filho1);
		std::cout << " + ";
		if (ast->filho2 != NULL)
			printAST(ast->filho2);
	break;
	case ARIT_SUB     :
		if (ast->filho1 != NULL)
			printAST(ast->filho1);
		std::cout << " - ";
		if (ast->filho2 != NULL)
			printAST(ast->filho2);
	break;
	case ARIT_MULT    :
		if (ast->filho1 != NULL)
			printAST(ast->filho1);
		std::cout << " * ";
		if (ast->filho2 != NULL)
			printAST(ast->filho2);
	break;
	case ARIT_DIV     :
		if (ast->filho1 != NULL)
			printAST(ast->filho1);
		std::cout << " / ";
		if (ast->filho2 != NULL)
			printAST(ast->filho2);
	break;
	case BOOL_NEGACAO :
	break;
	case BOOL_MENOR   :
	break;
	case BOOL_MAIOR   :
	break;
	case BOOL_IGUAL   :
	break;
	case BOOL_AND     :
	break;
	case BOOL_OR      :
	break;
	default:
	break;
		}
	}
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