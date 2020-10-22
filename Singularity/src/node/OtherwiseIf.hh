#ifndef OTHERWISE_IF_H
#define OTHERWISE_IF_H

#include "If.hh"
#include "node.hh"

namespace SNode
{

class OtherwiseIf : public Statement {
public:
    If& if_statement;
    OtherwiseIf(If& if_statement) : 
        Statement(NodeTypes::Otherwiseif), if_statement( if_statement ) { }
    virtual llvm::Value* codeGen(CodeGenContext& context);
    void print(size_t tabs = 0) const override;
    void createSymbolTable(SymbolTable& table, std::string name, size_t* subtableCounter) const override;
};

}

#endif // OTHERWISE_IF_H