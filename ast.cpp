// Etapa 6 do trabalho de Compiladores do semestre 2024/2
// Por Matheus Rodrigues Fonseca e Thalles Fernandes Rezende

#include "ast.hpp"



void printCode(AST *ast)
{
	if (ast != NULL)
	{
		switch (ast->type)
		{
		case IDENTIFICADOR:
			if (ast->filho1 != NULL)
			{
				if (ast->id != NULL)
					std::cout << ast->id->value << "[";
				printCode(ast->filho1);
				std::cout << "] ";
			}
			else
			{
				if (ast->id != NULL)
					std::cout << ast->id->value << " ";
			}
			break;
		case FUNCTION:
			if (ast->id != NULL)
			{
				std::cout << ast->id->value << "(";
				if (ast->filho1 != NULL)
					printCode(ast->filho1);
				std::cout << ")";
			}
			else
			{
				if (ast->filho1 != NULL)
					printCode(ast->filho1);
				if (ast->filho2 != NULL) {
					std::cout << ", ";
					printCode(ast->filho2);
				}
			}
			break;
		case ARIT_SOMA:
			if (ast->filho1 != NULL)
				printCode(ast->filho1);
			std::cout << " + ";
			if (ast->filho2 != NULL)
				printCode(ast->filho2);
			break;
		case ARIT_SUB:
			if (ast->filho1 != NULL)
				printCode(ast->filho1);
			std::cout << " - ";
			if (ast->filho2 != NULL)
				printCode(ast->filho2);
			break;
		case ARIT_MULT:
			if (ast->filho1 != NULL)
				printCode(ast->filho1);
			std::cout << " * ";
			if (ast->filho2 != NULL)
				printCode(ast->filho2);
			break;
		case ARIT_DIV:
			if (ast->filho1 != NULL)
				printCode(ast->filho1);
			std::cout << " / ";
			if (ast->filho2 != NULL)
				printCode(ast->filho2);
			break;
		case BOOL_NEGACAO:
			std::cout << "~ ";
			if (ast->filho1 != NULL)
				printCode(ast->filho1);
			break;
		case BOOL_MENOR:
			if (ast->filho1 != NULL)
				printCode(ast->filho1);
			std::cout << " < ";
			if (ast->filho2 != NULL)
				printCode(ast->filho2);
			break;
		case BOOL_MAIOR:
			if (ast->filho1 != NULL)
				printCode(ast->filho1);
			std::cout << " > ";
			if (ast->filho2 != NULL)
				printCode(ast->filho2);
			break;
		case BOOL_IGUAL:
			if (ast->filho1 != NULL)
				printCode(ast->filho1);
			std::cout << " = ";
			if (ast->filho2 != NULL)
				printCode(ast->filho2);
			break;
		case BOOL_AND:
			if (ast->filho1 != NULL)
				printCode(ast->filho1);
			std::cout << " & ";
			if (ast->filho2 != NULL)
				printCode(ast->filho2);
			break;
		case BOOL_OR:
			if (ast->filho1 != NULL)
				printCode(ast->filho1);
			std::cout << " | ";
			if (ast->filho2 != NULL)
				printCode(ast->filho2);
			break;
		case LIST_CMD:
			if (ast->filho1 != NULL)
				printCode(ast->filho1);
			if (ast->filho2 != NULL)
				printCode(ast->filho2);
			break;
		case CMD_IF:
			std::cout << "if (";
			if (ast->filho1 != NULL)
				printCode(ast->filho1);
			std::cout << ") then {\n";
			if (ast->filho2 != NULL)
				printCode(ast->filho2);
			std::cout << "\n}\n";
			if (ast->filho3 != NULL)
			{
				std::cout << "else {\n";
				printCode(ast->filho3);
				std::cout << "}\n";
			}
			break;
		case CMD_WHILE:
			std::cout << "while ( ";
			if (ast->filho1 != NULL)
				printCode(ast->filho1);
			std::cout << ") " << std::endl;
			std::cout << "{\n";
			if (ast->filho2 != NULL)
				printCode(ast->filho2);
			std::cout << "} \n";
			break;
		case CMD_READ:
			if (ast->id != NULL)
				std::cout << "read " << ast->id->value << "; \n";
			break;
		case CMD_PRINT:
			if (ast->id != NULL)
			{
				std::cout << "print " << ast->id->value;
				printCode(ast->filho1);
				std::cout << ";\n";
			}
			else
			{
				std::cout << "print ";
				if (ast->filho1 != NULL)
					printCode(ast->filho1);
				if (ast->filho2 != NULL)
					printCode(ast->filho2);
				std::cout << ";\n";
			}
			break;
		case CMD_RETURN:
			std::cout << "return ";
			if (ast->filho1 != NULL)
				printCode(ast->filho1);
			std::cout << ";\n";
			break;
		case CMD_ATTR:
			if (ast->filho2 != NULL)
			{
				if (ast->id != NULL)
					std::cout << ast->id->value << " [";
				if (ast->filho1 != NULL)
					printCode(ast->filho1);
				std::cout << "] = ";
				printCode(ast->filho2);
				std::cout << ";\n";
			}
			else
			{
				if (ast->id != NULL)
					std::cout << ast->id->value << " = ";
				if (ast->filho1 != NULL) {
					printCode(ast->filho1);
					std::cout << ";\n";
				}
			}
			break;
		case DEC_VAR:
			if (ast->filho1 != NULL)
				printCode(ast->filho1);
			if (ast->id != NULL)
				std::cout << ast->id->value;
			if (ast->filho2 != NULL)
			{
				std::cout << " = ";
				printCode(ast->filho2);
			}
			std::cout << ";\n";
			break;
		case DEC_VEC:
			if (ast->filho1 != NULL)
				printCode(ast->filho1);
			if (ast->id != NULL)
				std::cout << " " << ast->id->value << " [";
			std::cout << ast->id2->value << "]";
			if (ast->filho2 != NULL) {
				std::cout << " = ";
				printCode(ast->filho2);
			}
			std::cout << ";\n";
			break;
		case DEC_VEC_LIST:
			if (ast->filho1 != NULL)
				printCode(ast->filho1);
			std::cout << " ";
			if (ast->filho2 != NULL)
				printCode(ast->filho2);
			break;
		case DEC_FUN:
			if (ast->filho1 != NULL)
				printCode(ast->filho1);
			if (ast->id != NULL)
				std::cout << " " << ast->id->value << " (";
			if (ast->filho2 != NULL)
				printCode(ast->filho2);
			std::cout << ") { \n";
			if (ast->filho3 != NULL)
				printCode(ast->filho3);
			std::cout << "\n}\n";
			break;
		case DEC_FUN_LIST:
			if (ast->filho1 != NULL)
				printCode(ast->filho1);
			if (ast->id != NULL)
				std::cout << " " << ast->id->value;
			if (ast->filho2 != NULL) {
				std::cout << ", ";
				printCode(ast->filho2);
			}	
			break;
		case CHAR:
			std::cout << "char ";
			printCode(ast->filho1);
			break;
		case INT:
			std::cout << "int ";
			printCode(ast->filho1);
			break;

		default:
			if (ast->filho1 != NULL)
				printCode(ast->filho1);
			if (ast->filho2 != NULL)
				printCode(ast->filho2);
			if (ast->filho3 != NULL)
				printCode(ast->filho3);
			break;
		}
	}
}

