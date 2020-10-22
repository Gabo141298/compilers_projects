#include "Print.hh"

#include "node.hh"

namespace SNode
{

llvm::Value* Print::codeGen(CodeGenContext& context) { return nullptr; }
void Print::print(size_t tabs) const
{
    printTabs(tabs);
    std::cout << "Print: " << std::endl;
    expression.print(tabs + 1);
}

void Print::createSymbolTable(SymbolTable& table, std::string name, size_t* subtableCounter) const
{
	// getExpressionTye will manage the exception in case the symbol is not defined
    this->expression.getExpressionType();
    	
}

}
