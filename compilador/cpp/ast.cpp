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

string VariableNT::codeGen(){
  Enviroment* env = Enviroment::getInstance();
  if (this->entireVariable != 0){
    EnvVariable* var = env->getVariable(this->entireVariable->variableIdentifier->variableIdentifier->identifier);
    this->type = var->getType();
    if (this->type == 1) {
       IntVariable* intVar = (IntVariable*)var;
       this->value = intVar->getValue();
    }else if (this->type == 2) {
       BoolVariable* boolVar = (BoolVariable*)var;
       this->value = (boolVar->getValue()) ? 1 : 2;
    }else if (this->type == 3){
      StringVariable* stringVar = (StringVariable*)var;
      this->stringValue = stringVar->getValue();
    }
  }else if (this->indexedVariable != 0){
    this->indexedVariable->expression->codeGen();
    EnvVariable* var = env->getVariable(this->indexedVariable->arrayVariable->entireVariable->variableIdentifier->variableIdentifier->identifier);
    ArrayVariableEnv* arrayVar = (ArrayVariableEnv*)var;
    this->value = arrayVar->getInt(this->indexedVariable->expression->value);
  }
  return "";
}

NotFactor::NotFactor(AbstractFactor* factor) : AbstractFactor() {
   this->factor = factor;
}

