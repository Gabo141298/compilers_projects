#include "ComparisonOperation.hh"

#include "node.hh"

namespace SNode
{

llvm::Value* ComparisonOperation::codeGen(CodeGenContext&) { return nullptr; }
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

    // Both expressions being boolean is only valid if the user is checking if they are the same or if they are different.
    if(leftType == Datatype::BOOLEAN && rightType == Datatype::BOOLEAN && 
    (this->op == ComparisonOperator::equals || this->op == ComparisonOperator::isNot) )
        return Datatype::BOOLEAN;
    // If any of the expressions is boolean and the operation not an equals or isNot, throw an error
    else if(leftType == Datatype::BOOLEAN || rightType == Datatype::BOOLEAN)
        throw SingularityException(ExceptionType::COMP_EXPR_BOOL_USE);
    // If any of the expressions is a function, throw an error
    else if(leftType == Datatype::FUNCTION || rightType == Datatype::FUNCTION)
        throw SingularityException(ExceptionType::COMP_EXPR_FUNCTION_USE);
    // If any of the expressions is a list name, throw an error
    else if(leftType == Datatype::LIST || rightType == Datatype::LIST)
        throw SingularityException(ExceptionType::COMP_EXPR_LIST_USE);
    // If any of the expressions is a matrix name, throw an error
    else if(leftType == Datatype::MATRIX || rightType == Datatype::MATRIX)
        throw SingularityException(ExceptionType::COMP_EXPR_MATRIX_USE);
    // If any of the two expressions is unknown, then the resulting expression is unknown.
    else if(leftType == Datatype::UNKNOWN || rightType == Datatype::UNKNOWN)
        return Datatype::UNKNOWN;
    else if(leftType == Datatype::STRING && rightType == Datatype::STRING)
        return Datatype::BOOLEAN;
    // If only one of the expressions is a string, throw an error.
    else if(leftType == Datatype::STRING || rightType == Datatype::STRING)
        throw SingularityException(ExceptionType::COMP_EXPR_STRING_NUM);
    else
        return Datatype::BOOLEAN;

    return Datatype::UNKNOWN;
}

}