#ifndef LEXER_H_
#define LEXER_H_

#include<list>
#include "token.h"

namespace MiniPascal{
  class Lexer{
  public:
      Lexer();
      list<Token*>* tokenize(list<string>* code);
      void getTokensInLine(string line);
      void makeToken();
      void newState(char character);
      void checkKeyword();
      void makeTokenSymbol(char character, char nextChar);
      virtual ~Lexer();
    private:
      string buffer;
      TokenType _state;
      int rowNumber;
      list<Token*>* tokens;
      unsigned int charIterator;
      bool isComment;
  };
};
#endif
