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

struct ReturnInfo
{
    llvm::Value* returnValue;
    llvm::BasicBlock* block;

    ReturnInfo(llvm::Value* returnValue, llvm::BasicBlock* block)
        : returnValue(returnValue)
        , block(block)
    {
    }
};

struct VariableInfo
{
    llvm::Value* value;
    llvm::Value* row;
    llvm::Value* col;

    VariableInfo(llvm::Value* value, llvm::Value* row = nullptr, llvm::Value* col = nullptr)
        : value(value)
        , row(row)
        , col(col)
    {
    }
};

class CodeGenBlock {
public:
    llvm::BasicBlock *block;
    CodeGenBlock* parent;
    std::map<std::string, VariableInfo*> locals;

    CodeGenBlock(llvm::BasicBlock* block, CodeGenBlock* parent)
        : parent(parent)
        , block(block)
    {
    }
    llvm::Value* searchVar(const std::string& name);

    VariableInfo* searchVarInfo(const std::string& name);

    bool tryInsertVar(const std::string& name, llvm::Value* value, llvm::Value* row = nullptr, llvm::Value* col = nullptr);

    void insertVar(const std::string& name, llvm::Value* value, llvm::Value* row = nullptr, llvm::Value* col = nullptr);
};

class CodeGenContext {
    CodeGenBlock* block;
    llvm::Function *mainFunction;

public:
    llvm::LLVMContext context;
    llvm::Module *module;
    llvm::DataLayout dataLayout;
    llvm::IRBuilder<llvm::NoFolder>& builder;

    llvm::Function* dummy;

    llvm::BasicBlock* initBlock;
    llvm::BasicBlock* exitBlock;
    std::vector<llvm::BasicBlock*> functionBlocks;
    std::vector<ReturnInfo> returns;

    // Pointers to memory allocated with malloc that need to be freed.
    std::vector<llvm::Value*> heapMemAlloc;

    llvm::Value* formatInt;
    llvm::Value* formatDouble;
    llvm::Value* formatString;
    CodeGenContext();
    
    void generateCode(Program& root, std::string filename = "");
    llvm::BasicBlock *currentBlock() { return this->block->block; }
    inline void pushBlock(llvm::BasicBlock *block) { this->block = new CodeGenBlock(block, this->block); }
    inline void replaceBlock(llvm::BasicBlock *block) { this->block->block = block; }
    inline void popBlock() { CodeGenBlock* temp = this->block->parent; delete this->block; this->block = temp; }

    inline llvm::Value* searchVar(const std::string& name) { return block->searchVar(name); }
    VariableInfo* searchVarInfo(const std::string& name) { return block->searchVarInfo(name); }
    void insertVar(const std::string& name, llvm::Value* value, llvm::Value* row = nullptr, llvm::Value* col = nullptr) { block->insertVar(name, value, row, col); }

    void freeFunction();
    inline void insertFunctionBlock(llvm::BasicBlock* block) { this->functionBlocks.push_back(block); }

    void createPrintf();

    void createScanf();

    void createStrcmp();

    void createStrtod();

    void createStrtol();

    void createMalloc();

    void createFree();
};

}

#endif // CODEGEN_H
