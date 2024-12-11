// Etapa 5 do trabalho de Compiladores do semestre 2024/2
// Por Matheus Rodrigues Fonseca e Thalles Fernandes Rezende


#ifndef TAC_HPP
#define TAC_HPP

#include "symbols.hpp"
#include "parser.tab.hpp"
#include "ast.hpp"
#include <vector>



using namespace std;

enum TACTYPE {
	
	TAC_MOVE, 
	TAC_SYMBOL, 
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
	TAC_PRINT,
	TAC_READ,
	
	TAC_BEGINFUN,
	TAC_ENDFUN, 
	TAC_CALL, 
	TAC_ARG, 
	TAC_RET, 
};

typedef struct TAC {
	int type;	
	Symbol *res;
	Symbol *op1;
	Symbol *op2;
	
	TAC(int opcode, Symbol *rd, Symbol *rs, Symbol *rt) :
	type(opcode), res(rd), op1(rs), op2(rt) {}
} TAC;

void printTAC(vector<TAC*> tac);

vector<TAC*> joinTAC(vector<TAC*> tac1, vector<TAC*> tac2);

Symbol* makeLabel(SymbolsTable *symbolsTable);
Symbol* makeTemp(SymbolsTable *symbolsTable);

vector<TAC*> generateCode(AST *ast, SymbolsTable *symbolsTable);

vector<TAC*> generateCodeExp(Symbol* f1, Symbol* f2, TYPES tipo, SymbolsTable *symbolsTable);

#endif