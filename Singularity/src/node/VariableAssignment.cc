#include "VariableAssignment.hh"

#include "node.hh"
#include "DataStructure.hh"

namespace SNode
{

llvm::Value* VariableAssignment::codeGen(CodeGenContext& context) 
{
    llvm::Value* expr = assignmentExpr->codeGen(context);

    llvm::Value* allocMem = assignVariable(context, id.name, expr, assignmentExpr);

    return allocMem;
}

llvm::Value *VariableAssignment::assignVariable(CodeGenContext& context, std::string name, llvm::Value *expr, Expression* assignmentExpr)
{
    llvm::BasicBlock* currBlock = context.builder.GetInsertBlock();

    context.builder.SetInsertPoint(context.initBlock);
    llvm::Instruction* allocMem = context.builder.CreateAlloca(expr->getType(), nullptr);

    context.builder.SetInsertPoint(currBlock);
    context.builder.CreateStore(expr, allocMem);

    if(assignmentExpr && assignmentExpr->getType() == NodeTypes::List)
    {
        context.insertVar(name, allocMem, reinterpret_cast<List*>(assignmentExpr)->size);
    }
    else if(assignmentExpr && assignmentExpr->getType() == NodeTypes::Matrix)
    {
        context.insertVar(name, allocMem, reinterpret_cast<Matrix*>(assignmentExpr)->rowVal, reinterpret_cast<Matrix*>(assignmentExpr)->colVal);
    }
    else
    {
        context.insertVar(name, allocMem);
    }
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
