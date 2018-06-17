#include <map>
#include <string>
#include <headders/ast.h>

using namespace std;
class EnvVariable {
   public:
      EnvVariable(string idnetifier);
      string getIdentifier();
   protected:
      string identifier;
};

class IntVariable : EnvVariable {
   public:
      IntVariable(string idnetifier, int value);
      int getValue();
   protected:
      int value;
};

class CharVariable : EnvVariable {
   public:
      CharVariable(string idnetifier, char value);
      char getValue();
   protected:
      char value;
};

class BoolVariable : EnvVariable {
   public:
      BoolVariable(string idnetifier, bool value);
      bool getValue();
   protected:
      bool value;
};

class Enviroment {
   public:
      static Enviroment* getInstance();
      void addInt(string identifier, int value);
      void addBool(string identifier, bool value);
      void addChar(string identifier, char value);
      bool existes(string idnetifier);
      EnvVariable* getVariable(string identifier);
   private:
      Enviroment();
      static Enviroment* instance;
      map<string,EnvVariable> variables;
};
