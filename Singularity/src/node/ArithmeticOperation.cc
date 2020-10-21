#include "ArithmeticOperation.hh"

#include "node.hh"

namespace SNode
{

llvm::Value* ArithmeticOperation::codeGen(CodeGenContext& context) { return nullptr; }
void ArithmeticOperation::print(size_t tabs) const
{
    printTabs(tabs);
    std::cout << "ArithmeticOperation: op - " << op << std::endl;

    printTabs(tabs + 1);
    std::cout << "LeftExpression:" << std::endl;
    left.print(tabs + 1);

    printTabs(tabs + 1);
    std::cout << "RightExpression:" << std::endl;
    right.print(tabs + 1);
}
Datatype ArithmeticOperation::getExpressionType() const
{
    Datatype leftType = left.getExpressionType();
    Datatype rightType = right.getExpressionType();

    // If any of the expressions is boolean, throw an error
    if(leftType == Datatype::BOOLEAN || rightType == Datatype::BOOLEAN)
        std::cout << "Error: can't use a boolean expression as an arithmetic expression." << std::endl;
    // If any of the expressions is a function, throw an error
    else if(leftType == Datatype::FUNCTION || rightType == Datatype::FUNCTION)
        std::cout << "Error: can't use a function name as an arithmetic expression." << std::endl;
    // If any of the expressions is a list name, throw an error
    else if(leftType == Datatype::LIST || rightType == Datatype::LIST)
        std::cout << "Error: can't use a list name as an arithmetic expression." << std::endl;
    // If any of the expressions is a matrix name, throw an error
    else if(leftType == Datatype::MATRIX || rightType == Datatype::MATRIX)
        std::cout << "Error: can't use a matrix name as an arithmetic expression." << std::endl;
    // If any of the expressions is a string, throw an error.
    else if(leftType == Datatype::STRING || rightType == Datatype::STRING)
        std::cout << "Error: can't use a string as an arithmetic expression." << std::endl;
    // If any of the two expressions is unknown, then the resulting expression is unknown.
    else if(leftType == Datatype::UNKNOWN || rightType == Datatype::UNKNOWN)
        return Datatype::UNKNOWN;
    // If any of the two expressions is a double, then the resulting expression is a double.
    else if(leftType == Datatype::DOUBLE || rightType == Datatype::DOUBLE)
        return Datatype::DOUBLE;
    else
        return Datatype::INTEGER;

    return Datatype::UNKNOWN;
}

}