#ifndef ANALIZADOR_SINTACTICO_H_
#define ANALIZADOR_SINTACTICO_H_
#include "headders/ast.h"
#include "headders/token.h"
#include "headders/helpers.h"
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
      static void optionalVariableDeclarationsPart(list<Token*>* tokenList, VariableDeclarationPart* variableDeclarationPart);

      static void errorMsg(string msg);
      static void errorMsgTkn(string expected, Token* token);

      static VariableDeclaration* variableDeclaration(list<Token*>* tokenList);
      static void optionalVariableDeclarations(list<Token*>* tokenList, std::list<Identifier*>* identifierList);

      static DataType* dataType(list<Token*>* tokenList);
      static ArrayType* arrayType(list<Token*>* tokenList);
      static IndexRange* indexRange(list<Token*>* tokenList);
      static SimpleType simpleType(list<Token*>* tokenList);
      static TypeIdentifier* typeIdentifier(list<Token*>* tokenList);


      static StatementPart* statementPart(list<Token*>* tokenList);
      static CompoundStatement* compoundStatement(list<Token*>* tokenList);
      static Statement* statement(list<Token*>* tokenList);
      static void optionalStatements(list<Token*>* tokenList, CompoundStatement* compoundStatement);

      static SimpleStatement* simpleStatement(list<Token*>* tokenList);
      static AssignmentStatement* assignmentStatement(list<Token*>* tokenList);
      static ReadStatement* readStatement(list<Token*>* tokenList);
      static WriteStatement* writeStatement(list<Token*>* tokenList);

      static StructuredStatement* structuredStatement(list<Token*>* tokenList);
      static IfStatement* ifStatement(list<Token*>* tokenList);
      static WhileStatement* whileStatement(list<Token*>* tokenList);

      static VariableNT* variable(list<Token*>* tokenList);
      static EntireVariable* entireVariable(list<Token*>* tokenList);
      static VariableIdentifier* variableIdentifier(list<Token*>* tokenList);

      static IndexedVariable* indexedVariable(list<Token*>* tokenList);
      static ArrayVariable* arrayVariable(list<Token*>* tokenList);

      static void optionalVariables(list<Token*>* tokenList, ReadStatement* readStatement);
      static void optionalVariables(list<Token*>* tokenList, WriteStatement* writeStatement);

      static Expression* expression(list<Token*>* tokenList);
      static SimpleExpression* simpleExpression(list<Token*>* tokenList);
      static void optionalTerms(list<Token*>* tokenList, SimpleExpression* simpleExpression);
      static Term* term(list<Token*>* tokenList);
      static void optionalFactors(list<Token*>* tokenList, Term* term);
      static AbstractFactor* factor(list<Token*>* tokenList);


};
#endif
