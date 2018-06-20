#include <headders/ast.h>
#include <headders/env.h>
#include<headders/helpers.h>
#include<string>
#include<list>
#include<limits>

Node::Node() {}

Identifier::Identifier(string identifier) : Node() {
   this->identifier = identifier;
}

ConstantIdentifier::ConstantIdentifier(Identifier* identifier) : Node() {
   this->identifier = identifier;
}

Constant::Constant(int intConst) : Node() {
   this->intConst = intConst;
   this->stringConst = "";
}

Constant::Constant(string stringConst) : Node() {
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
   this->arrayType = 0;
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
   this->indexedVariable = 0;
}

VariableNT::VariableNT(IndexedVariable* indexedVariable) : Node() {
   this->indexedVariable = indexedVariable;
   this->entireVariable = 0;
}

void VariableNT::codeGen(){}

NotFactor::NotFactor(AbstractFactor* factor) : AbstractFactor() {
   this->factor = factor;
}

void NotFactor::codeGen(){}

Factor::Factor(VariableNT* variable) : AbstractFactor() {
   this->variable = variable;
   this->constant = 0;
   this->expression = 0;
}

Factor::Factor(Constant* constant) : AbstractFactor() {
   this->constant = constant;
   this->variable = 0;
   this->expression = 0;
}

Factor::Factor(Expression* expression) : AbstractFactor() {
   this->constant = 0;
   this->variable = 0;
   this->expression = expression;
}

void Factor::codeGen(){}

Term::Term(list<AbstractFactor*>* factors, list<MultiplicationOperator>* operators) : Node() {
   this->factors = factors;
   this->operators = operators;
}

void Term::codeGen(){}

SimpleExpression::SimpleExpression(Sign sign, list<Term*>* terms, list<AdditionOperator>* additionOperators) : Node() {
   this->sign = sign;
   this->terms = terms;
   this->additionOperators = additionOperators;
}

void SimpleExpression::codeGen(){}

Expression::Expression(SimpleExpression* simpleExpression1) : Node() {
   this->simpleExpression1 = simpleExpression1;
   this->simpleExpression2 = 0;
}

Expression::Expression(SimpleExpression* simpleExpression1, RelationalOperator relationalOperator, SimpleExpression* simpleExpression2) : Node() {
   this->simpleExpression1 = simpleExpression1;
   this->relationalOperator = relationalOperator;
   this->simpleExpression2 = simpleExpression2;
}

void Expression::codeGen(){}

WhileStatement::WhileStatement(Expression* expression, Statement* statement) : Node() {
   this->expression = expression;
   this->statement = statement;
}

void WhileStatement::codeGen(){}

IfStatement::IfStatement(Expression* expression, Statement* thenStatement){
   this->expression = expression;
   this->statement = thenStatement;
}

IfStatement::IfStatement(Expression* expression, Statement* thenStatement, Statement* elseStatement){
   this->expression = expression;
   this->statement = thenStatement;
   this->elseStatement = elseStatement;
}

void IfStatement::codeGen(){}

StructuredStatement::StructuredStatement(CompoundStatement* compoundStatement) : Node() {
   this->compoundStatement = compoundStatement;
   this->whileStatement = 0;
   this->ifStatement = 0;
}

StructuredStatement::StructuredStatement(IfStatement* ifStatement) : Node() {
   this->ifStatement = ifStatement;
   this->compoundStatement = 0;
   this->whileStatement = 0;
}

StructuredStatement::StructuredStatement(WhileStatement* whileStatement) : Node() {
   this->whileStatement = whileStatement;
   this->compoundStatement = 0;
   this->ifStatement = 0;
}

void StructuredStatement::codeGen() {}

WriteStatement::WriteStatement(list<VariableNT*>* variableList) : Node() {
   this->variableList = variableList;
}

void WriteStatement::codeGen() {}

ReadStatement::ReadStatement(list<VariableNT*>* variableList) : Node() {
   this->variableList = variableList;
}

void ReadStatement::codeGen() {}

AssignmentStatement::AssignmentStatement(VariableNT* variable, Expression* expression) : Node() {
   this->variable = variable;
   this->expression = expression;
}

void AssignmentStatement::codeGen() {}

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

void SimpleStatement::codeGen() {}

Statement::Statement(SimpleStatement* simpleStatement) : Node() {
   this->simpleStatement = simpleStatement;
   this->structuredStatement = 0;
}

