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

