#ifndef ANSWER_H
#define ANSWER_H

#include "node.hh"

namespace SNode
{

class Answer : public Statement {
public:
    Expression& returnExpression;
    Answer(Expression& returnExpression) :
        returnExpression(returnExpression) {}
    virtual llvm::Value* codeGen(CodeGenContext& context);
    void print(size_t tabs = 0) const override;
};

}

#endif // ANSWER_H