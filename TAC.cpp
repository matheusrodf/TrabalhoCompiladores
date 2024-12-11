// Etapa 5 do trabalho de Compiladores do semestre 2024/2
// Por Matheus Rodrigues Fonseca e Thalles Fernandes Rezende

#include "TAC.hpp"

#include <string>
#include <iterator>

using namespace std;


void printTAC(vector<TAC*> tac) {
	
	for (const auto &kv : tac) {
		switch(kv->type) {
			case TAC_SYMBOL: {
				fprintf(stderr, "SYMBOL ");
			}
				break;
			case TAC_LABEL: {
				fprintf(stderr, "LABEL ");
			}
				break;
			case TAC_ADD: {
				fprintf(stderr, "ADD ");
			}
				break;
			case TAC_SUB: {
				fprintf(stderr, "SUB ");
			}
			case TAC_MULT: {
				fprintf(stderr, "MULT ");
			}
				break;
			case TAC_DIV: {
				fprintf(stderr, "DIV ");
			}
				break;
			case TAC_BNEG: {
				fprintf(stderr, "NEG ");
			}
				break;
			case TAC_BLESS: {
				fprintf(stderr, "LESS ");
			}
				break;
			case TAC_BHIGHER: {
				fprintf(stderr, "HIGHER ");
			}
				break;
			case TAC_BEQUAL: {
				fprintf(stderr, "EQUAL ");
			}
				break;
			case TAC_BAND: {
				fprintf(stderr, "AND ");
			}
				break;
			case TAC_BOR: {
				fprintf(stderr, "OR ");
			}
				break;
			case TAC_IF: {
				fprintf(stderr, "IF ");
			}
				break;
			case TAC_JUMP: {
				fprintf(stderr, "JUMP ");
			}
				break;
			case TAC_PRINT: {
				fprintf(stderr, "PRINT ");
			}
				break;
			case TAC_READ: {
				fprintf(stderr, "READ ");
			}
				break;
			case TAC_MOVE: {
				fprintf(stderr, "ASS ");
			}
				break;
			case TAC_BEGINFUN: {
				fprintf(stderr, "BEGINFUN ");
			}
				break;
			case TAC_ENDFUN: {
				fprintf(stderr, "ENDFUN ");
			}
				break;
			case TAC_CALL: {
				fprintf(stderr, "CALL ");
			}
				break;
			case TAC_ARG: {
				fprintf(stderr, "ARG ");
			}
				break;
			case TAC_RET: {
				fprintf(stderr, "RET ");
			}
				break;
			default: {
				fprintf(stderr, "NADA ");
			}
				break;
		}
		if (kv->res) {
			fprintf(stderr, "%s ", kv->res->name.c_str());
		} else fprintf(stderr, "0 ");
		if (kv->op1) {
			fprintf(stderr, "%s ", kv->op1->name.c_str());
		} else fprintf(stderr, "0 ");
		if (kv->op2) {
			fprintf(stderr, "%s ", kv->op2->name.c_str());
		} else fprintf(stderr, "0 ");
		fprintf(stderr, "\n");
	}
}

vector<TAC*> joinTAC(vector<TAC*> tac1, vector<TAC*> tac2) {
	if (tac1.empty()) {return tac2;}
	if (tac2.empty()) {return tac1;}
	else {tac1.insert(tac1.end(),std::make_move_iterator(tac2.begin()),std::make_move_iterator(tac2.end()));}
	return tac1;
}

Symbol* makeLabel(SymbolsTable *symbolsTable) {
	static int labelId;
	string label = "__label";
	label += to_string(labelId++);
	return symbolsTable->createSymbol(TK_IDENTIFIER, label);
}

Symbol* makeTemp(SymbolsTable *symbolsTable) {
	static int tempId;
	string temp = "__temp";
	temp += to_string(tempId++);
	return symbolsTable->createSymbol(TK_IDENTIFIER, temp);
}

