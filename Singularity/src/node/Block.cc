#include "Block.hh"

#include "node.hh"

namespace SNode
{

llvm::Value* Block::codeGen(CodeGenContext& context) { return nullptr; }
void Block::print(size_t tabs) const
{
    printTabs(tabs);
    std::cout << "Block: " << std::endl;
    
    printTabs(tabs + 1);
    std::cout << "Statements:" << std::endl;
    for(size_t index = 0; index < statements.size(); ++index)
        statements[index]->print(tabs + 1);
}
void Block::createSymbolTable(SymbolTable& table, std::string name, size_t* subtableCounter) const
{
    for(auto itr = statements.begin(); itr != statements.end(); ++itr)
    {
        (*itr)->createSymbolTable(table, name, subtableCounter);
    }
}

}