#include "Answer.hh"

#include "node.hh"

namespace SNode
{

llvm::Value* Answer::codeGen(CodeGenContext& context) { return nullptr; }

void Answer::print(size_t tabs) const
{
    printTabs(tabs);
    std::cout << "Answer:" << std::endl;

    printTabs(tabs + 1);
    std::cout << "Expression:" << std::endl;
    returnExpression.print(tabs + 1);
}

}