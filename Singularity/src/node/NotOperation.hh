#ifndef NOT_OPERATION_H
#define NOT_OPERATION_H

#include "node.hh"

namespace SNode
{

class NotOperation : public Expression {
public:
    Expression& expression;
    NotOperation(Expression& expression) :
        Expression(NodeTypes::NotOperation), expression(expression) { }
    virtual llvm::Value* codeGen(CodeGenContext& context);
    void print(size_t tabs = 0) const override;
    Datatype getExpressionType() const override;
    inline std::vector<std::string> getFunctionCalls() override {return this->expression.getFunctionCalls();};

};

}

#endif // NOT_OPERATION_H