#include "codegen.hh"
#include "../node/Program.hh"

#include <iostream>

/* Compile the AST into a module */
void SNode::CodeGenContext::generateCode(SNode::Program& root)
{
    std::cout << "Generating code" << std::endl;
    root.codeGen(*this);
    module->print(llvm::errs(), nullptr);
}

llvm::Value* SNode::CodeGenBlock::searchVar(const std::string& name)
{
    llvm::Value* value = locals[name];
    if(value)
        return value;
    else if(parent)
        return parent->searchVar(name);
    return nullptr;
}