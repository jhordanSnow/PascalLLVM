#ifndef TOKEN_H_
#define TOKEN_H_

#include <string>

using namespace std;

namespace MiniPascal{
  enum class TokenType{
    IDENTIFIER,
    DIGIT,
    SYMBOL,
    KEYWORDS,
    UNKNOWN
  };

  class Token{
    public:
      Token(TokenType _type, int _row, string name);
      TokenType getTokenType();
      int getTokenLocation();
      string getTokenName();
      virtual ~Token();
    protected:
      TokenType _type;
      int _row;
      string _name;
  };

  class Variable: Token{
    public:
      Variable(TokenType _type, int _row, string name, string var_name);
      string getVariableName();
      virtual ~Variable();
    protected:
      string var_name;
  };

  class VariableString: Variable{
    public:
      VariableString(TokenType _type, int _row, string name, string var_name, string value);
      string getVariableValue();
      virtual ~VariableString();
    protected:
      string value;
  };

  class VariableInt: Variable{
    public:
      VariableInt(TokenType _type, int _row, string name, string var_name, int value);
      int getVariableValue();
      virtual ~VariableInt();
    protected:
      int value;
  };
}

#endif
