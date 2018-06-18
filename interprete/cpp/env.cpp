#include <headders/env.h>
#include <stdlib.h>
#include <stdio.h>

EnvVariable::EnvVariable(string identifier) {
   this->identifier = identifier;
}

string EnvVariable::getIdentifier() {
   return this->identifier;
}

int EnvVariable::getType() {
   return this->type;
}

IntVariable::IntVariable(string identifier, int value) : EnvVariable(identifier) {
   this->value = value;
   this->type = 1;
}

int IntVariable::getValue() {
   return this->value;
}

void IntVariable::setValue(int value) {
   this->value = value;
}

string IntVariable::toString() {
   return to_string(this->value);
}

StringVariable::StringVariable(string identifier, string value) : EnvVariable(identifier) {
   this->value = value;
   this->type = 3;
}

string StringVariable::getValue() {
   return this->value;
}

void StringVariable::setValue(string value) {
   this->value = value;
}

string StringVariable::toString() {
   return getValue();
}

BoolVariable::BoolVariable(string identifier, bool value) : EnvVariable(identifier) {
   this->value = value;
   this->type = 2;
}

bool BoolVariable::getValue() {
   return this->value;
}

void BoolVariable::setValue(bool value) {
   this->value = value;
}

string BoolVariable::toString() {
   if (value) {
      return "true";
   }
   return "false";
}

ArrayVariableEnv::ArrayVariableEnv(string identifier, int begining, int end, int type) : EnvVariable(identifier) {
   this->type = type;
   this->begining = begining;
   this->end = end;
   if (type == 1) {
      intArray = new int[end-begining];
      boolArray = 0;
      stringArray = 0;
   } else if (type == 2) {
      intArray = 0;
      boolArray = new bool[end-begining];
      stringArray = 0;
   } else {
      intArray = 0;
      boolArray = 0;
      stringArray = new string[end-begining];
   }
}

int ArrayVariableEnv::getType() {
   return this->type;
}

int ArrayVariableEnv::getInt(int index) {
   return intArray[index];
}

string ArrayVariableEnv::getString(int index) {
   return stringArray[index];
}

bool ArrayVariableEnv::getBool(int index) {
   return boolArray[this->begining + index];
}

void ArrayVariableEnv::setInt(int index, int value) {
   this->intArray[this->begining + index] = value;
}

void ArrayVariableEnv::setString(int index, string value) {
   this->stringArray[this->begining + index] = value;
}

void ArrayVariableEnv::setBool(int index, bool value) {
  this->boolArray[index] = value;
}

string ArrayVariableEnv::toString() {
   char buffer [40];
   sprintf(buffer, "Array: type=%i; range=[%i-%i]", type, begining, end);
   return string(buffer);
}

//singleton
Enviroment* Enviroment::instance = 0;

Enviroment::Enviroment() {}

Enviroment* Enviroment::getInstance() {
   if (instance == 0){
      instance = new Enviroment();
   }
   return instance;
}

void Enviroment::addInt(string identifier, int value){
   IntVariable* i = new IntVariable(identifier, value);
   variables[identifier] = i;
}

void Enviroment::addBool(string identifier, bool value){
   BoolVariable* b = new BoolVariable(identifier, value);
   variables[identifier] = b;
}

void Enviroment::addString(string identifier, string value){
   StringVariable* s = new StringVariable(identifier, value);
   variables[identifier] = s;
}

void Enviroment::addArray(string identifier, int begining, int end, int type) {
   ArrayVariableEnv* av = new ArrayVariableEnv(identifier, begining, end, type);
   variables[identifier] = av;
}

void Enviroment::print() {
   for (map<string, EnvVariable*>::iterator it= this->variables.begin(); it != this->variables.end(); ++it){;
      EnvVariable* ev = (it->second);
      cout << ev->getIdentifier() << " : "<< ev->toString() << endl;;
   }
}

bool Enviroment::exists(string identifier) {
   return variables.count(identifier) > 0;
}

EnvVariable* Enviroment::getVariable(string identifier) {
   return variables[identifier];
}