void printAST(AST *ast, int level)
{
	if (ast != NULL)
	{
		for(int i = level; i > 0; i--)
			fprintf(stderr, ".");
		switch (ast->type)
		{
		case IDENTIFICADOR:
			fprintf(stderr, "ID: ");
			break;
		case FUNCTION:
		case FUN_PARAMS:
			fprintf(stderr, "FUN: ");
			break;
		case ARIT_SOMA:
			fprintf(stderr, "SOMA: ");
			break;
		case ARIT_SUB:
			fprintf(stderr, "SUB: ");
			break;
		case ARIT_MULT:
			fprintf(stderr, "SUB: ");
			break;
		case ARIT_DIV:
			fprintf(stderr, "DIV: ");
			break;
		case BOOL_NEGACAO:
			fprintf(stderr, "B_NEG: ");
			break;
		case BOOL_MENOR:
			fprintf(stderr, "B_MENOR: ");
			break;
		case BOOL_MAIOR:
			fprintf(stderr, "B_MAIOR: ");
			break;
		case BOOL_IGUAL:
			fprintf(stderr, "B_IGUAL: ");
			break;
		case BOOL_AND:
			fprintf(stderr, "B_AND: ");
			break;
		case BOOL_OR:
			fprintf(stderr, "B_OR: ");
			break;
		case LIST_CMD:
			fprintf(stderr, "LIST_CMD: ");
			break;
		case CMD_IF:
			fprintf(stderr, "IF: ");
			break;
		case CMD_WHILE:
			fprintf(stderr, "WHILE: ");
			break;
		case CMD_READ:
			fprintf(stderr, "READ: ");
			break;
		case CMD_PRINT:
			fprintf(stderr, "PRINT: ");
			break;
		case CMD_RETURN:
			fprintf(stderr, "RETURN: ");
			break;
		case CMD_ATTR:
			fprintf(stderr, "ATTR: ");
			break;
		case DEC_VAR:
			fprintf(stderr, "DEC_VAR: ");
			break;
		case DEC_VEC:
			fprintf(stderr, "DEC_VEC: ");
			break;
		case DEC_VEC_LIST:
			fprintf(stderr, "DEC_VAR_LIST: ");
			break;
		case DEC_FUN:
			fprintf(stderr, "DEC_FUN: ");
			break;
		case DEC_FUN_LIST:
			fprintf(stderr, "DEC_FUN_LIST: ");
			break;
		case CHAR:
			fprintf(stderr, "CHAR: ");
			break;
		case INT:
			fprintf(stderr, "INT: ");
			break;
		case NENHUM:
			fprintf(stderr, "-: ");
			break;
		}
		if(ast->id != NULL) fprintf(stderr, "f1(%s) ", ast->id->value.c_str());
		if(ast->id2 != NULL) fprintf(stderr, "f2(%s) ", ast->id2->value.c_str());
		fprintf(stderr, "(tipo %d, args %d)", ast->datatype, ast->args);
			fprintf(stderr, "\n");
		if (ast->filho1 != NULL)
			printAST(ast->filho1, level+1);
		if (ast->filho2 != NULL)
			printAST(ast->filho2, level+1);
		if (ast->filho3 != NULL)
			printAST(ast->filho3, level+1);
	}
}

