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
      std::list<std::string> getFieldList;
   protected:
      std::list<std::string> fieldList;
};

class ElementType : protected Node {
   public:
      ElementType(std::string Type);
      std::string getType;
   protected:
      std::string Type;
};

class IndexType : protected Node {
   public:
      IndexType(SimpleType* simpleType);
      SimpleType* getSimpleType;
   protected:
      SimpleType* simpleType;
};

class ArrayType : protected Node {
   public:
      ArrayType(IndexType* indexType1, IndexType* indexType2, std::string type);
      IndexType* getIndexType1();
      IndexType* getIndexType2();
      std::string getType();
   public:
      IndexType* indexType1;
      IndexType* indexType2;
      std::string type;
};

class StructuredType : protected Node {
   public:
      StructuredType(ArrayType* arrayType);
      StructuredType(RecordType* recordType);
      ArrayType* getArrayType;
      RecordType* getRecordType;
   protected:
      ArrayType* arrayType;
      RecordType* recordType;
};

class SubrangeType : protected Node {
   public:
      SubrangeType(int lowerBound, int upperBound);
      int getLowerBound;
      int getUpperBound;
   protected:
      int lowerBound;
      int upperBound;
};

class EnumeratedType : protected Node {
   public:
      EnumeratedType(std::list<std::string>* identifierList);
      std::list<std::string>* getIdentifierList();
   protected:
      std::list<std::string>* identifierList;
};

class SimpleType : protected Node {
   public:
      SimpleType(SubrangeType* subrangeType);
      SimpleType(EnumeratedType* enumeratedType);
      SubrangeType* getSubrangeType();
      EnumeratedType* getEnumeratedType();
   protected:
      SubrangeType* subrangeType;
      EnumeratedType* enumeratedType;
};

class DataType : protected Node {
   public:
      DataType(SimpleType* simpleType);
      DataType(StructuredType* StructuredStatement);
      DataType(std::string typeIdentifier);
      SimpleType* getSimpleType();
      StructuredType* getStructuredStatement();
      std::string getTypeIdentifier();
   protected:
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
      RecordVariable* getRecordVariable();
      std::string getFieldIdentifier();
   protected:
      RecordVariable* recordVariable;
      std::string fieldIdentifier;
};

class IndexedVariable : protected Node {
   public:
      IndexedVariable(ArrayVariable* arrayVariable, std::list<Expression>* expressionList);
      std::list<Expression>* getExpressionList();
   protected:
      ArrayVariable* arrayVariable;
      std::list<Expression>* expressionList;
};

class ComponentVariable : protected Node {
   public:
      ComponentVariable(FieldDesignator* fieldDesignator);
      ComponentVariable(IndexedVariable* indexedVariable);
      FieldDesignator* getFieldDesignator();
      IndexedVariable* getIndexedVariable();
   protected:
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
      std::string getIdentifier();
      EntireVariable::Type getType;
   protected:
      std::string identifier;
      EntireVariable::Type type;
};

class Variable : protected Node {
   public:
      Variable(EntireVariable* entireVariable);
      Variable(ComponentVariable* componentVariable);
      Variable(ReferencedVariable* referenceVariable);
      EntireVariable* getEntireVariable();
      ComponentVariable* getComponentVariable();
      ReferencedVariable* getReferenceVariable();
   protected:
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
      Variable* getVariable();
   protected:
      Variable* variable;
};

class NumberFactor : protected AbstractFactor {
   public:
      NumberFactor(float number);
      float getNumber();
   protected:
      float number;
};

class ConstantIdentifierFactor : protected AbstractFactor {
   public:
      ConstantIdentifierFactor(float number);
      float getNumber();
   protected:
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
      std::string getFunctionIdentifier;
      ActualParameterList* getActualParameterList;
   protected:
      std::string functionIdentifier;
      ActualParameterList* actualParameterList;
};

class ExpressionFactor : protected AbstractFactor {
   public:
      ExpressionFactor(Expression* expression);
      Expression* getExpression;
   protected:
      Expression* expression;
};

class NotFactor : protected AbstractFactor {
   public:
      NotFactor(AbstractFactor* factor);
      AbstractFactor* getFactor;
   protected:
      AbstractFactor* factor;
};

class Term : protected Node {
   public:
      Term();
   protected:
      std::list<AbstractFactor>* factors;
      std::list<MultiplicationOperator>* operators;
};

class SimpleExpression : protected Node {
   public:
      SimpleExpression(std::string sign, std::list<Term>* terms, std::list<AdditionOperator>* additionOperators);
      std::string getSign;
      std::list<Term>* getTerms;
      std::list<AdditionOperator>* getAdditionOperators;
   protected:
      std::string sign;
      std::list<Term>* terms;
      std::list<AdditionOperator>* additionOperators;
};

class Expression : protected Node {
   public:
      Expression(SimpleExpression* simpleExpression1);
      Expression(SimpleExpression* simpleExpression1, RelationalOperator* relationalOperator, SimpleExpression* simpleExpression2);
      SimpleExpression* getSimpleExpression1;
      RelationalOperator* getRelationalOperator;
      SimpleExpression* getSimpleExpression2;
   protected:
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
   protected:
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
      ActualValue* getActualValue;
      ActualVariable* getActualVariable;
   protected:
      ActualValue* actualValue;
      ActualVariable* actualVariable;
};

