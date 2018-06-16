#include<string>
#include<list>

// Forward Declarations
class Block;
class StructuredStatement;

class Node {
   public:
      Node();
};

/* Types */
class SimpleType;

class RecordType : protected Node {
   public:
      RecordType(std::list<std::string> fieldList);
      std::list<std::string> fieldList;
};

class ElementType : protected Node {
   public:
      ElementType(std::string Type);
      std::string Type;
};

class IndexType : protected Node {
   public:
      IndexType(SimpleType* simpleType);
      SimpleType* simpleType;
};

class ArrayType : protected Node {
   public:
      ArrayType(IndexType* indexType1, IndexType* indexType2, std::string type);
   public:
      IndexType* indexType1;
      IndexType* indexType2;
      std::string type;
};

class StructuredType : protected Node {
   public:
      StructuredType(ArrayType* arrayType);
      StructuredType(RecordType* recordType);
      ArrayType* arrayType;
      RecordType* recordType;
};

class SubrangeType : protected Node {
   public:
      SubrangeType(int lowerBound, int upperBound);
      int lowerBound;
      int upperBound;
};

class EnumeratedType : protected Node {
   public:
      EnumeratedType(std::list<std::string>* identifierList);
      std::list<std::string>* identifierList;
};

class SimpleType : protected Node {
   public:
      SimpleType(SubrangeType* subrangeType);
      SimpleType(EnumeratedType* enumeratedType);
      SubrangeType* subrangeType;
      EnumeratedType* enumeratedType;
};

class DataType : protected Node {
   public:
      DataType(SimpleType* simpleType);
      DataType(StructuredType* StructuredStatement);
      DataType(std::string typeIdentifier);
      SimpleType* simpleType;
      StructuredType* structuredStatement;
      std::string typeIdentifier;
};
/* Types */

/* Expressions */
class Expression;
class ActualParameterList;

class RecordVariable : protected Node {
   public:
      RecordVariable();
};

class ReferencedVariable : protected Node {
   public:
      ReferencedVariable();
};

class ArrayVariable : protected Node {
   public: 
      ArrayVariable();
};

class FieldDesignator : protected Node {
   public:
      FieldDesignator(RecordVariable* recordVariable, std::string fieldIdentifier);
      RecordVariable* recordVariable;
      std::string fieldIdentifier;
};

class IndexedVariable : protected Node {
   public:
      IndexedVariable(ArrayVariable* arrayVariable, std::list<Expression>* expressionList);
      ArrayVariable* arrayVariable;
      std::list<Expression>* expressionList;
};

class ComponentVariable : protected Node {
   public:
      ComponentVariable(FieldDesignator* fieldDesignator);
      ComponentVariable(IndexedVariable* indexedVariable);
      FieldDesignator* fieldDesignator;
      IndexedVariable* indexedVariable;
};

class EntireVariable : protected Node {
   public:
      enum Type {
         VARIABLE_IDENTIFIER,
         FIELD_IDENTIFIER
      };

      EntireVariable(std::string identifier, EntireVariable::Type type);
      std::string identifier;
      EntireVariable::Type type;
};

class Variable : protected Node {
   public:
      Variable(EntireVariable* entireVariable);
      Variable(ComponentVariable* componentVariable);
      Variable(ReferencedVariable* referenceVariable);
      EntireVariable* entireVariable;
      ComponentVariable* componentVariable;
      ReferencedVariable* referenceVariable;
};

enum class RelationalOperator{
   EQ,
   NEQ,
   LT,
   LEQ,
   GT,
   GEQ
};

enum class AdditionOperator{
   ADD,
   SUB,
   OR
};

enum class MultiplicationOperator{
   MUL,
   DIV,
   WHOLEDIV,
   MOD,
   AND
};

class AbstractFactor : protected Node {};
class VariableFactor : protected AbstractFactor {
   public:
      VariableFactor(Variable* variable);
      Variable* variable;
};

class NumberFactor : protected AbstractFactor {
   public:
      NumberFactor(float number);
      float number;
};

class ConstantIdentifierFactor : protected AbstractFactor {
   public:
      ConstantIdentifierFactor(float number);
      float number;
};

class BoundIdentifierFactor : protected AbstractFactor {
   public:
      BoundIdentifierFactor();
// NPI que es esto...
};

class FunctionDesignator : protected AbstractFactor {
   public:
      FunctionDesignator(std::string functionIdentifier);
      FunctionDesignator(std::string functionIdentifier, ActualParameterList* actualParameterList);
      std::string functionIdentifier;
      ActualParameterList* actualParameterList;
};

