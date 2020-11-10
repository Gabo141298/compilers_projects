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

#pragma GCC diagnostic pop

namespace SNode
{
class Program;

class CodeGenBlock {
public:
    llvm::BasicBlock *block;
    std::map<std::string, llvm::Value*> locals;
};

class CodeGenContext {
    std::stack<CodeGenBlock *> blocks;
    llvm::Function *mainFunction;

public:
    llvm::LLVMContext context;
    llvm::Module *module;
    llvm::IRBuilder<>& builder;
    CodeGenContext() 
        : module (new llvm::Module("Singularity", context))
        , builder( *(new llvm::IRBuilder<>(this->context)) )
    {
    }
    
    void generateCode(Program& root);
    //llvm::GenericValue runCode();
    std::map<std::string, llvm::Value*>& locals() { return blocks.top()->locals; }
    llvm::BasicBlock *currentBlock() { return blocks.top()->block; }
    void pushBlock(llvm::BasicBlock *block) { blocks.push(new CodeGenBlock()); blocks.top()->block = block; }
    void popBlock() { CodeGenBlock *top = blocks.top(); blocks.pop(); delete top; }
};

}

#endif // CODEGEN_H