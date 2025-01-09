// Etapa 6 do trabalho de Compiladores do semestre 2024/2
// Por Matheus Rodrigues Fonseca e Thalles Fernandes Rezende

#ifndef SYMBOLS_HPP
#define SYMBOLS_HPP

#include <iostream>
#include <map>
#include <string>

struct AST;
struct Symbol;

#include "parser.tab.hpp"

typedef struct Symbol {
	std::string value;
	std::string nickname;
	int token;
} Symbol;

class SymbolsTable
{
private:
  std::map<std::string, Symbol> table;

public:
  void initializeTable();
  
  Symbol* createSymbol(const int token, const std::string value, const std::string nickname);
  

Symbol* modifySymbol(const std::string text, const int token, const std::string value);


  void displayTable();
  
  void printAsmSymbols();
};

#endif