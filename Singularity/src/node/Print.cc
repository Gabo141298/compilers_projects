#include "Print.hh"

#include "node.hh"

namespace SNode
{

llvm::Value* Print::codeGen(CodeGenContext& context) { return nullptr; }
void Print::print(size_t tabs) const
{
    this->expression.getExpressionType();
    printTabs(tabs);
    std::cout << "Print: " << std::endl;
    expression.print(tabs + 1);
}

}
