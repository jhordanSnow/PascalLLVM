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

void VariableNT::execute(){
  Enviroment* env = Enviroment::getInstance();
  if (this->entireVariable != 0){
    EnvVariable* var = env->getVariable(this->entireVariable->variableIdentifier->variableIdentifier->identifier);
    int varType = var->getType();
    if (varType == 1) {
       IntVariable* intVar = (IntVariable*)var;
       this->value = intVar->getValue();
    }else if (varType == 2) {
       BoolVariable* boolVar = (BoolVariable*)var;
       this->value = (boolVar->getValue()) ? 1 : 2;
    }
  }else if (this->indexedVariable != 0){
    this->indexedVariable->expression->execute();
    EnvVariable* var = env->getVariable(this->indexedVariable->arrayVariable->entireVariable->variableIdentifier->variableIdentifier->identifier);
    ArrayVariableEnv* arrayVar = (ArrayVariableEnv*)var;
    this->value = arrayVar->getInt(this->indexedVariable->expression->value);
  }
}

void AbstractFactor::execute(){}

NotFactor::NotFactor(AbstractFactor* factor) : AbstractFactor() {
   this->factor = factor;
}

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

void Factor::execute(){
  if (this->constant != 0) {
    this->value = this->constant->intConst;
  }else if (this->variable != 0){
    this->variable->execute();
    this->value = this->variable->value;
  } else if (this->expression != 0) {
   this->expression->execute();
   this->value = this->expression->value;
  }
}

Term::Term(list<AbstractFactor*>* factors, list<MultiplicationOperator>* operators) : Node() {
   this->factors = factors;
   this->operators = operators;
}

void Term::execute(){
  int termValue = 1;
  int itFact = 0;
  for (list<AbstractFactor*>::iterator it = this->factors->begin(); it != this->factors->end(); ++it) {
    AbstractFactor* factTemp = (*it);
    factTemp->execute();
    if (itFact == 0){
      termValue = factTemp->value;
    }
    if (this->operators->size() > 0 && itFact > 0){
      MultiplicationOperator mulOperator = this->operators->front();
      this->operators->pop_front();
      if (mulOperator == MultiplicationOperator::MUL){
        termValue *= factTemp->value;
      }else if (mulOperator == MultiplicationOperator::DIV){
        termValue /= factTemp->value;
      }
    }
    itFact++;
  }
  this->value = termValue;
}

SimpleExpression::SimpleExpression(Sign sign, list<Term*>* terms, list<AdditionOperator>* additionOperators) : Node() {
   this->sign = sign;
   this->terms = terms;
   this->additionOperators = additionOperators;
}

void SimpleExpression::execute(){
  int expValue = 0;
  int itTerm = 0;
  for (list<Term*>::iterator it = this->terms->begin(); it != this->terms->end(); ++it) {
    Term* tempTerm = (*it);
    tempTerm->execute();
    if (itTerm == 0){
      expValue = (sign == Sign::NEGATIVE) ? -1 * tempTerm->value : tempTerm->value;
    }
    if (this->additionOperators->size() > 0 && itTerm > 0){
      AdditionOperator AddOperator = this->additionOperators->front();
      this->additionOperators->pop_front();
      if (AddOperator == AdditionOperator::ADD){
        expValue += tempTerm->value;
      }else if (AddOperator == AdditionOperator::SUB){
        expValue -= tempTerm->value;
      }
    }
    itTerm++;
  }
  this->value = expValue;
}

Expression::Expression(SimpleExpression* simpleExpression1) : Node() {
   this->simpleExpression1 = simpleExpression1;
   this->simpleExpression2 = 0;
}

Expression::Expression(SimpleExpression* simpleExpression1, RelationalOperator relationalOperator, SimpleExpression* simpleExpression2) : Node() {
   this->simpleExpression1 = simpleExpression1;
   this->relationalOperator = relationalOperator;
   this->simpleExpression2 = simpleExpression2;
}

void Expression::execute(){
  simpleExpression1->execute();
  this->value = simpleExpression1->value;
  if (simpleExpression2 != 0){
    simpleExpression2->execute();
    if (this->relationalOperator == RelationalOperator::EQ){
      this->value = simpleExpression1->value == simpleExpression2->value;
    }else if (this->relationalOperator == RelationalOperator::NEQ){
      this->value = simpleExpression1->value != simpleExpression2->value;
    }else if (this->relationalOperator == RelationalOperator::LT){
      this->value = simpleExpression1->value < simpleExpression2->value;
    }else if (this->relationalOperator == RelationalOperator::LEQ){
      this->value = simpleExpression1->value <= simpleExpression2->value;
    }else if (this->relationalOperator == RelationalOperator::GT){
      this->value = simpleExpression1->value > simpleExpression2->value;
    }else if (this->relationalOperator == RelationalOperator::GEQ){
      this->value = simpleExpression1->value >= simpleExpression2->value;
    }else if (this->relationalOperator == RelationalOperator::OR){
      this->value = simpleExpression1->value || simpleExpression2->value;
    }else if (this->relationalOperator == RelationalOperator::AND){
      this->value = simpleExpression1->value && simpleExpression2->value;
    }
  }
}

