// Etapa 2 do trabalho de Compiladores do semestre 2024/2
// Por Matheus Rodrigues Fonseca e Thalles Fernandes Rezende

#ifndef SYMBOLS_HPP
#define SYMBOLS_HPP

#include <iostream>
#include <map>
#include <string>

struct Symbol {
	std::string name;
	int token;
};

class SymbolsTable
{
private:
  std::map<std::string, Symbol> table;

public:
  void initializeTable();
  
  Symbol* createSymbol(const int token, const std::string text);

  void insertSymbol(Symbol* symbol);

  void displayTable();
};

#endif