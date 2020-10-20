#ifndef OTHERWISE_H
#define OTHERWISE_H

#include "node.hh"

namespace SNode
{

class Otherwise : public Statement {
public:
    Block& block;
    Otherwise(Block& block) :  
         block(block) { }
    // virtual llvm::Value* codeGen(CodeGenContext& context) { }
    void print(size_t tabs = 0) const override
    {
        printTabs(tabs);
        std::cout << "Otherwise: " << std::endl;

        block.print(tabs + 1);
    }

    void createSymbolTable(SymbolTable& table, std::string name, size_t* subtableCounter) const override
    {
        name += "_" + std::to_string( (*subtableCounter)++);
        table.initializeScope(name);

        size_t* newSubtableCounter = new size_t(0);
        block.createSymbolTable(table, name, newSubtableCounter);
        delete newSubtableCounter;
        table.finalizeScope();
    }
};

}

#endif // OTHERWISE_H