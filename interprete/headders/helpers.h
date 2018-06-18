#ifndef HELPERS_H_
#define HELPERS_H_
#include "headders/ast.h"

class Helpers {
    public:
        static RelationalOperator stringToRelationalOperator(std::string string);
        static Sign stringToSign(std::string string);
        static AdditionOperator stringToAdditionOperator(std::string string);
        static MultiplicationOperator stringToMultiplicationOperator(std::string string);

};
#endif
