// Etapa 3 do trabalho de Compiladores do semestre 2024/2
// Por Matheus Rodrigues Fonseca e Thalles Fernandes Rezende

#include "ast.hpp"

void printAST(AST *ast)
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
				printAST(ast->filho1);
				std::cout << "] " << std::endl;
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
					printAST(ast->filho1);
				std::cout << ")" << std::endl;
			}
			else
			{
				if (ast->filho1 != NULL)
					printAST(ast->filho1);
				std::cout << ", ";
				if (ast->filho2 != NULL)
					printAST(ast->filho2);
			}
			break;
		case ARIT_SOMA:
			if (ast->filho1 != NULL)
				printAST(ast->filho1);
			std::cout << " + ";
			if (ast->filho2 != NULL)
				printAST(ast->filho2);
			break;
		case ARIT_SUB:
			if (ast->filho1 != NULL)
				printAST(ast->filho1);
			std::cout << " - ";
			if (ast->filho2 != NULL)
				printAST(ast->filho2);
			break;
		case ARIT_MULT:
			if (ast->filho1 != NULL)
				printAST(ast->filho1);
			std::cout << " * ";
			if (ast->filho2 != NULL)
				printAST(ast->filho2);
			break;
		case ARIT_DIV:
			if (ast->filho1 != NULL)
				printAST(ast->filho1);
			std::cout << " / ";
			if (ast->filho2 != NULL)
				printAST(ast->filho2);
			break;
		case BOOL_NEGACAO:
			std::cout << "~ ";
			if (ast->filho1 != NULL)
				printAST(ast->filho1);
			break;
		case BOOL_MENOR:
			if (ast->filho1 != NULL)
				printAST(ast->filho1);
			std::cout << " < ";
			if (ast->filho2 != NULL)
				printAST(ast->filho2);
			break;
		case BOOL_MAIOR:
			if (ast->filho1 != NULL)
				printAST(ast->filho1);
			std::cout << " > ";
			if (ast->filho2 != NULL)
				printAST(ast->filho2);
			break;
		case BOOL_IGUAL:
			if (ast->filho1 != NULL)
				printAST(ast->filho1);
			std::cout << " = ";
			if (ast->filho2 != NULL)
				printAST(ast->filho2);
			break;
		case BOOL_AND:
			if (ast->filho1 != NULL)
				printAST(ast->filho1);
			std::cout << " & ";
			if (ast->filho2 != NULL)
				printAST(ast->filho2);
			break;
		case BOOL_OR:
			if (ast->filho1 != NULL)
				printAST(ast->filho1);
			std::cout << " | ";
			if (ast->filho2 != NULL)
				printAST(ast->filho2);
			break;
		case LIST_CMD:
			if (ast->filho1 != NULL)
				printAST(ast->filho1);
			std::cout << "\n";
			if (ast->filho2 != NULL)
				printAST(ast->filho2);
			break;
		case CMD_IF:
			std::cout << "if (";
			if (ast->filho1 != NULL)
				printAST(ast->filho1);
			std::cout << ") then \n";
			if (ast->filho2 != NULL)
				printAST(ast->filho2);
			if (ast->filho3 != NULL)
			{
				std::cout << "else \n";
				printAST(ast->filho3);
			}
			break;
		case CMD_WHILE:
			std::cout << "while ( ";
			if (ast->filho1 != NULL)
				printAST(ast->filho1);
			std::cout << ") " << std::endl;
			if (ast->filho2 != NULL)
				printAST(ast->filho2);
			std::cout << "\n";
			break;
		case CMD_READ:
			if (ast->id != NULL)
				std::cout << "read " << ast->id->name;
			break;
		case CMD_PRINT:
			if (ast->id != NULL)
			{
				std::cout << "print " << ast->id->name;
				if (ast->filho1 != NULL)
					printAST(ast->filho1);
			}
			else
			{
				std::cout << "print ";
				if (ast->filho1 != NULL)
					printAST(ast->filho1);
				if (ast->filho2 != NULL)
					printAST(ast->filho2);
			}
			break;
		case CMD_PRINT_LIST:
			if (ast->id != NULL)
			{
				std::cout << "print " << ast->id->name;
				if (ast->filho1 != NULL)
					printAST(ast->filho1);
			}
			else
			{
				std::cout << "print ";
				if (ast->filho1 != NULL)
					printAST(ast->filho1);
				if (ast->filho2 != NULL)
					printAST(ast->filho2);
			}
			break;
		case CMD_RETURN:
			std::cout << "return ";
			if (ast->filho1 != NULL)
				printAST(ast->filho1);
			break;
		case CMD_ATTR:
			if (ast->filho2 != NULL)
			{
				if (ast->id != NULL)
					std::cout << ast->id->name << " [";
				if (ast->filho1 != NULL)
					printAST(ast->filho1);
				std::cout << "] = ";
				printAST(ast->filho2);
			}
			else
			{
				if (ast->id != NULL)
					std::cout << ast->id->name << " = ";
				if (ast->filho1 != NULL)
					printAST(ast->filho1);
			}
			break;
		case DEC_VAR:
			if (ast->id2 != NULL)
			{
				if (ast->filho1 != NULL)
					printAST(ast->filho1);
				if (ast->id != NULL)
					std::cout << " " << ast->id->name << " [";
				std::cout << ast->id2->name << "] = ";
				if (ast->filho2 != NULL)
					printAST(ast->filho2);
			}
			else
			{
				if (ast->filho1 != NULL)
					printAST(ast->filho1);
				if (ast->id != NULL)
					std::cout << ast->id->name;
				if (ast->filho2 != NULL)
				{
					std::cout << " = ";
					printAST(ast->filho2);
				}
			}
			break;
		case DEC_VAR_LIST:
			if (ast->filho1 != NULL)
				printAST(ast->filho1);
			std::cout << ", ";
			if (ast->filho2 != NULL)
				printAST(ast->filho2);
			break;
		case DEC_FUN:
			if (ast->filho1 != NULL)
				printAST(ast->filho1);
			if (ast->id != NULL)
				std::cout << " " << ast->id->name << " (";
			if (ast->filho2 != NULL)
				printAST(ast->filho2);
			std::cout << ")\n";
			if (ast->filho3 != NULL)
				printAST(ast->filho3);
			break;
		case DEC_FUN_LIST:
			if (ast->filho1 != NULL)
				printAST(ast->filho1);
			if (ast->id != NULL)
				std::cout << " " << ast->id->name << ", ";
			if (ast->filho2 != NULL)
				printAST(ast->filho2);
			break;
		case CHAR:
			std::cout << "char ";
			if (ast->filho1 != NULL)
				printAST(ast->filho1);
			break;
		case INT:
			std::cout << "int ";
			if (ast->filho1 != NULL)
				printAST(ast->filho1);
			break;

		default:
			std::cout << "DESCONHECIDO ";
			if (ast->id != NULL)
				std::cout << "id: " << ast->id->name;
			if (ast->filho1 != NULL)
				std::cout << "f1: ";
			printAST(ast->filho1);
			if (ast->filho2 != NULL)
				std::cout << "f2: ";
			printAST(ast->filho2);
			if (ast->filho3 != NULL)
				std::cout << "f3: ";
			printAST(ast->filho3);
			if (ast->id2 != NULL)
				std::cout << "id2: " << ast->id2->name;

			break;
		}
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

	if (tipo > 13)
	{
		printAST(ast);
	}
	return ast;
}