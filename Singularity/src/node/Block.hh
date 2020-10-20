#ifndef BLOCK_H
#define BLOCK_H

#include "node.hh"

namespace SNode
{

class Block : public Statement {
public:
    StatementList statements;
    Block() { }
    // virtual llvm::Value* codeGen(CodeGenContext& context) { }
    void print(size_t tabs = 0) const override
    {
        printTabs(tabs);
        std::cout << "Block: " << std::endl;
        
        printTabs(tabs + 1);
        std::cout << "Statements:" << std::endl;
        for(size_t index = 0; index < statements.size(); ++index)
            statements[index]->print(tabs + 1);
    }
    void createSymbolTable(SymbolTable& table, std::string name, size_t* subtableCounter) const override
    {
        for(auto itr = statements.begin(); itr != statements.end(); ++itr)
        {
            (*itr)->createSymbolTable(table, name, subtableCounter);
        }
    }
};

}

#endif // BLOCK_H