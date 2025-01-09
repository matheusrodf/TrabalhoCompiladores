// Etapa 6 do trabalho de Compiladores do semestre 2024/2
// Por Matheus Rodrigues Fonseca e Thalles Fernandes Rezende
#include "symbols.hpp"

extern int getLineNumber();

void SymbolsTable::initializeTable()
{
	table.clear();
};

Symbol* SymbolsTable::createSymbol(const int token, const std::string value, const std::string nickname)
{
	if (token == TOKEN_ERROR)
		printf("Erro detectado na linha %d\n", getLineNumber());

	Symbol *s = new Symbol();
	s->value = value;
	s->token = token;
	s->nickname = nickname;
	
	// Busca na tabela se nome ja existe, se não existir, cria
	if (table.find(s->value) == table.end()) {
		table[s->value] = *s;
	}
	
	return s;
};

Symbol* SymbolsTable::modifySymbol(const std::string text, const int token, const std::string value) {
	table[text].token = token;
	table[text].value = value;
	return &table[text];
}


void SymbolsTable::displayTable()
{
	std::cout << "\n---- TABELA DE SIMBOLOS ----" << std::endl;
	for (const auto &kv : table)
	{
		std::cout << "id[" << kv.first << "] = nome(" << kv.second.value << ", " << kv.second.nickname << ") " << "token(" << kv.second.token << ")" << std::endl;
	}
};

void SymbolsTable::printAsmSymbols() {
	for (const auto &kv : table)
	{
		switch(kv.second.token) {
		case LIT_STRING:
			printf("%s:\n.string %s\n", kv.second.nickname.c_str(), kv.second.value.c_str());
		break;
		case LIT_INT: {
			printf("%s:\n.long %s\n", kv.second.nickname.c_str(), kv.second.value.c_str());
		}
		break;
		case LIT_CHAR:
			printf("%s:\n.long %s\n", kv.second.nickname.c_str(), kv.second.value.c_str());
		break;
		case TK_VEC:
			printf("%s:\n", kv.second.nickname.c_str());
			for (int i = 0; i < stoi(kv.second.value); i++)
				printf(".long 0\n");
				
		break;
		case TK_IDENTIFIER_CHAR:
		case TK_IDENTIFIER_INT:
		case TK_IDENTIFIER:
			printf("%1$s:\n.long 0\n", kv.second.nickname.c_str());
		break;
		default:
		break;
		}
	}
};