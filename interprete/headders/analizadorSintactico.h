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
      static list<VariableDeclaration*>* variableDeclarations(list<Token*>* tokenList);
      static VariableDeclaration* variableDeclaration(list<Token*>* tokenList);
      static std::list<Identifier*>* optionalVariableDeclarations(list<Token*>* tokenList, std::list<Identifier*>* identifierList);
      static StatementPart* statementPart(list<Token*>* tokenList);
      static CompoundStatement* compoundStatement(list<Token*>* tokenList);
      static list<Statement*>* statements(list<Token*>* tokenList);

      static SimpleStatement* simpleStatement(list<Token*>* tokenList);
      static AssignmentStatement* assignmentStatement(list<Token*>* tokenList);
      static ReadStatement* readStatement(list<Token*>* tokenList);
      static WriteStatement* writeStatement(list<Token*>* tokenList);
      
      static StructuredStatement* structuredStatement(list<Token*>* tokenList);

      static Variable* variable(list<Token*>* tokenList);
      static EntireVariable* entireVariable(list<Token*>* tokenList);
      static VariableIdentifier* variableIdentifier(list<Token*>* tokenList);

      static IndexedVariable* indexedVariable(list<Token*>* tokenList);
      static ArrayVariable* arrayVariable(list<Token*>* tokenList);

      static Expression* expression(list<Token*>* tokenList);
      static SimpleExpression* simpleExpression(list<Token*>* tokenList);
      static Term* term(list<Token*>* tokenList);
      static Factor* factor(list<Token*>* tokenList);
      static Constant* constant(list<Token*>* tokenList);     


};
#endif
