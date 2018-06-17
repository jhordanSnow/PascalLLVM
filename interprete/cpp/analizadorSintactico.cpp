#include<headders/analizadorSintactico.h>
#include<iostream>

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
      i = AnalizadorSintactico::identifier(tokenList);
   }

   tokenHead = tokenList->front();
   if (tokenHead->getTokenName() == ";") {
      tokenList->pop_front();
   }

   tokenHead = tokenList->front();
   tokenList->pop_front();
   Block* b = AnalizadorSintactico::block(tokenList);

   return new Program(i, b);
}

Identifier* AnalizadorSintactico::identifier(list<Token*>* tokenList) {
   Token* tokenHead = tokenList->front();
   tokenList->pop_front();
   return new Identifier(tokenHead->getTokenName());
}

Block* AnalizadorSintactico::block(list<Token*>* tokenList) {
   Token* tokenHead = tokenList->front();
   if (tokenHead->getTokenName() == "var") {
      tokenList->pop_front();
   } else {
      
   }

   tokenHead = tokenList->front();

   // parche terror para que compile
   return new Block(
      new VariableDeclarationPart({}),
      new StatementPart(
      new CompoundStatement({})
      )
      );

}

VariableDeclarationPart* AnalizadorSintactico::variableDeclarationPart(list<Token*>* tokenList) {
   Token* tokenHead = tokenList->front();
   if (tokenHead->getTokenName() == "var") {
      tokenList->pop_front();
   }
   tokenHead = tokenList->front();
   VariableDeclaration* vd = variableDeclaration(tokenList);
   list<VariableDeclaration*>* variableDeclarations = new list<VariableDeclaration*>();
   variableDeclarations->push_back(vd);
   return new VariableDeclarationPart(variableDeclarations);
}

list<VariableDeclaration*>* AnalizadorSintactico::variableDeclarations(list<Token*>* tokenList) {
   //Variosxd   
   list<VariableDeclaration*>* variableDeclarations = new list<VariableDeclaration*>();
   return variableDeclarations;
}


VariableDeclaration* AnalizadorSintactico::variableDeclaration(list<Token*>* tokenList) {
   Token* tokenHead = tokenList->front();
   tokenList->pop_front();
   std::list<Identifier*>* identifierList = new list<Identifier*>();
   identifierList->push_back(new Identifier(tokenHead->getTokenName()));
   identifierList = optionalVariableDeclarations(tokenList, identifierList);
   tokenHead = tokenList->front();
   tokenList->pop_front();
   DataType* dt;
   if(tokenHead->getTokenName()=="integer"){
      dt = new DataType(SimpleType::INTEGER);
   }else if(tokenHead->getTokenName()=="char"){
      dt = new DataType(SimpleType::CHAR);
   }else if(tokenHead->getTokenName()=="boolean"){
      dt = new DataType(SimpleType::BOOLEAN);
   }else{
      //error
   }
   if (tokenHead->getTokenName() == ";") {
      tokenList->pop_front();
   }
   return new VariableDeclaration(identifierList,dt);
}

 std::list<Identifier*>* AnalizadorSintactico::optionalVariableDeclarations(list<Token*>* tokenList, std::list<Identifier*>* identifierList){
   Token* tokenHead = tokenList->front();
   tokenList->pop_front();
   if (tokenHead->getTokenName() == ":") {
      return identifierList;
   }else if (tokenHead->getTokenName() == ",") {
      identifierList->push_back(new Identifier(tokenHead->getTokenName()));
      return optionalVariableDeclarations(tokenList, identifierList);
   }
   //error
   return identifierList;
 }

