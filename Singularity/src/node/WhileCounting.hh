#ifndef WHILE_COUNTING_H
#define WHILE_COUNTING_H

#include "Block.hh"
#include "node.hh"

namespace SNode
{

class WhileCounting : public Statement {
public:
    Identifier& counter;
    Expression& beginValue;
    Expression& endValue;
    Block& block;
    WhileCounting(Identifier& counter, Expression& beginValue, Expression& endValue, Block& block) :
        counter(counter), beginValue(beginValue), endValue(endValue), block(block) { }
    virtual llvm::Value* codeGen(CodeGenContext& context);
    void print(size_t tabs = 0) const override;

    void createSymbolTable(SymbolTable& table, std::string name, size_t* subtableCounter) const override;
};

}

#endif // WHILE_COUNTING_H