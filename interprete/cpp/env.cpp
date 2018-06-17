#include <headders/env.h>

EnvVariable::EnvVariable(string identifier) {
   this->identifier = identifier;
}

string EnvVariable::getIdentifier() {
   return this->identifier;
}

IntVariable::IntVariable(string identifier, int value) : EnvVariable(identifier) {
   this->value = value;
}

int IntVariable::getValue() {
   return this->value;
}

CharVariable::CharVariable(string identifier, char value) : EnvVariable(identifier) {
   this->value = value;
}

char CharVariable::getValue() {
   return this->value;
}

BoolVariable::BoolVariable(string identifier, bool value) : EnvVariable(identifier) {
   this->value = value;
}

bool BoolVariable::getValue() {
   return this->value;
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
