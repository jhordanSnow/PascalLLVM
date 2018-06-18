#include<headders/analizadorSintactico.h>
#include<iostream>
#include<vector>
#include <ctype.h>

using namespace std;

Program* AnalizadorSintactico::analizar(list<Token*>* tokenList) {
   return AnalizadorSintactico::program(tokenList);
}

Program* AnalizadorSintactico::program(list<Token*>* tokenList) {
   Token* tokenHead = tokenList->front();
   if (tokenHead->getTokenName() == "program") {
      tokenList->pop_front();
   } // else error

   tokenHead = tokenList->front();
   Identifier* i;
   if (tokenHead->getTokenType() == TokenType::IDENTIFIER) {
      tokenList->pop_front();
      i = AnalizadorSintactico::identifier(tokenList);
   }

   tokenHead = tokenList->front();
   if (tokenHead->getTokenName() == ";") {
      tokenList->pop_front();
   }

   tokenHead = tokenList->front();
   Block* b = AnalizadorSintactico::block(tokenList);

   return new Program(i, b);
}

Identifier* AnalizadorSintactico::identifier(list<Token*>* tokenList) {
   Token* tokenHead = tokenList->front();
   tokenList->pop_front();
   return new Identifier(tokenHead->getTokenName());
}

Block* AnalizadorSintactico::block(list<Token*>* tokenList) {
   return new Block(variableDeclarationPart(tokenList),statementPart(tokenList));
}

StatementPart* AnalizadorSintactico::statementPart(list<Token*>* tokenList) {
   return new StatementPart(compoundStatement(tokenList));
}

CompoundStatement* AnalizadorSintactico::compoundStatement(list<Token*>* tokenList) {
   list<Statement*>* statementList = new list<Statement*>();
   statementList->push_back(AnalizadorSintactico::statement(tokenList));
   CompoundStatement* statement = new CompoundStatement(statementList);
   optionalStatements(tokenList,statement);
   Token* tokenHead = tokenList->front();
   if (tokenHead->getTokenName() == "end") {
      tokenList->pop_front();
   }
   return statement;
}

void AnalizadorSintactico::optionalStatements(list<Token*>* tokenList, CompoundStatement* compoundStatement){
   Token* tokenHead = tokenList->front();
   if (tokenHead->getTokenName() == ";"){
     tokenList->pop_front();
     compoundStatement->statementList->push_back(AnalizadorSintactico::statement(tokenList));
     optionalStatements(tokenList, compoundStatement);
   }
   
}

Statement* AnalizadorSintactico::statement(list<Token*>* tokenList){
   Token* tokenHead = tokenList->front();
   if (tokenHead->getTokenName() == "begin" || tokenHead->getTokenName() == "if" || tokenHead->getTokenName() == "while"){
      return new Statement(structuredStatement(tokenList));
   }else{
      return new Statement(simpleStatement(tokenList));
   }
}
SimpleStatement* AnalizadorSintactico::simpleStatement(list<Token*>* tokenList){
   Token* tokenHead = tokenList->front();
   if (tokenHead->getTokenName() == "read"){
      tokenList->pop_front();
      return new SimpleStatement(readStatement(tokenList));
   }else if(tokenHead->getTokenName() == "write"){
      tokenList->pop_front();
      return new SimpleStatement(writeStatement(tokenList));
   }else{
      return new SimpleStatement(assignmentStatement(tokenList));
   }
}

AssignmentStatement* AnalizadorSintactico::assignmentStatement(list<Token*>* tokenList){
   Token* tokenHead = tokenList->front();
   VariableNT* variable = AnalizadorSintactico::variable(tokenList);
   tokenHead = tokenList->front();
   if (tokenHead->getTokenName() == ":="){
      tokenList->pop_front();
      Expression* expression = AnalizadorSintactico::expression(tokenList);
      return new AssignmentStatement(variable, expression);
   }else{
      return new AssignmentStatement(variable, NULL);
   }
}

ReadStatement* AnalizadorSintactico::readStatement(list<Token*>* tokenList){
   Token* tokenHead = tokenList->front();
   if (tokenHead->getTokenName() == "("){
      tokenList->pop_front();
      list<VariableNT*>* variableList = new list<VariableNT*>();
      variableList->push_back(variable(tokenList));      
      ReadStatement* readStatement = new ReadStatement(variableList);
      optionalVariables(tokenList,readStatement);
      tokenHead = tokenList->front();
      if (tokenHead->getTokenName() == ")"){
         tokenList->pop_front();
         return readStatement;
      }
   }
   return NULL;
}

