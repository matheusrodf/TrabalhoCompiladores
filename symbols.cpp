// Etapa 2 do trabalho de Compiladores do semestre 2024/2
// Por Matheus Rodrigues Fonseca e Thalles Fernandes Rezende
#include "symbols.hpp"

extern int getLineNumber();

void SymbolsTable::initializeTable()
{
	table.clear();
};

Symbol* SymbolsTable::createSymbol(const int token, const std::string text)
{
	if (token == TOKEN_ERROR)
		printf("Erro detectado na linha %d\n", getLineNumber());

	Symbol *s = new Symbol();
	s->name = text;
	s->token = token;
	
	// Busca na tabela se nome ja existe, se não existir, cria
	if (table.find(s->name) == table.end()) {
		table[s->name] = *s;
	}
	
	return s;
};


void SymbolsTable::displayTable()
{
	std::cout << "\n---- TABELA DE SIMBOLOS ----" << std::endl;
	for (const auto &kv : table)
	{
		std::cout << "id[" << kv.first << "] = nome(" << kv.second.name << ") token(" << kv.second.token << ")" << std::endl;
	}
};