#ifndef ANALIZADOR_SINTACTICO_H_
#define ANALIZADOR_SINTACTICO_H_
#include "headders/ast.h"
#include "headders/token.h"
#include <list>

using namespace MiniPascal;
using namespace std;

class AnalizadorSintactico {
   private:
      AnalizadorSintactico();
   public:
      static Program* analizar(list<Token*>* tokenList);
      static Program* program(list<Token*>* tokenList);
      static Block* block(list<Token*>* tokenList);
      static Identifier* identifier(list<Token*>* tokenList);
      static VariableDeclarationPart* variableDeclarationPart(list<Token*>* tokenList);
};
#endif
