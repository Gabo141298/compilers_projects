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

    llvm::Function* currentFunc;

    llvm::Value* formatInt;
    llvm::Value* formatDouble;
    //llvm::Value* formatString;
    CodeGenContext();
    
    void generateCode(Program& root, std::string filename = "");
    llvm::BasicBlock *currentBlock() { return this->block->block; }
    inline void pushBlock(llvm::BasicBlock *block) { this->block = new CodeGenBlock(block, this->block); }
    inline void replaceBlock(llvm::BasicBlock *block) { this->block->block = block; }
    inline void popBlock() { CodeGenBlock* temp = this->block->parent; delete this->block; this->block = temp; }

    inline llvm::Value* searchVar(const std::string& name) { return block->searchVar(name); }
    inline void insertVar(const std::string& name, llvm::Value* value) { block->insertVar(name, value); }

    void createPrintf();
};

}

#endif // CODEGEN_H