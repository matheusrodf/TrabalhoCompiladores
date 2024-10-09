// Parte 1 do trabalho de Compiladores do semestre 2024/2
// Por Matheus Rodrigues Fonseca e Thalles Fernandes Rezende

#ifndef SYMBOLS_HPP
#define SYMBOLS_HPP

#include <iostream>
#include <map>
#include <string>

class SymbolsTable
{
private:
  std::map<std::string, int> table;

public:
  void initializeTable();

  void insertSymbol(const int &token, const std::string &text);

  void displayTable();
};

#endif