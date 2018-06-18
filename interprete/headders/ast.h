#ifndef AST_H_
#define AST_H_

#include<headders/env.h>
#include<string>
#include<list>
#include<iostream>

// Forward Declarations
class Block;
class StructuredStatement;
class CompoundStatement;

using namespace std;

class Node {
   public:
      Node();
      void execute();
      virtual void print() = 0;
};

class Expression;
/* Lexical Grammar */
class Identifier : public Node {
   public:
      Identifier(string identifier);
      string identifier;
      void execute();
      void print();
};

class ConstantIdentifier : public Node {
   public:
      ConstantIdentifier(Identifier* identifier);
      Identifier* identifier;
      void execute();
      void print();
};

class Constant : public Node {
   public:
      Constant(int intConst);
      Constant(string stringConst);
      Constant(ConstantIdentifier* constIdentifier);
      int intConst;
      string stringConst;
      ConstantIdentifier* constIdentifier;
      void execute();
      void print();
};
/* Lexical Grammar */

/* Types */
class TypeIdentifier : public Node {
   public:
      TypeIdentifier(Identifier* identifier);
      Identifier* identifier;
      void execute();
      void print();
};

enum class SimpleType{
   UNKNOWN,
   CHAR,
   INTEGER,
   BOOLEAN
};

class IndexRange : public Node {
   public:
      IndexRange(int begining, int end);
      int begining;
      int end;
      void execute();
      void print();
};

class ArrayType : public Node {
   public:
      ArrayType(SimpleType simpleType);
      ArrayType(IndexRange* indexRange, SimpleType simpleType);
      IndexRange* indexRange;
      SimpleType simpleType;
      void execute();
      void print();
};

class DataType : public Node {
   public:
      DataType(SimpleType simpleType);
      DataType(ArrayType* arrayType);
      SimpleType simpleType;
      ArrayType* arrayType;
      void execute();
      void print();
};
/* Types */

/* Expressions */

class VariableIdentifier : public Node {
   public:
      VariableIdentifier(Identifier* variableIdentifier);
      Identifier* variableIdentifier;
      void execute();
      void print();
};

class EntireVariable : public Node {
   public:
      EntireVariable(VariableIdentifier* variableIdentifier);
      VariableIdentifier* variableIdentifier;
      void execute();
      void print();
};

class ArrayVariable : public Node {
   public:
      ArrayVariable(EntireVariable* entireVariable);
      EntireVariable* entireVariable;
      void execute();
      void print();
};

class IndexedVariable : public Node {
   public:
      IndexedVariable(ArrayVariable* arrayVariable, Expression* expression);
      ArrayVariable* arrayVariable;
      Expression* expression;
      void execute();
      void print();
};

class VariableNT : public Node {
   public:
      VariableNT(EntireVariable* entireVariable);
      VariableNT(IndexedVariable* indexedVariable);
      EntireVariable* entireVariable;
      IndexedVariable* indexedVariable;
      int value;
      string stringValue;
      int type;
      void execute();
      void print();
};

enum class RelationalOperator{
   UNKNOWN,
   EQ,
   NEQ,
   LT,
   LEQ,
   GT,
   GEQ,
   OR,
   AND
};

enum class AdditionOperator{
   UNKNOWN,
   ADD,
   SUB
};

enum class MultiplicationOperator{
   UNKNOWN,
   MUL,
   DIV
};

enum class Sign {
   POSITIVE,
   NEGATIVE
};

class AbstractFactor : public Node {
   public:
      void execute();
      int value;
      string stringValue;
      int type;
      virtual void print() = 0;
};

class NotFactor : public AbstractFactor {
   public:
      NotFactor(AbstractFactor* factor);
      AbstractFactor* factor;
      void execute();
      void print();
};

class Factor : public AbstractFactor {
   public:
      Factor(VariableNT* variable);
      Factor(Constant* constant);
      Factor(Expression* expression);
      VariableNT* variable;
      Constant* constant;
      Expression* expression;
      void execute();
      void print();
};

class Term : public Node {
   public:
      Term(list<AbstractFactor*>* factors, list<MultiplicationOperator>* operators);
      list<AbstractFactor*>* factors;
      list<MultiplicationOperator>* operators;
      int value;
      string stringValue;
      int type;
      void execute();
      void print();
};

