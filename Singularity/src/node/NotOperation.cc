#include "NotOperation.hh"

#include "node.hh"

namespace SNode
{

llvm::Value* NotOperation::codeGen(CodeGenContext& context)
{
    llvm::Value* exprValue = this->expression.codeGen(context);
    llvm::Value* result = nullptr;

    llvm::Type* exprType = exprValue->getType();

    if (exprType->isIntegerTy())
    {   
        result = context.builder.CreateNot(exprValue);
    } 

    return result;
}


void NotOperation::print(size_t tabs) const
{
    printTabs(tabs);
    std::cout << "NotOperation:" << std::endl;

    printTabs(tabs + 1);
    std::cout << "Expression:" << std::endl;
    expression.print(tabs + 1);
}

Datatype NotOperation::getExpressionType() const
{
    Datatype type = expression.getExpressionType();
    switch(type)
    {
        case Datatype::UNKNOWN: return Datatype::UNKNOWN;
        case Datatype::BOOLEAN: return Datatype::BOOLEAN;
        case Datatype::INTEGER: throw SingularityException(ExceptionType::NOT_EXPR_INTEGER);
        case Datatype::DOUBLE: throw SingularityException(ExceptionType::NOT_EXPR_DOUBLE);
        case Datatype::STRING: throw SingularityException(ExceptionType::NOT_EXPR_STRING);
        case Datatype::FUNCTION: throw SingularityException(ExceptionType::NOT_EXPR_FUNCTION);
        case Datatype::LIST: throw SingularityException(ExceptionType::NOT_EXPR_LIST);
        case Datatype::MATRIX: throw SingularityException(ExceptionType::NOT_EXPR_MATRIX);
        default: break;
    }
    return Datatype::UNKNOWN;
}

}