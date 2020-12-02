#include "Read.hh"

#include "node.hh"
#include "llvm/IR/Instructions.h"

namespace SNode
{

llvm::Value* Read::codeGen(CodeGenContext& context) { 
    
    // llvm::FunctionType *funcType = llvm::FunctionType::get(builder.getVoidTy(), false);
    // llvm::Function *mainFunc = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, "main", module);
    // llvm::BasicBlock *entry = llvm::BasicBlock::Create(context.context, "read");
    
    // context.builder.SetInsertPoint(entry);

    // Gets the function
    llvm::Function *theScanf = context.module->getFunction("scanf");
    llvm::BasicBlock *entry = llvm::BasicBlock::Create(context.context, "scanf", theScanf);
    context.builder.SetInsertPoint(entry);
    //context.builder.SetInsertPoint(context.builder.GetInsertBlock());
    // Format
    
    llvm::Value *scanfFormat = SNode::createString(context, "%u");

    // Allocate memory
    llvm::AllocaInst *Alloca = context.builder.CreateAlloca(llvm::Type::getInt64Ty(context.context), nullptr, this->identifier.name );    
   
    // Vector with args
    std::vector<llvm::Value *> scanfArgs = {scanfFormat, Alloca};

    
    // Build the call
    llvm::Value* response = context.builder.CreateCall(theScanf, scanfArgs);
    
         

}
void Read::print(size_t tabs) const
{
    printTabs(tabs);
    std::cout << "Read: " << std::endl;
    identifier.print(tabs + 1);
}
void Read::createSymbolTable(SymbolTable& table, std::string, size_t*) const
{
    // Can't infer datatype that is read from an input.
    table.insertToCurrentSubtable(identifier.name, Datatype::UNKNOWN);
}

}