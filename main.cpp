// Parte 1 do trabalho de Compiladores do semestre 2024/2
// Por Matheus Rodrigues Fonseca e Thalles Rezende


#include <iostream>
#include "tokens.h"

int yylex();
extern FILE *yyin;
int getLineNumber();
void PrintSymbols();

int isRunning(void);
void initMe(void);

int main(int argc, char** argv) {
	
	int token = 0;
	
	if (argc < 2) {
		fprintf(stderr, "./etapa1 <file>\n");
		//return 0;
	} else {
		yyin = fopen(argv[1],"r");
	}
	token = yylex();
	while(isRunning()) {
		switch(token) {
			case KW_CHAR       :
				fprintf(stderr,  "char ");
				break;             
			case KW_INT        :
				fprintf(stderr,  "int ");
				break;             
			case KW_IF         :
				fprintf(stderr,  "if ");
				break;             
			case KW_THEN       :
				fprintf(stderr,  "then ");
				break;             
			case KW_ELSE       :
				fprintf(stderr,  "else ");
				break;             
			case KW_WHILE      :
				fprintf(stderr,  "while ");
				break;             
			case KW_READ       :
				fprintf(stderr,  "read ");
				break;             
			case KW_PRINT      :
				fprintf(stderr,  "print ");
				break;             
			case KW_RETURN     :
				fprintf(stderr,  "return ");
				break;             
			case TK_IDENTIFIER :
				fprintf(stderr,  "id ");
				break;             
			case LIT_INT       :
				fprintf(stderr,  "Lint ");
				break;             
			case LIT_CHAR      :
				fprintf(stderr,  "Lchar ");
				break;             
			case LIT_STRING    :
				fprintf(stderr,  "Lstring ");
				break;             
			case TOKEN_ERROR   :
				fprintf(stderr,  "ERROR ");
				break;
			default:
				fprintf(stderr, "%c ", token);
		}
		
		token = yylex();		
	}
	std::cout << "\n\nlinhas: " << getLineNumber() << "\n";
	PrintSymbols();
	
	return 0;
}