#ifndef READ_H
#define READ_H

#include "node.hh"

namespace SNode
{

class Read : public Statement {
public:
    Identifier& identifier;

    Read( Identifier& identifier) :
        Statement(NodeTypes::Read), identifier(identifier) { }
    virtual llvm::Value* codeGen(CodeGenContext& context);
    void print(size_t tabs = 0) const override;
    void createSymbolTable(SymbolTable& table, std::string, size_t*) const override;
};

}

#endif // READ_H
