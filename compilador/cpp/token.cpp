#include "../headders/token.h"

namespace MiniPascal{
  Token::Token(TokenType _type, int _row, string _name){
    this->_type = _type;
    this->_row = _row;
    this->_name = _name;
  }

  TokenType Token::getTokenType(){
    return _type;
  }

  int Token::getTokenLocation(){
    return _row;
  }

  string Token::getTokenName(){
    return _name;
  }

  Token::~Token(){}

  Variable::Variable(TokenType _type, int _row, string name, string var_name) : Token(_type, _row, name){
    this->var_name = var_name;
  }

  string Variable::getVariableName(){
    return var_name;
  }

  Variable::~Variable(){}

  VariableString::VariableString(TokenType _type, int _row, string name, string var_name, string value) : Variable(_type, _row, name, var_name){
    this->value = value;
  }

  string VariableString::getVariableValue(){
    return value;
  }

  VariableString::~VariableString(){}

  VariableInt::VariableInt(TokenType _type, int _row, string name, string var_name, int value) : Variable(_type, _row, name, var_name){
    this->value = value;
  }

  int VariableInt::getVariableValue(){
    return value;
  }

  VariableInt::~VariableInt(){}
}
