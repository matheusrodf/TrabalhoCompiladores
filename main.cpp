// Etapa 6 do trabalho de Compiladores do semestre 2024/2
// Por Matheus Rodrigues Fonseca e Thalles Fernandes Rezende

#include <iostream>

extern FILE *yyin;
extern int getLineNumber();

int isRunning(void);
void initMe(void);
int yyparse();

int main(int argc, char **argv)
{

	int token = 0;

	if (argc < 3)
	{
		fprintf(stderr, "./etapa6 <source_file> <output_file>\n");
		return 1;
	}
	else
	{
		yyin = fopen(argv[1], "r");
		if (yyin == NULL)
		{

			fprintf(stderr, "Erro ao ler o arquivo.\n");
			return 2;
		};
	}
	freopen(argv[2], "w", stdout);
	return yyparse();
}