string NotFactor::codeGen(){
  this->factor->codeGen();
  this->factor->value = (this->factor->value == 0) ? 1 : 0;
  return "";
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

string Factor::codeGen(){
  if (this->constant != 0) {
    this->value = this->constant->intConst;
    this->stringValue = this->constant->stringConst;
    this->type = (this->constant->stringConst != "") ? 3 : 1;
  }else if (this->variable != 0){
    this->variable->codeGen();
    this->value = this->variable->value;
    this->stringValue = this->variable->stringValue;
    this->type = this->variable->value;
  } else if (this->expression != 0) {
   this->expression->codeGen();
   this->value = this->expression->value;
   this->stringValue = this->expression->stringValue;
   this->type = this->expression->type;
  }
  return "";
}

Term::Term(list<AbstractFactor*>* factors, list<MultiplicationOperator>* operators) : Node() {
   this->factors = factors;
   this->operators = operators;
}

string Term::codeGen(){
  int termValue = 1;
  int itFact = 0;
  for (list<AbstractFactor*>::iterator it = this->factors->begin(); it != this->factors->end(); ++it) {
    AbstractFactor* factTemp = (*it);
    factTemp->codeGen();
    if (itFact == 0){
      termValue = factTemp->value;
      this->stringValue = factTemp->stringValue;
    }
    // Lanzar error tal vez (?)
    if (this->operators->size() > 0 && itFact > 0){
      list<MultiplicationOperator>::iterator mulIt = this->operators->begin();
      advance(mulIt, itFact - 1);
      MultiplicationOperator mulOperator = *mulIt;
      if (mulOperator == MultiplicationOperator::MUL){
        termValue *= factTemp->value;
      }else if (mulOperator == MultiplicationOperator::DIV && factTemp->value > 0){
        termValue /= factTemp->value;
      }
    }
    itFact++;
  }
  this->value = termValue;
  this->type = (this->stringValue != "") ? 3 : 1;
  return "";
}

SimpleExpression::SimpleExpression(Sign sign, list<Term*>* terms, list<AdditionOperator>* additionOperators) : Node() {
   this->sign = sign;
   this->terms = terms;
   this->additionOperators = additionOperators;
}

string SimpleExpression::codeGen(){
  int expValue = 0;
  string expValueS = "";
  int itTerm = 0;
  for (list<Term*>::iterator it = this->terms->begin(); it != this->terms->end(); ++it) {
    Term* tempTerm = (*it);
    tempTerm->codeGen();
    if (itTerm == 0){
      expValue = (sign == Sign::NEGATIVE) ? -1 * tempTerm->value : tempTerm->value;
      expValueS = tempTerm->stringValue;
    }
    if (this->additionOperators->size() > 0 && itTerm > 0){
      list<AdditionOperator>::iterator addIt = this->additionOperators->begin();
      advance(addIt, itTerm - 1);
      AdditionOperator AddOperator = *addIt;
      if (AddOperator == AdditionOperator::ADD){
        expValue += tempTerm->value;
        expValueS += tempTerm->stringValue;
      }else if (AddOperator == AdditionOperator::SUB){
        expValue -= tempTerm->value;
      }
    }
    itTerm++;
  }
  this->stringValue = expValueS;
  this->value = expValue;
  this->type = (this->stringValue != "") ? 3 : 1;
  return "";
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

string Expression::codeGen(){
  this->simpleExpression1->codeGen();
  this->type = this->simpleExpression1->type;
  this->value = this->simpleExpression1->value;
  this->stringValue = this->simpleExpression1->stringValue;
  if (this->simpleExpression2 != 0){
    this->simpleExpression2->codeGen();
    if (this->relationalOperator == RelationalOperator::EQ){
      this->value = (this->type != 3) ? this->simpleExpression1->value == this->simpleExpression2->value : this->simpleExpression1->stringValue == this->simpleExpression2->stringValue;
    }else if (this->relationalOperator == RelationalOperator::NEQ){
      this->value = (this->type != 3) ? this->simpleExpression1->value != this->simpleExpression2->value : this->simpleExpression1->stringValue != this->simpleExpression2->stringValue;
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
  return "";
}

WhileStatement::WhileStatement(Expression* expression, Statement* statement) : Node() {
   this->expression = expression;
   this->statement = statement;
}

string WhileStatement::codeGen(){
  expression->codeGen();
  while (expression->value) {
    statement->codeGen();
    expression->codeGen();
  }
  return "";
}

IfStatement::IfStatement(Expression* expression, Statement* thenStatement){
   this->expression = expression;
   this->statement = thenStatement;
}

IfStatement::IfStatement(Expression* expression, Statement* thenStatement, Statement* elseStatement){
   this->expression = expression;
   this->statement = thenStatement;
   this->elseStatement = elseStatement;
}

string IfStatement::codeGen(){
  expression->codeGen();
  if (expression->value){
    statement->codeGen();
  }else{
    if (elseStatement != 0){
      elseStatement->codeGen();
    }
  }
  return "";
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

string StructuredStatement::codeGen() {
   if (this->compoundStatement != 0){
     this->compoundStatement->codeGen();
   }else if (this->ifStatement != 0){
     this->ifStatement->codeGen();
   }else if (this->whileStatement != 0){
     this->whileStatement->codeGen();
   }
   return "";
}

WriteStatement::WriteStatement(list<VariableNT*>* variableList) : Node() {
   this->variableList = variableList;
}

string WriteStatement::codeGen() {
   for (list<VariableNT*>::iterator it = this->variableList->begin(); it != this->variableList->end(); ++it) {
      Enviroment* env = Enviroment::getInstance();
      VariableNT* requestedVar = (*it);

      if (requestedVar->entireVariable != 0) {
         EnvVariable* var = env->getVariable(requestedVar->entireVariable->variableIdentifier->variableIdentifier->identifier);
         int varType = var->getType();
         if (varType == 1) { // int
            IntVariable* intVar = (IntVariable*)var;
            cout << intVar->toString() << endl;
         } else if (varType == 2) { // BOOL
            BoolVariable* boolVar = (BoolVariable*)var;
            cout << boolVar->toString() << endl;
         } else if (varType == 3) { // CHAR
            StringVariable* stringVar = (StringVariable*)var;
            cout << stringVar->toString() << endl;
         }
      } else { // indexed variable
         ArrayVariableEnv* var = (ArrayVariableEnv*)env->getVariable(requestedVar->indexedVariable->arrayVariable->entireVariable->variableIdentifier->variableIdentifier->identifier);
         requestedVar->indexedVariable->expression->codeGen();
         int varType = var->getType();
         if (varType == 1) { // int
            cout << var->getInt(requestedVar->indexedVariable->expression->value) << endl;
         } else if (varType == 2) { // boolean
            cout << var->getBool(requestedVar->indexedVariable->expression->value) << endl;
         } else if (varType == 3) { // string
            cout << var->getString(requestedVar->indexedVariable->expression->value) << endl;
         }

      }
   }
   return "";
}

ReadStatement::ReadStatement(list<VariableNT*>* variableList) : Node() {
   this->variableList = variableList;
}

string ReadStatement::codeGen() {
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
      } else { // indexed variable
         ArrayVariableEnv* var = (ArrayVariableEnv*)env->getVariable(requestedVar->indexedVariable->arrayVariable->entireVariable->variableIdentifier->variableIdentifier->identifier);
         requestedVar->indexedVariable->expression->codeGen();
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
            var->setInt(requestedVar->indexedVariable->expression->value, newVar);
         } else if (varType == 2) { // boolean
            bool newVar = false;
            cout << "boolean(1/0): ";
            while(!(cin >> newVar)){
               cout << "el valor debe ser un booleano(1/0)." << endl;
               cout << "boolean(1/0): ";
               cin.clear();
               cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            var->setBool(requestedVar->indexedVariable->expression->value, newVar);
         } else if (varType == 3) { // string
            string newVar = "";
            cout << "string: ";
            while (!(cin >> newVar)) {
               cout << "el valor debe ser un string." << endl;
               cout << "string: ";
               cin.clear();
               cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            var->setString(requestedVar->indexedVariable->expression->value, newVar);
         }
      }
   }
   return "";
}

AssignmentStatement::AssignmentStatement(VariableNT* variable, Expression* expression) : Node() {
   this->variable = variable;
   this->expression = expression;
}

string AssignmentStatement::codeGen() {
  string code = "";
  if (this->variable->entireVariable != 0) {
     string identifier = this->variable->entireVariable->variableIdentifier->variableIdentifier->identifier;
     code += identifier + " = " + this->expression->codeGen() + ";";
  } else { // indexed variable
     string identifier = this->variable->entireVariable->variableIdentifier->variableIdentifier->identifier;
     code += identifier << "[" << this->variable->indexedVariable->expression->value << "] = " << this->variable->indexedVariable->expression->codeGen() << ";";
  }
  return code;
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

string SimpleStatement::codeGen() {
   string code = ""
   if (assignmentStatement != 0) {
      code += this->assignmentStatement->codeGen();
   } else if (readStatement != 0) {
      code += this->readStatement->codeGen();
   } else if (writeStatement != 0) {
      code += this->writeStatement->codeGen();
   }
   return code;
}

Statement::Statement(SimpleStatement* simpleStatement) : Node() {
   this->simpleStatement = simpleStatement;
   this->structuredStatement = 0;
}

Statement::Statement(StructuredStatement* structuredStatement) : Node() {
   this->structuredStatement = structuredStatement;
   this->simpleStatement = 0;
}

string Statement::codeGen() {
   string code = "";
   if (this->simpleStatement != 0) {
      code += this->simpleStatement->codeGen();
   } else {
      code += this->structuredStatement->codeGen();
   }
   return "";
}

CompoundStatement::CompoundStatement(list<Statement*>* statementList) : Node() {
   this->statementList = statementList;
}

string CompoundStatement::codeGen() {
   string code = "{\n";
   for (list<Statement*>::iterator it = this->statementList->begin(); it != this->statementList->end(); ++it) {
      Statement* s = (*it);
      code += s->codeGen();
   }
   code += "}\n";
   return code;
}

StatementPart::StatementPart(CompoundStatement* compoundStatement) : Node() {
   this->compoundStatement = compoundStatement;
}

string StatementPart::codeGen() {
   return this->compoundStatement->codeGen();
}

VariableDeclaration::VariableDeclaration(list<Identifier*>* identifierList, DataType* dataType) : Node() {
   this->identifierList = identifierList;
   this->dataType = dataType;
}

string VariableDeclaration::codeGen() {
   string code = "";
   DataType* dt = this->dataType;
   if (dt->arrayType == 0) { // si es un tipo simple
      for (list<Identifier*>::iterator it = this->identifierList->begin(); it != this->identifierList->end(); ++it) {
         Identifier* id = (*it);
         if (dt->simpleType == SimpleType::INTEGER){
            code += "int " + id->identifier + " = 0;\n";
         } else if (dt->simpleType == SimpleType::BOOLEAN) {
            code += "bool " + id->identifier + " = false\n";
         } else if (dt->simpleType == SimpleType::CHAR) {
            code +=  "string " + id->identifier + " = \"\";\n";
         }
      }
   } else { // si es un tipo array
      for (list<Identifier*>::iterator it = this->identifierList->begin(); it != this->identifierList->end(); ++it) {
         Identifier* id = (*it);
         ArrayType* at = dt->arrayType;
         IndexRange* ir = at->indexRange;
         if (at->simpleType == SimpleType::INTEGER){
            code += "int* " + id->identifier +  " = int[" + to_string(ir->end - ir->begining) +"]\n";
         } else if (at->simpleType == SimpleType::BOOLEAN) {
            code += "bool* " + id->identifier +  " = bool[" + to_string(ir->end - ir->begining) +"]\n";
         } else if (at->simpleType == SimpleType::CHAR) {
            code += "char* " + id->identifier +  " = char[" + to_string(ir->end - ir->begining) +"]\n";
         }
      }
   }
   return code;
}

VariableDeclarationPart::VariableDeclarationPart(list<VariableDeclaration*>* variableDeclarations) : Node() {
   this->variableDeclarations = variableDeclarations;
}

VariableDeclarationPart::VariableDeclarationPart() : Node() {
   this->variableDeclarations = 0;
}

string VariableDeclarationPart::codeGen() {
   string code;
   for (list<VariableDeclaration*>::iterator it = this->variableDeclarations->begin(); it != this->variableDeclarations->end(); ++it){
      VariableDeclaration* varDeclaration = (*it);
      code =varDeclaration->codeGen();
   }
   return code;
}

Block::Block(VariableDeclarationPart* variableDeclarationPart, StatementPart* statementPart) : Node() {
   this->variableDeclarationPart = variableDeclarationPart;
   this->statementPart = statementPart;
}

string Block::codeGen() {
   string code = this->variableDeclarationPart->codeGen() + "\n" + this->statementPart->codeGen() ;
   return code;
}

Program::Program(Identifier* identifier, Block* block) : Node() {
   this->identifier = identifier;
   this->block = block;
}

string Program::codeGen () {
   string code = "#include<stdio.h>\n#include<string.h>\n";
   string blockCode = block->codeGen();
   cout << "Code: " << code + blockCode << endl;
   return code + blockCode;
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

string FunctionBlock::codeGen(){
  block->codeGen();
  return "";
}

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
