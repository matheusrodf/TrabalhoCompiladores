// Etapa 6 do trabalho de Compiladores do semestre 2024/2
// Por Matheus Rodrigues Fonseca e Thalles Fernandes Rezende


#ifndef TAC_HPP
#define TAC_HPP

#include "symbols.hpp"
#include "parser.tab.hpp"
#include "ast.hpp"
#include <vector>



using namespace std;

enum TACTYPE {
	
	TAC_CHAR,
	TAC_INT,
	
	TAC_MOVE, 
	TAC_MOVERETURN,
	TAC_DECVAR, 
	TAC_DECVEC, 
	TAC_SYMBOL, 
	TAC_SYMBOL_VEC, 
	TAC_LABEL,
	TAC_ADD, 
	TAC_SUB,
	TAC_MULT,
	TAC_DIV,
	TAC_BNEG,
	TAC_BLESS,
	TAC_BHIGHER,
	TAC_BEQUAL,
	TAC_BAND,
	TAC_BOR,
	TAC_IF, 
	TAC_JUMP, 
	TAC_PRINT_CHAR,
	TAC_PRINT_INT,
	TAC_PRINT_STRING,
	TAC_READ_INT,
	TAC_READ_CHAR,
	
	TAC_BEGINFUN,
	TAC_ENDFUN, 
	TAC_CALL, 
	TAC_ARG, 
	TAC_DEC_ARG, 
	TAC_RET, 
};

typedef struct TAC {
	int type;	
	Symbol *res;
	Symbol *op1;
	Symbol *op2;
	int args;
	
	TAC(int opcode, Symbol *rd, Symbol *rs, Symbol *rt) :
	type(opcode), res(rd), op1(rs), op2(rt) {}
} TAC;

void printTAC(vector<TAC*> tac);

vector<TAC*> joinTAC(vector<TAC*> tac1, vector<TAC*> tac2);

Symbol* makeLabel(SymbolsTable *symbolsTable);
Symbol* makeTemp(SymbolsTable *symbolsTable);

vector<TAC*> generateCode(AST *ast, SymbolsTable *symbolsTable);

vector<TAC*> generateCodeExp(Symbol* f1, Symbol* f2, TYPES tipo, SymbolsTable *symbolsTable);

void generateAsm(vector<TAC*> tac, SymbolsTable *symbolsTable);


#endif