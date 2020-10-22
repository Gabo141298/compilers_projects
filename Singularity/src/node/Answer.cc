#include "Answer.hh"

#include "node.hh"

namespace SNode
{

llvm::Value* Answer::codeGen(CodeGenContext& context) { return nullptr; }

void Answer::print(size_t tabs) const
{
    printTabs(tabs);
    std::cout << "Answer:" << std::endl;

    printTabs(tabs + 1);
    std::cout << "Expression:" << std::endl;
    returnExpression.print(tabs + 1);
}

void Answer::createSymbolTable(SymbolTable& table, std::string name, size_t* subtableCounter) const
{
	// getExpressionTye will manage the exception in case the symbol is not defined
    Datatype datatype = this->returnExpression.getExpressionType();

    TableRow* row = table.searchCurrentSubtable(name);
    if (row)
    {
    	// Asign the datatype to the return symbol in the table
    	row->setType(datatype);
    }
    
}


}