WhileStatement::WhileStatement(Expression* expression, Statement* statement) : Node() {
   this->expression = expression;
   this->statement = statement;
}

void WhileStatement::execute(){
  expression->execute();
  while (expression->value) {
    statement->execute();
    expression->execute();
  }
}

IfStatement::IfStatement(Expression* expression, Statement* thenStatement){
   this->expression = expression;
   this->statement = statement;
}

IfStatement::IfStatement(Expression* expression, Statement* thenStatement, Statement* elseStatement){
   this->expression = expression;
   this->statement = statement;
   this->elseStatement = elseStatement;
}

void IfStatement::execute(){
  expression->execute();
  if (expression->value){
    statement->execute();
  }else{
    if (elseStatement != 0){
      elseStatement->execute();
    }
  }
}

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

void StructuredStatement::execute() {
   if (this->compoundStatement != 0){
     this->compoundStatement->execute();
   }else if (this->ifStatement != 0){
     this->ifStatement->execute();
   }else if (this->whileStatement != 0){
     this->whileStatement->execute();
   }
}

WriteStatement::WriteStatement(list<VariableNT*>* variableList) : Node() {
   this->variableList = variableList;
}

void WriteStatement::execute() {
   for (list<VariableNT*>::iterator it = this->variableList->begin(); it != this->variableList->end(); ++it) {
      Enviroment* env = Enviroment::getInstance();
      VariableNT* requestedVar = (*it);

      if (requestedVar->entireVariable != 0) {
         EnvVariable* var = env->getVariable(requestedVar->entireVariable->variableIdentifier->variableIdentifier->identifier);
         int varType = var->getType();
         if (varType == 1) { // int
            IntVariable* intVar = (IntVariable*)var;
            cout << intVar->toString() << endl;
         } else if (varType == 2) { // string
            BoolVariable* boolVar = (BoolVariable*)var;
            cout << boolVar->toString() << endl;
         } else if (varType == 3) { // boolean
            StringVariable* stringVar = (StringVariable*)var;
            cout << stringVar->toString() << endl;
         }
      } else { // indexed variable
         ArrayVariableEnv* var = (ArrayVariableEnv*)env->getVariable(requestedVar->indexedVariable->arrayVariable->entireVariable->variableIdentifier->variableIdentifier->identifier);
         int varType = var->getType();
         if (varType == 1) { // int
            cout << var->getInt(1) << endl;
         } else if (varType == 2) { // boolean
            cout << var->getBool(1) << endl;
         } else if (varType == 3) { // string
            cout << var->getString(1) << endl;
         }

      }
   }
}

ReadStatement::ReadStatement(list<VariableNT*>* variableList) : Node() {
   this->variableList = variableList;
}

