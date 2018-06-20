#include<headders/analizadorSintactico.h>
#include<iostream>
#include<vector>
#include<ctype.h>
#include <algorithm>

using namespace std;

AnalizadorSintactico::AnalizadorSintactico(){
  procedures = new list<Function*>();
  procedureNames = new list<string>();
}

Program* AnalizadorSintactico::analizar(list<Token*>* tokenList) {
   return AnalizadorSintactico::program(tokenList);
}

Program* AnalizadorSintactico::program(list<Token*>* tokenList) {
   Token* tokenHead = tokenList->front();
   string expected = "program";
   if (tokenHead->getTokenName() == expected) {
      tokenList->pop_front();
   }else{
     errorMsgTkn(expected, tokenHead);
   }

   tokenHead = tokenList->front();
   Identifier* i;
   if (tokenHead->getTokenType() == TokenType::IDENTIFIER) {
      i = AnalizadorSintactico::identifier(tokenList);
   }

   tokenHead = tokenList->front();
   if (tokenHead->getTokenName() == ";") {
      tokenList->pop_front();
   }else{
     errorMsgTkn(";", tokenHead);
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
  VariableDeclarationPart* VD = variableDeclarationPart(tokenList);
  if (tokenList->front()->getTokenName() == "function"  || tokenList->front()->getTokenName() == "procedure"){
    functionsPart(tokenList);
  }
  return new Block(VD, statementPart(tokenList));
}

void AnalizadorSintactico::functionsPart(list<Token*>* tokenList){
  Token* type = tokenList->front();
  tokenList->pop_front();
  Token* name = tokenList->front();
  procedureNames->push_back(name->getTokenName());
  tokenList->pop_front();
  list<VariableDeclaration*>* variableDeclarations = functionVariables(tokenList);
  if (type->getTokenName() == "procedure"){
    StatementPart* statPart = statementPart(tokenList);
    Token* tokenHead = tokenList->front();
    if (tokenHead->getTokenName() == ";"){
      tokenList->pop_front();
    }else{
        errorMsgTkn(";", tokenHead);
    }
    this->procedures->push_back(new Function(variableDeclarations, statPart));
  }else if (type->getTokenName() == "function"){
    errorMsg("Functions are not supported");
  }
}

list<VariableDeclaration*>* AnalizadorSintactico::functionVariables(list<Token*>* tokenList){
  Token* tokenHead = tokenList->front();
  list<VariableDeclaration*>* variableDeclarations = new list<VariableDeclaration*>();
  if (tokenHead->getTokenName() == "("){
    tokenList->pop_front();
    tokenList->push_front(new Token(TokenType::UNKNOWN, 420, "var"));
    VariableDeclarationPart* vdp = variableDeclarationPart(tokenList);
    variableDeclarations = vdp->variableDeclarations;
    tokenHead = tokenList->front();
    if (tokenHead->getTokenName() == ")"){
      tokenList->pop_front();
      tokenHead = tokenList->front();
      if (tokenHead->getTokenName() == ";"){
        tokenList->pop_front();
      }else{
          errorMsgTkn(";", tokenHead);
      }
    }else{
      errorMsgTkn(")", tokenHead);
    }
  }else{
    errorMsgTkn("(", tokenHead);
  }

  return variableDeclarations;
}

VariableDeclarationPart* AnalizadorSintactico::variableDeclarationPart(list<Token*>* tokenList) {
   Token* tokenHead = tokenList->front();
   if (tokenHead->getTokenName() == "var") {
      tokenList->pop_front();
      list<VariableDeclaration*>* variableDeclarations = new list<VariableDeclaration*>();
      tokenHead = tokenList->front();
      variableDeclarations->push_back(variableDeclaration(tokenList));
      VariableDeclarationPart* variableDeclarationPart = new VariableDeclarationPart(variableDeclarations);
      tokenHead = tokenList->front();
      if (tokenHead->getTokenName() == ";") {
          tokenList->pop_front();
      }else{
        if (tokenHead->getTokenName() != ")"){
          errorMsgTkn(";", tokenHead);
        }
      }
      optionalVariableDeclarationsPart(tokenList, variableDeclarationPart);
      return variableDeclarationPart;
   }else{
     errorMsgTkn("var", tokenHead);
   }
   return NULL;
}

void AnalizadorSintactico::optionalVariableDeclarationsPart(list<Token*>* tokenList, VariableDeclarationPart* variableDeclarationPart) {
  Token* tokenHead = tokenList->front();
  if (tokenHead->getTokenName() != "function" && tokenHead->getTokenName() != "procedure"){
    if (tokenHead->getTokenType() == TokenType::IDENTIFIER) {
      variableDeclarationPart->variableDeclarations->push_back(variableDeclaration(tokenList));
      tokenHead = tokenList->front();
      if (tokenHead->getTokenName() == ";") {
        tokenList->pop_front();
        optionalVariableDeclarationsPart(tokenList, variableDeclarationPart);
      }else{
        if (tokenHead->getTokenName() != ")"){
          errorMsgTkn(";", tokenHead);
        }
      }
    }
  }
}


VariableDeclaration* AnalizadorSintactico::variableDeclaration(list<Token*>* tokenList) {
   std::list<Identifier*>* identifierList = new list<Identifier*>();
   identifierList->push_back(identifier(tokenList));
   optionalVariableDeclarations(tokenList, identifierList);
   DataType* dataType = AnalizadorSintactico::dataType(tokenList);
   return new VariableDeclaration(identifierList,dataType);
}

 void AnalizadorSintactico::optionalVariableDeclarations(list<Token*>* tokenList, std::list<Identifier*>* identifierList){
   Token* tokenHead = tokenList->front();
   tokenList->pop_front();
   if (tokenHead->getTokenName() == ":") {
      return;
   }else if (tokenHead->getTokenName() == ",") {
      identifierList->push_back(identifier(tokenList));
      return optionalVariableDeclarations(tokenList, identifierList);
   }else{
     errorMsgTkn(",", tokenHead);
   }
 }

DataType* AnalizadorSintactico::dataType(list<Token*>* tokenList){
   Token* tokenHead = tokenList->front();
   if (tokenHead->getTokenName() == "char" || tokenHead->getTokenName() == "integer"|| tokenHead->getTokenName() == "boolean") {
      return new DataType(simpleType(tokenList));
   }else{
      return new DataType(arrayType(tokenList));
   }
}

StatementPart* AnalizadorSintactico::statementPart(list<Token*>* tokenList) {
  Token* tokenHead = tokenList->front();
  if (tokenHead->getTokenName() == "begin"){
    tokenList->pop_front();
    return new StatementPart(compoundStatement(tokenList));
  }else{
    errorMsgTkn("begin", tokenHead);
  }
  return NULL;
}

CompoundStatement* AnalizadorSintactico::compoundStatement(list<Token*>* tokenList) {
   list<Statement*>* statementList = new list<Statement*>();
   statementList->push_back(AnalizadorSintactico::statement(tokenList));
   CompoundStatement* statement = new CompoundStatement(statementList);
   optionalStatements(tokenList,statement);
   Token* tokenHead = tokenList->front();
   if (tokenHead->getTokenName() == "end") {
      tokenList->pop_front();
   }else{
     errorMsgTkn("end", tokenHead);
   }
   return statement;
}

void AnalizadorSintactico::optionalStatements(list<Token*>* tokenList, CompoundStatement* compoundStatement){
   Token* tokenHead = tokenList->front();
   if (tokenHead->getTokenName() == ";"){
     tokenList->pop_front();
     compoundStatement->statementList->push_back(AnalizadorSintactico::statement(tokenList));
     optionalStatements(tokenList, compoundStatement);
   }else{
     if (tokenHead->getTokenName() != "end"){
       errorMsgTkn(";", tokenHead);
     }
   }
}

Statement* AnalizadorSintactico::statement(list<Token*>* tokenList){
   Token* tokenHead = tokenList->front();
   int indexProcedure = getIndexProcedure(this->procedureNames, tokenHead->getTokenName());
   if (tokenHead->getTokenName() == "begin" || tokenHead->getTokenName() == "if" || tokenHead->getTokenName() == "while"){
      return new Statement(structuredStatement(tokenList));
   }else if (indexProcedure >= 0){
      tokenList->pop_front();
      return new Statement(procedureStatement(tokenList, indexProcedure));
   }else{
      return new Statement(simpleStatement(tokenList));
   }
}

int AnalizadorSintactico::getIndexProcedure(list<string>* procedureNames, string name){
  int i = 0;
  for (list<string>::iterator currentName = procedureNames->begin(); currentName != procedureNames->end(); ++currentName){
    if ((*currentName) == name){
      return i;
    }
    i++;
  }
  return -1;
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
      errorMsgTkn(":=", tokenHead);
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
      }else{
        errorMsgTkn(")", tokenHead);
      }
   }else{
     errorMsgTkn("(", tokenHead);
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
      tokenHead = tokenList->front();
      if (tokenHead->getTokenName() == ")"){
         tokenList->pop_front();
         return writeStatement;
      }else{
        errorMsgTkn(")", tokenHead);
      }
   }else{
     errorMsgTkn("(", tokenHead);
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

int AnalizadorSintactico::getCantParams(list<VariableDeclaration*>* varaibleDecaraions){
  int cant = 0;
  for (list<VariableDeclaration*>::iterator it = varaibleDecaraions->begin(); it != varaibleDecaraions->end(); ++it) {
    cant += (*it)->identifierList->size();
  }
  return cant;
}

StructuredStatement* AnalizadorSintactico::procedureStatement(list<Token*>* tokenList, int index){
  Token* tokenHead = tokenList->front();
  tokenList->pop_front();

  list<Function*>::iterator fncIt = this->procedures->begin();
  advance(fncIt, index);
  Function* fnc = *fncIt;
  int cantParams = getCantParams(fnc->variableDeclarations);
  CompoundStatement* stateFnc = new CompoundStatement(new list<Statement*>(*fnc->statement->compoundStatement->statementList));

  if (tokenHead->getTokenName() == "("){
    int i = 0;
    for (list<VariableDeclaration*>::iterator it = fnc->variableDeclarations->begin(); it != fnc->variableDeclarations->end(); ++it) {
      VariableDeclaration* varDeclaration = *it;
      for (list<Identifier*>::iterator it2 = varDeclaration->identifierList->begin(); it2 != varDeclaration->identifierList->end(); ++it2) {
        i++;
        tokenHead = tokenList->front();
        list<Token*>* tmpTokenList = new list<Token*>();
        tmpTokenList->push_back(new Token(TokenType::IDENTIFIER, tokenHead->getTokenLocation(), (*it2)->identifier));
        tmpTokenList->push_back(new Token(TokenType::SYMBOL, tokenHead->getTokenLocation(), ":="));
        tmpTokenList->push_back(new Token(TokenType::IDENTIFIER, tokenHead->getTokenLocation(), tokenHead->getTokenName()));
        tmpTokenList->push_back(new Token(TokenType::SYMBOL, tokenHead->getTokenLocation(), ";"));

        //stateFnc->statementList->push_front(new Statement(new SimpleStatement(assignmentStatement(tmpTokenList))));

        tokenList->pop_front();
        tokenHead = tokenList->front();
        if (tokenHead->getTokenName() == ")"){
          if (cantParams != i){
            errorMsg("Parameter count does not match in line " + to_string(tokenHead->getTokenLocation()));
          }
        }else{
          if (tokenHead->getTokenName() == ","){
            tokenList->pop_front();
          }else{
            errorMsgTkn(",", tokenHead);
          }
        }
      }
    }
    if (tokenHead->getTokenName() == ","){
      errorMsg("Parameter count does not match in line " + to_string(tokenHead->getTokenLocation()));
    }
    if (tokenHead->getTokenName() == ")"){
      tokenList->pop_front();
      tokenHead = tokenList->front();
      return new StructuredStatement(stateFnc);
    }else{
      errorMsgTkn(")", tokenHead);
    }
   }else{
     errorMsgTkn("(", tokenHead);
   }
   return NULL;
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
   }else{
     errorMsgTkn("then", tokenHead);
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
   }else{
     errorMsgTkn("do", tokenHead);
   }
   return NULL;
}

