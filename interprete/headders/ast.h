#include<string>
#include<list>

// Forward Declarations
class Block;
class StructuredStatement;
class CompoundStatement;

class Node {
   public:
      Node();
      execute();
};

class Expression;
/* Lexical Grammar */
class Identifier : public Node {
   public:
      Identifier(std::string identifier);
      std::string identifier;
      execute();
};

class ConstantIdentifier : public Node { 
   public:
      ConstantIdentifier(Identifier* identifier);
      Identifier* identifier;
      execute();
};

class Constant : public Node {
   public:
      Constant(int intConst);
      Constant(char charConst);
      Constant(ConstantIdentifier* constIdentifier);
      int intConst;
      char charConst;
      ConstantIdentifier* constIdentifier;
      execute();
};
/* Lexical Grammar */

/* Types */
class TypeIdentifier : public Node {
   public:
      TypeIdentifier(Identifier* identifier);
      Identifier* identifier;
      execute();
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
      execute();
};

class ArrayType : public Node {
   public:
      ArrayType(SimpleType simpleType);
      ArrayType(IndexRange* indexRange, SimpleType simpleType);
      IndexRange* indexRange;
      SimpleType simpleType;
      execute();
};

class DataType : public Node {
   public:
      DataType(SimpleType simpleType);
      DataType(ArrayType* arrayType);
      SimpleType simpleType;
      ArrayType* arrayType;
      execute();
};
/* Types */

/* Expressions */

class VariableIdentifier : public Node {
   public:
      VariableIdentifier(Identifier* variableIdentifier);
      Identifier* variableIdentifier;
      execute();
};

class EntireVariable : public Node {
   public:
      EntireVariable(VariableIdentifier* variableIdentifier);
      VariableIdentifier* variableIdentifier;
      execute();
};

class ArrayVariable : public Node {
   public: 
      ArrayVariable(EntireVariable* entireVariable);
      EntireVariable* entireVariable;
      execute();
};

class IndexedVariable : public Node {
   public:
      IndexedVariable(ArrayVariable* arrayVariable, std::list<Expression>* expressionList);
      ArrayVariable* arrayVariable;
      std::list<Expression>* expressionList;
      execute();
};

class VariableNT : public Node {
   public:
      VariableNT(EntireVariable* entireVariable);
      VariableNT(IndexedVariable* indexedVariable);
      EntireVariable* entireVariable;
      IndexedVariable* indexedVariable;
      execute();
};

enum class RelationalOperator{
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
   ADD,
   SUB
};

enum class MultiplicationOperator{
   MUL,
   DIV
};

enum class Sign {
   POSITIVE,
   NEGATIVE
};

class AbstractFactor : public Node {execute();
};
class NotFactor : public AbstractFactor {
   public:
      NotFactor(AbstractFactor* factor);
      AbstractFactor* factor;
      execute();
};

class Factor : public AbstractFactor {
   public:
      Factor(VariableNT* variable);
      Factor(Constant* constant);
      VariableNT* variable;
      Constant* constant;
      execute();
};

class Term : public Node {
   public:
      Term(std::list<Factor>* factors, std::list<MultiplicationOperator>* operators);
      std::list<Factor>* factors;
      std::list<MultiplicationOperator>* operators;
      execute();
};

class SimpleExpression : public Node {
   public:
      SimpleExpression(Sign sign, std::list<Term>* terms, std::list<AdditionOperator>* additionOperators);
      Sign sign;
      std::list<Term>* terms;
      std::list<AdditionOperator>* additionOperators;
      execute();
};

class Expression : public Node {
   public:
      Expression(SimpleExpression* simpleExpression1);
      Expression(SimpleExpression* simpleExpression1, RelationalOperator relationalOperator, SimpleExpression* simpleExpression2);
      SimpleExpression* simpleExpression1;
      RelationalOperator relationalOperator;
      SimpleExpression* simpleExpression2;
      execute();
};
/* Expressions */

/* Statements */
class Statement;

class WhileStatement : public Node {
   public:
      WhileStatement(Expression* expression, Statement* statement);
      Expression* expression;
      Statement* statement;
      execute();
};

class IfStatement : public Node {
   public:
      IfStatement(Expression* expression, Statement* thenStatement, Statement* elseStatement);
      Expression* expression;
      Statement* statement;
      Statement* elseStatement;
      execute();
};

class StructuredStatement : public Node {
   public:
      StructuredStatement(CompoundStatement* compoundStatement);
      StructuredStatement(IfStatement* ifStatement);
      StructuredStatement(WhileStatement* whileStatement);
      CompoundStatement* compoundStatement;
      IfStatement* ifStatement;
      WhileStatement* whileStatement;
      execute();
};

class WriteStatement : public Node {
   public:
      WriteStatement(std::list<VariableNT> variableList);
      std::list<VariableNT> variableList;
      execute();
};

class ReadStatement : public Node {
   public:
      ReadStatement(std::list<VariableNT>* variableList);
      std::list<VariableNT>* variableList;
      execute();
};

class AssignmentStatement : public Node {
   public:
      AssignmentStatement(VariableNT* variable, Expression* expression);
      VariableNT* variable;
      Expression* expression;
      execute();
};

class SimpleStatement : public Node {
   public:
      SimpleStatement(AssignmentStatement* assignmentStatement);
      SimpleStatement(ReadStatement* readStatement);
      SimpleStatement(WriteStatement* writeStatement);
      AssignmentStatement* assignmentStatement;
      ReadStatement* readStatement;
      WriteStatement* writeStatement;
      execute();
};

class Statement : public Node {
   public:
      Statement(SimpleStatement* simpleStatement);
      Statement(StructuredStatement* structuredStatement);
      SimpleStatement* simpleStatement;
      StructuredStatement* structuredStatement;
      execute();
};

class CompoundStatement : public Node {
   public:
      CompoundStatement(std::list<Statement> statementList);
      std::list<Statement> statementList;
      execute();
};

class StatementPart : public Node {
   public:
      StatementPart(CompoundStatement* compoundStatement);
      CompoundStatement* compoundStatement;
      execute();
};

/* Statements */

class VariableDeclaration : public Node {
   public:
      VariableDeclaration(std::list<Identifier>* identifierList, DataType* dataType);
      std::list<Identifier>* identifierList;
      DataType* dataType;
      execute();
};

class VariableDeclarationPart : public Node {
   public:
      VariableDeclarationPart(std::list<VariableDeclaration>* variableDeclarations);
      std::list<VariableDeclaration>* variableDeclarations;
      execute();
};

class Block : public Node {
   public:
      Block(VariableDeclarationPart* variableDeclarationPart, StatementPart* statementPart);
      VariableDeclarationPart* variableDeclarationPart;
      StatementPart* statementPart;
      execute();
};

class Program : public Node {
   public:
      Program(Identifier* identifier, Block* block);
      Identifier* identifier;
      Block* block;
      execute();
};
