#include <iostream>

int yylex();
extern FILE *yyin;
int getLineCount();

int isRunning(void);
void initMe(void);

int main(int argc, char** argv) {
	
	if (argc < 2) {
		fprintf(stderr, "./etapa1 <file>\n");
		//return 0;
	} else {
		yyin = fopen(argv[1],"r");
	}
	while(isRunning()) {
		yylex();	
	}
	std::cout << "linhas: " << getLineCount();
	
	return 0;
}