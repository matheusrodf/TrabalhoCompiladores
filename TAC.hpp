// Etapa 5 do trabalho de Compiladores do semestre 2024/2
// Por Matheus Rodrigues Fonseca e Thalles Fernandes Rezende


#ifndef SYMBOLS_HPP
#define SYMBOLS_HPP

#include "symbols.hpp"
#include <vector>
struct Symbol;
struct AST;


using namespace std;

enum TACTYPE {
	TAC_SYMBOL, 
	TAC_LABEL,
	TAC_MOVE, 
	
	TAC_SOMA, 
	TAC_SUB,
	TAC_MULT,
	TAC_DIV,
	TAC_BNEG,
	TAC_BMENOR,
	TAC_BMAIOR,
	TAC_BIGUAL,
	TAC_BAND,
	TAC_BOR,
	
	TAC_BEGINFUN,
	TAC_ENDFUN, 
	TAC_IFZ, 
	TAC_JUMP, 
	TAC_CALL, 
	TAC_ARG, 
	TAC_RET, 
	TAC_PRINT,
	TAC_READ
};

typedef struct TAC {
	int type;	
	Symbol *res;
	Symbol *op1;
	Symbol *op2;
	
	TAC(int opcode, Symbol *rd, Symbol *rs, Symbol *rt) :
	type(opcode), res(rd), op1(rs), op2(rt) {}
} TAC;

void printTAC(vector<TAC> aaa);

vector<TAC*> joinTAC(vector<TAC()> tac1, vector<TAC> tac2);

Symbol* makeLabel();
Symbol* makeTemp();

vector<TAC> generateCode();

#endif