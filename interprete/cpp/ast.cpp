#include <headders/ast.h>
#include<string>
#include<list>

Node::Node() {}

Identifier::Identifier(std::string identifier) : Node() {
   this->identifier = identifier;
}

ConstantIdentifier::ConstantIdentifier(Identifier* identifier) : Node() {
   this->identifier = identifier;
}

Constant::Constant(int intConst) : Node() {
   this->intConst = intConst;
}

Constant::Constant(char charConst) : Node() {
   this->charConst = charConst;
}

TypeIdentifier::TypeIdentifier(Identifier* identifier) : Node() {
   this->identifier = identifier;
}

IndexRange::IndexRange(int begining, int end) : Node() {
   this->begining = begining;
   this->end = end;
}

ArrayType::ArrayType(SimpleType* simpleType) : Node() {
   this->simpleType = simpleType;
}

ArrayType::ArrayType(IndexRange* indexRange, SimpleType* simpleType) : Node() {
   this->indexRange = indexRange;
   this->simpleType = simpleType;
}

DataType::DataType(SimpleType* simpleType) : Node() {
   this->simpleType = simpleType;
}

DataType::DataType(ArrayType* arrayType) : Node() {
   this->arrayType = arrayType;
}

VariableIdentifier::VariableIdentifier(Identifier* variableIdentifier) : Node() {
   this->variableIdentifier = variableIdentifier;
}

EntireVariable::EntireVariable(VariableIdentifier* variableIdentifier) : Node() {
   this->variableIdentifier = variableIdentifier;
}

ArrayVariable::ArrayVariable(EntireVariable* entireVariable) : Node() {
   this->entireVariable = entireVariable;
}

IndexedVariable::IndexedVariable(ArrayVariable* arrayVariable, std::list<Expression>* expressionList) : Node() {
   this->arrayVariable = arrayVariable;
   this->expressionList = expressionList;
}

Variable::Variable(EntireVariable* entireVariable) : Node() {
   this->entireVariable = entireVariable;
}

Variable::Variable(IndexedVariable* indexedVariable) : Node() {
   this->indexedVariable = indexedVariable;
}

NotFactor::NotFactor(AbstractFactor* factor) : AbstractFactor() {
   this->factor = factor;
}

Factor::Factor(Variable* variable) : AbstractFactor() {
   this->variable = variable;
}

Factor::Factor(Constant* constant) : AbstractFactor() {
   this->constant = constant;
}

Term::Term(std::list<Factor>* factors, std::list<MultiplicationOperator>* operators) : Node() {
   this->factors = factors;
   this->operators = operators;
}

SimpleExpression::SimpleExpression(Sign* sign, std::list<Term>* terms, std::list<AdditionOperator>* additionOperators) : Node() {
   this->sign = sign;
   this->terms = terms;
   this->additionOperators = additionOperators;
}

Expression::Expression(SimpleExpression* simpleExpression1) : Node() {
   this->simpleExpression1 = simpleExpression1;
}

Expression::Expression(SimpleExpression* simpleExpression1, RelationalOperator* relationalOperator, SimpleExpression* simpleExpression2) : Node() {
   this->simpleExpression1 = simpleExpression1;
   this->relationalOperator = relationalOperator;
   this->simpleExpression2 = simpleExpression2;
}

WhileStatement::WhileStatement(Expression* expression, Statement* statement) : Node() {
   this->expression = expression;
   this->statement = statement;
}

StructuredStatement::StructuredStatement(CompoundStatement* compoundStatement) : Node() {
   this->compoundStatement = compoundStatement;
}

StructuredStatement::StructuredStatement(IfStatement* ifStatement) : Node() {
   this->ifStatement = ifStatement;
}

StructuredStatement::StructuredStatement(WhileStatement* whileStatement) : Node() {
   this->whileStatement = whileStatement;
}

WriteStatement::WriteStatement(std::list<Variable> variableList) : Node() {
   this->variableList = variableList;
}

ReadStatement::ReadStatement(std::list<Variable> variableList) : Node() {
   this->variableList = variableList;
}

AssignmentStatement::AssignmentStatement(Variable* variable, Expression* expression) : Node() {
   this->variable = variable;
   this->expression = expression;
}

SimpleStatement::SimpleStatement(AssignmentStatement* assignmentStatement) : Node() {
   this->assignmentStatement = assignmentStatement;
}

SimpleStatement::SimpleStatement(ReadStatement* readStatement) : Node() {
   this->readStatement = readStatement;
}

SimpleStatement::SimpleStatement(WriteStatement* writeStatement) : Node() {
   this->writeStatement = writeStatement;
}

Statement::Statement(SimpleStatement* simpleStatement) : Node() {
   this->simpleStatement = simpleStatement;
}

Statement::Statement(StructuredStatement* structuredStatement) : Node() {
   this->structuredStatement = structuredStatement;
}

CompoundStatement::CompoundStatement(std::list<Statement> statementList) : Node() {
   this->statementList = statementList;
}

StatementPart::StatementPart(CompoundStatement* compoundStatement) : Node() {
   this->compoundStatement = compoundStatement;
}

VariableDeclaration::VariableDeclaration(std::list<Identifier>* identifierList, DataType* dataType) : Node() {
   this->identifierList = identifierList;
   this->dataType = dataType;
}

VariableDeclarationPart::VariableDeclarationPart(std::list<VariableDeclaration>* variableDeclarations) : Node() {
   this->variableDeclarations = variableDeclarations;
}

Block::Block(VariableDeclarationPart* variableDeclarationPart, StatementPart* statementPart) : Node() {
   this->variableDeclarationPart = variableDeclarationPart;
   this->statementPart = statementPart;
}

Program::Program(Identifier* identifier, Block* block) : Node() {
   this->identifier = identifier;
   this->block = block;
}

#if false
//macros
//^yiwPa::f;s {
//kf(yi)jVp:s/, /\n/€kb€kbr/g€kbeVi}^:normal daWVi}^:normal yaWA = pA;Vi{^I	this->
#endif
