#ifndef PRINT_H
#define PRINT_H

#include "node.hh"

namespace SNode
{

class Print : public Statement {
public:
    Expression& expression;
    Print(Expression& expression) :
        expression(expression) { }
    virtual llvm::Value* codeGen(CodeGenContext& context);
    void print(size_t tabs = 0) const override;
};

}

#endif // PRINT_H