Statement::Statement(StructuredStatement* structuredStatement) : Node() {
   this->structuredStatement = structuredStatement;
   this->simpleStatement = 0;
}

void Statement::codeGen() {}

CompoundStatement::CompoundStatement(list<Statement*>* statementList) : Node() {
   this->statementList = statementList;
}

void CompoundStatement::codeGen() {}

StatementPart::StatementPart(CompoundStatement* compoundStatement) : Node() {
   this->compoundStatement = compoundStatement;
}

void StatementPart::codeGen() {}

VariableDeclaration::VariableDeclaration(list<Identifier*>* identifierList, DataType* dataType) : Node() {
   this->identifierList = identifierList;
   this->dataType = dataType;
}

void VariableDeclaration::codeGen() {}

VariableDeclarationPart::VariableDeclarationPart(list<VariableDeclaration*>* variableDeclarations) : Node() {
   this->variableDeclarations = variableDeclarations;
}

VariableDeclarationPart::VariableDeclarationPart() : Node() {
   this->variableDeclarations = 0;
}

void VariableDeclarationPart::codeGen() {}

Block::Block(VariableDeclarationPart* variableDeclarationPart, StatementPart* statementPart) : Node() {
   this->variableDeclarationPart = variableDeclarationPart;
   this->statementPart = statementPart;
}

void Block::codeGen() {}

Program::Program(Identifier* identifier, Block* block) : Node() {
   this->identifier = identifier;
   this->block = block;
}

void Program::codeGen() {}

// PRINTS

void Program::print() {
   cout << "program {\n";
   if(identifier != 0) identifier->print();
   if (block != 0) block->print();
   cout << "}" << endl;
}


void Identifier::print() {
   cout << "identifier: "<< this->identifier << endl;
}

void ConstantIdentifier::print() {
   cout << "ConstantIdentifier {" << endl;
   if(identifier != 0) identifier->print();
   cout << "}" << endl;
}

void Constant::print() {
   cout << "constant {" << endl;
   if(this->stringConst != "") cout << this->stringConst << endl;
   cout << this->intConst << endl;
   if(constIdentifier != 0) constIdentifier->print();
   cout << "}" << endl;
}

void TypeIdentifier::print() {
   cout << "TypeIdentifier {" << endl;
   if(identifier != 0) identifier->print();
   cout << "}" << endl;
}

void IndexRange::print() {
   cout << "IndexRange {" << endl;
   cout << "Beginning: " << this->begining << endl;
   cout << "End:" << this->end << endl;
   cout << "}" << endl;
}

void ArrayType::print() {
   cout << "ArrayType {" << endl;
   if(indexRange != 0) indexRange->print();
   cout << Helpers::SimpleTypeToString(simpleType) << endl;
   cout << "}" << endl;
}

void DataType::print() {
   cout << "DataType { " << endl;
   if(arrayType != 0) arrayType->print();
   else{
     cout << Helpers::SimpleTypeToString(simpleType);
   }
   cout << "}" << endl;
}

void VariableIdentifier::print() {
   cout << "Variable Identifier {" << endl;
   if(variableIdentifier != 0) variableIdentifier->print();
   cout << "}" << endl;
}

void EntireVariable::print() {
   cout << "Entire Variable {" << endl;
   if(variableIdentifier != 0) variableIdentifier->print();
   cout << "}" << endl;
}

void ArrayVariable::print() {
   cout << "ArrayVariableEnv {" << endl;
   if(entireVariable != 0) entireVariable->print();
   cout << "}" << endl;
}

void IndexedVariable::print() {
   cout << "IndexedVariable {" << endl;
   if(arrayVariable != 0) arrayVariable->print();
   if(expression != 0) expression->print();
   cout << "}" << endl;
}

void VariableNT::print() {
   cout << "variable {" << endl;
   if(entireVariable != 0) entireVariable->print();
   if(indexedVariable != 0) indexedVariable->print();
   cout << "}" << endl;
}

void NotFactor::print() {
   cout << "Not Factor {" << endl;
   if(factor != 0) factor->print();
   cout << "}" << endl;
}

void Factor::print() {
   cout << "factor {" << endl;
   if(variable != 0) variable->print();
   if(constant != 0) constant->print();
   if(expression != 0) expression->print();
   cout << "}" << endl;
}

void Term::print() {
   cout << "Term {" << endl;
   for (list<AbstractFactor*>::iterator it = factors->begin(); it != factors->end(); ++it) {
      AbstractFactor* var = (*it);
      var->print();
   }
   cout << "}" << endl;
}

