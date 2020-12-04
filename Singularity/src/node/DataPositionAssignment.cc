#include "DataPositionAssignment.hh"

#include "node.hh"

namespace SNode
{

llvm::Value* DataPositionAssignment::codeGen(CodeGenContext& context)
{
    llvm::Value* expr = expression.codeGen(context);
    llvm::Value* memVal = position.calculateMemDir(context, id.codeGen(context));

    return context.builder.CreateStore(expr, memVal);
}

void DataPositionAssignment::print(size_t tabs) const
{
    printTabs(tabs);
    std::cout << "DataPositionAssignment: " << std::endl;

    id.print(tabs + 1);

    printTabs(tabs + 1);
    std::cout << "Position:" << std::endl;
    position.print(tabs + 1);

    printTabs(tabs + 1);
    std::cout << "Expression:" << std::endl;
    expression.print(tabs + 1);
}

void DataPositionAssignment::createSymbolTable(SymbolTable& symbolTable, std::string, size_t*) const
{
    NodeTypes positionType = position.getType();
    Datatype idType = id.getExpressionType();
    if(positionType == NodeTypes::MatrixPosition && idType != Datatype::MATRIX)
        throw SingularityException(ExceptionType::MATR_INDEX_EXCP, id.name + " is not a matrix.");
    else if(positionType == NodeTypes::ListPosition && idType != Datatype::LIST)
        throw SingularityException(ExceptionType::LIST_INDEX_EXCP, id.name + " is not a list.");
    
    // Checks if expression has undeclared variables or invalid operators for any of its operations.
    expression.getExpressionType();

    // Checks if its position values are integers or unknown values.
    position.checkPosition();
}

}