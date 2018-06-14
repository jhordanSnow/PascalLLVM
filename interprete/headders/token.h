#ifndef TOKEN_H_
#define TOKEN_H_

#include <string>

using namespace std;

namespace MiniPascal{
  enum class TokenType{
    INTEGER,
    REAL,
    BOOLEAN,
    CHAR,
    STRING_LITERAL,

    IDENTIFIER,
    KEYWORDS,
    OPERATORS,
    DELIMITER,
    END_OF_FILE,
    UNKNOWN
  };
  enum class TokenValue{
    PROGRAM,
    BEGIN,
    END,
    OF,
    DO,
    IF,
    THEN,
    ELSE,
    NOT,
    WHILE,
    PROCEDURE,
    FUNCTION,

    RECORD,
    ARRAY,
    TYPE,
    VAR,

    PAREN_LEFT,
    PAREN_RIGHT,
    SQUARE_LEFT,
    SQUARE_RIGHT,
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    COMMA,
    SEMICOLON,
    COLON,
    ASSIGN,
    PERIOD,
    DOT_DOT,
    DIV,
    MOD,

    LESS_OR_EQUAL,
    LESS_THAN,
    GREATER_OR_EQUAL,
    GREATER_THAN,
    EQUAL,
    NOT_EQUAL,

    UNRESERVED
  };

  class Token{
    public:
      Token(TokenType _type, TokenValue _value, int _row, string name);
      TokenType getTokenType();
      TokenValue getTokenValue();
      int getTokenLocation();
      string getTokenName();
      virtual ~Token();
    protected:
      TokenType _type;
      TokenValue _value;
      int _row;
      string _name;
  };

  class Variable: Token{
    public:
      Variable(TokenType _type, TokenValue _value, int _row, string name, string var_name);
      string getVariableName();
      virtual ~Variable();
    protected:
      string var_name;
  };

  class VariableString: Variable{
    public:
      VariableString(TokenType _type, TokenValue _value, int _row, string name, string var_name, string value);
      string getVariableValue();
      virtual ~VariableString();
    protected:
      string value;
  };

  class VariableInt: Variable{
    public:
      VariableInt(TokenType _type, TokenValue _value, int _row, string name, string var_name, int value);
      int getVariableValue();
      virtual ~VariableInt();
    protected:
      int value;
  };
}

#endif
