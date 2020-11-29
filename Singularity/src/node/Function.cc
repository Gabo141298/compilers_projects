#include "Function.hh"

#include "llvm/IR/Verifier.h"

#include "node.hh"

namespace SNode
{
llvm::Type* Function::getReturnType(CodeGenContext& context)
{
    if(context.returns.size() == 0)
        return context.builder.getVoidTy();
    llvm::Type* type = context.returns[0].returnValue->getType();
    if(type->isDoubleTy() || type->isPointerTy())
        return type;
    // If it's an integer, check if there's a double as any other return type.
    for(size_t index = 1; index < context.returns.size(); ++index)
    {
        if(context.returns[index].returnValue->getType()->isDoubleTy())
            return context.returns[index].returnValue->getType();
    }
    return type;
}

llvm::Function* Function::createFunction(CodeGenContext& context)
{
    llvm::Type* returnType = getReturnType(context);
    llvm::FunctionType *funcType =
        llvm::FunctionType::get(returnType, llvm::Function::ExternalLinkage);
    llvm::Function* currentFunc = llvm::Function::Create(
        funcType, llvm::Function::ExternalLinkage, id.name, context.module);

    llvm::AllocaInst* returnPtr = nullptr;

    if(!returnType->isVoidTy())
    {
        llvm::BasicBlock* initBlock = llvm::BasicBlock::Create(context.context, "__init", currentFunc);
        context.builder.SetInsertPoint(initBlock);
        returnPtr = context.builder.CreateAlloca(returnType, nullptr, "__return.value");
        context.builder.CreateBr(context.functionBlocks[0]);
    }

    for(size_t index = 0; index < context.functionBlocks.size(); ++index)
    {
        context.functionBlocks[index]->insertInto(currentFunc);
    }

    if(returnType->isVoidTy())
    {
        context.builder.CreateRetVoid();
    }
    else
    {
        llvm::BasicBlock* returnBlock = llvm::BasicBlock::Create(context.context, "__return", currentFunc);
        context.builder.SetInsertPoint(returnBlock);
        llvm::Value* retVal = context.builder.CreateLoad(returnPtr);
        context.builder.CreateRet(retVal);

        for(size_t index = 0; index < context.returns.size(); ++index)
        {
            context.builder.SetInsertPoint(context.returns[index].block);
            context.builder.CreateStore(context.returns[index].returnValue, returnPtr);
            context.builder.CreateBr(returnBlock);
        }
    }

    return currentFunc;
}

llvm::Value* Function::codeGen(CodeGenContext& context) 
{
    context.freeFunction();

    llvm::BasicBlock* block = llvm::BasicBlock::Create(context.context, "entry");
    context.insertFunctionBlock(block);
    context.pushBlock(block);
    context.builder.SetInsertPoint(block);

    this->block.codeGen(context);

    context.popBlock();

    llvm::Function* func = createFunction(context);

    llvm::verifyFunction(*func);
    return func;
}

void Function::print(size_t tabs) const
{
    printTabs(tabs);
    std::cout << "Function:" << std::endl;

    printTabs(tabs + 1);
    std::cout << "FunctionName:" << std::endl;
    id.print(tabs + 1);

    if(arguments.size() > 0)
    {
        printTabs(tabs + 1);
        std::cout << "Arguments:" << std::endl;
        for(size_t index = 0; index < arguments.size(); ++ index)
            arguments[index]->print(tabs + 1);
    }

    block.print(tabs + 1);
}

void Function::createSymbolTable(SymbolTable& table) const
{
    table.initializeScope(id.name);

    for(auto itr = arguments.begin(); itr != arguments.end(); ++itr)
    {
        // Difficult to infer the datatype of the arguments, although maybe not impossible.
        table.insertToCurrentSubtable((*itr)->name, Datatype::UNKNOWN);        
    }

    size_t* subtableCounter = new size_t(0);
    block.createSymbolTable(table, id.name, subtableCounter);
    delete subtableCounter;
    table.finalizeScope();

    if(block.hasInfiniteRecursion(id.name))
        throw SingularityException(ExceptionType::INFINITE_RECURSION, "Infinite recursion in " + id.name);

}

}