#ifndef POSITION_ACCESS_H
#define POSITION_ACCESS_H

#include "node.hh"
#include "Position.hh"

namespace SNode
{

class PositionAccess : public Expression {
public: 
    Identifier& id;
    Position& position;
    SymbolTable& symbolTable;
    PositionAccess(Identifier& id, Position& position, SymbolTable& symbolTable) :
        Expression(NodeTypes::PositionAccesss), id(id), position(position), symbolTable(symbolTable) {}
    virtual llvm::Value* codeGen(CodeGenContext& context);
    void print(size_t tabs = 0) const override;
    Datatype getExpressionType() const override;
};

}

#endif // POSITION_ACCESS_H