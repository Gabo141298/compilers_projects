#include "Otherwise.hh"

#include "node.hh"

namespace SNode
{

llvm::Value* Otherwise::codeGen(CodeGenContext& context) { return nullptr; }
void Otherwise::print(size_t tabs) const
{
    printTabs(tabs);
    std::cout << "Otherwise: " << std::endl;

    block.print(tabs + 1);
}

void Otherwise::createSymbolTable(SymbolTable& table, std::string name, size_t* subtableCounter) const
{
    name += "_" + std::to_string( (*subtableCounter)++);
    table.initializeScope(name);

    size_t* newSubtableCounter = new size_t(0);
    block.createSymbolTable(table, name, newSubtableCounter);
    delete newSubtableCounter;
    table.finalizeScope();
}

}