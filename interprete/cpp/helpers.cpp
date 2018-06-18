#include "headders/helpers.h"
using namespace std;

RelationalOperator Helpers::stringToRelationalOperator(std::string string){
    if(string=="="){
        return RelationalOperator::EQ;
    }else if (string=="<>"){
        return RelationalOperator::NEQ;
    }else if (string=="<"){
        return RelationalOperator::LT;
    }else if (string=="<="){
        return RelationalOperator::LEQ;
    }else if (string==">="){
        return RelationalOperator::GEQ;
    }else if (string==">"){
        return RelationalOperator::GT;
    }else if (string=="or"){
        return RelationalOperator::OR;
    }else if (string=="and"){
        return RelationalOperator::AND;
    }else{
        return RelationalOperator::UNKNOWN;
    }
}

Sign Helpers::stringToSign(std::string string){
    if(string=="+"){
        return Sign::POSITIVE;
    }else if (string=="-"){
        return Sign::NEGATIVE;
    }else{
        return Sign::POSITIVE;
    }
}

AdditionOperator Helpers::stringToAdditionOperator(std::string string){
    if(string=="+"){
        return AdditionOperator::ADD;
    }else if (string=="-"){
        return AdditionOperator::SUB;
    }else{
        return AdditionOperator::UNKNOWN;
    }
}


MultiplicationOperator Helpers::stringToMultiplicationOperator(std::string string){
    if(string=="*"){
        return MultiplicationOperator::MUL;
    }else if (string=="/"){
        return MultiplicationOperator::DIV;
    }else{
        return MultiplicationOperator::UNKNOWN;
    }
}

string Helpers::TokenTypeToString(TokenType token){
    switch(token){
        case(TokenType::IDENTIFIER):
            return "Identifier";
            break;
        case(TokenType::DIGIT):
            return "Digit";
            break;
        case(TokenType::KEYWORDS):
            return "Keywords";
            break;
        case(TokenType::SYMBOL):
            return "Symbol";
            break;
        case(TokenType::UNKNOWN):
            return "UNKNOWN";
            break;
        default:
            return "NULL";
            break;
    }
}


string Helpers::SimpleTypeToString(SimpleType token){
    switch(token){
        case(SimpleType::BOOLEAN):
            return "Boolean";
            break;
        case(SimpleType::CHAR):
            return "Char";
            break;
        case(SimpleType::INTEGER):
            return "Int";
            break;
        case(SimpleType::UNKNOWN):
            return "UNKNOWN";
            break;
        default:
            return "NULL";
            break;
    }
}

string Helpers::RelationalOperatorToString(RelationalOperator token){
    switch(token){
        case(RelationalOperator::EQ):
            return "=";
            break;
        case(RelationalOperator::NEQ):
            return "<>";
            break;
        case(RelationalOperator::LT):
            return "<";
            break;
        case(RelationalOperator::LEQ):
            return "<=";
            break;
        case(RelationalOperator::GEQ):
            return ">=";
            break;
        case(RelationalOperator::GT):
            return ">";
            break;
        case(RelationalOperator::OR):
            return "or";
            break;
        case(RelationalOperator::AND):
            return "and";
            break;
        case(RelationalOperator::UNKNOWN):
            return "UNKNOWN";
            break;
        default:
            return "UNKNOWN";
            break;
    }
}