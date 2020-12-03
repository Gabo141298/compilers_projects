#include "codegen.hh"
#include "../node/node.hh"
#include "../node/Program.hh"

#include <iostream>
#include <system_error>

SNode::CodeGenContext::CodeGenContext()
        : block ( nullptr)//new CodeGenBlock(llvm::BasicBlock::Create(context), nullptr) )
        , module ( new llvm::Module("Singularity", context) )
        , builder ( *(new llvm::IRBuilder<llvm::NoFolder>(this->context)) )
    {
        formatInt = createString(*this, "%lld");
        formatDouble = createString(*this, "%lf");
        //formatString = createString(*this, "%s");
    }

/* Compile the AST into a module */
void SNode::CodeGenContext::generateCode(SNode::Program& root, std::string filename)
{
	createPrintf();
    createScanf();
    createStrcmp();
    createStrtol();

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

bool SNode::CodeGenBlock::tryInsertVar(const std::string& name, llvm::Value* value)
{
    llvm::Value* currentValue = locals[name];
    if(currentValue)
    {
        this->locals[name] = value;
        return true;
    }
    else if(parent)
        return this->parent->tryInsertVar(name, value);
    else
        return false;
}

void SNode::CodeGenBlock::insertVar(const std::string &name, llvm::Value *value)
{
    if(! tryInsertVar(name, value))
    {
        this->locals[name] = value;
    }
}

void SNode::CodeGenContext::createPrintf()
{
	std::vector<llvm::Type *> args;
	args.push_back(llvm::Type::getInt8PtrTy(context));
	/*`true` specifies the function as variadic*/
	llvm::FunctionType *printfType = llvm::FunctionType::get(builder.getInt32Ty(), args, true);
	llvm::Function::Create(printfType, llvm::Function::ExternalLinkage, "printf", module);
}

void SNode::CodeGenContext::createStrcmp()
{
    std::vector<llvm::Type *> args;
    args.push_back(llvm::Type::getInt8PtrTy(context));
    args.push_back(llvm::Type::getInt8PtrTy(context));
    llvm::FunctionType *strcmpType = llvm::FunctionType::get(builder.getInt32Ty(), args, false);
    llvm::Function::Create(strcmpType, llvm::Function::ExternalLinkage, "strcmp", module);
}

void SNode::CodeGenContext::createStrtol()
{
    std::vector<llvm::Type *> args;
    args.push_back(llvm::Type::getInt8PtrTy(context));
    args.push_back(llvm::Type::getInt8PtrTy(context));
    args.push_back(llvm::Type::getInt32Ty(context));

    llvm::FunctionType *strTolType = llvm::FunctionType::get(builder.getInt64Ty(), args, false);
    llvm::Function::Create(strTolType, llvm::Function::ExternalLinkage, "strtol", module);
}

void SNode::CodeGenContext::createScanf()
{
	std::vector<llvm::Type *> args;
	args.push_back(llvm::Type::getInt8PtrTy(context));
	/*`true` specifies the function as variadic*/
	llvm::FunctionType *scanfType = llvm::FunctionType::get(builder.getInt64Ty(), args, true);
	llvm::Function::Create(scanfType, llvm::Function::ExternalLinkage, "scanf", module);
}

void SNode::CodeGenContext::freeFunction()
{
    this->returns.erase(this->returns.begin(), this->returns.end());
    this->functionBlocks.erase(this->functionBlocks.begin(), this->functionBlocks.end());
}
