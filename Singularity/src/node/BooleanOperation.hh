#ifndef BOOLEAN_OPERATION_H
#define BOOLEAN_OPERATION_H

#include "node.hh"

namespace SNode
{

class BooleanOperation : public Expression {
public:
    Expression& left;
    BooleanOperator op;
    Expression& right;
    BooleanOperation(Expression& left, BooleanOperator op, Expression& right) :
        left(left), op(op), right(right) { }
    // virtual llvm::Value* codeGen(CodeGenContext& context) { }
    void print(size_t tabs = 0) const override
    {
        printTabs(tabs);
        std::cout << "BooleanOperation: op - " << op << std::endl;

        printTabs(tabs + 1);
        std::cout << "LeftExpression:" << std::endl;
        left.print(tabs + 1);

        printTabs(tabs + 1);
        std::cout << "RightExpression:" << std::endl;
        right.print(tabs + 1);
    }
    Datatype getExpressionType() const override
    {
        Datatype leftType = left.getExpressionType();
        Datatype rightType = right.getExpressionType();

        // If any of the expressions is a function, throw an error
        if(leftType == Datatype::FUNCTION || rightType == Datatype::FUNCTION)
            std::cout << "Error: can't use a function name as a boolean expression." << std::endl;
        // If any of the expressions is a list name, throw an error
        else if(leftType == Datatype::LIST || rightType == Datatype::LIST)
            std::cout << "Error: can't use a list name as a boolean expression." << std::endl;
        // If any of the expressions is a matrix name, throw an error
        else if(leftType == Datatype::MATRIX || rightType == Datatype::MATRIX)
            std::cout << "Error: can't use a matrix name as a boolean expression." << std::endl;
        // If any of the expressions is a string, throw an error.
        else if(leftType == Datatype::STRING || rightType == Datatype::STRING)
            std::cout << "Error: can't use a string as a boolean expression." << std::endl;
        else if(leftType == Datatype::DOUBLE || rightType == Datatype::DOUBLE 
            || leftType == Datatype::INTEGER || rightType == Datatype::INTEGER)
            std::cout << "Error: can't use a numeric value as a boolean expression." << std::endl;
        // If any of the two expressions is unknown, then the resulting expression is unknown.
        else if(leftType == Datatype::UNKNOWN || rightType == Datatype::UNKNOWN)
            return Datatype::UNKNOWN;
        else
            return Datatype::BOOLEAN;

        return Datatype::UNKNOWN;
    }
};

}

#endif // BOOLEAN_OPERATION_H