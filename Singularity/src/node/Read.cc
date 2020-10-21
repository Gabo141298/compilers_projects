#include "Read.hh"

#include "node.hh"

namespace SNode
{

llvm::Value* Read::codeGen(CodeGenContext& context) { return nullptr; }
void Read::print(size_t tabs) const
{
    printTabs(tabs);
    std::cout << "Read: " << std::endl;
    identifier.print(tabs + 1);
}
void Read::createSymbolTable(SymbolTable& table, std::string, size_t*) const
{
    // Can't infer datatype that is read from an input.
    table.insertToCurrentSubtable(identifier.name, Datatype::UNKNOWN);
}

}