#ifndef ANALIZADOR_SINTACTICO_H_
#define ANALIZADOR_SINTACTICO_H_
#include "headders/ast.h"
#include "headders/token.h"
#include "headders/helpers.h"
#include <list>

using namespace MiniPascal;
using namespace std;

class AnalizadorSintactico {
   public:
     AnalizadorSintactico();
      list<Function*>* procedures;
      list<string>* procedureNames;
      Program* analizar(list<Token*>* tokenList);
      Program* program(list<Token*>* tokenList);
      Block* block(list<Token*>* tokenList);
      Identifier* identifier(list<Token*>* tokenList);
      VariableDeclarationPart* variableDeclarationPart(list<Token*>* tokenList);
      void optionalVariableDeclarationsPart(list<Token*>* tokenList, VariableDeclarationPart* variableDeclarationPart);

      void functionsPart(list<Token*>* tokenList);
      int getIndexProcedure(list<string>* procedureNames, string name);
      StructuredStatement* procedureStatement(list<Token*>* tokenList, int index);
      list<VariableDeclaration*>* functionVariables(list<Token*>* tokenList);

      void errorMsgTkn(string expected, Token* token);
      void errorMsg(string msg);

      VariableDeclaration* variableDeclaration(list<Token*>* tokenList);
      void optionalVariableDeclarations(list<Token*>* tokenList, std::list<Identifier*>* identifierList);
      int getCantParams(list<VariableDeclaration*>* varaibleDecaraions);

      DataType* dataType(list<Token*>* tokenList);
      ArrayType* arrayType(list<Token*>* tokenList);
      IndexRange* indexRange(list<Token*>* tokenList);
      SimpleType simpleType(list<Token*>* tokenList);
      TypeIdentifier* typeIdentifier(list<Token*>* tokenList);


      StatementPart* statementPart(list<Token*>* tokenList);
      CompoundStatement* compoundStatement(list<Token*>* tokenList);
      Statement* statement(list<Token*>* tokenList);
      void optionalStatements(list<Token*>* tokenList, CompoundStatement* compoundStatement);

      SimpleStatement* simpleStatement(list<Token*>* tokenList);
      AssignmentStatement* assignmentStatement(list<Token*>* tokenList);
      ReadStatement* readStatement(list<Token*>* tokenList);
      WriteStatement* writeStatement(list<Token*>* tokenList);

      StructuredStatement* structuredStatement(list<Token*>* tokenList);
      IfStatement* ifStatement(list<Token*>* tokenList);
      WhileStatement* whileStatement(list<Token*>* tokenList);

      VariableNT* variable(list<Token*>* tokenList);
      EntireVariable* entireVariable(list<Token*>* tokenList);
      VariableIdentifier* variableIdentifier(list<Token*>* tokenList);

      IndexedVariable* indexedVariable(list<Token*>* tokenList);
      ArrayVariable* arrayVariable(list<Token*>* tokenList);

      void optionalVariables(list<Token*>* tokenList, ReadStatement* readStatement);
      void optionalVariables(list<Token*>* tokenList, WriteStatement* writeStatement);

      Expression* expression(list<Token*>* tokenList);
      SimpleExpression* simpleExpression(list<Token*>* tokenList);
      void optionalTerms(list<Token*>* tokenList, SimpleExpression* simpleExpression);
      Term* term(list<Token*>* tokenList);
      void optionalFactors(list<Token*>* tokenList, Term* term);
      AbstractFactor* factor(list<Token*>* tokenList);

};
#endif
