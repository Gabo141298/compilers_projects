#include "PositionAccess.hh"

#include "node.hh"

namespace SNode
{

llvm::Value* PositionAccess::codeGen(CodeGenContext& context) { return nullptr; }
void PositionAccess::print(size_t tabs) const
{
    printTabs(tabs);
    std::cout << "PositionAccess: " << std::endl;

    id.print(tabs + 1);

    position.print(tabs + 1);
}
Datatype PositionAccess::getExpressionType() const
{
    if(!position.validPosition())
        std::cout << "Error: invalid position" << std::endl;
    return Datatype::UNKNOWN;
}

}