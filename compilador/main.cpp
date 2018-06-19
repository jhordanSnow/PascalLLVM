#include<iostream>
#include<fstream>
#include<string>
#include<list>

#include "headders/lexer.h"
#include "headders/ast.h"
#include "headders/analizadorSintactico.h"
#include "headders/env.h"

using namespace std;
using namespace MiniPascal;

void reportError(string error){
  std::cout << error << '\n';
}

list<string>* getInputStream(string fileName){
  ifstream codefile (fileName);
  string line;
  list<string>* code = new list<string>();

  if (codefile.is_open()) {
     while (getline(codefile, line)) {
        code->push_back(line);
     }
     codefile.close();
  } else {
     reportError("No se abrio ningun archivo");
  }

  return code;
}

int main(int argc, char** argv) {
   if (argc != 2) {
      reportError("uso " + string(argv[0]) + " <NombreArchivo>");
      return -1;
   }

   Lexer* lexer = new Lexer();

   list<string>* code = getInputStream(argv[1]);
   list<Token*>* tokens = lexer->tokenize(code);

   Program* p = AnalizadorSintactico::analizar(tokens);
   p->print();
   //p->compile();

   return 0;
}
