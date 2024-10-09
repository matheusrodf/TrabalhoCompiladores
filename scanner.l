%{
	// Parte 1 do trabalho de Compiladores do semestre 2024/2
	// Por Matheus Rodrigues Fonseca e Thalles Rezende
	#include <iostream>
	#include "tokens.h"
	using namespace std;
	int running = 1;
	int lineCount = 1;

	int getLineNumber();
	void InsertSymbol(int token, string text);
%}

%x BLOCK_COMMENT

%option nounput 

%%

"char"							{ return KW_CHAR;    }
"int"							{ return KW_INT;     }
"if"							{ return KW_IF;      }
"then"							{ return KW_THEN;    }
"else"							{ return KW_ELSE;    }
"while"							{ return KW_WHILE;   }
"read"							{ return KW_READ;    }
"print"							{ return KW_PRINT;   }
"return"						{ return KW_RETURN;  }
[-,;:()[\]{}=+*/%<>&|~]			{ return yytext[0];  }

#[0-9]+							{ InsertSymbol(LIT_INT, yytext); return LIT_INT;    }
\'.\'							{ InsertSymbol(LIT_CHAR, yytext); return LIT_CHAR;   }
\"(\\\"|[^"\n])*\"				{ InsertSymbol(LIT_STRING, yytext); return LIT_STRING; }

[0-9a-zA-Z]+					{ InsertSymbol(TK_IDENTIFIER, yytext); return TK_IDENTIFIER; }

[ \t]							{  }
"\n"							{ lineCount++; }

"//".*							{  }
"/*"							{ BEGIN BLOCK_COMMENT; }

.								{ return TOKEN_ERROR; }



<BLOCK_COMMENT>"\n"				{ lineCount++; }
<BLOCK_COMMENT>"."				{  }
<BLOCK_COMMENT>"*/"				{ BEGIN INITIAL; }


%%

int getLineNumber() {
	return lineCount;
}

// Precisa ter
void initMe() {

}

// Precisa ter
int isRunning() {
	return running;
}

int yywrap() {
	running = 0;
	return 1;
}