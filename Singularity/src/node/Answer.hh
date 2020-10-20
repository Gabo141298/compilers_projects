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
    // virtual llvm::Value* codeGen(CodeGenContext& context) { }
    void print(size_t tabs = 0) const override
    {
        printTabs(tabs);
        std::cout << "Answer:" << std::endl;

        printTabs(tabs + 1);
        std::cout << "Expression:" << std::endl;
        returnExpression.print(tabs + 1);
    }
};

}

#endif // ANSWER_H