void SimpleExpression::print() {
   cout << "SimpleExpression {" << endl;
   for (list<Term*>::iterator it = terms->begin(); it != terms->end(); ++it) {
      Term* var = (*it);
      var->print();
   }
   cout << "}" << endl;
}

void Expression::print() {
   cout << "Expression {" << endl;
   if(simpleExpression1 != 0) simpleExpression1->print();
   if(simpleExpression2 != 0) simpleExpression2->print();
   cout << "}" << endl;
}

void WhileStatement::print() {
   cout << "while Statement {" << endl;
   if(expression != 0) expression->print();
   if(statement != 0) statement->print();
   cout << "}" << endl;
}

void IfStatement::print() {
   cout << "If statement {" << endl;
   if(this->expression != 0) this->expression->print();
   if(this->statement != 0) this->statement->print();
   if(this->elseStatement != 0) this->elseStatement->print();
   cout << "}" << endl;
}

void StructuredStatement::print() {
   cout << "structuredStatement {" << endl;
   if(compoundStatement != 0) compoundStatement->print();
   if(ifStatement != 0) ifStatement->print();
   if(whileStatement != 0) whileStatement->print();
   cout << "}" << endl;
}

void WriteStatement::print() {
   cout << "Write Statement {" << endl;
   for (list<VariableNT*>::iterator it = variableList->begin(); it != variableList->end(); ++it) {
      VariableNT* var = (*it);
      var->print();
   }
   cout << "}" << endl;
}

void ReadStatement::print() {
   cout << "read statement {" << endl;
   for (list<VariableNT*>::iterator it = variableList->begin(); it != variableList->end(); ++it) {
      VariableNT* var = (*it);
      var->print();
   }
   cout << "}" << endl;
}

void AssignmentStatement::print() {
   cout << "Assignment Statement {" << endl;
   if(variable != 0) variable->print();
   if(expression != 0) expression->print();
   cout << "}" << endl;
}

void SimpleStatement::print() {
   cout << "simpleStatement {" << endl;
   if(assignmentStatement != 0) assignmentStatement->print();
   if(readStatement != 0) readStatement->print();
   if(writeStatement != 0) writeStatement->print();
   cout << "}" << endl;
}

void Statement::print() {
   cout << "Statement {" << endl;
   if (simpleStatement != 0) simpleStatement->print();
   if (structuredStatement != 0) structuredStatement->print();
   cout << "}" << endl;
}

void CompoundStatement::print() {
   cout << "compoundStatement {" << endl;
   if (statementList != 0) {
      for (list<Statement*>::iterator it = statementList->begin(); it != statementList->end(); ++it) {
         Statement* st = (*it);
         st->print();
      }
   }
   cout << "}" << endl;
}

void StatementPart::print() {
   cout << "statementPart {" << endl;
   if (compoundStatement != 0) compoundStatement->print();
   cout << "}" << endl;
}

void VariableDeclaration::print() {
   cout << "variable declaration {" << endl;
   if (identifierList != 0) {
      for (list<Identifier*>::iterator it = identifierList->begin(); it != identifierList->end(); ++it) {
         Identifier* id = (*it);
         id->print();
      }
   }
   cout<< ":";
   dataType->print();
   cout << "}" << endl;
}

void VariableDeclarationPart::print() {
   cout << "var declaration part {\n";
   if (variableDeclarations != 0) {
      for (list<VariableDeclaration*>::iterator it = variableDeclarations->begin(); it != variableDeclarations->end(); ++it) {
         VariableDeclaration* var = (*it);
         var->print();
      }
   }
   cout << "}" << endl;
}

void Block::print() {
   cout << "block {\n";
   if (variableDeclarationPart != 0) variableDeclarationPart->print();
   if (statementPart != 0) statementPart->print();
   cout << "}" << endl;
}

FunctionBlock::FunctionBlock(Block* block) : Node(){
  this->block = block;
}

void FunctionBlock::codeGen(){}

Function::Function(Identifier* identifier, list<VariableDeclaration*>* variableDeclarations, FunctionBlock* block) : Node(){
  this->identifier = identifier;
  this->variableDeclarations = variableDeclarations;
  this->block = block;
}

Block::Block(VariableDeclarationPart* variableDeclarationPart, list<Function*>* functions, StatementPart* statementPart):Node(){
  this->variableDeclarationPart = variableDeclarationPart;
  this->functions = functions;
  this->statementPart = statementPart;
}
