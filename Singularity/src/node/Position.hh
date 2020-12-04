#ifndef POSITION_H
#define POSITION_H

#include "node.hh"

namespace SNode
{

class Position : public Expression {
public:
    Position(NodeTypes type = NodeTypes::Position): Expression(type) {}
    virtual inline void checkPosition() { }
    virtual llvm::Value* calculateMemDir(CodeGenContext& context, llvm::Value* ptr) { return nullptr; }
};

class ListPosition : public Position {
public:
    Expression& position;
    ListPosition(Expression& position) :
        Position(NodeTypes::ListPosition), position(position) { }
    virtual llvm::Value* codeGen(CodeGenContext& context);
    void print(size_t tabs = 0) const override;
    void checkPosition();
    virtual llvm::Value* calculateMemDir(CodeGenContext& context, llvm::Value* ptr);
};

class MatrixPosition : public Position {
public:
    Expression& row;
    Expression& col;
    MatrixPosition(Expression& row, Expression& col) :
        Position(NodeTypes::MatrixPosition), row(row), col(col) { }
    virtual llvm::Value* codeGen(CodeGenContext& context);
    void print(size_t tabs = 0) const override;
    void checkPosition();
    virtual llvm::Value* calculateMemDir(CodeGenContext& context, llvm::Value* ptr);
};

}

#endif // POSITION_H