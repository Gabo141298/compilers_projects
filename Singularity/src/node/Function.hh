#ifndef FUNCTION_H
#define FUNCTION_H

#include "node.hh"

namespace SNode
{

class Function : public Node {
public:
    const Identifier& id;
    VariableList arguments;
    Block& block;
    Function(const Identifier& id, Block& block) :
        id(id), block(block) { }
    Function(const Identifier& id, 
            const VariableList& arguments, Block& block) :
        id(id), arguments(arguments), block(block) { }
    // virtual llvm::Value* codeGen(CodeGenContext& context) { }
    void print(size_t tabs = 0) const override
    {
        printTabs(tabs);
        std::cout << "Function:" << std::endl;

        printTabs(tabs + 1);
        std::cout << "FunctionName:" << std::endl;
        id.print(tabs + 1);

        if(arguments.size() > 0)
        {
            printTabs(tabs + 1);
            std::cout << "Arguments:" << std::endl;
            for(size_t index = 0; index < arguments.size(); ++ index)
                arguments[index]->print(tabs + 1);
        }

        block.print(tabs + 1);
    }

    void createSymbolTable(SymbolTable& table) const
    {
        table.initializeScope(id.name);

        for(auto itr = arguments.begin(); itr != arguments.end(); ++itr)
        {
            // Difficult to infer the datatype of the arguments, although maybe not impossible.
            table.insertToCurrentSubtable((*itr)->name, Datatype::UNKNOWN);
        }

        size_t* subtableCounter = new size_t(0);
        block.createSymbolTable(table, id.name, subtableCounter);
        delete subtableCounter;
        table.finalizeScope();
    }
};

}

#endif // FUNCTION_H