void AnalizadorSintactico::optionalVariables(list<Token*>* tokenList, ReadStatement* readStatement){
   Token* tokenHead = tokenList->front();
   if (tokenHead->getTokenName() == ","){
      tokenList->pop_front();
      readStatement->variableList->push_back(variable(tokenList));
      optionalVariables(tokenList,readStatement);
   }
}

WriteStatement* AnalizadorSintactico::writeStatement(list<Token*>* tokenList){
   Token* tokenHead = tokenList->front();
   if (tokenHead->getTokenName() == "("){
      tokenList->pop_front();
      list<VariableNT*>* variableList = new list<VariableNT*>();
      variableList->push_back(variable(tokenList)); 
      WriteStatement* writeStatement = new WriteStatement(variableList);
      optionalVariables(tokenList,writeStatement);
      if (tokenHead->getTokenName() == ")"){
         tokenList->pop_front();
         return writeStatement;
      }
   }
   return NULL;
}

void AnalizadorSintactico::optionalVariables(list<Token*>* tokenList, WriteStatement* writeStatement){
   Token* tokenHead = tokenList->front();
   if (tokenHead->getTokenName() == ","){
      tokenList->pop_front();
      writeStatement->variableList->push_back(variable(tokenList));
      optionalVariables(tokenList,writeStatement);
   }
}

StructuredStatement* AnalizadorSintactico::structuredStatement(list<Token*>* tokenList){
   Token* tokenHead = tokenList->front();
   tokenList->pop_front();
   if (tokenHead->getTokenName() == "begin"){      
      return new StructuredStatement(compoundStatement(tokenList));
   }else if(tokenHead->getTokenName() == "if"){
      return new StructuredStatement(ifStatement(tokenList));
   }else if(tokenHead->getTokenName() == "while"){
      return new StructuredStatement(whileStatement(tokenList));
   }
   return NULL;
}

IfStatement* AnalizadorSintactico::ifStatement(list<Token*>* tokenList){
   Expression* ifExpression = AnalizadorSintactico::expression(tokenList);
   Token* tokenHead = tokenList->front();
   if (tokenHead->getTokenName() == "then"){
      tokenList->pop_front();
      Statement* thenStatement = AnalizadorSintactico::statement(tokenList);
      tokenHead = tokenList->front();
      if (tokenHead->getTokenName() == "else"){
         tokenList->pop_front();
         Statement* elseStatement = AnalizadorSintactico::statement(tokenList);
         return new IfStatement(ifExpression, thenStatement, elseStatement);
      }else{
         return new IfStatement(ifExpression, thenStatement);
      }
   }
   return NULL;
}

WhileStatement* AnalizadorSintactico::whileStatement(list<Token*>* tokenList){
   Expression* whileExpression = AnalizadorSintactico::expression(tokenList);
   Token* tokenHead = tokenList->front();
   if (tokenHead->getTokenName() == "do"){
      tokenList->pop_front();
      Statement* doStatement = AnalizadorSintactico::statement(tokenList);
      return new WhileStatement(whileExpression, doStatement);
   }
   return NULL;
}


VariableDeclarationPart* AnalizadorSintactico::variableDeclarationPart(list<Token*>* tokenList) {
   Token* tokenHead = tokenList->front();
   if (tokenHead->getTokenName() == "var") {
      tokenList->pop_front();
   }
   list<VariableDeclaration*>* variableDeclarations = new list<VariableDeclaration*>();
   tokenHead = tokenList->front();
   variableDeclarations->push_back(variableDeclaration(tokenList));
   VariableDeclarationPart* variableDeclarationPart = new VariableDeclarationPart(variableDeclarations);
   optionalVariableDeclarationsPart(tokenList, variableDeclarationPart);
   return variableDeclarationPart;
}

void AnalizadorSintactico::optionalVariableDeclarationsPart(list<Token*>* tokenList, VariableDeclarationPart* variableDeclarationPart) {
  Token* tokenHead = tokenList->front();
	if (tokenHead->getTokenType() == TokenType::IDENTIFIER) {
     variableDeclarationPart->variableDeclarations->push_back(variableDeclaration(tokenList));
	}	
}


