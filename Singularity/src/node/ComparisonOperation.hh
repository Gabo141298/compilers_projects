#ifndef COMPARISON_OPERATION_H
#define COMPARISON_OPERATION_H

#include "node.hh"

namespace SNode
{

class ComparisonOperation : public Expression {
public:
    Expression& left;
    ComparisonOperator op;
    Expression& right;
    ComparisonOperation(Expression& left, ComparisonOperator op, Expression& right) :
        left(left), op(op), right(right) { }
    // virtual llvm::Value* codeGen(CodeGenContext& context) { }
    void print(size_t tabs = 0) const override
    {
        printTabs(tabs);
        std::cout << "ComparisonOperation: op - " << op << std::endl;

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

        // If any of the expressions is boolean, throw an error
        if(leftType == Datatype::BOOLEAN || rightType == Datatype::BOOLEAN)
            std::cout << "Error: can't use a boolean expression to compare." << std::endl;
        // If any of the expressions is a function, throw an error
        else if(leftType == Datatype::FUNCTION || rightType == Datatype::FUNCTION)
            std::cout << "Error: can't use a function name as an expression." << std::endl;
        // If any of the expressions is a list name, throw an error
        else if(leftType == Datatype::LIST || rightType == Datatype::LIST)
            std::cout << "Error: can't use a list name as an expression." << std::endl;
        // If any of the expressions is a matrix name, throw an error
        else if(leftType == Datatype::MATRIX || rightType == Datatype::MATRIX)
            std::cout << "Error: can't use a matrix name as an expression." << std::endl;
        // If any of the two expressions is unknown, then the resulting expression is unknown.
        else if(leftType == Datatype::UNKNOWN || rightType == Datatype::UNKNOWN)
            return Datatype::UNKNOWN;
        else if(leftType == Datatype::STRING && rightType == Datatype::STRING)
            return Datatype::BOOLEAN;
        // If any of the expressions is a string, throw an error.
        else if(leftType == Datatype::STRING || rightType == Datatype::STRING)
            std::cout << "Error: can't compare a string with a numeric expression" << std::endl;
        else
            return Datatype::BOOLEAN;

        return Datatype::UNKNOWN;
    }
};

}

#endif // COMPARISON_OPERATION_H