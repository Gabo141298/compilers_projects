#include "While.hh"

#include "node.hh"

namespace SNode
{

llvm::Value* While::codeGen(CodeGenContext& context) { return nullptr; }
void While::print(size_t tabs) const
{
    printTabs(tabs);
    std::cout << "While: " << std::endl;

    printTabs(tabs + 1);
    std::cout << "Condition:" << std::endl;
    condition.print(tabs + 1);

    block.print(tabs + 1);
}
void While::createSymbolTable(SymbolTable& table, std::string name, size_t* subtableCounter) const
{
    Datatype conditionType = condition.getExpressionType();
    if( conditionType == Datatype::BOOLEAN || conditionType == Datatype::UNKNOWN )
    {
        name += "_" + std::to_string( (*subtableCounter)++);
        table.initializeScope(name);

        size_t* newSubtableCounter = new size_t(0);
        block.createSymbolTable(table, name, newSubtableCounter);
        delete newSubtableCounter;
        table.finalizeScope();
    }
    else
    {
        std::cout << "Error: while needs a boolean expression as its condition." << std::endl;
    }
}

}