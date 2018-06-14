#include<iostream>
#include<fstream>
#include<string>
#include<list>

using namespace std;
int main(int argc, char** argv) {
   if (argc != 2) {
      cout << "uso " << argv [0] << " <NombreArchivo>";
      return -1;
   }

   ifstream codefile (argv[1]);
   string line;
   list<string>* code = new list<string>();
   if (codefile.is_open()) {
      while (getline(codefile, line)) {
         code->push_front(line);
      }
      codefile.close();
   } else {
      cout << "No se abrio ningun archivo";
   }

   cout << code->size() << endl;

   return 0;
}