class SimpleExpression : public Node {
   public:
      SimpleExpression(Sign sign, list<Term*>* terms, list<AdditionOperator>* additionOperators);
      Sign sign;
      list<Term*>* terms;
      list<AdditionOperator>* additionOperators;
      int value;
      string stringValue;
      int type;
      void execute();
      void print();
};

class Expression : public Node {
   public:
      Expression(SimpleExpression* simpleExpression1);
      Expression(SimpleExpression* simpleExpression1, RelationalOperator relationalOperator, SimpleExpression* simpleExpression2);
      SimpleExpression* simpleExpression1;
      RelationalOperator relationalOperator;
      SimpleExpression* simpleExpression2;
      int value;
      string stringValue;
      int type;
      void execute();
      void print();
};
/* Expressions */

/* Statements */
class Statement;

class WhileStatement : public Node {
   public:
      WhileStatement(Expression* expression, Statement* statement);
      Expression* expression;
      Statement* statement;
      void execute();
      void print();
};

class IfStatement : public Node {
   public:
      IfStatement(Expression* expression, Statement* thenStatement);
      IfStatement(Expression* expression, Statement* thenStatement, Statement* elseStatement);
      Expression* expression;
      Statement* statement;
      Statement* elseStatement;
      void execute();
      void print();
};

class StructuredStatement : public Node {
   public:
      StructuredStatement(CompoundStatement* compoundStatement);
      StructuredStatement(IfStatement* ifStatement);
      StructuredStatement(WhileStatement* whileStatement);
      CompoundStatement* compoundStatement;
      IfStatement* ifStatement;
      WhileStatement* whileStatement;
      void execute();
      void print();
};

class WriteStatement : public Node {
   public:
      WriteStatement(list<VariableNT*>* variableList);
      list<VariableNT*>* variableList;
      void execute();
      void print();
};

class ReadStatement : public Node {
   public:
      ReadStatement(list<VariableNT*>* variableList);
      list<VariableNT*>* variableList;
      void execute();
      void print();
};

class AssignmentStatement : public Node {
   public:
      AssignmentStatement(VariableNT* variable, Expression* expression);
      VariableNT* variable;
      Expression* expression;
      void execute();
      void print();
};

class SimpleStatement : public Node {
   public:
      SimpleStatement(AssignmentStatement* assignmentStatement);
      SimpleStatement(ReadStatement* readStatement);
      SimpleStatement(WriteStatement* writeStatement);
      AssignmentStatement* assignmentStatement;
      ReadStatement* readStatement;
      WriteStatement* writeStatement;
      void execute();
      void print();
};

class Statement : public Node {
   public:
      Statement(SimpleStatement* simpleStatement);
      Statement(StructuredStatement* structuredStatement);
      SimpleStatement* simpleStatement;
      StructuredStatement* structuredStatement;
      void execute();
      void print();
};
;
class CompoundStatement : public Node {
   public:
      CompoundStatement(list<Statement*>* statementList);
      list<Statement*>* statementList;
      void execute();
      void print();
};

class StatementPart : public Node {
   public:
      StatementPart(CompoundStatement* compoundStatement);
      CompoundStatement* compoundStatement;
      void execute();
      void print();
};

/* Statements */

class VariableDeclaration : public Node {
   public:
      VariableDeclaration(list<Identifier*>* identifierList, DataType* dataType);
      list<Identifier*>* identifierList;
      DataType* dataType;
      void execute();
      void print();
};

class VariableDeclarationPart : public Node {
   public:
      VariableDeclarationPart(list<VariableDeclaration*>* variableDeclarations);
      VariableDeclarationPart();
      list<VariableDeclaration*>* variableDeclarations;
      void execute();
      void print();
};

class Block : public Node {
   public:
      Block(VariableDeclarationPart* variableDeclarationPart, StatementPart* statementPart);
      VariableDeclarationPart* variableDeclarationPart;
      StatementPart* statementPart;
      void execute();
      void print();
};

class Program : public Node {
   public:
      Program(Identifier* identifier, Block* block);
      Identifier* identifier;
      Block* block;
      void execute();
      void print();
};
#endif
