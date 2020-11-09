#include <stack>
#include <llvm/Module.h>
#include <llvm/Function.h>
#include <llvm/Type.h>
#include <llvm/DerivedTypes.h>
#include <llvm/LLVMContext.h>
#include <llvm/PassManager.h>
#include <llvm/Instructions.h>
#include <llvm/CallingConv.h>
#include <llvm/Bitcode/ReaderWriter.h>
#include <llvm/Analysis/Verifier.h>
#include <llvm/Assembly/PrintModulePass.h>
#include <llvm/Support/IRBuilder.h>
#include <llvm/ModuleProvider.h>
#include <llvm/Target/TargetSelect.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/ExecutionEngine/JIT.h>
#include <llvm/Support/raw_ostream.h>

class SNode::Program;

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
    CodeGenContext() { module = new llvm::Module("Singularity", context); }
    
    void generateCode(SNode::Program& root);
    llvm::GenericValue runCode();
    std::map<std::string, llvm::Value*>& locals() { return blocks.top()->locals; }
    llvm::BasicBlock *currentBlock() { return blocks.top()->block; }
    void pushBlock(llvm::BasicBlock *block) { blocks.push(new CodeGenBlock()); blocks.top()->block = block; }
    void popBlock() { CodeGenBlock *top = blocks.top(); blocks.pop(); delete top; }
};