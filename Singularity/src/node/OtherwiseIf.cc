#include "OtherwiseIf.hh"

#include "node.hh"

namespace SNode
{

llvm::Value* OtherwiseIf::codeGen(CodeGenContext& context) { return nullptr; }
void OtherwiseIf::print(size_t tabs) const
{
    printTabs(tabs);
    std::cout << "Otherwise if: " << std::endl;

    if_statement.print(tabs + 1);
}
void OtherwiseIf::createSymbolTable(SymbolTable& table, std::string name, size_t* subtableCounter) const
{
    if_statement.createSymbolTable(table, name, subtableCounter);
}

}