#include "codegen.hh"
#include "../node/node.hh"
#include "../node/Program.hh"

#include <iostream>
#include <system_error>

SNode::CodeGenContext::CodeGenContext()
        : block ( nullptr)//new CodeGenBlock(llvm::BasicBlock::Create(context), nullptr) )
        , module ( new llvm::Module("Singularity", context) )
        , builder ( *(new llvm::IRBuilder<llvm::NoFolder>(this->context)) )
        , currentFunc (nullptr)
    {
        formatInt = createString(*this, "%lld");
        formatDouble = createString(*this, "%lf");
        //formatString = createString(*this, "%s");
    }

/* Compile the AST into a module */
void SNode::CodeGenContext::generateCode(SNode::Program& root, std::string filename)
{
	createPrintf();
    root.codeGen(*this);

    llvm::raw_ostream* stream = &llvm::outs();
    std::error_code ec;
    if(filename.length())
        stream = new llvm::raw_fd_ostream(filename, ec);

    module->print(*stream, nullptr);
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

void SNode::CodeGenContext::createPrintf()
{
	std::vector<llvm::Type *> args;
	args.push_back(llvm::Type::getInt8PtrTy(context));
	/*`true` specifies the function as variadic*/
	llvm::FunctionType *printfType = llvm::FunctionType::get(builder.getInt32Ty(), args, true);
	llvm::Function::Create(printfType, llvm::Function::ExternalLinkage, "printf", module);
}