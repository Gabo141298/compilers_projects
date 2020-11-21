#include "Program.hh"

#include "node.hh"

namespace SNode
{

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