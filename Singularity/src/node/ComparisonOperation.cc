#include "ComparisonOperation.hh"

#include "node.hh"

namespace SNode
{


llvm::Value* ComparisonOperation::createIntComparison(CodeGenContext& context, llvm::Value* left, llvm::Value* right)
{
    llvm::Value* leftValue = this->left.codeGen(context);
    llvm::Value* rightValue = this->right.codeGen(context);
    llvm::Value* result = nullptr;

    switch(this->op)
    {
        case ComparisonOperator::leq:
            result = context.builder.CreateICmpSLE(left,right);
            break;
        case ComparisonOperator::greater:
            result = context.builder.CreateICmpSGT(left,right);
            break;
        case ComparisonOperator::less:
            result = context.builder.CreateICmpSLT(left,right);
            break;
        case ComparisonOperator::equals:
            result = context.builder.CreateICmpEQ(left,right);
            break;
        case ComparisonOperator::isNot:
            result = context.builder.CreateICmpNE(left,right);
            break; 

    }

    return result;
}

llvm::Value* ComparisonOperation::createFloatComparison(CodeGenContext& context, llvm::Value* left, llvm::Value* right)
{
    llvm::Value* leftValue = this->left.codeGen(context);
    llvm::Value* rightValue = this->right.codeGen(context);
    llvm::Value* result = nullptr;

    switch(this->op)
    {
        case ComparisonOperator::leq:
            result = context.builder.CreateFCmpULE(left,right);
            break;
        case ComparisonOperator::greater:
            result = context.builder.CreateFCmpUGT(left,right);
            break;
        case ComparisonOperator::less:
            result = context.builder.CreateFCmpULT(left,right);
            break;
        case ComparisonOperator::equals:
            result = context.builder.CreateFCmpUEQ(left,right);
            break;
        case ComparisonOperator::isNot:
            result = context.builder.CreateFCmpUNE(left,right);
            break; 
    }

    return result;
}

llvm::Value* ComparisonOperation::createStringComparison(CodeGenContext& context, llvm::Value* left, llvm::Value* right)
{
    llvm::Value* leftValue = this->left.codeGen(context);
    llvm::Value* rightValue = this->right.codeGen(context);
    llvm::Value* result = nullptr;

    llvm::Type* leftType = leftValue->getType();
    llvm::Type* rightType = rightValue->getType();

    if(leftType->isIntegerTy() && rightType->isIntegerTy())
    {
        result = createIntComparison(context, leftValue, rightValue);
    }
    else
    {
        result = createFloatComparison(context, leftValue, rightValue);
    }

    return result;
}

llvm::Value* ComparisonOperation::codeGen(CodeGenContext& context) 
{ 
    llvm::Value* leftValue = this->left.codeGen(context);
    llvm::Value* rightValue = this->right.codeGen(context);
    llvm::Value* result = nullptr;

    Datatype leftType = this->left.getExpressionType();
    Datatype rightType = this->right.getExpressionType();

    if(leftType == Datatype::INTEGER && rightType == Datatype::INTEGER)
    {
        result = createIntComparison(context, leftValue, rightValue);
    }
    else if (leftType == Datatype::INTEGER && rightType == Datatype::DOUBLE
            || leftType == Datatype::DOUBLE && rightType == Datatype::INTEGER)
    {
        leftValue = context.builder.CreateCast(llvm::Instruction::SIToFP, leftValue, llvm::Type::getDoubleTy(context.context));
        rightValue = context.builder.CreateCast(llvm::Instruction::SIToFP, rightValue, llvm::Type::getDoubleTy(context.context));
        result = createFloatComparison(context, leftValue, rightValue);
    }
    else if (leftType == Datatype::STRING && rightType == Datatype::STRING)
    {
        // F ;
        ;
    }

    return result;
}

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

std::vector<std::string> ComparisonOperation::getFunctionCalls()
{
    std::vector<std::string> leftVector = this->left.getFunctionCalls();
    std::vector<std::string> rightVector = this->right.getFunctionCalls();
    
    leftVector.insert(leftVector.end(),rightVector.begin(), rightVector.end());
    return leftVector;    
}

}