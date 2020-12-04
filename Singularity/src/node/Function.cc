#include "Function.hh"

#include "llvm/IR/Verifier.h"

#include "node.hh"
#include "VariableAssignment.hh"

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
    llvm::BasicBlock* currBlock = context.builder.GetInsertBlock();
    context.builder.SetInsertPoint(context.initBlock);

    llvm::AllocaInst* returnPtr = context.builder.CreateAlloca(context.builder.getDoubleTy(), nullptr, "__return.value");

    context.builder.CreateBr(context.functionBlocks[0]);

    context.builder.SetInsertPoint(context.exitBlock);

    llvm::Value* retVal = context.builder.CreateLoad(returnPtr);
    
    if(context.returns.size())
        context.builder.CreateRet(retVal);
    else
        context.builder.CreateRet(llvm::ConstantFP::get(llvm::Type::getDoubleTy(context.context), 0.0));

    for(size_t index = 0; index < context.returns.size(); ++index)
    {
        context.builder.SetInsertPoint(context.returns[index].block);
        llvm::Value* val = context.returns[index].returnValue;
        if(val->getType()->isIntegerTy())
            val = context.builder.CreateCast(llvm::Instruction::SIToFP, val, llvm::Type::getDoubleTy(context.context));
        context.builder.CreateStore(val, returnPtr);
        context.builder.CreateBr(context.exitBlock);
    }

    context.builder.SetInsertPoint(currBlock);
    context.builder.CreateBr(context.exitBlock);

    return nullptr;
}

llvm::Value* Function::codeGen(CodeGenContext& context) 
{
    context.freeFunction();

    llvm::FunctionType* type = nullptr;
    if(this->arguments.size() == 0)
        type = llvm::FunctionType::get(context.builder.getDoubleTy(), llvm::Function::ExternalLinkage);
    else
    {
        std::vector<llvm::Type *> args;
        for(size_t index = 0; index < this->arguments.size(); ++index)
	        args.push_back(context.builder.getDoubleTy());
        type = llvm::FunctionType::get(context.builder.getDoubleTy(), args, false);
    }
    context.dummy = llvm::Function::Create(
        type, llvm::Function::ExternalLinkage, id.name, context.module);

    context.initBlock = llvm::BasicBlock::Create(context.context, "__init", context.dummy);
    context.exitBlock = llvm::BasicBlock::Create(context.context, "__exit", context.dummy);

    llvm::BasicBlock* block = llvm::BasicBlock::Create(context.context, "entry", context.dummy);
    context.insertFunctionBlock(block);
    context.builder.SetInsertPoint(context.initBlock);
    context.pushBlock(block);
    
    size_t index = 0;
    for(auto itr = context.dummy->arg_begin(); itr != context.dummy->arg_end(); ++itr)
    {
        itr->setName(arguments[index]->name);
        ++index;
    }
    
    context.builder.SetInsertPoint(block);

    this->block.codeGen(context);

    context.popBlock();

    createFunction(context);

    //context.module->print(llvm::outs(), nullptr);

    llvm::verifyFunction(*context.dummy);
    return context.dummy;
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