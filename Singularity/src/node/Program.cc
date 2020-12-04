#include "Program.hh"

#include "node.hh"

namespace SNode
{

llvm::BasicBlock* Program::createMain(CodeGenContext& context)
{
	llvm::FunctionType *funcType =
        llvm::FunctionType::get(context.builder.getInt32Ty(), llvm::Function::ExternalLinkage);
    llvm::Function* mainFunc = llvm::Function::Create(
        funcType, llvm::Function::ExternalLinkage, "main", context.module);

    llvm::BasicBlock* block = llvm::BasicBlock::Create(context.context, "entry", mainFunc);

    return block;

}

llvm::Value* Program::codeGen(CodeGenContext& context) 
{

    llvm::BasicBlock* blockMain = createMain(context);
    context.builder.SetInsertPoint(blockMain);

    context.pushBlock(nullptr);
    for(size_t index = 0; index < globals.size(); ++index)
	{
        llvm::Value* expression = globals[index]->assignmentExpr->codeGen(context);
        // Creates the variable
        llvm::ConstantInt* const_int_val = context.builder.getInt64(4000);

		llvm::Value* var = context.module->getOrInsertGlobal(llvm::StringRef(globals[index]->id.name), expression->getType() );
		llvm::GlobalVariable *gVar = context.module->getNamedGlobal(llvm::StringRef(globals[index]->id.name));
		gVar->setLinkage(llvm::GlobalValue::ExternalLinkage);
		gVar->setAlignment(8); 
        gVar->setInitializer(context.builder.getInt64(0));

        llvm::StoreInst* store = context.builder.CreateStore(expression, gVar);

        context.insertVar( globals[index]->id.name, gVar);
	}


	for(size_t index = 0; index < functions.size(); ++index)
		functions[index]->codeGen(context);

	
        

    context.builder.SetInsertPoint(blockMain);
    

    context.builder.CreateCall(context.module->getFunction("start"));

    context.builder.CreateRet(context.builder.getInt32(0));




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