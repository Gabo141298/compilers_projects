#include "BooleanOperation.hh"

#include "node.hh"

namespace SNode
{

llvm::Value* BooleanOperation::codeGen(CodeGenContext& context) 
{ 
    llvm::Value* leftValue = this->left.codeGen(context);
    llvm::Value* rightValue = this->right.codeGen(context);
    llvm::Value* result = nullptr;

    switch(this->op)
    {
        case BooleanOperator::bAnd:
            result = context.builder.CreateAnd(leftValue, rightValue);
            break;
        case BooleanOperator::bOr:
            result = context.builder.CreateOr(leftValue, rightValue);
            break;
        case BooleanOperator::bXor:
            result = context.builder.CreateXor(leftValue, rightValue);
            break;
        default:
            break;
    }
    return result;
}
void BooleanOperation::print(size_t tabs) const
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
Datatype BooleanOperation::getExpressionType() const
{
    Datatype leftType = left.getExpressionType();
    Datatype rightType = right.getExpressionType();

    // If any of the expressions is a function, throw an error
    if(leftType == Datatype::FUNCTION || rightType == Datatype::FUNCTION)
        throw SingularityException(ExceptionType::BOOL_EXPR_FUNCTION_USE);
    // If any of the expressions is a list name, throw an error
    else if(leftType == Datatype::LIST || rightType == Datatype::LIST)
        throw SingularityException(ExceptionType::BOOL_EXPR_LIST_USE);
    // If any of the expressions is a matrix name, throw an error
    else if(leftType == Datatype::MATRIX || rightType == Datatype::MATRIX)
        throw SingularityException(ExceptionType::BOOL_EXPR_MATRIX_USE);
    // If any of the expressions is a string, throw an error.
    else if(leftType == Datatype::STRING || rightType == Datatype::STRING)
        throw SingularityException(ExceptionType::BOOL_EXPR_STRING_USE);
    else if(leftType == Datatype::DOUBLE || rightType == Datatype::DOUBLE 
        || leftType == Datatype::INTEGER || rightType == Datatype::INTEGER)
        throw SingularityException(ExceptionType::BOOL_EXPR_NUM_USE);
    // If any of the two expressions is unknown, then the resulting expression is unknown.
    else if(leftType == Datatype::UNKNOWN || rightType == Datatype::UNKNOWN)
        return Datatype::UNKNOWN;
    else
        return Datatype::BOOLEAN;

    return Datatype::UNKNOWN;
}
std::vector<std::string> BooleanOperation::getFunctionCalls()
{
    std::vector<std::string> leftVector = this->left.getFunctionCalls();
    std::vector<std::string> rightVector = this->right.getFunctionCalls();
    
    leftVector.insert(leftVector.end(),rightVector.begin(), rightVector.end());
    return leftVector;    
}

}