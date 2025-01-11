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

enum DATATYPE {
	SYM_NONE,
	SYM_INT,
	SYM_CHAR,
	SYM_BOOL,
	SYM_STRING
};

typedef struct Symbol {
	std::string value;
	std::string nickname;
	int token;
	DATATYPE type;
	int args;
} Symbol;

class SymbolsTable
{
private:
  std::map<std::string, Symbol> table;

public:
  void initializeTable();
  
  Symbol* createSymbol(const int token, const std::string value, const std::string nickname, DATATYPE type);

  Symbol* modifySymbol(const std::string text, const int token, const std::string value, DATATYPE datatype);
  Symbol* setArgsSymbol(const std::string text, int args);

  Symbol* find(const std::string text);


  void displayTable();
  
  void printAsmSymbols();
  
  bool checkUndeclaration();

};

#endif
