// Parte 1 do trabalho de Compiladores do semestre 2024/2
// Por Matheus Rodrigues Fonseca e Thalles Rezende

#include <string>
#include <iostream>
#include <map>
using namespace std;

map<string, int> symbolTable;

void InsertSymbol(int token, string text) {
	symbolTable[text] = token;
}

void PrintSymbols() {
	for (map<string,int>::iterator it=symbolTable.begin(); it != symbolTable.end(); ++it) {
		std::cout << "id:" << it->first << " tipo: " << it->second << '\n';		
	}
}