class ExpressionFactor : protected AbstractFactor {
   public:
      ExpressionFactor(Expression* expression);
      Expression* expression;
};

class NotFactor : protected AbstractFactor {
   public:
      NotFactor(AbstractFactor* factor);
      AbstractFactor* factor;
};

class Term : protected Node {
   public:
      Term();
      std::list<AbstractFactor>* factors;
      std::list<MultiplicationOperator>* operators;
};

class SimpleExpression : protected Node {
   public:
      SimpleExpression(std::string sign, std::list<Term>* terms, std::list<AdditionOperator>* additionOperators);
      std::string sign;
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
class StatementSequence;
class Statement;

class ActualValue : protected Node {
   public:
      ActualValue();
      Expression* expression;
};

class ActualVariable : protected Node {
   public:
      ActualVariable();
};

class ActualParameter : protected Node {
   public:
      ActualParameter(ActualValue* actualValue);
      ActualParameter(ActualVariable* actualVariable);
      ActualValue* actualValue;
      ActualVariable* actualVariable;
};

class ActualParameterList : protected Node {
   public:
      ActualParameterList(std::list<ActualParameter>* actualParameterList);
      std::list<ActualParameter>* actualParameterList;
};

class IfStatement : protected Node {
   public:
      IfStatement(Expression* expression, Statement* statement);
      Expression* expression;
      Statement* statement;
};

class ConditionalStatement : protected Node {
   public:
      ConditionalStatement(IfStatement* ifStatement);
   private:
      IfStatement* ifStatement;
};

class WhileStatement : protected Node {
   public:
      WhileStatement(Expression* expression, Statement* statement);
   private:
      Expression* expression;
      Statement* statement;
};

class RepetitiveStatement : protected Node {
   public:
      RepetitiveStatement(WhileStatement* whileStatement);
   private:
      WhileStatement* whileStatement;
};

class CompoundStatement : protected Node {
   public:
      CompoundStatement(StatementSequence* statementSequence);
   private:
      StatementSequence* statementSequence;
};

class StructuredStatement : protected Node {
   public:
      StructuredStatement(CompoundStatement* compoundStatement);
      StructuredStatement(RepetitiveStatement* repetitiveStatement);
      StructuredStatement(ConditionalStatement* conditionalStatement);
      CompoundStatement* compoundStatement;
      RepetitiveStatement* repetitiveStatement;
      ConditionalStatement* conditionalStatement;
};

class ProcedureStatement : protected Node {
   public:
      ProcedureStatement(std::string procedureIdentifier);
      ProcedureStatement(ActualParameterList* actualParameterList);
      std::string procedureIdentifier;
      ActualParameterList* actualParameterList;
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
      SimpleStatement(ProcedureStatement* procedureStatement);
      AssignmentStatement* assignmentStatement;
      ProcedureStatement* procedureStatement;
};

class Statement : protected Node {
   public:
      Statement(SimpleStatement* simpleStatement);
      Statement(StructuredStatement* structuredStatement);
      SimpleStatement* simpleStatement;
      StructuredStatement* structuredStatement;
};

class StatementSequence : protected Node {
   public:
      StatementSequence(std::list<Statement>* statementList);
      std::list<Statement>* statementList;
};

class StatementPart : protected Node {
   public:
      StatementPart(StatementSequence* statementSequence);
      StatementSequence* statementSequence;
};

/* Statements */

/* Procedure and function definitions */
class ConformantArraySchema;

class BoundSpecification : protected Node {
   public:
      BoundSpecification(std::string identifier1, std::string identifier2, std::string ordinalTypeIdentifier);
      std::string identifier1;
      std::string identifier2;
      std::string ordinalTypeIdentifier;
};

class ArraySchema : protected Node {
   public:
      ArraySchema(std::string typeIdentifier);
      ArraySchema(ConformantArraySchema* conformantArraySchema);
      ArraySchema(BoundSpecification* boundSpecification, std::string typeIdentifier);
      ArraySchema(BoundSpecification* boundSpecification, ConformantArraySchema* conformantArraySchema);
   protected:;
      BoundSpecification* boundSpecification;
      std::string typeIdentifier;
      ConformantArraySchema* conformantArraySchema;
};

class ConformantArraySchema : protected Node {
   public:
      ConformantArraySchema(ArraySchema*  arraySchema);
      ArraySchema* arraySchema;
};

class ParameterType : protected Node {
   public:
      ParameterType(ConformantArraySchema* conformantArraySchema);
      ParameterType(std::string typeIdentifier);
      
