#ifndef AST_H_
#define AST_H_

#include<string>
#include<list>

// Forward Declarations
class Block;
class StructuredStatement;
class CompoundStatement;

class Node {
   public:
      Node();
      void execute();
};

class Expression;
/* Lexical Grammar */
class Identifier : public Node {
   public:
      Identifier(std::string identifier);
      std::string identifier;
      void execute();
};

class ConstantIdentifier : public Node {
   public:
      ConstantIdentifier(Identifier* identifier);
      Identifier* identifier;
      void execute();
};

class Constant : public Node {
   public:
      Constant(int intConst);
      Constant(std::string stringConst);
      Constant(ConstantIdentifier* constIdentifier);
      int intConst;
      std::string stringConst;
      ConstantIdentifier* constIdentifier;
      void execute();
};
/* Lexical Grammar */

/* Types */
class TypeIdentifier : public Node {
   public:
      TypeIdentifier(Identifier* identifier);
      Identifier* identifier;
      void execute();
};

enum class SimpleType{
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
};

class ArrayType : public Node {
   public:
      ArrayType(SimpleType simpleType);
      ArrayType(IndexRange* indexRange, SimpleType simpleType);
      IndexRange* indexRange;
      SimpleType simpleType;
      void execute();
};

class DataType : public Node {
   public:
      DataType(SimpleType simpleType);
      DataType(ArrayType* arrayType);
      SimpleType simpleType;
      ArrayType* arrayType;
      void execute();
};
/* Types */

/* Expressions */

class VariableIdentifier : public Node {
   public:
      VariableIdentifier(Identifier* variableIdentifier);
      Identifier* variableIdentifier;
      void execute();
};

class EntireVariable : public Node {
   public:
      EntireVariable(VariableIdentifier* variableIdentifier);
      VariableIdentifier* variableIdentifier;
      void execute();
};

class ArrayVariable : public Node {
   public:
      ArrayVariable(EntireVariable* entireVariable);
      EntireVariable* entireVariable;
      void execute();
};

class IndexedVariable : public Node {
   public:
      IndexedVariable(ArrayVariable* arrayVariable, Expression* expression);
      ArrayVariable* arrayVariable;
      Expression* expression;
      void execute();
};

class VariableNT : public Node {
   public:
      VariableNT(EntireVariable* entireVariable);
      VariableNT(IndexedVariable* indexedVariable);
      EntireVariable* entireVariable;
      IndexedVariable* indexedVariable;
      void execute();
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

class AbstractFactor : public Node {void execute();
};
class NotFactor : public AbstractFactor {
   public:
      NotFactor(AbstractFactor* factor);
      AbstractFactor* factor;
      void execute();
};

class Factor : public AbstractFactor {
   public:
      Factor(VariableNT* variable);
      Factor(Constant* constant);
      VariableNT* variable;
      Constant* constant;
      void execute();
};

class Term : public Node {
   public:
      Term(std::list<AbstractFactor*>* factors, std::list<MultiplicationOperator>* operators);
      std::list<AbstractFactor*>* factors;
      std::list<MultiplicationOperator>* operators;
      void execute();
};

class SimpleExpression : public Node {
   public:
      SimpleExpression(Sign sign, std::list<Term*>* terms, std::list<AdditionOperator>* additionOperators);
      Sign sign;
      std::list<Term*>* terms;
      std::list<AdditionOperator>* additionOperators;
      void execute();
};

class Expression : public Node {
   public:
      Expression(SimpleExpression* simpleExpression1);
      Expression(SimpleExpression* simpleExpression1, RelationalOperator relationalOperator, SimpleExpression* simpleExpression2);
      SimpleExpression* simpleExpression1;
      RelationalOperator relationalOperator;
      SimpleExpression* simpleExpression2;
      void execute();
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
};

class IfStatement : public Node {
   public:
      IfStatement(Expression* expression, Statement* thenStatement);
      IfStatement(Expression* expression, Statement* thenStatement, Statement* elseStatement);
      Expression* expression;
      Statement* statement;
      Statement* elseStatement;
      void execute();
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
};

class WriteStatement : public Node {
   public:
      WriteStatement(std::list<VariableNT*>* variableList);
      std::list<VariableNT*>* variableList;
      void execute();
};

class ReadStatement : public Node {
   public:
      ReadStatement(std::list<VariableNT*>* variableList);
      std::list<VariableNT*>* variableList;
      void execute();
};

class AssignmentStatement : public Node {
   public:
      AssignmentStatement(VariableNT* variable, Expression* expression);
      VariableNT* variable;
      Expression* expression;
      void execute();
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
};

class Statement : public Node {
   public:
      Statement(SimpleStatement* simpleStatement);
      Statement(StructuredStatement* structuredStatement);
      SimpleStatement* simpleStatement;
      StructuredStatement* structuredStatement;
      void execute();
};

class CompoundStatement : public Node {
   public:
      CompoundStatement(std::list<Statement*>* statementList);
      std::list<Statement*>* statementList;
      void execute();
};

class StatementPart : public Node {
   public:
      StatementPart(CompoundStatement* compoundStatement);
      CompoundStatement* compoundStatement;
      void execute();
};

/* Statements */

class VariableDeclaration : public Node {
   public:
      VariableDeclaration(std::list<Identifier*>* identifierList, DataType* dataType);
      std::list<Identifier*>* identifierList;
      DataType* dataType;
      void execute();
};

class VariableDeclarationPart : public Node {
   public:
      VariableDeclarationPart(std::list<VariableDeclaration*>* variableDeclarations);
      VariableDeclarationPart();
      std::list<VariableDeclaration*>* variableDeclarations;
      void execute();
};

class Block : public Node {
   public:
      Block(VariableDeclarationPart* variableDeclarationPart, StatementPart* statementPart);
      VariableDeclarationPart* variableDeclarationPart;
      StatementPart* statementPart;
      void execute();
};

class Program : public Node {
   public:
      Program(Identifier* identifier, Block* block);
      Identifier* identifier;
      Block* block;
      void execute();
};
#endif
