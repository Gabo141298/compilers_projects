#ifndef IF_H
#define IF_H

#include "Block.hh"
#include "node.hh"

namespace SNode
{

class If : public Statement {
public:
    Expression& condition;
    Block& block;
    Statement* otherwise;
    If(Expression& condition, Block& block, Statement* otherwise = nullptr) :
        condition(condition), block(block), otherwise(otherwise) { }
    virtual llvm::Value* codeGen(CodeGenContext& context);
    void print(size_t tabs = 0) const override;

    void createSymbolTable(SymbolTable& table, std::string name, size_t* subtableCounter) const override;
};

}

#endif // IF_H