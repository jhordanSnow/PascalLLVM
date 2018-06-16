#include "../headders/lexer.h"
#include<vector>
#include <algorithm>

#include<iostream>
using namespace std;

namespace MiniPascal{
  Lexer::Lexer(){
    this->tokens = new list<Token*>();
    this->_state = TokenType::UNKNOWN;
    this->rowNumber = 1;
    this->buffer = "";
  }

  list<Token*>* Lexer::tokenize(list<string>* code){
    for (list<string>::iterator line = code->begin(); line != code->end(); ++line){
      getTokensInLine(*line + " ");
      this->rowNumber++;
    }
    return this->tokens;
  }

  void Lexer::getTokensInLine(string line){
    string endWord = "\n ,;():+-*/[]=";
    string delimeters = ",;()";
    string doubleDelimeters = ":=..//";

    for(unsigned i=0; i < line.length(); ++i){
      char c = line.at(i);

      if (this->buffer == "" && this->_state == TokenType::UNKNOWN){
        newState(c);
        this->buffer = "";
      }

      if (endWord.find(string(1, c)) != string::npos){
        makeToken();
        if (delimeters.find(string(1, c)) != string::npos){
          makeTokenDelimiter(c);
        }
      }else{
        this->buffer += c;
      }
    }
  }

  void Lexer::makeTokenDelimiter(char character){
    this->buffer = string(1, character);
    this->_state = TokenType::DELIMITER;
    makeToken();
  }

  void Lexer::makeToken(){
    if (this->buffer != ""){
      Token* token = new Token(this->_state, TokenValue::UNRESERVED, this->rowNumber, this->buffer);
      this->buffer = "";
      this->_state = TokenType::UNKNOWN;
      this->tokens->push_back(token);
    }
  }

  void Lexer::newState(char character){



  }


  Lexer::~Lexer(){
    delete tokens;
  }
}
