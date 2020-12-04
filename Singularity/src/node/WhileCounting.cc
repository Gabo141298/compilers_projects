#include "WhileCounting.hh"

#include "node.hh"
#include "VariableAssignment.hh"

namespace SNode
{

//llvm::Value* WhileCounting::codeGen(CodeGenContext& context)
//{

//    llvm::BasicBlock* initBlock = llvm::BasicBlock::Create(context.context, "initializer", context.currentFunc);
//    llvm::BasicBlock* conditionBlock = llvm::BasicBlock::Create(context.context, "condition", context.currentFunc);
//    llvm::BasicBlock* loopBlock = llvm::BasicBlock::Create(context.context, "loop", context.currentFunc);
//    llvm::BasicBlock* merge = llvm::BasicBlock::Create(context.context, "merge", context.currentFunc);

//    context.builder.CreateBr(initBlock);

//    context.builder.SetInsertPoint(initBlock);
//    context.pushBlock(loopBlock);

//    llvm::Value* tmp =  this->beginValue.codeGen(context);
//    llvm::PHINode* counterVariable = context.builder.CreatePHI(context.builder.getInt64Ty(), 2 , this->counter.name);
//    counterVariable->addIncoming(tmp, initBlock);
//    llvm::Value* endVariable = this->endValue.codeGen(context);
//    context.insertVar(counter.name, counterVariable);
//    llvm::Value* increment = context.builder.getInt64(1);
//    context.builder.CreateBr(conditionBlock);


//    context.builder.SetInsertPoint(conditionBlock);
//    llvm::Value* conditionEvaluation = context.builder.CreateICmpSLE(counterVariable,endVariable);
//    context.builder.CreateCondBr(conditionEvaluation, loopBlock, merge);

//    context.builder.SetInsertPoint(loopBlock);
//    this->block.codeGen(context);
//    llvm::Value* sum = context.builder.CreateAdd(counterVariable, increment , "nextvar" );
//    llvm::BasicBlock* endLoop = context.builder.GetInsertBlock();
//    counterVariable->addIncoming(sum, endLoop);
//    context.builder.CreateBr(conditionBlock);

//    context.builder.SetInsertPoint(merge);
//    context.popBlock();
//    context.replaceBlock(merge);
//    return merge;
//}

llvm::Value* WhileCounting::codeGen(CodeGenContext& context)
{
    llvm::Value* StartVal = this->beginValue.codeGen(context);

    llvm::BasicBlock* PreheaderBB = context.builder.GetInsertBlock();
    llvm::BasicBlock* LoopBB = llvm::BasicBlock::Create(context.context, "loop", context.dummy);
    context.insertFunctionBlock(LoopBB);

    context.builder.CreateBr(LoopBB);
    context.builder.SetInsertPoint(LoopBB);
    llvm::PHINode *Variable = context.builder.CreatePHI(llvm::Type::getInt64Ty(context.context), 2, this->counter.name);
    Variable->addIncoming(StartVal, PreheaderBB);

    context.pushBlock(LoopBB);
    VariableAssignment::assignVariable(context, this->counter.name, Variable);
    this->block.codeGen(context);
    llvm::Value* StepVal = context.builder.getInt64(1);
    llvm::Value* NextVar = context.builder.CreateAdd(Variable, StepVal, "nextvar", context.dummy);

    llvm::Value* EndCond = this->endValue.codeGen(context);

    EndCond = context.builder.CreateICmpSLT(Variable, EndCond, "loopcond");

    llvm::BasicBlock * LoopEndBB = context.builder.GetInsertBlock();
    llvm::BasicBlock * AfterBB = llvm::BasicBlock::Create(context.context, "afterloop", context.dummy);
    context.insertFunctionBlock(AfterBB);

    context.builder.CreateCondBr(EndCond, LoopBB, AfterBB);
    context.builder.SetInsertPoint(AfterBB);

    Variable->addIncoming(NextVar, LoopEndBB);

    context.popBlock();

    return  AfterBB;
}
void WhileCounting::print(size_t tabs) const
{
    printTabs(tabs);
    std::cout << "WhileCounting: " << std::endl;

    printTabs(tabs + 1);
    std::cout << "Counter:" << std::endl;
    counter.print(tabs + 1);

    printTabs(tabs + 1);
    std::cout << "BeginValue:" << std::endl;
    beginValue.print(tabs + 1);

    printTabs(tabs + 1);
    std::cout << "EndValue:" << std::endl;
    endValue.print(tabs + 1);

    block.print(tabs + 1);
}

void WhileCounting::createSymbolTable(SymbolTable& table, std::string name, size_t* subtableCounter) const
{
    Datatype beginType = beginValue.getExpressionType();
    Datatype endType = endValue.getExpressionType();
    if( (beginType == Datatype::INTEGER || beginType == Datatype::UNKNOWN) 
        && (endType == Datatype::INTEGER || endType == Datatype::UNKNOWN) )
    {
        name += "_" + std::to_string( (*subtableCounter)++);
        table.initializeScope(name);

        table.insertToCurrentSubtable(counter.name, Datatype::INTEGER);

        size_t* newSubtableCounter = new size_t(0);
        block.createSymbolTable(table, name, newSubtableCounter);
        delete newSubtableCounter;
        table.finalizeScope();
    }
    else
    {
        throw SingularityException(ExceptionType::WHILE_COUNTING_RANGE);
    }
}

}
