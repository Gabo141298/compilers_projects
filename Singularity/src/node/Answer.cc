#include "Answer.hh"

#include "node.hh"

namespace SNode
{

llvm::Value* Answer::codeGen(CodeGenContext& context)
{
    llvm::Value* returnVal = returnExpression.codeGen(context);
    context.returns.push_back(ReturnInfo(returnVal, context.builder.GetInsertBlock()));
    return returnVal;
}

void Answer::print(size_t tabs) const
{
    printTabs(tabs);
    std::cout << "Answer:" << std::endl;

    printTabs(tabs + 1);
    std::cout << "Expression:" << std::endl;
    returnExpression.print(tabs + 1);
}

void Answer::createSymbolTable(SymbolTable& table, std::string name, size_t*) const
{
	// getExpressionTye will manage the exception in case the symbol is not defined
    Datatype datatype = this->returnExpression.getExpressionType();

    TableRow* row = table.searchCurrentSubtable(name);
    if (row)
    {
    	// Asign the datatype to the return symbol in the table
    	reinterpret_cast<FunctionTableRow*>(row)->setReturnType(datatype);
    }
    
}


}