AST *createAST(TYPES type, Symbol *id, AST *filho1, AST *filho2, AST *filho3, Symbol *id2)
{
	AST *ast = new AST();
	ast->type = type;
	ast->id = id;
	ast->filho1 = filho1;
	ast->filho2 = filho2;
	ast->filho3 = filho3;
	ast->id2 = id2;
	return ast;
}


int semanticVerification(AST *ast, SymbolsTable *symbolsTable) {
	bool errors = false;
	
	errors = checkDeclaration(ast, symbolsTable, 0, NULL) || errors;
	errors = symbolsTable->checkUndeclaration() || errors;
	errors = checkDataType(ast, symbolsTable, 0) || errors;
	
	return errors;
}

int getNumArgs(AST *ast) {
	int i = 0;	
	AST *it = ast;
	while (it != NULL) {
		it->args = i;
		it = it->filho2;
		i++;
	}
	return i;
}

AST* setReturnType(AST *ast, DATATYPE datatype) {
	if (ast == NULL) return NULL;
	setReturnType(ast->filho1, datatype);
	setReturnType(ast->filho2, datatype);
	setReturnType(ast->filho3, datatype);
	if (ast->type == CMD_RETURN) ast->datatype = datatype;
	return ast;
}

bool checkDeclaration(AST *ast, SymbolsTable *symbolsTable, bool isError, AST *parent) {
	if (ast != NULL) {
		switch (ast->type) {
		
		case DEC_VAR:
			if (symbolsTable->find(ast->id->value)->token == TK_IDENTIFIER) {
				if (ast->filho1->type == CHAR) {
					ast->id = symbolsTable->modifySymbol(ast->id->value, TK_ID, ast->id->value, SYM_CHAR);
					ast->datatype = SYM_CHAR;
				} else if (ast->filho1->type == INT) {
					ast->id = symbolsTable->modifySymbol(ast->id->value, TK_ID, ast->id->value, SYM_INT);
					ast->datatype = SYM_INT;
				}
			} else {
				fprintf(stderr, "[ERROR] Redeclaracao do simbolo: %s \n", ast->id->value.c_str());
				isError = true;
			}
			break;
		case DEC_VEC:
			if (symbolsTable->find(ast->id->value)->token == TK_IDENTIFIER) {
				if (ast->filho1->type == CHAR) {
					ast->id = symbolsTable->modifySymbol(ast->id->value, TK_VEC, ast->id->value, SYM_CHAR);
					ast->datatype = SYM_CHAR;
					
				} else if (ast->filho1->type == INT) {
					ast->id = symbolsTable->modifySymbol(ast->id->value, TK_VEC, ast->id->value, SYM_INT);
					ast->datatype = SYM_INT;
				}
				ast->args = stoi(ast->id2->value);
				symbolsTable->setArgsSymbol(ast->id->value, ast->args);
				if (getNumArgs(ast->filho2) > ast->args) {
					fprintf(stderr, "[ERROR] Muitos literais na declaracao de %s\n", ast->id->value.c_str());
					fprintf(stderr, "[ERROR] Recebido: %d, Maximo: %d\n", getNumArgs(ast->filho2), ast->args);
					isError = true;
				}
			} else {
				fprintf(stderr, "[ERROR] Redeclaracao do simbolo: %s \n", ast->id->value.c_str());
				isError = true;
			}
			break;
		case DEC_VEC_LIST:
			ast->id = parent->id;
			ast->datatype = symbolsTable->find(ast->id->value)->type;
			break;
		case DEC_FUN:
			if (symbolsTable->find(ast->id->value)->token == TK_IDENTIFIER) {
				ast->args = getNumArgs(ast->filho2);
				if (ast->filho1->type == CHAR) {
					ast->id = symbolsTable->modifySymbol(ast->id->value, TK_FUN, ast->id->value, SYM_CHAR);
					ast->datatype = SYM_CHAR;
				} else if (ast->filho1->type == INT) {
					ast->datatype = SYM_INT;
					ast->id = symbolsTable->modifySymbol(ast->id->value, TK_FUN, ast->id->value, SYM_INT);
				}
				ast->id = symbolsTable->setArgsSymbol(ast->id->value, ast->args);
				ast = setReturnType(ast, ast->datatype);
			} else {
				fprintf(stderr, "[ERROR] Redeclaracao da funcao\n: %s \n", ast->id->value.c_str());
				isError = true;
			}
			break;
		case DEC_FUN_LIST:
			if (symbolsTable->find(ast->id->value)->token == TK_IDENTIFIER) {
				if (ast->filho1->type == CHAR) {
					ast->id = symbolsTable->modifySymbol(ast->id->value, TK_ID, ast->id->value, SYM_CHAR);
					ast->datatype = SYM_CHAR;
				} else if (ast->filho1->type == INT) {
					ast->datatype = SYM_INT;
					ast->id = symbolsTable->modifySymbol(ast->id->value, TK_ID, ast->id->value, SYM_INT);
				}
				ast->id2 = parent->id2;
				if (parent->type == DEC_FUN) ast->args = 0;
				else ast->args = parent->args + 1;
			} else {
				fprintf(stderr, "[ERROR] Redeclaracao do simbolo: %s \n", ast->id->value.c_str());
				isError = true;
			}
			break;
		case FUNCTION: {
			ast->id2 = ast->id;
		}
			break;
		case FUN_PARAMS: {
			ast->id2 = parent->id2;
		}
			break;
		default:
			break;
		}
		if (ast->filho1 != NULL)
			isError = checkDeclaration(ast->filho1, symbolsTable, isError, ast) || isError;
		if (ast->filho2 != NULL)
			isError = checkDeclaration(ast->filho2, symbolsTable, isError, ast) || isError;
		if (ast->filho3 != NULL)
			isError = checkDeclaration(ast->filho3, symbolsTable, isError, ast) || isError;
	}
	return isError;
}

