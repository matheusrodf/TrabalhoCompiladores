// Etapa 5 do trabalho de Compiladores do semestre 2024/2
// Por Matheus Rodrigues Fonseca e Thalles Fernandes Rezende

#include "TAC.hpp"
#include "parser.tab.hpp"

#include <string>
using namespace std;
Symbol* createSymbol(const int token, const std::string text);



void printTAC(vector<TAC> tac) {
}

vector<TAC> joinTAC(vector<TAC> tac1,vector<TAC> tac2) {
}

Symbol* makeLabel() {
	static int labelId;
	string label = "__label";
	label += to_string(labelId++);
	return createSymbol(TK_IDENTIFIER, label);
}

Symbol* makeTemp() {
	static int tempId;
	string temp = "__temp";
	temp += to_string(tempId++);
	return createSymbol(TK_IDENTIFIER, temp);
}

vector<TAC> generateCode() {
	
}
