#include "Program.hh"

#include "node.hh"

namespace SNode
{

void Program::createMain(CodeGenContext& context)
{
	llvm::FunctionType *funcType =
        llvm::FunctionType::get(context.builder.getInt32Ty(), llvm::Function::ExternalLinkage);
    llvm::Function* mainFunc = llvm::Function::Create(
        funcType, llvm::Function::ExternalLinkage, "main", context.module);

    llvm::BasicBlock* block = llvm::BasicBlock::Create(context.context, "entry", mainFunc);
    context.builder.SetInsertPoint(block);

    context.builder.CreateCall(context.module->getFunction("start"));

    context.builder.CreateRet(context.builder.getInt32(0));
}

llvm::Value* Program::codeGen(CodeGenContext& context) 
{
	/*for(size_t index = 0; index < globals.size(); ++index)
	{
		context.module->getOrInsertGlobal(globals[index]->id.name, context.builder.getInt32Ty());
		llvm::GlobalVariable *gVar = context.module->getNamedGlobal(globals[index]->id.name);
		gVar->setLinkage(llvm::GlobalValue::CommonLinkage);
		gVar->setAlignment(8); 
	}*/
	for(size_t index = 0; index < functions.size(); ++index)
		functions[index]->codeGen(context);

	createMain(context);

	return nullptr;
}

void Program::print(size_t tabs) const
{
    printTabs(tabs);
    std::cout << "Program: " << std::endl;
    for(size_t index = 0; index < functions.size(); ++index)
        functions[index]->print(tabs + 1);
    for(size_t index = 0; index < globals.size(); ++index)
        globals[index]->print(tabs + 1);
}
void Program::createSymbolTable(SymbolTable& table) const
{
    for(auto itr = functions.begin(); itr != functions.end(); ++itr)
        (*itr)->createSymbolTable(table);
}

}