#ifndef COMPARISON_OPERATION_H
#define COMPARISON_OPERATION_H

#include "node.hh"

namespace SNode
{

class ComparisonOperation : public Expression {
public:
    Expression& left;
    ComparisonOperator op;
    Expression& right;
    ComparisonOperation(Expression& left, ComparisonOperator op, Expression& right) :
        Expression(NodeTypes::ComparisonOperation), left(left), op(op), right(right) { }
    virtual llvm::Value* codeGen(CodeGenContext& context);
    void print(size_t tabs = 0) const override;
    Datatype getExpressionType() const override;
};

}

#endif // COMPARISON_OPERATION_H