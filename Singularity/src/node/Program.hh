#ifndef PROGRAM_H
#define PROGRAM_H

#include "node.hh"

namespace SNode
{

class Program : public Node {
public:
    FunctionList functions;
    GlobalList globals;
    Program() {}
    // virtual llvm::Value* codeGen(CodeGenContext& context) { }
    void print(size_t tabs = 0) const override
    {
        printTabs(tabs);
        std::cout << "Program: " << std::endl;
        for(size_t index = 0; index < functions.size(); ++index)
            functions[index]->print(tabs + 1);
        for(size_t index = 0; index < globals.size(); ++index)
            globals[index]->print(tabs + 1);
    }
    void createSymbolTable(SymbolTable& table) const
    {
        for(auto itr = functions.begin(); itr != functions.end(); ++itr)
            (*itr)->createSymbolTable(table);
    }
};

}

#endif // PROGRAM_H