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
   string line;
   if (codefile.is_open()) {
      while (getline(codefile, line)) {
         cout << line << endl;
      }
      codefile.close();
   } else {
      cout << "No se abrio ningun archivo";
   }


   return 0;
}
