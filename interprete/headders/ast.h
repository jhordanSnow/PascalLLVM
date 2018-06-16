#include<string>
#include<list>

// Forward Declarations
class Block;
class StructuredStatement;
class CompoundStatement;

class Node {
   public:
      Node();
};

class Expression;
/* Lexical Grammar */
class Identifier : protected Node {
   public:
      Identifier(std::string identifier);
      std::string identifier;
};

class ConstantIdentifier : protected Node { 
   public:
      ConstantIdentifier(Identifier* identifier);
      Identifier* identifier;
};

class Constant : protected Node {
   public:
      Constant(int intConst);
      Constant(char charConst);
      Constant(ConstantIdentifier* constIdentifier);
      int intConst;
      char charConst;
      ConstantIdentifier* constIdentifier;
};
/* Lexical Grammar */

/* Types */
class TypeIdentifier : protected Node {
   public:
      TypeIdentifier(Identifier* identifier);
      Identifier* identifier;
};

enum class SimpleType{
   CHAR,
   INTEGER,
   BOOLEAN
};

class IndexRange : protected Node {
   public:
      IndexRange(int begining, int end);
      int begining;
      int end;
};

class ArrayType : protected Node {
   public:
      ArrayType(SimpleType* simpleType);
      ArrayType(IndexRange* indexRange, SimpleType* simpleType);
      IndexRange* indexRange;
      SimpleType* simpleType;
};

class DataType : protected Node {
   public:
      DataType(SimpleType* simpleType);
      DataType(ArrayType* arrayType);
      SimpleType* simpleType;
      ArrayType* arrayType;
};
/* Types */

/* Expressions */

class VariableIdentifier : protected Node {
   public:
      VariableIdentifier(Identifier* variableIdentifier);
      Identifier* variableIdentifier;
};

class EntireVariable : protected Node {
   public:
      EntireVariable(VariableIdentifier* variableIdentifier);
      VariableIdentifier* variableIdentifier;
};

class ArrayVariable : protected Node {
   public: 
      ArrayVariable(EntireVariable* entireVariable);
      EntireVariable* entireVariable;
};

class IndexedVariable : protected Node {
   public:
      IndexedVariable(ArrayVariable* arrayVariable, std::list<Expression>* expressionList);
      ArrayVariable* arrayVariable;
      std::list<Expression>* expressionList;
};

class Variable : protected Node {
   public:
      Variable(EntireVariable* entireVariable);
      Variable(IndexedVariable* indexedVariable);
      EntireVariable* entireVariable;
      IndexedVariable* indexedVariable;
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

class AbstractFactor : protected Node {};
class NotFactor : protected AbstractFactor {
   public:
      NotFactor(AbstractFactor* factor);
      AbstractFactor* factor;
};

class Factor : protected AbstractFactor {
   public:
      Factor(Variable* variable);
      Factor(Constant* constant);
      Variable* variable;
      Constant* constant;
};

class Term : protected Node {
   public:
      Term(std::list<Factor>* factors, std::list<MultiplicationOperator>* operators);
      std::list<Factor>* factors;
      std::list<MultiplicationOperator>* operators;
};

class SimpleExpression : protected Node {
   public:
      SimpleExpression(Sign* sign, std::list<Term>* terms, std::list<AdditionOperator>* additionOperators);
      Sign* sign;
      std::list<Term>* terms;
      std::list<AdditionOperator>* additionOperators;
};

class Expression : protected Node {
   public:
      Expression(SimpleExpression* simpleExpression1);
      Expression(SimpleExpression* simpleExpression1, RelationalOperator* relationalOperator, SimpleExpression* simpleExpression2);
      SimpleExpression* simpleExpression1;
      RelationalOperator* relationalOperator;
      SimpleExpression* simpleExpression2;
};
/* Expressions */

/* Statements */
class Statement;

class WhileStatement : protected Node {
   public:
      WhileStatement(Expression* expression, Statement* statement);
      Expression* expression;
      Statement* statement;
};

class IfStatement : protected Node {
   public:
      IfStatement(Expression* expression, Statement* thenStatement, Statement* elseStatement);
      Expression* expression;
      Statement* statement;
      Statement* elseStatement;
};

class StructuredStatement : protected Node {
   public:
      StructuredStatement(CompoundStatement* compoundStatement);
      StructuredStatement(IfStatement* ifStatement);
      StructuredStatement(WhileStatement* whileStatement);
      CompoundStatement* compoundStatement;
      IfStatement* ifStatement;
      WhileStatement* whileStatement;
};

class WriteStatement : protected Node {
   public:
      WriteStatement(std::list<Variable> variableList);
      std::list<Variable> variableList;
};

class ReadStatement : protected Node {
   public:
      ReadStatement(std::list<Variable> variableList);
      std::list<Variable> variableList;
};

class AssignmentStatement : protected Node {
   public:
      AssignmentStatement(Variable* variable, Expression* expression);
      Variable* variable;
      Expression* expression;
};

class SimpleStatement : protected Node {
   public:
      SimpleStatement(AssignmentStatement* assignmentStatement);
      SimpleStatement(ReadStatement* readStatement);
      SimpleStatement(WriteStatement* writeStatement);
      AssignmentStatement* assignmentStatement;
      ReadStatement* readStatement;
      WriteStatement* writeStatement;
};

class Statement : protected Node {
   public:
      Statement(SimpleStatement* simpleStatement);
      Statement(StructuredStatement* structuredStatement);
      SimpleStatement* simpleStatement;
      StructuredStatement* structuredStatement;
};

class CompoundStatement : protected Node {
   public:
      CompoundStatement(std::list<Statement> statementList);
      std::list<Statement> statementList;
};

class StatementPart : protected Node {
   public:
      StatementPart(CompoundStatement* compoundStatement);
      CompoundStatement* compoundStatement;
};

/* Statements */

class VariableDeclaration : protected Node {
   public:
      VariableDeclaration(std::list<Identifier>* identifierList, DataType* dataType);
      std::list<Identifier>* identifierList;
      DataType* dataType;
};

class VariableDeclarationPart : protected Node {
   public:
      VariableDeclarationPart(std::list<VariableDeclaration>* variableDeclarations);
      std::list<VariableDeclaration>* variableDeclarations;
};

class Block : protected Node {
   public:
      Block(VariableDeclarationPart* variableDeclarationPart, StatementPart* statementPart);
      VariableDeclarationPart* variableDeclarationPart;
      StatementPart* statementPart;
};

class Program : protected Node {
   public:
      Program(Identifier* identifier, Block* block);
      Identifier* identifier;
      Block* block;
};