class ActualParameterList : protected Node {
   public:
      ActualParameterList(std::list<ActualParameter>* actualParameterList);
      std::list<ActualParameter>* getActualParameterList();
   protected:
      std::list<ActualParameter>* actualParameterList;
};

class IfStatement : protected Node {
   public:
      IfStatement(Expression* expression, Statement* statement);
      Expression* getExpression();
      Statement* getStatement();
   protected:
      Expression* expression;
      Statement* statement;
};

class ConditionalStatement : protected Node {
   public:
      ConditionalStatement(IfStatement* ifStatement);
      IfStatement* getIfStatement();
   private:
      IfStatement* ifStatement;
};

class WhileStatement : protected Node {
   public:
      WhileStatement(Expression* expression, Statement* statement);
      Expression* getExpression();
      Statement* getStatement();
   private:
      Expression* expression;
      Statement* statement;
};

class RepetitiveStatement : protected Node {
   public:
      RepetitiveStatement(WhileStatement* whileStatement);
      WhileStatement* getWhileStatement();
   private:
      WhileStatement* whileStatement;
};

class CompoundStatement : protected Node {
   public:
      CompoundStatement(StatementSequence* statementSequence);
      StatementSequence* getStatementSequence();
   private:
      StatementSequence* statementSequence;
};

class StructuredStatement : protected Node {
   public:
      StructuredStatement(CompoundStatement* compoundStatement);
      StructuredStatement(RepetitiveStatement* repetitiveStatement);
      StructuredStatement(ConditionalStatement* conditionalStatement);
      CompoundStatement* getCompoundStatement();
      RepetitiveStatement* getRepetitiveStatement();
      ConditionalStatement* getConditionalStatement();
   protected:
      CompoundStatement* compoundStatement;
      RepetitiveStatement* repetitiveStatement;
      ConditionalStatement* conditionalStatement;
};

class ProcedureStatement : protected Node {
   public:
      ProcedureStatement(std::string procedureIdentifier);
      ProcedureStatement(ActualParameterList* actualParameterList);
      std::string getProcedureIdentifier();
      ActualParameterList* getActualParameterList();
   protected:
      std::string procedureIdentifier;
      ActualParameterList* actualParameterList;
};

class AssignmentStatement : protected Node {
   public:
      AssignmentStatement(Variable* variable, Expression* expression);
      Variable* getVariable();
      Expression* getExpression();
   protected:
      Variable* variable;
      Expression* expression;
};

class SimpleStatement : protected Node {
   public:
      SimpleStatement(AssignmentStatement* assignmentStatement);
      SimpleStatement(ProcedureStatement* procedureStatement);
      AssignmentStatement* getAssignmentStatement();
      ProcedureStatement* getProcedureStatement();
   protected:
      AssignmentStatement* assignmentStatement;
      ProcedureStatement* procedureStatement;
};

class Statement : protected Node {
   public:
      Statement(SimpleStatement* simpleStatement);
      Statement(StructuredStatement* structuredStatement);
      SimpleStatement* getSimpleStatement();
      StructuredStatement* getStructuredStatement();
   protected:
      SimpleStatement* simpleStatement;
      StructuredStatement* structuredStatement;
};

class StatementSequence : protected Node {
   public:
      StatementSequence(std::list<Statement>* statementList);
      std::list<Statement>* getStatementList();
   protected:
      std::list<Statement>* statementList;
};

class StatementPart : protected Node {
   public:
      StatementPart(StatementSequence* statementSequence);
      StatementSequence* getStatementSequence();
   protected:
      StatementSequence* statementSequence;
};

/* Statements */

/* Procedure and function definitions */
class ConformantArraySchema;

class BoundSpecification : protected Node {
   public:
      BoundSpecification(std::string identifier1, std::string identifier2, std::string ordinalTypeIdentifier);
      std::string getIdentifier1();
      std::string getIdentifier2();
      std::string getOrdinalTypeIdentifier();
   protected:
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
      BoundSpecification* getBoundSpecification();
      std::string getTypeIdentifier();
      ConformantArraySchema* getConformantArraySchema();
   protected:;
      BoundSpecification* boundSpecification;
      std::string typeIdentifier;
      ConformantArraySchema* conformantArraySchema;
};

class ConformantArraySchema : protected Node {
   public:
      ConformantArraySchema(ArraySchema*  arraySchema);
      ArraySchema* getArraySchema();
   protected:
      ArraySchema* arraySchema;
};

class ParameterType : protected Node {
   public:
      ParameterType(ConformantArraySchema* conformantArraySchema);
      ParameterType(std::string typeIdentifier);
      std::string getTypeIdentifier();
      ConformantArraySchema* getConformantArraySchema();
   protected:
      
      std::string typeIdentifier;
      ConformantArraySchema* conformantArraySchema;
};

