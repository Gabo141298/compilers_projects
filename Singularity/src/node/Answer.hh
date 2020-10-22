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
    void createSymbolTable(SymbolTable& table, std::string name, size_t* subtableCounter) const;
};

}

#endif // ANSWER_H