#ifndef OTHERWISE_H
#define OTHERWISE_H

#include "Block.hh"
#include "node.hh"

namespace SNode
{

class Otherwise : public Statement {
public:
    Block& block;
    Otherwise(Block& block) :  
        Statement( NodeTypes::Otherwise), block(block) { }
    virtual llvm::Value* codeGen(CodeGenContext& context);
    void print(size_t tabs = 0) const override;

    void createSymbolTable(SymbolTable& table, std::string name, size_t* subtableCounter) const override;
};

}

#endif // OTHERWISE_H