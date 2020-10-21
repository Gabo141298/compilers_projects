#include "DataStructure.hh"

#include "node.hh"

namespace SNode
{

llvm::Value* List::codeGen(CodeGenContext& context) { return nullptr; }
void List::print(size_t tabs) const
{
    printTabs(tabs);
    std::cout << "List" << std::endl;
}

llvm::Value* Matrix::codeGen(CodeGenContext& context) { }
void Matrix::print(size_t tabs) const
{
    printTabs(tabs);
    std::cout << "Matrix: " << std::endl;

    printTabs(tabs + 1);
    std::cout << "Row:" << std::endl;
    row->print(tabs + 1);

    printTabs(tabs + 1);
    std::cout << "Col:" << std::endl;
    col->print(tabs + 1);
}

}