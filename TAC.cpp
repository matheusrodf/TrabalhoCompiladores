// Etapa 6 do trabalho de Compiladores do semestre 2024/2
// Por Matheus Rodrigues Fonseca e Thalles Fernandes Rezende

#include "TAC.hpp"

#include <string>
#include <iterator>
#include <algorithm>

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
				break;
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
			case TAC_PRINT_CHAR: {
				fprintf(stderr, "PRINT C ");
			}
				break;
			case TAC_PRINT_STRING: {
				fprintf(stderr, "PRINT S ");
			}
				break;
			case TAC_PRINT_INT: {
				fprintf(stderr, "PRINT I ");
			}
				break;
			case TAC_READ_CHAR: {
				fprintf(stderr, "READ C ");
			}
				break;
			case TAC_READ_INT: {
				fprintf(stderr, "READ I ");
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
			case TAC_DEC_ARG: {
				fprintf(stderr, "DECARG ");
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
			case TAC_DECVEC: {
				fprintf(stderr, "DECVEC ");
			}
				break;
			case TAC_SYMBOL_VEC: {
				fprintf(stderr, "SYM_VEC ");
			}
				break;
			default: {
				fprintf(stderr, "NADA ");
			}
				break;
		}
		if (kv->res) {
			fprintf(stderr, "(%s ", kv->res->nickname.c_str());
		} else fprintf(stderr, "(0 ");
		if (kv->op1) {
			fprintf(stderr, "%s ", kv->op1->nickname.c_str());
		} else fprintf(stderr, "0 ");
		if (kv->op2) {
			fprintf(stderr, "%s) ", kv->op2->nickname.c_str());
		} else fprintf(stderr, "0) ");
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
	string label = "label";
	label += to_string(labelId++);
	return symbolsTable->createSymbol(TK_LABEL, label, label, SYM_NONE);
}

