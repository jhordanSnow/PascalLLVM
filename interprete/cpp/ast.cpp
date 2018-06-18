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

Constant::Constant(std::string stringConst) : Node() {
   this->stringConst = stringConst;
}

TypeIdentifier::TypeIdentifier(Identifier* identifier) : Node() {
   this->identifier = identifier;
}

IndexRange::IndexRange(int begining, int end) : Node() {
   this->begining = begining;
   this->end = end;
}

ArrayType::ArrayType(SimpleType simpleType) : Node() {
   this->simpleType = simpleType;
}

ArrayType::ArrayType(IndexRange* indexRange, SimpleType simpleType) : Node() {
   this->indexRange = indexRange;
   this->simpleType = simpleType;
}

DataType::DataType(SimpleType simpleType) : Node() {
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

IndexedVariable::IndexedVariable(ArrayVariable* arrayVariable, Expression* expression) : Node() {
   this->arrayVariable = arrayVariable;
   this->expression = expression;
}

VariableNT::VariableNT(EntireVariable* entireVariable) : Node() {
   this->entireVariable = entireVariable;
}

VariableNT::VariableNT(IndexedVariable* indexedVariable) : Node() {
   this->indexedVariable = indexedVariable;
}

NotFactor::NotFactor(AbstractFactor* factor) : AbstractFactor() {
   this->factor = factor;
}

Factor::Factor(VariableNT* variable) : AbstractFactor() {
   this->variable = variable;
}

Factor::Factor(Constant* constant) : AbstractFactor() {
   this->constant = constant;
}

Term::Term(std::list<AbstractFactor*>* factors, std::list<MultiplicationOperator>* operators) : Node() {
   this->factors = factors;
   this->operators = operators;
}

SimpleExpression::SimpleExpression(Sign sign, std::list<Term*>* terms, std::list<AdditionOperator>* additionOperators) : Node() {
   this->sign = sign;
   this->terms = terms;
   this->additionOperators = additionOperators;
}

Expression::Expression(SimpleExpression* simpleExpression1) : Node() {
   this->simpleExpression1 = simpleExpression1;
}

Expression::Expression(SimpleExpression* simpleExpression1, RelationalOperator relationalOperator, SimpleExpression* simpleExpression2) : Node() {
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
   this->whileStatement = 0;
}

StructuredStatement::StructuredStatement(WhileStatement* whileStatement) : Node() {
   this->whileStatement = whileStatement;
   this->ifStatement = 0;
}

void StructuredStatement::execute() {
   // FALTA
}

WriteStatement::WriteStatement(std::list<VariableNT*>* variableList) : Node() {
   this->variableList = variableList;
}

void WriteStatement::execute() {
   //FALTA EL DICCIONARIO
}

ReadStatement::ReadStatement(std::list<VariableNT*>* variableList) : Node() {
   this->variableList = variableList;
}

void ReadStatement::execute() {
   // FALTA EL DICCIONARIO
}

AssignmentStatement::AssignmentStatement(VariableNT* variable, Expression* expression) : Node() {
   this->variable = variable;
   this->expression = expression;
}

void AssignmentStatement::execute() {
   // FALTA EXPRESSION
}

SimpleStatement::SimpleStatement(AssignmentStatement* assignmentStatement) : Node() {
   this->assignmentStatement = assignmentStatement;
   this->readStatement = 0;
   this->writeStatement = 0;
}

SimpleStatement::SimpleStatement(ReadStatement* readStatement) : Node() {
   this->readStatement = readStatement;
   this->writeStatement = 0;
   this->assignmentStatement = 0;
}

SimpleStatement::SimpleStatement(WriteStatement* writeStatement) : Node() {
   this->writeStatement = writeStatement;
   this->readStatement = 0;
   this->assignmentStatement = 0;
}

void SimpleStatement::execute() {
   if (assignmentStatement != 0) {
      this->assignmentStatement->execute();
   } else if (readStatement != 0) {
      this->readStatement->execute();
   } else if (writeStatement != 0) {
      this->writeStatement->execute();
   }
}

Statement::Statement(SimpleStatement* simpleStatement) : Node() {
   this->simpleStatement = simpleStatement;
   this->structuredStatement = 0;
}

Statement::Statement(StructuredStatement* structuredStatement) : Node() {
   this->structuredStatement = structuredStatement;
   this->simpleStatement = 0;
}

void Statement::execute() {
   if (this->simpleStatement != 0) {
      this->simpleStatement->execute();
   } else {
      this->structuredStatement->execute();
   }
}

CompoundStatement::CompoundStatement(std::list<Statement*>* statementList) : Node() {
   this->statementList = statementList;
}

void CompoundStatement::execute() {
   for (std::list<Statement*>::iterator it = this->statementList->begin(); it != this->statementList->end(); ++it) {
      Statement* s = (*it);
      s->execute();
   }
}

StatementPart::StatementPart(CompoundStatement* compoundStatement) : Node() {
   this->compoundStatement = compoundStatement;
}

void StatementPart::execute() {
   this->compoundStatement->execute();
}

VariableDeclaration::VariableDeclaration(std::list<Identifier*>* identifierList, DataType* dataType) : Node() {
   this->identifierList = identifierList;
   this->dataType = dataType;
}

void VariableDeclaration::execute() {
   //Enviroment* env = Enviroment::getInstance();
}

VariableDeclarationPart::VariableDeclarationPart(std::list<VariableDeclaration*>* variableDeclarations) : Node() {
   this->variableDeclarations = variableDeclarations;
}

VariableDeclarationPart::VariableDeclarationPart() : Node() {
   this->variableDeclarations = 0;
}

void VariableDeclarationPart::execute() {
   for (std::list<VariableDeclaration*>::iterator it = this->variableDeclarations->begin(); it != this->variableDeclarations->end(); ++it){
      VariableDeclaration* varDeclaration = (*it);
      varDeclaration->execute();
   }
}

Block::Block(VariableDeclarationPart* variableDeclarationPart, StatementPart* statementPart) : Node() {
   this->variableDeclarationPart = variableDeclarationPart;
   this->statementPart = statementPart;
}

void Block::execute() {
   this->variableDeclarationPart->execute();
   this->statementPart->execute();
}

Program::Program(Identifier* identifier, Block* block) : Node() {
   this->identifier = identifier;
   this->block = block;
}

void Program::execute () {
   block->execute();
}

#if false
//macros
//^yiwPa::f;s {

//kf(yi)jVp:s/, /\n/�kb�kbr/g�kbe
Vi}^:normal daW
Vi}^:normal yaWA = pA;
Vi{^I	this->
#endif
