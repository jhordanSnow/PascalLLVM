#ifndef HELPERS_H_
#define HELPERS_H_
#include "headders/ast.h"
#include "headders/token.h"
using namespace MiniPascal;

class Helpers {
    public:
        static RelationalOperator stringToRelationalOperator(std::string string);
        static Sign stringToSign(std::string string);
        static AdditionOperator stringToAdditionOperator(std::string string);
        static MultiplicationOperator stringToMultiplicationOperator(std::string string);
        static string TokenTypeToString(TokenType type);
        static string SimpleTypeToString(SimpleType type);
        static string RelationalOperatorToString(RelationalOperator type);
        
        

};
#endif
