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
    // checkPosition throws an exception if there's a problem.
    position.checkPosition();
    return Datatype::UNKNOWN;
}

}