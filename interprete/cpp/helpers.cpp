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