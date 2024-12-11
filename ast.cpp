// Etapa 5 do trabalho de Compiladores do semestre 2024/2
// Por Matheus Rodrigues Fonseca e Thalles Fernandes Rezende

#include "ast.hpp"

void printCode(AST *ast)
{
	if (ast != NULL)
	{
		switch (ast->tipo)
		{
		case IDENTIFICADOR:
			if (ast->filho1 != NULL)
			{
				if (ast->id != NULL)
					std::cout << ast->id->name << "[";
				printCode(ast->filho1);
				std::cout << "] ";
			}
			else
			{
				if (ast->id != NULL)
					std::cout << ast->id->name << " ";
			}
			break;
		case FUNCTION:
			if (ast->id != NULL)
			{
				std::cout << ast->id->name << "(";
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
				std::cout << "read " << ast->id->name << "; \n";
			break;
		case CMD_PRINT:
			if (ast->id != NULL)
			{
				std::cout << "print " << ast->id->name;
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
		case CMD_PRINT_LIST:
			if (ast->id != NULL)
			{
				std::cout << ast->id->name;
				printCode(ast->filho1);
			}
			else
			{
				if (ast->filho1 != NULL)
					printCode(ast->filho1);
				if (ast->filho2 != NULL)
					printCode(ast->filho2);
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
					std::cout << ast->id->name << " [";
				if (ast->filho1 != NULL)
					printCode(ast->filho1);
				std::cout << "] = ";
				printCode(ast->filho2);
				std::cout << ";\n";
			}
			else
			{
				if (ast->id != NULL)
					std::cout << ast->id->name << " = ";
				if (ast->filho1 != NULL) {
					printCode(ast->filho1);
					std::cout << ";\n";
				}
			}
			break;
		case DEC_VAR:
			if (ast->id2 != NULL)
			{
				if (ast->filho1 != NULL)
					printCode(ast->filho1);
				if (ast->id != NULL)
					std::cout << " " << ast->id->name << " [";
				std::cout << ast->id2->name << "]";
				if (ast->filho2 != NULL) {
					std::cout << " = ";
					printCode(ast->filho2);
				}
				std::cout << ";\n";
			}
			else
			{
				if (ast->filho1 != NULL)
					printCode(ast->filho1);
				if (ast->id != NULL)
					std::cout << ast->id->name;
				if (ast->filho2 != NULL)
				{
					std::cout << " = ";
					printCode(ast->filho2);
				}
				std::cout << ";\n";
			}
			break;
		case DEC_VAR_LIST:
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
				std::cout << " " << ast->id->name << " (";
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
				std::cout << " " << ast->id->name;
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
		switch (ast->tipo)
		{
		case IDENTIFICADOR:
			fprintf(stderr, "ID: ");
			break;
		case FUNCTION:
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
		case CMD_PRINT_LIST:
			fprintf(stderr, "PRINT_LIST: ");
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
		case DEC_VAR_LIST:
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
		if(ast->id != NULL) fprintf(stderr, "%s ", ast->id->name.c_str());
		if(ast->id2 != NULL) fprintf(stderr, "%s ", ast->id2->name.c_str());
			fprintf(stderr, "\n");
		if (ast->filho1 != NULL)
			printAST(ast->filho1, level+1);
		if (ast->filho2 != NULL)
			printAST(ast->filho2, level+1);
		if (ast->filho3 != NULL)
			printAST(ast->filho3, level+1);
	}
}

AST *createAST(TYPES tipo, Symbol *id, AST *filho1, AST *filho2, AST *filho3, Symbol *id2)
{
	AST *ast = new AST();
	ast->tipo = tipo;
	ast->id = id;
	ast->filho1 = filho1;
	ast->filho2 = filho2;
	ast->filho3 = filho3;
	ast->id2 = id2;
	return ast;
}