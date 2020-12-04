#include "VariableAssignment.hh"

#include "node.hh"

namespace SNode
{

llvm::Value* VariableAssignment::codeGen(CodeGenContext& context) 
{
    llvm::Value* expr = assignmentExpr->codeGen(context);
    return assignVariable(context, id.name, expr);
}

llvm::Value *VariableAssignment::assignVariable(CodeGenContext& context, std::string name, llvm::Value *expr)
{
    llvm::BasicBlock* currBlock = context.builder.GetInsertBlock();

    context.builder.SetInsertPoint(context.initBlock);
    llvm::Instruction* allocMem = context.builder.CreateAlloca(expr->getType(), nullptr);

    context.builder.SetInsertPoint(currBlock);
    context.builder.CreateStore(expr, allocMem);

    context.insertVar(name, allocMem);
    return allocMem;
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
