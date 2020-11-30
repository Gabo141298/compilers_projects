#include "If.hh"

#include "node.hh"

namespace SNode
{

llvm::Value* If::codeGen(CodeGenContext& context) 
{
    llvm::Value* cond = condition.codeGen(context);
    llvm::BasicBlock* thenBlock = llvm::BasicBlock::Create(context.context, "then");
    context.insertFunctionBlock(thenBlock);
    llvm::BasicBlock* merge = llvm::BasicBlock::Create(context.context, "merge");
    context.insertFunctionBlock(merge);
    
    if(!this->otherwise)
    {
        context.builder.CreateCondBr(cond, thenBlock, merge);
    }
    else
    {
        llvm::BasicBlock* elseBlock = llvm::BasicBlock::Create(context.context, "else");
        context.insertFunctionBlock(elseBlock);
        context.builder.CreateCondBr(cond, thenBlock, elseBlock);
        context.builder.SetInsertPoint(elseBlock);
        context.pushBlock(elseBlock);
        otherwise->codeGen(context);
        context.popBlock();
        context.builder.CreateBr(merge);
    }

    context.builder.SetInsertPoint(thenBlock);
    context.pushBlock(thenBlock);
    block.codeGen(context);
    context.popBlock();
    context.builder.CreateBr(merge);
    
    context.builder.SetInsertPoint(merge);
    context.replaceBlock(merge);
    return merge;
}

void If::print(size_t tabs) const
{
    printTabs(tabs);
    std::cout << "If: " << std::endl;

    printTabs(tabs + 1);
    std::cout << "Condition:" << std::endl;
    condition.print(tabs + 1);

    block.print(tabs + 1);

    if (otherwise)
        otherwise->print(tabs);

    block.print(tabs + 1);
}

void If::createSymbolTable(SymbolTable& table, std::string name, size_t* subtableCounter) const
{
    Datatype conditionType = condition.getExpressionType();
    if( conditionType == Datatype::BOOLEAN || conditionType == Datatype::UNKNOWN )
    {
        std::string newName = name + "_" + std::to_string( (*subtableCounter)++);
        table.initializeScope(newName);

        size_t* newSubtableCounter = new size_t(0);
        block.createSymbolTable(table, newName, newSubtableCounter);
        delete newSubtableCounter;
        table.finalizeScope();

        if(otherwise)
            otherwise->createSymbolTable(table, name, subtableCounter);
    }
    else
    {
        throw SingularityException(ExceptionType::IF_CONDITION);
    }
}

}