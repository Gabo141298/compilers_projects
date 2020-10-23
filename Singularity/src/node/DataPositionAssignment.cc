#include "DataPositionAssignment.hh"

#include "node.hh"

namespace SNode
{

llvm::Value* DataPositionAssignment::codeGen(CodeGenContext&) { return nullptr; }
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

}