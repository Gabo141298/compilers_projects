#include "Function.hh"

#include "node.hh"

namespace SNode
{

llvm::Value* Function::codeGen(CodeGenContext& context) { return nullptr; }
void Function::print(size_t tabs) const
{
    printTabs(tabs);
    std::cout << "Function:" << std::endl;

    printTabs(tabs + 1);
    std::cout << "FunctionName:" << std::endl;
    id.print(tabs + 1);

    if(arguments.size() > 0)
    {
        printTabs(tabs + 1);
        std::cout << "Arguments:" << std::endl;
        for(size_t index = 0; index < arguments.size(); ++ index)
            arguments[index]->print(tabs + 1);
    }

    block.print(tabs + 1);
}

void Function::createSymbolTable(SymbolTable& table) const
{
    table.initializeScope(id.name);

    for(auto itr = arguments.begin(); itr != arguments.end(); ++itr)
    {
        // Difficult to infer the datatype of the arguments, although maybe not impossible.
        table.insertToCurrentSubtable((*itr)->name, Datatype::UNKNOWN);        
    }

    bool hasCondition = false;
    size_t* subtableCounter = new size_t(0);
    block.createSymbolTable(table, id.name, subtableCounter);
    delete subtableCounter;
    table.finalizeScope();

    if(block.hasInfiniteRecursion(id.name))
        throw SingularityException::INFINITE_RECURSION;

}

}