#include "PositionAccess.hh"

#include "node.hh"

namespace SNode
{

llvm::Value* PositionAccess::codeGen(CodeGenContext&) { return nullptr; }
void PositionAccess::print(size_t tabs) const
{
    printTabs(tabs);
    std::cout << "PositionAccess: " << std::endl;

    id.print(tabs + 1);

    position.print(tabs + 1);
}
Datatype PositionAccess::getExpressionType() const
{
    NodeTypes positionType = position.getType();
    Datatype idType = id.getExpressionType();
    if(positionType == NodeTypes::MatrixPosition && idType != Datatype::MATRIX)
        throw SingularityException(ExceptionType::MATR_INDEX_EXCP, id.name + " is not a matrix.");
    else if(positionType == NodeTypes::ListPosition && idType != Datatype::LIST)
        throw SingularityException(ExceptionType::LIST_INDEX_EXCP, id.name + " is not a list.");
    // checkPosition throws an exception if there's a problem.
    position.checkPosition();
    return Datatype::UNKNOWN;
}

}