void ReadStatement::execute() {
   for (list<VariableNT*>::iterator it = this->variableList->begin(); it != this->variableList->end(); ++it) {
      Enviroment* env = Enviroment::getInstance();
      VariableNT* requestedVar = (*it);

      if (requestedVar->entireVariable != 0) {
         EnvVariable* var = env->getVariable(requestedVar->entireVariable->variableIdentifier->variableIdentifier->identifier);
         int varType = var->getType();
         if (varType == 1) { // int
            IntVariable* intVar = (IntVariable*)var;
            int newVar = 0;
            cout << "int: ";
            while(!(cin >> newVar)){
               cout << "Valor debe ser un int" << endl;
               cout << "int: ";
               cin.clear();
               cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            intVar->setValue(newVar);
         } else if (varType == 2) { // boolean
            BoolVariable* boolVar = (BoolVariable*)var;
            bool newVar = false;
            cout << "boolean(1/0): ";
            while(!(cin >> newVar)){
               cout << "el valor debe ser un booleano(1/0)." << endl;
               cout << "boolean(1/0): ";
               cin.clear();
               cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            boolVar->setValue(newVar);
         } else if (varType == 3) { // string
            StringVariable* stringVar = (StringVariable*)var;
            string newVar = "";
            cout << "string: ";
            while (!(cin >> newVar)) {
               cout << "el valor debe ser un string." << endl;
               cout << "string: ";
               cin.clear();
               cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            stringVar->setValue(newVar);
         }
      } else { // indexed variable // FALTA Cambiar los 1 por expression
         ArrayVariableEnv* var = (ArrayVariableEnv*)env->getVariable(requestedVar->indexedVariable->arrayVariable->entireVariable->variableIdentifier->variableIdentifier->identifier);
         int varType = var->getType();
         if (varType == 1) { // int
            int newVar = 0;
            cout << "int: ";
            while(!(cin >> newVar)){
               cout << "Valor debe ser un int" << endl;
               cout << "int: ";
               cin.clear();
               cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            var->setInt(1, newVar);
         } else if (varType == 2) { // boolean
            bool newVar = false;
            cout << "boolean(1/0): ";
            while(!(cin >> newVar)){
               cout << "el valor debe ser un booleano(1/0)." << endl;
               cout << "boolean(1/0): ";
               cin.clear();
               cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            var->setBool(1, newVar);
         } else if (varType == 3) { // string
            string newVar = "";
            cout << "string: ";
            while (!(cin >> newVar)) {
               cout << "el valor debe ser un string." << endl;
               cout << "string: ";
               cin.clear();
               cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            var->setString(1, newVar);
         }
      }
   }
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

CompoundStatement::CompoundStatement(list<Statement*>* statementList) : Node() {
   this->statementList = statementList;
}

void CompoundStatement::execute() {
   for (list<Statement*>::iterator it = this->statementList->begin(); it != this->statementList->end(); ++it) {
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

VariableDeclaration::VariableDeclaration(list<Identifier*>* identifierList, DataType* dataType) : Node() {
   this->identifierList = identifierList;
   this->dataType = dataType;
}

void VariableDeclaration::execute() {
   Enviroment* env = Enviroment::getInstance();
   DataType* dt = this->dataType;
   if (dt->arrayType == 0) { // si es un tipo simple
      for (list<Identifier*>::iterator it = this->identifierList->begin(); it != this->identifierList->end(); ++it) {
         Identifier* id = (*it);
         if (dt->simpleType == SimpleType::INTEGER){
            env->addInt(id->identifier, 0);
         } else if (dt->simpleType == SimpleType::CHAR) {
            env->addString(id->identifier, "");
         } else if (dt->simpleType == SimpleType::BOOLEAN) {
            env->addBool(id->identifier, false);
         }
      }
   } else { // si es un tipo array
      for (list<Identifier*>::iterator it = this->identifierList->begin(); it != this->identifierList->end(); ++it) {
         Identifier* id = (*it);
         ArrayType* at = dt->arrayType;
         IndexRange* ir = at->indexRange;
         if (at->simpleType == SimpleType::INTEGER){
            env->addArray(id->identifier, ir->begining, ir->end, 1);
         } else if (at->simpleType == SimpleType::CHAR) {
            env->addArray(id->identifier, ir->begining, ir->end, 2);
         } else if (at->simpleType == SimpleType::BOOLEAN) {
            env->addArray(id->identifier, ir->begining, ir->end, 3);
         }
      }
   }
}

VariableDeclarationPart::VariableDeclarationPart(list<VariableDeclaration*>* variableDeclarations) : Node() {
   this->variableDeclarations = variableDeclarations;
}

VariableDeclarationPart::VariableDeclarationPart() : Node() {
   this->variableDeclarations = 0;
}

void VariableDeclarationPart::execute() {
   for (list<VariableDeclaration*>::iterator it = this->variableDeclarations->begin(); it != this->variableDeclarations->end(); ++it){
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

// PRINTS

void Program::print() {
   cout << "program {\n";
   if(identifier != 0) identifier->print();
   if (block != 0) block->print();
   cout << "}" << endl;
}


void Identifier::print() {
   cout << "identifier: "<< this->identifier << endl;
};

void ConstantIdentifier::print() {
   cout << "ConstantIdentifier {" << endl;
   if(identifier != 0) identifier->print();
   cout << "}" << endl;
};

void Constant::print() {
   cout << "constant {" << endl;
   if(this->stringConst != "") cout << this->stringConst << endl;
   cout << this->intConst << endl;
   if(constIdentifier != 0) constIdentifier->print();
   cout << "}" << endl;
};

void TypeIdentifier::print() {
   cout << "TypeIdentifier {" << endl;
   if(identifier != 0) identifier->print();
   cout << "}" << endl;
};

void IndexRange::print() {
   cout << "IndexRange {" << endl;
   cout << this->begining << endl;
   cout << this->end << endl;
   cout << "}" << endl;
};

void ArrayType::print() {
   cout << "ArrayType {" << endl;
   if(indexRange != 0) indexRange->print();
   cout << "}" << endl;
};

void DataType::print() {
   cout << "DataType { ";
   if(arrayType != 0) arrayType->print();
   else{ 
     cout << Helpers::SimpleTypeToString(simpleType);
   }
   cout << " }" << endl;
};

void VariableIdentifier::print() {
   cout << "Variable Identifier {" << endl;
   if(variableIdentifier != 0) variableIdentifier->print();
   cout << "}" << endl;
};

void EntireVariable::print() {
   cout << "Entire Variable {" << endl;
   if(variableIdentifier != 0) variableIdentifier->print();
   cout << "}" << endl;
};

void ArrayVariable::print() {
   cout << "ArrayVariableEnv {" << endl;
   if(entireVariable != 0) entireVariable->print();
   cout << "}" << endl;
};

void IndexedVariable::print() {
   cout << "IndexedVariable {" << endl;
   if(arrayVariable != 0) arrayVariable->print();
   if(expression != 0) expression->print();
   cout << "}" << endl;
};

void VariableNT::print() {
   cout << "variable {" << endl;
   if(entireVariable != 0) entireVariable->print();
   if(indexedVariable != 0) indexedVariable->print();
   cout << "}" << endl;
};

void NotFactor::print() {
   cout << "Not Factor {" << endl;
   if(factor != 0) factor->print();
   cout << "}" << endl;
};

void Factor::print() {
   cout << "factor {" << endl;
   if(variable != 0) variable->print();
   if(constant != 0) constant->print();
   if(expression != 0) expression->print();
   cout << "}" << endl;
};

void Term::print() {
   cout << "Term {" << endl;
   for (list<AbstractFactor*>::iterator it = factors->begin(); it != factors->end(); ++it) {
      AbstractFactor* var = (*it);
      var->print();
   }
   cout << "}" << endl;
};

void SimpleExpression::print() {
   cout << "SimpleExpression {" << endl;
   for (list<Term*>::iterator it = terms->begin(); it != terms->end(); ++it) {
      Term* var = (*it);
      var->print();
   }
   cout << "}" << endl;
};

void Expression::print() {
   cout << "Expression {" << endl;
   if(simpleExpression1 != 0) simpleExpression1->print();
   if(simpleExpression2 != 0) simpleExpression2->print();
   cout << "}" << endl;
};

void WhileStatement::print() {
   cout << "while Statement {" << endl;
   if(expression != 0) expression->print();
   if(statement != 0) statement->print();
   cout << "}" << endl;
};

void IfStatement::print() {
   cout << "If statement {" << endl;
   if(expression != 0) expression->print();
   if(statement != 0) statement->print();
   if(elseStatement != 0) elseStatement->print();
   cout << "}" << endl;
};

void StructuredStatement::print() {
   cout << "structuredStatement {" << endl;
   if(compoundStatement != 0) compoundStatement->print();
   if(ifStatement != 0) ifStatement->print();
   if(whileStatement != 0) whileStatement->print();
   cout << "}" << endl;
};

void WriteStatement::print() {
   cout << "Write Statement" << endl;
   for (list<VariableNT*>::iterator it = variableList->begin(); it != variableList->end(); ++it) {
      VariableNT* var = (*it);
      var->print();
   }
   cout << "}" << endl;
};

void ReadStatement::print() {
   cout << "read statement {" << endl;
   for (list<VariableNT*>::iterator it = variableList->begin(); it != variableList->end(); ++it) {
      VariableNT* var = (*it);
      var->print();
   }
   cout << "}" << endl;
};

void AssignmentStatement::print() {
   cout << "Assignment Statement {" << endl;
   if(variable != 0) variable->print();
   if(expression != 0) expression->print();
   cout << "}" << endl;
};

void SimpleStatement::print() {
   cout << "simpleStatement {" << endl;
   if(assignmentStatement != 0) assignmentStatement->print();
   if(readStatement != 0) readStatement->print();
   if(writeStatement != 0) writeStatement->print();
   cout << "}" << endl;
};

void Statement::print() {
   cout << "Statement {" << endl;
   if (simpleStatement != 0) simpleStatement->print();
   if (structuredStatement != 0) structuredStatement->print();
   cout << "}" << endl;
};

void CompoundStatement::print() {
   cout << "compoundStatement {" << endl;
   if (statementList != 0) {
      for (list<Statement*>::iterator it = statementList->begin(); it != statementList->end(); ++it) {
         Statement* st = (*it);
         st->print();
      }
   }
   cout << "}" << endl;
};

void StatementPart::print() {
   cout << "statementPart {" << endl;
   if (compoundStatement != 0) compoundStatement->print();
   cout << "}" << endl;
};

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
};

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