VariableDeclaration* AnalizadorSintactico::variableDeclaration(list<Token*>* tokenList) {
   Token* tokenHead = tokenList->front();
   std::list<Identifier*>* identifierList = new list<Identifier*>();
   identifierList->push_back(new Identifier(tokenHead->getTokenName()));
   optionalVariableDeclarations(tokenList, identifierList);
   tokenHead = tokenList->front();
   DataType* dataType = AnalizadorSintactico::dataType(tokenList);
   return new VariableDeclaration(identifierList,dataType);
}

 void AnalizadorSintactico::optionalVariableDeclarations(list<Token*>* tokenList, std::list<Identifier*>* identifierList){
   Token* tokenHead = tokenList->front();
   tokenList->pop_front();
   if (tokenHead->getTokenName() == ":") {
      return;
   }else if (tokenHead->getTokenName() == ",") {
      identifierList->push_back(new Identifier(tokenHead->getTokenName()));
      return optionalVariableDeclarations(tokenList, identifierList);
   }
   //error
 }

DataType* AnalizadorSintactico::dataType(list<Token*>* tokenList){
   Token* tokenHead = tokenList->front();
   if (tokenHead->getTokenName() == "char" || tokenHead->getTokenName() == "integer"|| tokenHead->getTokenName() == "boolean") {
      return new DataType(simpleType(tokenList));
   }else{
      return new DataType(arrayType(tokenList));
   }
}

ArrayType* AnalizadorSintactico::arrayType(list<Token*>* tokenList){
   Token* tokenHead = tokenList->front();
   if (tokenHead->getTokenName() == "array"){
      tokenList->pop_front();
      tokenHead = tokenList->front();
      if (tokenHead->getTokenName() == "["){
         tokenList->pop_front();
         IndexRange* index = indexRange(tokenList);
         tokenHead = tokenList->front();
         tokenList->pop_front();
         Token* tokenHead2 = tokenList->front();
         if (tokenHead->getTokenName() == "]" && tokenHead2->getTokenName() == "of"){
            tokenList->pop_front();
            SimpleType type = simpleType(tokenList);
            return new ArrayType(index, type);
         }
      }
   }
   return NULL;
}

IndexRange* AnalizadorSintactico::indexRange(list<Token*>* tokenList){
   Token* tokenHead = tokenList->front();
   std::locale loc;
   if (isdigit(tokenHead->getTokenName(), loc)) {
      int begin = atoi(tokenHead->getTokenName().data());
      tokenList->pop_front();
      tokenHead = tokenList->front();
      if (tokenHead->getTokenName() == "..") {
        tokenList->pop_front();
        tokenHead = tokenList->front();
        if (isdigit(tokenHead->getTokenName(), loc)) {
          tokenList->pop_front();
          int end = atoi(tokenHead->getTokenName().data());
          return new IndexRange(begin,end);
        }
      }   
   }  
   return NULL;
}

SimpleType AnalizadorSintactico::simpleType(list<Token*>* tokenList){
   Token* tokenHead = tokenList->front();
   tokenList->pop_front();
   if (tokenHead->getTokenName() == "char") {
      return SimpleType::CHAR;
   }else if (tokenHead->getTokenName() == "integer") {
      return SimpleType::INTEGER;
   }else if (tokenHead->getTokenName() == "boolean") {
      return SimpleType::BOOLEAN;
   }
   return SimpleType::UNKNOWN;
}

TypeIdentifier* AnalizadorSintactico::typeIdentifier(list<Token*>* tokenList){
   return new TypeIdentifier(identifier(tokenList));
}

VariableNT* AnalizadorSintactico::variable(list<Token*>* tokenList){
   // return new Variable();
   Token* tokenHead = tokenList->front();
   tokenList->pop_front();
   Token* brackets = tokenList->front();
   if (brackets->getTokenName() == "["){
      tokenList->push_back(brackets);
      tokenList->push_back(tokenHead);
      return new VariableNT(indexedVariable(tokenList));
   }else{
      tokenList->push_front(brackets);
      tokenList->push_front(tokenHead);
      return new VariableNT(entireVariable(tokenList));
   }
}

EntireVariable* AnalizadorSintactico::entireVariable(list<Token*>* tokenList){
   return new EntireVariable(variableIdentifier(tokenList));
}
VariableIdentifier* AnalizadorSintactico::variableIdentifier(list<Token*>* tokenList){
   return new VariableIdentifier(identifier(tokenList));
}

