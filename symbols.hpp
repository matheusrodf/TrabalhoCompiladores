// Etapa 3 do trabalho de Compiladores do semestre 2024/2
// Por Matheus Rodrigues Fonseca e Thalles Fernandes Rezende

#ifndef SYMBOLS_HPP
#define SYMBOLS_HPP

#include <iostream>
#include <map>
#include <string>

struct AST;
struct Symbol;

#include "parser.tab.hpp"

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

  void displayTable();
};

#endif