Symbol* makeTemp(SymbolsTable *symbolsTable) {
	static int tempId;
	string temp = "temp";
	temp += to_string(tempId++);
	return symbolsTable->createSymbol(TK_ID, temp, temp, SYM_NONE);
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
	
	switch(ast->type) {
		case IDENTIFICADOR: {
			if (f1 != NULL) {
				Symbol *temp = makeTemp(symbolsTable);
				result = joinTAC(result, filho1);
				result.push_back(new TAC(TAC_SYMBOL_VEC, temp, ast->id, f1));
				result.push_back(new TAC(TAC_SYMBOL, temp,0,0));
			}
			else result.push_back(new TAC(TAC_SYMBOL, ast->id,0,0));
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
			result = joinTAC(result, generateCodeExp(f1, f2, ast->type, symbolsTable));
			break;
		case CMD_IF: {
			TAC *labelFalse = new TAC(TAC_LABEL, makeLabel(symbolsTable),0,0);
			TAC *labelTrue = new TAC(TAC_LABEL, makeLabel(symbolsTable),0,0);
			TAC *jumpTrue = new TAC(TAC_JUMP, labelTrue->res,0,0);
			
			//if (cond)
			//jump False
			//cmd
			//jumpTrue
			//labelFalse
			//else
			//cmd
			//labelTrue
			
			//cond
			result = joinTAC(result, filho1);
			//if (cond)
			result.push_back(new TAC(TAC_IF, f1, labelFalse->res, 0));
			//jump False
			//result.push_back(jumpFalse);
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
			TAC *jumpLoop = new TAC(TAC_JUMP, labelLoop->res,0,0);
			
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
			result.push_back(new TAC(TAC_IF, f1, labelFim->res, 0));
			// cmd
			result = joinTAC(result, filho2);
			// jump label
			result.push_back(jumpLoop);
			// label2
			result.push_back(labelFim);
		}
			break;
			
		case DEC_FUN:
			result.push_back(new TAC(TAC_BEGINFUN, ast->id, f2,0));
			result = joinTAC(result, filho2);
			result = joinTAC(result, filho3);
			result.push_back(new TAC(TAC_ENDFUN, ast->id, 0,0));
			break;
		case DEC_FUN_LIST: {
			TAC *arg = new TAC(TAC_DEC_ARG, ast->id,ast->id2, 0);
			arg->args = ast->args;
			result.push_back(arg);
			result = joinTAC(result, filho2);
		}
			break;
			
		case FUNCTION: {
			result = joinTAC(result, filho1);
			Symbol *temp = makeTemp(symbolsTable);
			result.push_back(new TAC(TAC_CALL, ast->id, f1,0));
			result.push_back(new TAC(TAC_MOVERETURN, temp, 0,0));
		}
			break;
		case FUN_PARAMS: {
			TAC *arg = new TAC(TAC_ARG, f1, f2,ast->id2);
			result = joinTAC(result, filho1);
			arg->args = ast->args;
			result.push_back(arg);
			result = joinTAC(result, filho2);
		}
			break;
		case CMD_RETURN: {
			result = joinTAC(result, filho1);
			result.push_back(new TAC(TAC_RET, f1, 0,0));
			result.push_back(new TAC(TAC_ENDFUN, 0, 0,0));
			}
			break;
		
		case CMD_PRINT: {
			if (ast->id != NULL) {
				result.push_back(new TAC(TAC_PRINT_STRING, ast->id, f2,0));
				result = joinTAC(result, filho2);
			} else {
				result = joinTAC(result, filho1);
				if (ast->datatype == SYM_CHAR) {
					result.push_back(new TAC(TAC_PRINT_CHAR, f1, f2, 0));
				} else if (ast->datatype == SYM_INT) {
					result.push_back(new TAC(TAC_PRINT_INT, f1, f2, 0));					
				}
					
				result = joinTAC(result, filho2);
			}
		}
			break;
		
		case CMD_ATTR:
			if (filho2.empty()) {
				result = joinTAC(result, filho1);
				result.push_back(new TAC(TAC_MOVE, ast->id, f1,0));
			} else {
				result = joinTAC(result, joinTAC(filho1, filho2));
				result.push_back(new TAC(TAC_MOVE, ast->id, f1,f2));
			}
			break;
		
		case DEC_VAR: {
			result.push_back(new TAC(TAC_MOVE, ast->id, f2,0));
			result = joinTAC(result, joinTAC(filho1, filho2));
		}
			break;
		case DEC_VEC: {
			//result.push_back(new TAC(TAC_DECVEC, ast->id, ast->id2, f2));
			result = joinTAC(result, joinTAC(filho1, filho2));
		}
			break;
		case DEC_VEC_LIST: {
			TAC *arg = new TAC(TAC_DECVEC, ast->id, f1,f2);
			arg->args = ast->args;
			result.push_back(arg);
			result = joinTAC(result, joinTAC(filho1, filho2));
		}
			break;
			
		case CMD_READ:
			if (ast->datatype == SYM_CHAR) 
				result.push_back(new TAC(TAC_READ_CHAR, ast->id,0,0));
			else if (ast->datatype == SYM_INT) 
				result.push_back(new TAC(TAC_READ_INT, ast->id,0,0));
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

void generateAsm(vector<TAC*> tac, SymbolsTable *symbolsTable) {
	printf(".data\n.printInt: .string \"%%d\"\n.printChar: .string \"%%c\"\n.printNewLine: .string \"\\n\"\n.readChar: .string \" %%c\"\n.globl main\n");
	
	symbolsTable->printAsmSymbols();
	printf(".text\n");
	printf("main:\n");
	
	for (const auto &kv : tac) {
		switch(kv->type) {
			
			case TAC_SYMBOL_VEC: {
			//TAC(TAC_SYMBOL_VEC, temp, ast->id, f1));
				printf("\n # SYMBOL_VEC\n");
				printf("movl %s(%%rip), %%eax\n leaq 0(,%%rax,4), %%rdx\n ", kv->op2->nickname.c_str());
				printf("leaq %s(%%rip), %%rax\n movl (%%rdx,%%rax), %%eax\n movl %%eax, %s(%%rip)\n", kv->op1->nickname.c_str() , kv->res->nickname.c_str());
				}
				break;
				
			case TAC_MOVERETURN: {
				printf("\n # MOVERETURN\n");
				printf("movl %%eax, %s(%%rip)\n", kv->res->nickname.c_str());
			}
				break;
			case TAC_LABEL: {
				printf("%s:\n", kv->res->nickname.c_str());
			}
				break;
			case TAC_ADD: {
				//add res op1 op2
				//movl op1(%rip), %eax
				//addl op2(%rip), %eax
				//movl %eax, res(%rip)
				printf("\n # ADD\n");
				printf("movl %s(%%rip), %%eax\n addl %s(%%rip), %%eax\n movl %%eax, %s(%%rip)\n", kv->op1->nickname.c_str(), kv->op2->nickname.c_str(), kv->res->nickname.c_str());
				}
				break;
			case TAC_SUB: {
				printf("\n # SUB\n");
				printf("movl %s(%%rip), %%eax\n subl %s(%%rip), %%eax\n movl %%eax, %s(%%rip)\n", kv->op1->nickname.c_str(), kv->op2->nickname.c_str(), kv->res->nickname.c_str());
			}
				break;
			case TAC_MULT: {
				printf("\n # MULT\n");
				printf("movl %s(%%rip), %%edx\n movl %s(%%rip), %%eax\n imull %%edx, %%eax\n movl %%eax, %s(%%rip)\n", kv->op1->nickname.c_str(), kv->op2->nickname.c_str(), kv->res->nickname.c_str());
			}
				break;
			case TAC_DIV: {
				printf("\n # DIV\n");
				printf("movl %s(%%rip), %%eax\n movl %s(%%rip), %%ecx\n cltd\n idivl %%ecx, %%eax\n movl %%eax, %s(%%rip)\n", kv->op1->nickname.c_str(), kv->op2->nickname.c_str(), kv->res->nickname.c_str());
			}
				break;
			case TAC_BNEG: {
				printf("\n # NEG\n");
				printf("movl %s(%%rip), %%eax\n testl %%eax, %%eax\n sete %%al\n movzbl %%al, %%eax\n movl %%eax, %s(%%rip)\n", kv->op1->nickname.c_str(), kv->res->nickname.c_str());
			}
				break;
			case TAC_BLESS: {
				printf("\n # LESS\n");
				printf("movl %s(%%rip), %%edx\n movl %s(%%rip), %%eax\n cmpl %%eax, %%edx\n setl %%al\n movzbl %%al, %%eax\n movl %%eax, %s(%%rip)\n", kv->op1->nickname.c_str(), kv->op2->nickname.c_str(), kv->res->nickname.c_str());
			}
				break;
			case TAC_BHIGHER: {
				printf("\n # \n");
				printf("movl %s(%%rip), %%edx\n movl %s(%%rip), %%eax\n cmpl %%eax, %%edx\n setg %%al\n movzbl %%al, %%eax\n movl %%eax, %s(%%rip)\n", kv->op1->nickname.c_str(), kv->op2->nickname.c_str(), kv->res->nickname.c_str());
			}
				break;
			case TAC_BEQUAL: {
				printf("\n # =\n");
				printf("movl %s(%%rip), %%edx\n movl %s(%%rip), %%eax\n cmpl %%eax, %%edx\n sete %%al\n movzbl %%al, %%eax\n movl %%eax, %s(%%rip)\n", kv->op1->nickname.c_str(), kv->op2->nickname.c_str(), kv->res->nickname.c_str());
			}
				break;
			case TAC_BAND: {
				printf("\n # AND\n");
				printf("movl %s(%%rip), %%edx\n movl %s(%%rip), %%eax\n andl %%edx, %%eax\n movl %%eax, %s(%%rip)\n", kv->op1->nickname.c_str(), kv->op2->nickname.c_str(), kv->res->nickname.c_str());
			}
				break;
			case TAC_BOR: {
				printf("\n # OR\n");
				printf("movl %s(%%rip), %%edx\n movl %s(%%rip), %%eax\n orl %%edx, %%eax\n movl %%eax, %s(%%rip)\n", kv->op1->nickname.c_str(), kv->op2->nickname.c_str(), kv->res->nickname.c_str());
			}
				break;
			case TAC_IF: {
				printf("\n # IF\n");
				printf("movl %s(%%rip), %%eax\n testl %%eax, %%eax\n", kv->res->nickname.c_str());
				printf(" je %s\n", kv->op1->nickname.c_str());
			}
				break;
			case TAC_JUMP: {
				printf("\n # JMP\n");
				printf("jmp %s\n", kv->res->nickname.c_str());
			}
				break;
			case TAC_PRINT_CHAR: {
				printf("\n # PRINT_CHAR\n");
				printf("movl %s(%%rip), %%eax\n movl %%eax, %%esi\n leaq .printChar(%%rip), %%rax\n movq %%rax, %%rdi\n call printf@PLT\n", kv->res->nickname.c_str());
				if (kv->op1 == NULL) {
					printf("leaq .printNewLine(%%rip), %%rax\n movq %%rax, %%rdi\n call printf@PLT\n");
				}
			}
				break;
			case TAC_PRINT_INT: {
				printf("\n # PRINT_INT\n");
				printf("movl %s(%%rip), %%eax\n movl %%eax, %%esi\n leaq .printInt(%%rip), %%rax\n movq %%rax, %%rdi\n call printf@PLT\n", kv->res->nickname.c_str());
				if (kv->op1 == NULL) {
					printf("leaq .printNewLine(%%rip), %%rax\n movq %%rax, %%rdi\n call printf@PLT\n");
				}
			}
				break;
			case TAC_PRINT_STRING: {
				printf("\n # PRINT_STRING\n");
				printf("leaq %s(%%rip), %%rax\n movq %%rax, %%rdi\n call printf@PLT\n", kv->res->nickname.c_str());
				if (kv->op1 == NULL) {
					printf("leaq .printNewLine(%%rip), %%rax\n movq %%rax, %%rdi\n call printf@PLT\n");
				}
			}
				break;
			case TAC_READ_INT: {
				printf("\n # READ_INT\n");
				printf("leaq %s(%%rip), %%rax\n movq %%rax, %%rsi\n", kv->res->nickname.c_str());
				printf("leaq .printInt(%%rip), %%rax\n movq %%rax, %%rdi\n call scanf@PLT\n");
			}
				break;
			case TAC_READ_CHAR: {
				printf("\n # READ_CHAR\n");
				printf("leaq %s(%%rip), %%rax\n movq %%rax, %%rsi\n", kv->res->nickname.c_str());
				printf("leaq .readChar(%%rip), %%rax\n movq %%rax, %%rdi\n call scanf@PLT\n");
			}
				break;
			case TAC_MOVE: {
				printf("\n # MOVE\n");
				if (kv->op2 != NULL) {
					printf("  # VEC\n");
					printf("movl %s(%%rip), %%edx\n movl %s(%%rip), %%eax\n movslq %%edx, %%rdx\n leaq 0(,%%rdx,4), %%rcx\n leaq %s(%%rip), %%rdx\n movl %%eax, (%%rcx, %%rdx)\n", kv->op2->nickname.c_str(), kv->op1->nickname.c_str(), kv->res->nickname.c_str());					
				} else {
					printf("movl %s(%%rip), %%eax\n movl %%eax, %s(%%rip)\n", kv->op1->nickname.c_str(), kv->res->nickname.c_str());
				}
			}
				break;
			case TAC_DECVEC: {
				printf("\n # DECVEC\n");
				printf("movl %s(%%rip), %%eax\n movl %%eax, %d+%s(%%rip)\n", kv->op1->nickname.c_str(), 4*kv->args, kv->res->nickname.c_str());
			}
				break;
			case TAC_BEGINFUN: {
				printf("\n # BEGINFUN\n");
				printf("%s:\n pushq %%rbp\n movq %%rsp, %%rbp\n", kv->res->nickname.c_str());
			}
				break;
			case TAC_ENDFUN: {
				printf("\n # ENDFUN\n");
				printf("popq %%rbp\n ret\n");
			}
				break;
			case TAC_CALL: {
				printf("\n # CALL\n");
				printf("call %s\n", kv->res->nickname.c_str());
			}
				break;
			case TAC_DEC_ARG: {
				printf("\n # DEC ARG\n");
				printf("movl %s_%d(%%rip), %%eax\n movl %%eax, %s(%%rip)\n", kv->op1->nickname.c_str(), kv->args, kv->res->nickname.c_str());
			}
				break;
			case TAC_ARG: {
				printf("\n # ARG\n");
				printf("movl %s(%%rip), %%eax\n movl %%eax, %s_%d(%%rip)\n", kv->res->nickname.c_str(), kv->op2->nickname.c_str(), kv->args);
			}
				break;
			case TAC_RET: {
				printf("\n # RETURN\n");
				printf("movl %s(%%rip), %%eax\n", kv->res->nickname.c_str());
			}
				break;
			default: {
				//fprintf(stderr, "NADA ");
			}
				break;
		}
	}
	printf(".section .note.GNU-stack,\"\",@progbits\n");
}