#include "VariableAssignment.hh"

#include "node.hh"

namespace SNode
{

llvm::Value* VariableAssignment::codeGen(CodeGenContext&) { return nullptr; }
void VariableAssignment::print(size_t tabs) const
{
    printTabs(tabs);
    std::cout << "VariableAssignment: " << std::endl;

    id.print(tabs + 1);

    printTabs(tabs + 1);
    std::cout << "Expression:" << std::endl;
    assignmentExpr->print(tabs + 1);
}
void VariableAssignment::createSymbolTable(SymbolTable& table, std::string, size_t*) const
{
    table.insertToCurrentSubtable(id.name, assignmentExpr->getExpressionType());
}

}