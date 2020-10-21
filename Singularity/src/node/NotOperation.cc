#include "NotOperation.hh"

#include "node.hh"

namespace SNode
{

llvm::Value* NotOperation::codeGen(CodeGenContext& context) { return nullptr; }
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

}