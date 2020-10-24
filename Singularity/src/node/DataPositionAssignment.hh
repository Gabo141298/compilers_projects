#ifndef DATA_POSITION_ASSIGNMENT_H
#define DATA_POSITION_ASSIGNMENT_H

#include "node.hh"
#include "Position.hh"

namespace SNode
{

class DataPositionAssignment : public Statement {
public:
    Identifier& id;
    Position& position;
    Expression& expression;
    DataPositionAssignment(Identifier& id, Position& position, Expression& expression) : 
        Statement(NodeTypes::DataPositionAssignment), id(id), position(position), expression(expression) { }
    virtual llvm::Value* codeGen(CodeGenContext& context);
    void print(size_t tabs = 0) const override;
    void createSymbolTable(SymbolTable& table, std::string name, size_t* subtableCounter) const override;
};

}

#endif // DATA_POSITION_ASSIGNMENT_H