%{
#include <iostream>
#include "tokens.h"
int running = 1;
int lineCount = 1;

int getLineCount();
%}

%x BLOCK_COMMENT
%x STRING

%option nounput 

%%

"char"							{ fprintf(stderr, "CHAR "); }
"int"							{ fprintf(stderr, "INT "); }
"if"							{ fprintf(stderr, "IF "); }
"then"							{ fprintf(stderr, "THEN "); }
"else"							{ fprintf(stderr, "ELSE "); }
"while"							{ fprintf(stderr, "WHILE "); }
"read"							{ fprintf(stderr, "READ "); }
"print"							{ fprintf(stderr, "PRINT "); }
"return"						{ fprintf(stderr, "RETURN "); }
[-,;:()[\]{}=+*/%<>&|~]			{ fprintf(stderr, "(a)%c ", yytext[0]); }

#[0-9]+							{ fprintf(stderr, "LIT_INT "); }
\'.\'							{ fprintf(stderr, "LIT_CHAR "); }
\".*\"							{ fprintf(stderr, "LIT_STRING "); }

[0-9a-zA-Z]+					{ fprintf(stderr, "VARIAVEL "); }


[ \t]		{ }
"\n"		{ lineCount++; }

"//".*		{ fprintf(stderr, "//COMMENT "); }
"/*"		{ BEGIN BLOCK_COMMENT; fprintf(stderr, "/COMMENTBEGIN "); }

.		{ fprintf(stderr, ". "); }

<BLOCK_COMMENT>"\n"			{ lineCount++; }
<BLOCK_COMMENT>"."			{ }
<BLOCK_COMMENT>"*/"			{ BEGIN INITIAL; fprintf(stderr, "/ENDCOMMENT "); }


%%

int getLineCount() {
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