#ifndef CODEGEN_H
#define CODEGEN_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

#include <stack>
#include <llvm/IR/Module.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/PassManager.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/CallingConv.h>
#include <llvm/IR/Verifier.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/Support/raw_ostream.h>
#include "llvm/IR/NoFolder.h"

#pragma GCC diagnostic pop

#include <iostream>

namespace SNode
{
class Program;

class CodeGenBlock {
public:
    llvm::BasicBlock *block;
    CodeGenBlock* parent;
    std::map<std::string, llvm::Value*> locals;

    CodeGenBlock(llvm::BasicBlock* block, CodeGenBlock* parent)
        : parent(parent)
        , block(block)
    {
    }
    llvm::Value* searchVar(const std::string& name);
    inline void insertVar(const std::string& name, llvm::Value* value) { this->locals[name] = value; }
};

class CodeGenContext {
    CodeGenBlock* block;
    llvm::Function *mainFunction;

public:
    llvm::LLVMContext context;
    llvm::Module *module;
    llvm::IRBuilder<llvm::NoFolder>& builder;

    std::string blockCaller;
    llvm::Function* currentFunc;
    CodeGenContext() 
        : block ( nullptr)//new CodeGenBlock(llvm::BasicBlock::Create(context), nullptr) )
        , module ( new llvm::Module("Singularity", context) )
        , builder ( *(new llvm::IRBuilder<llvm::NoFolder>(this->context)) )
        , currentFunc (nullptr)
    {
    }
    
    void generateCode(Program& root);
    //llvm::GenericValue runCode();
    //std::map<std::string, llvm::Value*>& locals() { return block->locals; }
    llvm::BasicBlock *currentBlock() { return this->block->block; }
    void pushBlock(llvm::BasicBlock *block) { this->block = new CodeGenBlock(block, this->block); }
    void popBlock() { CodeGenBlock* temp = this->block->parent; delete this->block; this->block = temp; }

    inline llvm::Value* searchVar(const std::string& name) { return block->searchVar(name); }
    inline void insertVar(const std::string& name, llvm::Value* value) { block->insertVar(name, value); }
};

}

#endif // CODEGEN_H