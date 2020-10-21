#include "FunctionCall.hh"

#include "node.hh"

namespace SNode
{

llvm::Value* FunctionCall::codeGen(CodeGenContext& context) { return nullptr; }
void FunctionCall::print(size_t tabs) const
{
    printTabs(tabs);
    std::cout << "FunctionCall:" << std::endl;

    id.print(tabs + 1);

    if(parameters.size() > 0)
    {
        printTabs(tabs + 1);
        std::cout << "parameters:" << std::endl;
        for(size_t index = 0; index < parameters.size(); ++ index)
            parameters[index]->print(tabs + 1);
    }
}

}