#include<iostream>
#include<fstream>
#include<string>
#include<list>

#include "headders/ast.h"
#include "headders/lexer.h"

using namespace std;
using namespace MiniPascal;

void reportError(string error){
  std::cout << error << '\n';
}

list<string>* getInputStream(string fileName){
  ifstream codefile (fileName);
  string line;
  list<string>* code = new list<string>();

  if (codefile.is_open()) {
     while (getline(codefile, line)) {
        code->push_back(line);
     }
     codefile.close();
  } else {
     reportError("No se abrio ningun archivo");
  }

  return code;
}

Program* ArbolEjemplo () {
   list<Identifier>* identifierList = new list<Identifier>();
   identifierList->push_front(Identifier("a"));
   identifierList->push_front(Identifier("b"));
   identifierList->push_front(Identifier("c"));
   identifierList->push_front(Identifier("d"));

   list<VariableDeclaration>* variableDeclarationsList = new list<VariableDeclaration>();
   variableDeclarationsList->push_front(VariableDeclaration(identifierList, new DataType(SimpleType::INTEGER)));

   list<VariableNT>* variableListRead = new list<VariableNT>();
   variableListRead->push_front(VariableNT(new EntireVariable(new VariableIdentifier(new Identifier("a")))));
   variableListRead->push_front(VariableNT(new EntireVariable(new VariableIdentifier(new Identifier("b")))));
   variableListRead->push_front(VariableNT(new EntireVariable(new VariableIdentifier(new Identifier("c")))));
   variableListRead->push_front(VariableNT(new EntireVariable(new VariableIdentifier(new Identifier("d")))));

   list<Statement>* statementList = new list<Statement>();
   statementList->push_front(
         Statement(
            new SimpleStatement(
               new ReadStatement(
                     variableListRead
                  )
               )
            )
         );

   Program* p = new Program(
         new Identifier("ejemplo"),
         new Block(
            new VariableDeclarationPart(variableDeclarationsList),
            new StatementPart(
               new CompoundStatement(statementList)
               )
            )
         );
   return p;
}

int main(int argc, char** argv) {
   if (argc != 2) {
      reportError("uso " + string(argv[0]) + " <NombreArchivo>");
      return -1;
   }

   Lexer* lexer = new Lexer();

   list<string>* code = getInputStream(argv[1]);
   list<Token*>* tokens = lexer->tokenize(code);

   for (list<Token*>::iterator it = tokens->begin(); it != tokens->end(); ++it){
      Token* t = (*it);
      std::cout << t->getTokenLocation() << ": " << t->getTokenName() << "\n";
   }

   std::cout << "Tokens - " << tokens->size() << '\n';

   Program* p = ArbolEjemplo();
   cout << "identificador" << p->identifier->identifier << endl;

   return 0;
}
