#ifndef BLOCK_H
#define BLOCK_H

#include "node.hh"

namespace SNode
{

class Block : public Statement {
public:
    StatementList statements;
    Block() { }
    virtual llvm::Value* codeGen(CodeGenContext& context);
    void print(size_t tabs = 0) const override;
    void createSymbolTable(SymbolTable& table, std::string name, size_t* subtableCounter) const override;
};

}

#endif // BLOCK_H