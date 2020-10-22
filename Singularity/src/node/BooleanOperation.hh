#ifndef BOOLEAN_OPERATION_H
#define BOOLEAN_OPERATION_H

#include "node.hh"

namespace SNode
{

class BooleanOperation : public Expression {
public:
    Expression& left;
    BooleanOperator op;
    Expression& right;
    BooleanOperation(Expression& left, BooleanOperator op, Expression& right) :
        Expression(NodeTypes::BooleanOperation), left(left), op(op), right(right) { }
    virtual llvm::Value* codeGen(CodeGenContext& context);
    void print(size_t tabs = 0) const override;
    Datatype getExpressionType() const override;
};

}

#endif // BOOLEAN_OPERATION_H