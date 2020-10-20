#ifndef READ_H
#define READ_H

#include "node.hh"

namespace SNode
{

class Read : public Statement {
public:
    Identifier& identifier;
    Read(const std::string& identifier) :
        identifier(*(new SNode::Identifier(identifier))) { }
    // virtual llvm::Value* codeGen(CodeGenContext& context) { }
    void print(size_t tabs = 0) const override
    {
        printTabs(tabs);
        std::cout << "Read: " << std::endl;
        identifier.print(tabs + 1);
    }
    void createSymbolTable(SymbolTable& table, std::string, size_t*) const override
    {
        // Can't infer datatype that is read from an input.
        table.insertToCurrentSubtable(identifier.name, Datatype::UNKNOWN);
    }
};

}

#endif // READ_H