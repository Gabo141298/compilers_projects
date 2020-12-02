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

    // Format
    llvm::Value *scanfFormat = context.builder.CreateGlobalStringPtr("%u");

    // Allocate memory
    llvm::AllocaInst *Alloca = context.builder.CreateAlloca(llvm::Type::getInt64Ty(context.context), nullptr, this->identifier.name );    
   
    // Vector with args
    std::vector<llvm::Value *> scanfArgs = {scanfFormat, Alloca};

    // Gets the function
    llvm::Function *theScanf = context.module->getFunction("scanf");
    
    // Build the call
    return context.builder.CreateCall(theScanf, scanfArgs);;     
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