#include "While.hh"

#include "node.hh"

namespace SNode
{

llvm::Value* While::codeGen(CodeGenContext& context)
{
    llvm::Value* cond = this->condition.codeGen(context);
    llvm::BasicBlock* conditionBlock = llvm::BasicBlock::Create(context.context, "condition", context.currentFunc);
    llvm::BasicBlock* thenBlock = llvm::BasicBlock::Create(context.context, "then", context.currentFunc);
    llvm::BasicBlock* merge = llvm::BasicBlock::Create(context.context, "merge", context.currentFunc);

    context.builder.SetInsertPoint(conditionBlock);
    context.builder.CreateCondBr(cond, thenBlock, merge);

    context.builder.SetInsertPoint(thenBlock);
    this->block.codeGen(context);
    context.popBlock();
    context.builder.CreateBr(conditionBlock);

    context.builder.SetInsertPoint(merge);
    context.replaceBlock(merge);
    return merge;
}

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
        throw SingularityException(ExceptionType::WHILE_CONDITION);
    }
}

}