IndexedVariable* AnalizadorSintactico::indexedVariable(list<Token*>* tokenList){
   ArrayVariable* array = arrayVariable(tokenList);
   Token* tokenHead = tokenList->front();
   tokenList->pop_front();
   if (tokenHead->getTokenName() == "[") {
      Expression* expression = AnalizadorSintactico::expression(tokenList);
      tokenHead = tokenList->front();
      if (tokenHead->getTokenName() == "]") {
         tokenList->pop_front();
         return new IndexedVariable(array, expression);
      }else{
        //No hay cerrar parentesis ]
      }
   }//no hay
   return NULL;

}

ArrayVariable* AnalizadorSintactico::arrayVariable(list<Token*>* tokenList){
   return new ArrayVariable(entireVariable(tokenList));
}

Expression* AnalizadorSintactico::expression(list<Token*>* tokenList){
   SimpleExpression* firstExp = simpleExpression(tokenList);
   Token* tokenHead = tokenList->front();
   RelationalOperator op = Helpers::stringToRelationalOperator(tokenHead->getTokenName());
   if (op!= RelationalOperator::UNKNOWN){
      tokenList->pop_front();
      SimpleExpression* secondExp = simpleExpression(tokenList);
      return new Expression(firstExp,op, secondExp);
   }
   return new Expression(firstExp);
}
SimpleExpression* AnalizadorSintactico::simpleExpression(list<Token*>* tokenList){
   Token* tokenHead = tokenList->front();
   std::list<Term*>* terms = new list<Term*>();
   std::list<AdditionOperator>* operators = new list<AdditionOperator>();
   Sign sign = Helpers::stringToSign(tokenHead->getTokenName()); 
   terms->push_back(term(tokenList));
   SimpleExpression* expression = new SimpleExpression(sign,terms,operators);
   optionalTerms(tokenList,expression);
   return expression;
}

void AnalizadorSintactico::optionalTerms(list<Token*>* tokenList,SimpleExpression* simpleExpression){
  string token = tokenList->front()->getTokenName();
  AdditionOperator op = Helpers::stringToAdditionOperator(token); 
  if (op!= AdditionOperator::UNKNOWN){ 
   simpleExpression->additionOperators->push_back(op);
   tokenList->pop_front();
   Term* secondTerm = term(tokenList);
   simpleExpression->terms->push_back(secondTerm);
   optionalTerms(tokenList,simpleExpression);
  }
}

Term* AnalizadorSintactico::term(list<Token*>* tokenList){
   std::list<AbstractFactor*>* factors = new list<AbstractFactor*>();
   std::list<MultiplicationOperator>* operators = new list<MultiplicationOperator>();
   AbstractFactor* firstFactor = factor(tokenList);
   factors->push_back(firstFactor);
   Term* term = new Term(factors,operators);
   optionalFactors(tokenList,term);
   return term;
}

void AnalizadorSintactico::optionalFactors(list<Token*>* tokenList,Term* term){
   string token = tokenList->front()->getTokenName();
   MultiplicationOperator op = Helpers::stringToMultiplicationOperator(token); 
   if (op!= MultiplicationOperator::UNKNOWN){ 
      term->operators->push_back(op);
      tokenList->pop_front();
      AbstractFactor* secondFactor = factor(tokenList);
      term->factors->push_back(secondFactor);
      optionalFactors(tokenList,term);
   }
}

AbstractFactor* AnalizadorSintactico::factor(list<Token*>* tokenList){
   Token* tokenHead = tokenList->front();
   tokenList->pop_front();
   std::locale loc;
   //if variable{} if constant identifier

   if (tokenHead->getTokenName() == "\'" || tokenHead->getTokenName() == "\"") { //constant string
      tokenHead = tokenList->front();
      tokenList->pop_front();
      tokenList->pop_front();
      return new Factor(new Constant(tokenHead->getTokenName()));
   }else if (isdigit(tokenHead->getTokenName(), loc)) { //constant digit
      tokenHead = tokenList->front();
      tokenList->pop_front();
      return new Factor(new Constant(atoi(tokenHead->getTokenName().data())));
   }else if (tokenHead->getTokenName() == "not") { //not
      tokenHead = tokenList->front();
      tokenList->pop_front();
      return new NotFactor(factor(tokenList));
   }else if (tokenHead->getTokenName() == "(") { //(expr)
      expression(tokenList);
      tokenHead = tokenList->front();
      if (tokenHead->getTokenName() == ")") {
         tokenList->pop_front();
      }
   }else{
      return new Factor(new VariableNT(entireVariable(tokenList)));
   }
  return new Factor(new Constant(0));
}


