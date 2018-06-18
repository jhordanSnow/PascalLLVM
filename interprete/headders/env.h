#ifndef ENV_H_
#define ENV_H_

#include <map>
#include <string>
#include <iostream>

using namespace std;

class EnvVariable {
   public:
      virtual string getIdentifier();
      virtual string toString() = 0;
      virtual int getType();
   protected:
      EnvVariable(string idnetifier);
      string identifier;
      int type;
};

class IntVariable : public EnvVariable {
   public:
      IntVariable(string idnetifier, int value);
      int getValue();
      void setValue(int value);
      string toString();
   protected:
      int value;
};

class StringVariable : public EnvVariable {
   public:
      StringVariable(string idnetifier, string value);
      string getValue();
      string toString();
      void setValue(string value);
   protected:
      string value;
};

class BoolVariable : public EnvVariable {
   public:
      BoolVariable(string idnetifier, bool value);
      bool getValue();
      string toString();
      void setValue(bool value);
   protected:
      bool value;
};

class ArrayVariableEnv : public EnvVariable {
   public:
      ArrayVariableEnv(string identifier, int begining, int end, int type);
      string toString();
      int type;
      int begining;
      int end;
      int* intArray;
      string* stringArray;
      bool* boolArray;
};

class Enviroment {
   public:
      static Enviroment* getInstance();
      void addInt(string identifier, int value);
      void addBool(string identifier, bool value);
      void addString(string identifier, string value);
      void addArray(string identifier, int begining, int end, int type);
      bool exists(string idnetifier);
      EnvVariable* getVariable(string identifier);
      void print();
   private:
      Enviroment();
      static Enviroment* instance;
      map<string,EnvVariable*> variables;
};

#endif