      std::string typeIdentifier;
      ConformantArraySchema* conformantArraySchema;
};

class ResultType : protected Node {
   public:
      ResultType(std::string typeIdentifier);
      std::string typeIdentifier;
};

class ValueParameterSection : protected Node {
   public:
      ValueParameterSection(std::list<std::string> identifierList, ConformantArraySchema* conformantArraySchema);
      std::list<std::string> identifierList;
      ConformantArraySchema* conformantArraySchema;
};

class FormalParameterSection : protected Node {
   public:
      FormalParameterSection(ValueParameterSection* valueParameterSection);
      ValueParameterSection* valueParameterSection;
};

class FormalParameterList : protected Node {
   public:
      FormalParameterList(std::list<FormalParameterSection>* formalParameterSection);
      std::list<FormalParameterSection>* formalParameterSection;
};

class FunctionHeading : protected Node {
   public:
      FunctionHeading(std::string identifier, FormalParameterList* parameterList, ResultType* resultType);
      FunctionHeading(std::string identifier, ResultType* resultType);
      std::string identifier;
      FormalParameterList* parameterList;
      ResultType* resultType;
};

class FunctionBody : protected Node {
   public:
      FunctionBody(Block* block);
      Block* block;
};

class ProcHeading : protected Node {
   public:
      ProcHeading(std::string identifier, FormalParameterList* parameterList);
      ProcHeading(std::string identifier);
      std::string identifier;
      FormalParameterList* parameterList;
};

class ProcBody : protected Node {
   public:
      ProcBody(Block* block);
      Block* block;
};
/* Procedure and function definitions */

class VariableDeclaration : protected Node {
   public:
      VariableDeclaration(std::list<std::string>* identifierList, DataType* dataType);
      std::list<std::string>* identifierList;
      DataType* dataType;
};

class TypeDefinition : protected Node {
   public:
      TypeDefinition(std::string identifier, DataType* dataType);
      std::string identifier;
      DataType* dataType;
};

class FuncDeclaration : protected Node {
   public:
      FuncDeclaration(FunctionHeading* functionHeading, FunctionBody* functionBody);
      FunctionHeading* functionHeading;
      FunctionBody* functionBody;
};

class ProcDeclaration : protected Node {
   public:
      ProcDeclaration(ProcHeading* procHeading, ProcBody* procBody);

      ProcHeading* procHeading;
      ProcBody* procBody;
};

class ProcFuncDeclaration : protected Node {
   public:
      ProcFuncDeclaration(ProcDeclaration* procDeclaration);
      ProcFuncDeclaration(FuncDeclaration* funcDeclaration);
      ProcDeclaration* procDeclaration;
      FuncDeclaration* funcDeclaration;
};

class TypeDefinitionPart : protected Node {
   public:
      TypeDefinitionPart(std::list<TypeDefinition>* typeDefinitions);
      std::list<TypeDefinition>* typeDefinitions;
};

class VariableDeclarationPart : protected Node {
   public:
      VariableDeclarationPart(std::list<VariableDeclaration>* variableDeclarations);
      std::list<VariableDeclaration>* variableDeclarations;
};

class ProcFuncDeclarationPart : protected Node {
   public:
      ProcFuncDeclarationPart(std::list<ProcFuncDeclaration>* procFuncDeclarations);
      std::list<ProcFuncDeclaration>* procFuncDeclarations;
};

class DeclarationPart : protected Node {
   public:
      DeclarationPart(TypeDefinitionPart* typeDefinitionPart);
      DeclarationPart(VariableDeclarationPart* variableDeclarations);
      DeclarationPart(ProcFuncDeclarationPart*  procFuncDeclarationPart);
      TypeDefinitionPart* typeDefinitionPart;
      VariableDeclarationPart* variableDeclarations;
      ProcFuncDeclarationPart*  procFuncDeclarationPart;
};

class Block : protected Node {
   public:
      Block(DeclarationPart* declarationPart, StatementPart* statementPart);
      DeclarationPart* declarationPart;
      StatementPart* statementPart;
};

class ProgramHeading : protected Node {
   public:
      ProgramHeading(std::string identifier);
      std::string identifier;
};

class Program : protected Node {
   public:
      Program(ProgramHeading* programHeading, Block* block);
      ProgramHeading* programHeading;
      Block* block;
};
