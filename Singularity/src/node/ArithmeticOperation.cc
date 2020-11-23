#include "ArithmeticOperation.hh"

#include "node.hh"

namespace SNode
{

llvm::Value* ArithmeticOperation::createIntOperation(CodeGenContext& context, llvm::Value* left, llvm::Value* right)
{
    llvm::Value* result = nullptr;

    switch(this->op)
    {
        case ArithmeticOperator::addition:
            result = context.builder.CreateAdd(left, right);
            break;
        case ArithmeticOperator::substraction:
            result = context.builder.CreateSub(left, right);
            break;
        case ArithmeticOperator::multiplication:
            result = context.builder.CreateMul(left, right);
            break;
        case ArithmeticOperator::division:
            result = context.builder.CreateSDiv(left, right);
            break;
        case ArithmeticOperator::modulo:
            result = context.builder.CreateSRem(left, right);
            break;
        default:
            break;
    }
    
    return result;
}

llvm::Value* ArithmeticOperation::createFloatOperation(CodeGenContext& context, llvm::Value* left, llvm::Value* right)
{
    llvm::Value* result = nullptr;

    switch(this->op)
    {
        case ArithmeticOperator::addition:
            result = context.builder.CreateFAdd(left, right);
            break;
        case ArithmeticOperator::substraction:
            result = context.builder.CreateFSub(left, right);
            break;
        case ArithmeticOperator::multiplication:
            result = context.builder.CreateFMul(left, right);
            break;
        case ArithmeticOperator::division:
            result = context.builder.CreateFDiv(left, right);
            break;
        case ArithmeticOperator::modulo:
            result = context.builder.CreateFRem(left, right);
            break;
        default:
            break;
    }
    
    return result;
}

llvm::Value* ArithmeticOperation::codeGen(CodeGenContext& context) 
{
    llvm::Value* leftValue = this->left.codeGen(context);
    llvm::Value* rightValue = this->right.codeGen(context);
    llvm::Value* result = nullptr;

    llvm::Type* leftType = leftValue->getType();
    llvm::Type* rightType = rightValue->getType();

    if(leftType->isIntegerTy() && rightType->isIntegerTy())
    {
        result = createIntOperation(context, leftValue, rightValue);
    }
    else
    {
        leftValue = context.builder.CreateCast(llvm::Instruction::SIToFP, leftValue, llvm::Type::getDoubleTy(context.context));
        rightValue = context.builder.CreateCast(llvm::Instruction::SIToFP, rightValue, llvm::Type::getDoubleTy(context.context));
        result = createFloatOperation(context, leftValue, rightValue);
    }
    
    return result;
}


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
        throw SingularityException(ExceptionType::ARITH_EXPR_BOOLEAN_USE);
    // If any of the expressions is a function, throw an error
    else if(leftType == Datatype::FUNCTION || rightType == Datatype::FUNCTION)
        throw SingularityException(ExceptionType::ARITH_EXPR_FUNCTION_USE);
    // If any of the expressions is a list name, throw an error
    else if(leftType == Datatype::LIST || rightType == Datatype::LIST)
        throw SingularityException(ExceptionType::ARITH_EXPR_LIST_USE);
    // If any of the expressions is a matrix name, throw an error
    else if(leftType == Datatype::MATRIX || rightType == Datatype::MATRIX)
        throw SingularityException(ExceptionType::ARITH_EXPR_MATRIX_USE);
    // If any of the expressions is a string, throw an error.
    else if(leftType == Datatype::STRING || rightType == Datatype::STRING)
        throw SingularityException(ExceptionType::ARITH_EXPR_STRING_USE);
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


std::vector<std::string> ArithmeticOperation::getFunctionCalls()
{
    std::vector<std::string> leftVector = this->left.getFunctionCalls();
    std::vector<std::string> rightVector = this->right.getFunctionCalls();
    
    leftVector.insert(leftVector.end(),rightVector.begin(), rightVector.end());
    return leftVector;    
}

}