ArrayType* AnalizadorSintactico::arrayType(list<Token*>* tokenList){
   Token* tokenHead = tokenList->front();
   if (tokenHead->getTokenName() == "array"){
      tokenList->pop_front();
      tokenHead = tokenList->front();
       Token* tokenHead = tokenList->front();
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
   }else{
     errorMsgTkn("array", tokenHead);
   }
   return NULL;
}

IndexRange* AnalizadorSintactico::indexRange(list<Token*>* tokenList){
   Token* tokenHead = tokenList->front();
   if (strtol(tokenHead->getTokenName().data(), NULL, 10) || tokenHead->getTokenName() == "0") {
      int begin = atoi(tokenHead->getTokenName().data());
      tokenList->pop_front();
      tokenHead = tokenList->front();
      if (tokenHead->getTokenName() == "..") {
        tokenList->pop_front();
        tokenHead = tokenList->front();
        if (strtol(tokenHead->getTokenName().data(), NULL, 10)) {
          tokenList->pop_front();
          int end = atoi(tokenHead->getTokenName().data());
          IndexRange* ir = new IndexRange(begin,end);
          return ir;
        }else{
          errorMsgTkn("number", tokenHead);
        }
      }else{
        errorMsgTkn("..", tokenHead);
      }
   }else{
     errorMsgTkn("number", tokenHead);
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
   Token* tokenHead = tokenList->front();
   tokenList->pop_front();
   Token* brackets = tokenList->front();
   if (brackets->getTokenName() == "["){
      tokenList->push_front(tokenHead);
      return new VariableNT(indexedVariable(tokenList));
   }else{
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
   tokenHead = tokenList->front();
   if (tokenHead->getTokenName() == "[") {
      tokenList->pop_front();
      Expression* expression = AnalizadorSintactico::expression(tokenList);
      tokenHead = tokenList->front();
      if (tokenHead->getTokenName() == "]") {
         tokenList->pop_front();
         return new IndexedVariable(array, expression);
      }else{
        errorMsgTkn("]", tokenHead);
      }
   }else{
     errorMsgTkn("[", tokenHead);
   }
   return NULL;

}

ArrayVariable* AnalizadorSintactico::arrayVariable(list<Token*>* tokenList){
   return new ArrayVariable(entireVariable(tokenList));
}

Expression* AnalizadorSintactico::expression(list<Token*>* tokenList){
   Token* tokenHead = tokenList->front();
   SimpleExpression* firstExp = simpleExpression(tokenList);
   tokenHead = tokenList->front();
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
   if (sign != Sign::UNKNOWN){tokenList->pop_front();}else{sign = Sign::POSITIVE;}
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
   //if variable{} if constant identifier
   if (tokenHead->getTokenName() == "\'" || tokenHead->getTokenName() == "\"") { //constant string
      tokenList->pop_front();
      tokenHead = tokenList->front();
      Constant* string = new Constant(tokenHead->getTokenName());
      tokenList->pop_front();
      tokenList->pop_front();
      tokenHead = tokenList->front();
      return new Factor(string);
   }else if (strtol(tokenHead->getTokenName().data(), NULL, 10) || tokenHead->getTokenName() == "0") { //constant digit
      tokenHead = tokenList->front();
      tokenList->pop_front();
      return new Factor(new Constant(atoi(tokenHead->getTokenName().data())));
   }else if (tokenHead->getTokenType() == TokenType::IDENTIFIER) {
      return new Factor(variable(tokenList));
   }else if (tokenHead->getTokenName() == "not") { //not
      tokenHead = tokenList->front();
      tokenList->pop_front();
      return new NotFactor(factor(tokenList));
   }else if (tokenHead->getTokenName() == "(") { //(expr)
      tokenList->pop_front();
      Expression* exp =  expression(tokenList);
      tokenHead = tokenList->front();
      if (tokenHead->getTokenName() == ")") {
         tokenList->pop_front();
         return new Factor(exp);
      }else{
        errorMsgTkn(")", tokenHead);
      }
   }

   return new Factor(new VariableNT(entireVariable(tokenList)));
}

void AnalizadorSintactico::errorMsgTkn(string expected, Token* token){
  string msg = "Syntax error: Expected '" + expected;
  msg += "' at line " + to_string(token->getTokenLocation());
  msg += " got '" + token->getTokenName() + "' instead.";
  errorMsg(msg);
}

void AnalizadorSintactico::errorMsg(string msg){
  std::cout << msg << '\n';
  exit(0);
}
