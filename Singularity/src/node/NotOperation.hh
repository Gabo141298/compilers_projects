#ifndef NOT_OPERATION_H
#define NOT_OPERATION_H

#include "node.hh"

namespace SNode
{

class NotOperation : public Expression {
public:
    Expression& expression;
    NotOperation(Expression& expression) :
        expression(expression) { }
    // virtual llvm::Value* codeGen(CodeGenContext& context) { }
    void print(size_t tabs = 0) const override
    {
        printTabs(tabs);
        std::cout << "NotOperation:" << std::endl;

        printTabs(tabs + 1);
        std::cout << "Expression:" << std::endl;
        expression.print(tabs + 1);
    }
    Datatype getExpressionType() const override
    {
        Datatype type = expression.getExpressionType();
        switch(type)
        {
            case Datatype::UNKNOWN: return Datatype::UNKNOWN;
            case Datatype::BOOLEAN: return Datatype::BOOLEAN;
            case Datatype::INTEGER: std::cout << "Error: can't use an integer as a boolean expression." << std::endl; break;
            case Datatype::DOUBLE: std::cout << "Error: can't use a double as a boolean expression." << std::endl; break;
            case Datatype::STRING: std::cout << "Error: can't use a string as a boolean expression." << std::endl; break;
            case Datatype::FUNCTION: std::cout << "Error: can't use a function name as a boolean expression." << std::endl; break;
            case Datatype::LIST: std::cout << "Error: can't use a list name as a boolean expression." << std::endl; break;
            case Datatype::MATRIX: std::cout << "Error: can't use a matrix name as a boolean expression." << std::endl; break;
            default: break;
        }
        return Datatype::UNKNOWN;
    }
};

}

#endif // NOT_OPERATION_H