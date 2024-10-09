// Parte 1 do trabalho de Compiladores do semestre 2024/2
// Por Matheus Rodrigues Fonseca e Thalles Fernandes Rezende
#include "symbols.hpp"
#include "tokens.h"

extern int getLineNumber();

void SymbolsTable::initializeTable()
{
	table.clear();
};

void SymbolsTable::insertSymbol(const int &token, const std::string &text)
{
	if (token == TOKEN_ERROR)
		printf("Erro detectado na linha %d\n", getLineNumber());

	table[text] = token;
};

void SymbolsTable::displayTable()
{
	std::cout << "---- TABELA DE SIMBOLOS ----" << std::endl;
	for (const auto &kv : table)
	{
		std::cout << "id: " << kv.first << " tipo: " << kv.second << std::endl;
	}
};