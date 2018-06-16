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
    string symbols = ",;():+-*[]=<>";
    string endWord = "\n ,"+symbols;
    string doubleDelimeters = ":=..//";

    for(unsigned i=0; i < line.length(); ++i){
      char c = line.at(i);

      if (this->buffer == "" && this->_state == TokenType::UNKNOWN){
        newState(c);
        this->buffer = "";
      }

      if (endWord.find(string(1, c)) != string::npos){
        makeToken();
        if (symbols.find(string(1, c)) != string::npos){
          makeTokenSymbol(c);
        }
      }else{
        this->buffer += c;
      }
    }
  }

  void Lexer::makeTokenSymbol(char character){
    this->buffer = string(1, character);
    this->_state = TokenType::SYMBOL;
    makeToken();
  }

  void Lexer::makeToken(){
    if (this->buffer != ""){
      checkKeyword();
      Token* token = new Token(this->_state, TokenValue::UNRESERVED, this->rowNumber, this->buffer);
      this->buffer = "";
      this->_state = TokenType::UNKNOWN;
      this->tokens->push_back(token);
    }
  }

  void Lexer::checkKeyword(){
    string keywords[] = {"div","or","and","not","if","then","else","of","while","do","begin","end","read","write","var","array","function ","procedure","program","true","false","char","integer","boolean"};
    if (find(begin(keywords), end(keywords), this->buffer) != end(keywords)){
      cout << "caca: " << this->buffer << "\n";
      this->_state = TokenType::KEYWORDS;
    }
  }

  void Lexer::newState(char character){
    string numbers = "0123456789";
    if (numbers.find(string(1, character)) != string::npos){
      this->_state = TokenType::DIGIT;
    }else{
      this->_state = TokenType::IDENTIFIER;
    }
  }


  Lexer::~Lexer(){
    delete tokens;
  }
}
