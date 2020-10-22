#include "ComparisonOperation.hh"

#include "node.hh"

namespace SNode
{

llvm::Value* ComparisonOperation::codeGen(CodeGenContext& context) { return nullptr; }
void ComparisonOperation::print(size_t tabs) const
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
Datatype ComparisonOperation::getExpressionType() const
{
    Datatype leftType = left.getExpressionType();
    Datatype rightType = right.getExpressionType();

    // If any of the expressions is boolean, throw an error
    if(leftType == Datatype::BOOLEAN || rightType == Datatype::BOOLEAN)
        throw SingularityException::COMP_EXPR_BOOL_USE;
    // If any of the expressions is a function, throw an error
    else if(leftType == Datatype::FUNCTION || rightType == Datatype::FUNCTION)
        throw SingularityException::COMP_EXPR_FUNCTION_USE;
    // If any of the expressions is a list name, throw an error
    else if(leftType == Datatype::LIST || rightType == Datatype::LIST)
        throw SingularityException::COMP_EXPR_LIST_USE;
    // If any of the expressions is a matrix name, throw an error
    else if(leftType == Datatype::MATRIX || rightType == Datatype::MATRIX)
        throw SingularityException::COMP_EXPR_MATRIX_USE;
    // If any of the two expressions is unknown, then the resulting expression is unknown.
    else if(leftType == Datatype::UNKNOWN || rightType == Datatype::UNKNOWN)
        return Datatype::UNKNOWN;
    else if(leftType == Datatype::STRING && rightType == Datatype::STRING)
        return Datatype::BOOLEAN;
    // If any of the expressions is a string, throw an error.
    else if(leftType == Datatype::STRING || rightType == Datatype::STRING)
        throw SingularityException::COMP_EXPR_STRING_NUM;
    else
        return Datatype::BOOLEAN;

    return Datatype::UNKNOWN;
}

}