vector<TAC*> generateCode(AST *ast, SymbolsTable *symbolsTable) {
	
	if (ast == NULL) return {};
	
	vector<TAC*> filho1 = {};
	vector<TAC*> filho2 = {};
	vector<TAC*> filho3 = {};
	
	
	//Filhos
	if (ast->filho1) {
		filho1 = generateCode(ast->filho1, symbolsTable);
	}
	if (ast->filho2) {
		filho2 = generateCode(ast->filho2, symbolsTable);
	}
	if (ast->filho3) {
		filho3 = generateCode(ast->filho3, symbolsTable);
	}
	
	Symbol* f1 = NULL;
	Symbol* f2 = NULL;
	if (!filho1.empty()) {
		f1 = filho1.back()->res;
	}
	if (!filho2.empty()) {
		f2 = filho2.back()->res;
	}
	
	vector<TAC*> result = {};
	
	switch(ast->tipo) {
		case IDENTIFICADOR: {
			result.push_back(new TAC(TAC_SYMBOL, ast->id,0,0));
		}
			break;
			
		case ARIT_SOMA:
		case ARIT_SUB:		
		case ARIT_MULT:
		case ARIT_DIV:
		case BOOL_NEGACAO:
		case BOOL_MENOR:
		case BOOL_MAIOR:	
		case BOOL_IGUAL:
		case BOOL_AND: 	
		case BOOL_OR:
			result = joinTAC(result, filho1);
			result = joinTAC(result, filho2);
			result = generateCodeExp(f1, f2, ast->tipo, symbolsTable);
			break;
		case CMD_IF: {
			TAC *labelFalse = new TAC(TAC_LABEL, makeLabel(symbolsTable),0,0);
			TAC *labelTrue = new TAC(TAC_LABEL, makeLabel(symbolsTable),0,0);
			TAC *jumpFalse = new TAC(TAC_JUMP, labelFalse->res,filho1.back()->res,0);
			TAC *jumpTrue = new TAC(TAC_JUMP, labelTrue->res,filho1.back()->res,0);
			
			//if (cond)
			//jump False
			//cmd
			//labelFalse
			//jumpTrue
			//else
			//cmd
			//labelTrue
			
			//cond
			result = joinTAC(result, filho1);
			//if (cond)
			result.push_back(new TAC(TAC_IF, f1, jumpTrue->res, jumpFalse->res));
			//jump False
			result.push_back(jumpFalse);
			//cmd
			result = joinTAC(result, filho2);
			//jumpTrue
			result.push_back(jumpTrue);
			//labelFalse
			result.push_back(labelFalse);
			//else
			//cmd
			result = joinTAC(result, filho3);
			//labelTrue
			result.push_back(labelTrue);
		}
			break;
			
		case CMD_WHILE: {
			TAC *labelFim = new TAC(TAC_LABEL, makeLabel(symbolsTable),0,0);
			TAC *labelLoop = new TAC(TAC_LABEL, makeLabel(symbolsTable),0,0);
			TAC *jumpFim = new TAC(TAC_JUMP, labelFim->res,f1,0);
			TAC *jumpLoop = new TAC(TAC_JUMP, labelLoop->res,f1,0);
			
		// labelLoop
		// if (cond) jump labelFim
		// cmd
		// jump label
		// label2
	
			// labelLoop
			result.push_back(labelLoop);
			//cond
			result = joinTAC(result,filho1);
			// if (cond) jump labelFim
			result.push_back(new TAC(TAC_IF, f1, 0, jumpFim->res));
			// cmd
			result = joinTAC(result, filho2);
			// jump label
			result.push_back(jumpLoop);
			// label2
			result.push_back(labelFim);
		}
			break;
			
		case DEC_FUN:
			result = joinTAC(result, filho2);
			result.push_back(new TAC(TAC_BEGINFUN, ast->id, f2,0));
			result = joinTAC(result, filho3);
			result.push_back(new TAC(TAC_ENDFUN, ast->id, 0,0));
			break;
		case DEC_FUN_LIST:
			result.push_back(new TAC(TAC_ARG, ast->id, f2,0));
			break;
			
		case FUNCTION: {
			if (ast->id != NULL) {
				result.push_back(new TAC(TAC_CALL, ast->id, f1,0));
			} else {
				result.push_back(new TAC(TAC_ARG, f1, f2,0));
			}
		}
			break;
		case CMD_RETURN: {
			result = joinTAC(result, filho1);
			result.push_back(new TAC(TAC_RET, f1, 0,0));
		}
			break;
		
		case CMD_PRINT:
		case CMD_PRINT_LIST: {
			if (ast->id != NULL) {
				result = joinTAC(result, filho1);
				result.push_back(new TAC(TAC_PRINT, ast->id, f1,f2));
			} else {
				result = joinTAC(result, joinTAC(filho1, filho2));
				result.push_back(new TAC(TAC_PRINT, makeTemp(symbolsTable), f1, f2));
			}
		}
			break;
		
		case CMD_ATTR:
			if (filho2.empty()) {
				result.push_back(new TAC(TAC_MOVE, ast->id, f1,0));
			} else {
				result.push_back(new TAC(TAC_MOVE, ast->id, f1,f2));
			}
			break;
		
		case DEC_VAR: {
			if (ast->id2 != NULL) { //Vetor
				result.push_back(new TAC(TAC_MOVE, ast->id, ast->id2, f1));

			} else {
				result.push_back(new TAC(TAC_MOVE, ast->id, f2,0));
			}
				result = joinTAC(result, joinTAC(filho1, filho2));
		}
			break;
		case DEC_VAR_LIST: {
			result = joinTAC(result, joinTAC(filho1, filho2));
			result.push_back(new TAC(TAC_MOVE, makeTemp(symbolsTable), f1,f2));
		}
			break;
			
		case CMD_READ:
			result.push_back(new TAC(TAC_READ, ast->id,0,0));
			break;
		
		case LIST_CMD:	
		default: {
			result = joinTAC(filho1, joinTAC(filho2, filho3));
		}
			break;
	}

	return result;
}

vector<TAC*> generateCodeExp(Symbol* f1, Symbol* f2, TYPES tipo, SymbolsTable *symbolsTable) {
	vector<TAC*> result = {};
	
	TACTYPE tacTipo;
	
	switch(tipo) {
		case ARIT_SOMA:
			tacTipo = TAC_ADD;
		break;
		case ARIT_SUB:		
			tacTipo = TAC_SUB;
		break;
		case ARIT_MULT:
			tacTipo = TAC_MULT;
		break;
		case ARIT_DIV:
			tacTipo = TAC_DIV;
		break;
		case BOOL_NEGACAO:
			tacTipo = TAC_BNEG;
		break;
		case BOOL_MENOR:
			tacTipo = TAC_BLESS;
		break;
		case BOOL_MAIOR:	
			tacTipo = TAC_BHIGHER;
		break;
		case BOOL_IGUAL:
			tacTipo = TAC_BEQUAL;
		break;
		case BOOL_AND: 	
			tacTipo = TAC_BAND;
		break;
		case BOOL_OR:
			tacTipo = TAC_BOR;
		break;
		default:
			tacTipo = TAC_ADD;
	}
	result.push_back(new TAC(tacTipo, makeTemp(symbolsTable), f1,f2));
	return result;
}