#ifndef POSITION_H
#define POSITION_H

#include "node.hh"

namespace SNode
{

class Position : public Expression {
public:
    virtual inline bool validPosition() { return false; }
};

class ListPosition : public Position {
public:
    Expression& position;
    ListPosition(Expression& position) :
        position(position) { }
    virtual llvm::Value* codeGen(CodeGenContext& context);
    void print(size_t tabs = 0) const override;
    bool validPosition();
};

class MatrixPosition : public Position {
public:
    Expression& row;
    Expression& col;
    MatrixPosition(Expression& row, Expression& col) :
        row(row), col(col) { }
    virtual llvm::Value* codeGen(CodeGenContext& context);
    void print(size_t tabs = 0) const override;
    bool validPosition();
};

}

#endif // POSITION_H