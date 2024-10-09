// Parte 1 do trabalho de Compiladores do semestre 2024/2
// Por Matheus Rodrigues Fonseca e Thalles Fernandes Rezende

#include <iostream>
#include "tokens.h"

int yylex();
extern FILE *yyin;
extern int getLineNumber();

int isRunning(void);
void initMe(void);

int main(int argc, char **argv)
{

	int token = 0;

	if (argc < 2)
	{
		fprintf(stderr, "./etapa1 <file>\n");
		return -1;
	}
	else
	{
		yyin = fopen(argv[1], "r");
	}
	while (isRunning())
	{
		token = yylex();
	}
	std::cout << "\n\nNumero de linhas: " << getLineNumber() << "\n";

	return 0;
}