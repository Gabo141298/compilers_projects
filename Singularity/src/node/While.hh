#ifndef WHILE_H
#define WHILE_H

#include "Block.hh"
#include "node.hh"

namespace SNode
{

class While : public Statement {
public:
    Expression& condition;
    Block& block;
    While(Expression& condition, Block& block) :
        Statement(NodeTypes::While), condition(condition), block(block) { }
    virtual llvm::Value* codeGen(CodeGenContext& context);
    void print(size_t tabs = 0) const override;
    void createSymbolTable(SymbolTable& table, std::string name, size_t* subtableCounter) const override;
};

}

#endif // WHILE_H