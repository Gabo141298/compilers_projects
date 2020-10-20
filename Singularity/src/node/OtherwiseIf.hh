#ifndef OTHERWISE_IF_H
#define OTHERWISE_IF_H

#include "node.hh"

namespace SNode
{

class OtherwiseIf : public Statement {
public:
    If& if_statement;
    OtherwiseIf(If& if_statement) : 
        if_statement( if_statement ) { }
    // virtual llvm::Value* codeGen(CodeGenContext& context) { }
    void print(size_t tabs = 0) const override
    {
        printTabs(tabs);
        std::cout << "Otherwise if: " << std::endl;

        if_statement.print(tabs + 1);
    }
    void createSymbolTable(SymbolTable& table, std::string name, size_t* subtableCounter) const override
    {
        if_statement.createSymbolTable(table, name, subtableCounter);
    }
};

}

#endif // OTHERWISE_IF_H