bool checkDataType(AST *ast, SymbolsTable *symbolsTable, bool isError) {
	if (ast != NULL) {
		if (ast->filho1 != NULL)
			isError = checkDataType(ast->filho1, symbolsTable, isError) || isError;
		if (ast->filho2 != NULL)
			isError = checkDataType(ast->filho2, symbolsTable, isError) || isError;
		if (ast->filho3 != NULL)
			isError = checkDataType(ast->filho3, symbolsTable, isError) || isError;
	}
	switch(ast->type) {		
		case IDENTIFICADOR: {
			Symbol *sym = symbolsTable->find(ast->id->value);
			if (sym->token == TK_FUN) {
				fprintf(stderr, "[ERROR] Funcao %s sem parametros\n", ast->id->value.c_str());
				isError = true;
			} else if((sym->token == TK_VEC) && (ast->filho1 == NULL)) {
				fprintf(stderr, "[ERROR] Indice faltando do vetor %s \n", ast->id->value.c_str());
				isError = true;
			} else if ((sym->token == TK_ID) && (ast->filho1 != NULL)) {
				fprintf(stderr, "[ERROR] %s nao eh um vetor\n", ast->id->value.c_str());
				isError = true;
			} else if (ast->filho1 != NULL) {
				if (ast->filho1->datatype == SYM_BOOL) {
					fprintf(stderr, "[ERROR] Expressao bool no indice do vetor %s\n", ast->id->value.c_str());
					isError = true;
				}
			}
			ast->datatype = symbolsTable->find(ast->id->value)->type;
		}
		break;
		case FUNCTION:
			if (ast->id) {
				Symbol *sym = symbolsTable->find(ast->id->value);
				if (sym->token != TK_FUN) {
					fprintf(stderr, "[ERROR] %s nao eh uma funcao\n", ast->id->value.c_str());
					isError = true;
				} else if (getNumArgs(ast->filho1) != sym->args) {
					fprintf(stderr, "[ERROR] Numero incorreto de parametros na chamada de %s\n", ast->id->value.c_str());
					fprintf(stderr, "[ERROR] Recebido: %d, Esperado: %d\n", getNumArgs(ast->filho1), sym->args);
					isError = true;
				} else {
					ast->datatype = sym->type;
				}
			}
		break;
		
		case FUN_PARAMS: {
			if (ast->filho1->datatype == SYM_BOOL) {
				fprintf(stderr, "[ERROR] Tipo incompativel em parametro da funcao\n");
				isError = true;
			}
		}
			break;
		case ARIT_SOMA:
		case ARIT_SUB:
		case ARIT_MULT:
		case ARIT_DIV:
			if (ast->filho1->datatype == SYM_BOOL) {
				fprintf(stderr, "[ERROR] Nao pode juntar bool e int\n");
				isError = true;
			} else ast->datatype = SYM_INT;
			if (ast->filho2->datatype == SYM_BOOL) {
				fprintf(stderr, "[ERROR] Nao pode juntar bool e int\n");
				isError = true;
			} else ast->datatype = SYM_INT;
			break;
		case BOOL_MENOR:
		case BOOL_MAIOR:
		case BOOL_IGUAL:
		case BOOL_AND:
		case BOOL_OR:
			if (((ast->filho2->datatype == SYM_INT) || (ast->filho2->datatype == SYM_CHAR)) && (ast->filho2->type != IDENTIFICADOR))  {
				fprintf(stderr, "[ERROR] Nao pode juntar bool e int\n");
				isError = true;
			} else ast->datatype = SYM_BOOL;
		case BOOL_NEGACAO:
			if (((ast->filho1->datatype == SYM_INT) || (ast->filho1->datatype == SYM_CHAR)) && (ast->filho1->type != IDENTIFICADOR))  {
				fprintf(stderr, "[ERROR] Nao pode juntar bool e int\n");
				isError = true;
			} else ast->datatype = SYM_BOOL;
			break;
			
		case CMD_READ:
				ast->datatype = symbolsTable->find(ast->id->value)->type;
			break;
			
		case CMD_PRINT:
			if (ast->id == NULL) {
				ast->datatype = ast->filho1->datatype;
			} else {
				ast->datatype = SYM_STRING;
			}	
			break;
		case CMD_ATTR: {
			Symbol *sym = symbolsTable->find(ast->id->value);
			if (ast->filho1->datatype == SYM_BOOL) {
				fprintf(stderr, "[ERROR] Bool nao pode ser atribuido para %s\n", ast->id->value.c_str());
				isError = true;
			} else 
			if (sym->token == TK_VEC) {
				
				if (ast->filho2 == NULL) {
					fprintf(stderr, "[ERROR] Indice faltando do vetor %s\n", ast->id->value.c_str());
					isError = true;
				} else if (ast->filho2->datatype == SYM_BOOL) {
					fprintf(stderr, "[ERROR] Expressao bool no indice do vetor %s\n", ast->id->value.c_str());
					isError = true;
				}
			} 
			
			else if (sym->token == TK_FUN) {
				fprintf(stderr, "[ERROR] Nao pode atribuir a funcao %s\n", ast->id->value.c_str());
				isError = true;	
			}
		}
			break;
		case CMD_IF:
			if (ast->filho1->datatype != SYM_BOOL) {
				fprintf(stderr, "[ERROR] If precisa de expressao condicional\n");
				isError = true;
			}
		break;
		case CMD_WHILE:
			if (ast->filho1->datatype != SYM_BOOL) {
				fprintf(stderr, "[ERROR] While precisa de expressao condicional\n");
				isError = true;
			}
		break;
		
		case CMD_RETURN:
			if (ast->filho1->datatype == SYM_BOOL) {
				fprintf(stderr, "[ERROR] Tipo do return incompativel\n");
				isError = true;
			}
		break;
		default:
			break;
	}
	return isError;
}