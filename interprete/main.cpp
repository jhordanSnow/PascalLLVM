#include<iostream>
#include<fstream>
#include<string>
#include<list>

using namespace std;

void reportError(string error){
  std::cout << error << '\n';
}

list<string>* getInputStream(string fileName){
  ifstream codefile (fileName);
  string line;
  list<string>* code = new list<string>();

  if (codefile.is_open()) {
     while (getline(codefile, line)) {
        code->push_front(line);
     }
     codefile.close();
  } else {
     reportError("No se abrio ningun archivo");
  }

  return code;
}


int main(int argc, char** argv) {
   if (argc != 2) {
      reportError("uso " + string(argv[0]) + " <NombreArchivo>");
      return -1;
   }

   list<string>* code = getInputStream(argv[1]);

   std::cout << "caca - " << code->size() << '\n';

   return 0;
}
