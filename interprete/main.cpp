#include<iostream>
#include<fstream>
#include<string>

using namespace std;
int main(int argc, char** argv) {
   if (argc != 2) {
      cout << "uso " << argv [0] << " <NombreArchivo>";
      return -1;
   }

   ifstream codefile (argv[1]);
   string code;
   if (codefile.is_open()) {
      codefile.seekg(0, ios::end);   
      code.reserve(codefile.tellg());
      codefile.seekg(0, ios::beg);

      code.assign((istreambuf_iterator<char>(codefile)),
            istreambuf_iterator<char>());
      cout << code << endl;
   } else {
      cout << "No se abrio ningun archivo";
   }


   return 0;
}
