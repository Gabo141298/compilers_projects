#include "VariableAssignment.hh"

#include "node.hh"

namespace SNode
{

llvm::Value* VariableAssignment::codeGen(CodeGenContext& context) 
{ 
	llvm::Value* expr = assignmentExpr->codeGen(context);
	expr->setName(id.name);

	context.insertVar(id.name, expr);

	return expr;
}

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