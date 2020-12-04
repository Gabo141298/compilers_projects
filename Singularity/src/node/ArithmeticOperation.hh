#ifndef ARITHMETIC_OPERATION_H
#define ARITHMETIC_OPERATION_H

#include "node.hh"

namespace SNode
{

class ArithmeticOperation : public Expression {
public:
    Expression& left;
    ArithmeticOperator op;
    Expression& right;
    ArithmeticOperation(Expression& left, ArithmeticOperator op, Expression& right) :
        Expression(NodeTypes::ArithmeticOperation ), left(left), op(op), right(right) { }
    virtual llvm::Value* codeGen(CodeGenContext& context);
    void print(size_t tabs = 0) const override;
    Datatype getExpressionType() const override;
    std::vector<std::string> getFunctionCalls() override;
    llvm::Value* getDoubleFromString (CodeGenContext& context, llvm::Value* string);
    llvm::Value* createArithmeticOperation(CodeGenContext& context, llvm::Value* leftValue, llvm::Value* rightValue);
    llvm::Value* createIntOperation(CodeGenContext& context, llvm::Value* left, llvm::Value* right);
    llvm::Value* createFloatOperation(CodeGenContext& context, llvm::Value* left, llvm::Value* right);

};

}

#endif // ARITHMETIC_OPERATION_H