class ResultType : protected Node {
   public:
      ResultType(std::string typeIdentifier);
      std::string getTypeIdentifier();
   protected:
      std::string typeIdentifier;
};

class ValueParameterSection : protected Node {
   public:
      ValueParameterSection();
      std::string getIdentifierList();
      ConformantArraySchema* getConformantArraySchema();
   protected:
      std::list<std::string> identifierList;
      ConformantArraySchema* conformantArraySchema;
};

class FormalParameterSection : protected Node {
   public:
      FormalParameterSection();
   protected:
      ValueParameterSection* valueParameterSection;
};

class FormalParameterList : protected Node {
   public:
      FormalParameterList(std::list<FormalParameterSection>* formalParameterSection);
      FormalParameterSection* getFormalParameterSection();
   protected:
      std::list<FormalParameterSection>* formalParameterSection;
};

class FunctionHeading : protected Node {
   public:
      FunctionHeading(std::string identifier, FormalParameterList* parameterList, ResultType* resultType);
      FunctionHeading(std::string identifier, ResultType* resultType);
      std::string getIdentifier();
      FormalParameterList* getFormalParameters();
      ResultType* getReturnType();
   protected:
      std::string identifier;
      FormalParameterList* parameterList;
      ResultType* resultType;
};

class FunctionBody : protected Node {
   public:
      FunctionBody();
      Block* getBlock();
   protected:
      Block* block;
};

class ProcHeading : protected Node {
   public:
      ProcHeading(std::string identifier, FormalParameterList* parameterList);
      ProcHeading(std::string identifier);
      std::string getIdentifier();
      FormalParameterList* getFormalParameters();
   protected:
      std::string identifier;
      FormalParameterList* parameterList;
};

class ProcBody : protected Node {
   public:
      ProcBody();
      Block* getBlock();
   protected:
      Block* block;
};
/* Procedure and function definitions */

class VariableDeclaration : protected Node {
   public:
      VariableDeclaration();
   protected:
      std::list<std::string>* identifierList;
      DataType* dataType;
};

class TypeDefinition : protected Node {
   public:
      TypeDefinition(std::string identifier, DataType* dataType);
      std::string getIdentifier();
      DataType* getType();
   protected:
      std::string identifier;
      DataType* dataType;
};

class FuncDeclaration : protected Node {
   public:
      FuncDeclaration();
   protected:
      FunctionHeading* functionHeading;
      FunctionBody* functionBody;
};

class ProcDeclaration : protected Node {
   public:
      ProcDeclaration(ProcHeading* procHeading, ProcBody* procBody);
   protected:
      ProcHeading* procHeading;
      ProcBody* procBody;
};

class ProcFuncDeclaration : protected Node {
   public:
      ProcFuncDeclaration(ProcDeclaration* procDeclaration);
      ProcFuncDeclaration(FuncDeclaration* funcDeclaration);
      ProcDeclaration* getProcDeclaration();
      FuncDeclaration* getFuncDeclaration();
   protected:
      ProcDeclaration* procDeclaration;
      FuncDeclaration* funcDeclaration;
};

class TypeDefinitionPart : protected Node {
   public:
      TypeDefinitionPart();
      std::list<TypeDefinition>* getTypeDefinitions();
   protected:
      std::list<TypeDefinition>* typeDefinitions;
};

class VariableDeclarationPart : protected Node {
   public:
      VariableDeclarationPart();
      std::list<VariableDeclaration>* getVariableDeclarations();
   protected:
      std::list<VariableDeclaration>* variableDeclarations;
};

class ProcFuncDeclarationPart : protected Node {
   public:
      ProcFuncDeclarationPart();
      std::list<ProcFuncDeclaration>* getProcFuncDeclarations();
   protected:
      std::list<ProcFuncDeclaration>* procFuncDeclarations;
};

class DeclarationPart : protected Node {
   public:
      DeclarationPart(TypeDefinitionPart* typeDefinitionPart);
      DeclarationPart(VariableDeclarationPart* variableDeclarations);
      DeclarationPart(ProcFuncDeclarationPart*  procFuncDeclarationPart);
      TypeDefinitionPart* getTypeDefinitionPart();
      VariableDeclarationPart* getVariableDeclarations();
      ProcFuncDeclarationPart*  getProcFuncDeclarationPart();
   protected:
      TypeDefinitionPart* typeDefinitionPart;
      VariableDeclarationPart* variableDeclarations;
      ProcFuncDeclarationPart*  procFuncDeclarationPart;
};

class Block : protected Node {
   public:
      Block(DeclarationPart* declarationPart, StatementPart statementPart);
      DeclarationPart* getDeclarationPart();
      StatementPart* getStatementPart();
   protected:
      DeclarationPart* delcarationPart;
      StatementPart* statementPart;
};

class ProgramHeading : protected Node {
   public:
      ProgramHeading();
      std::string getIdentifier();
   protected:
      std::string identifier;
};

class Program : protected Node {
   public:
      Program(ProgramHeading* programHeading, Block* block);
      ProgramHeading* getProgramHeading();
      Block* getBlock();
   protected:
      ProgramHeading* programHeading;
      Block* block;
};
