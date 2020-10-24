#include "FunctionCall.hh"

#include "node.hh"

namespace SNode
{

llvm::Value* FunctionCall::codeGen(CodeGenContext&) { return nullptr; }
void FunctionCall::print(size_t tabs) const
{
    printTabs(tabs);
    std::cout << "FunctionCall:" << std::endl;

    id.print(tabs + 1);

    if(parameters.size() > 0)
    {
        printTabs(tabs + 1);
        std::cout << "parameters:" << std::endl;
        for(size_t index = 0; index < parameters.size(); ++ index)
            parameters[index]->print(tabs + 1);
    }
}

Datatype FunctionCall::getExpressionType() const
{
    TableRow* row = this->symbolTable.searchCurrentSubtable(this->id.name);

    // Checks if the symbol was not declared
    if (!row)
        throw SingularityException(ExceptionType::UNDECLARED_VARIABLE, id.name + " was not declared.");
    // Checks that that symbols is a function and not a variable
    else if (row->getType() != FUNCTION)
        throw SingularityException(ExceptionType::VAR_CALLED_AS_FUNCTN, id.name + " is not a function.");
    // Checks that the amount of parameters matches the argument count
    else 
    {
        FunctionTableRow* tableRow = reinterpret_cast<FunctionTableRow*>(&(*row) );

        if (tableRow->getArgumentCount() != parameters.size())
            throw SingularityException(ExceptionType::INVALID_ARG_COUNT);   
    }


    // Se puede inferir en algunos casos, ya veremos
    return Datatype::UNKNOWN;
}

std::vector<std::string> FunctionCall::getFunctionCalls()
{
    std::vector<std::string> calls;
    calls.push_back(std::string(this->id.name.c_str()));
    return  calls;
}

}