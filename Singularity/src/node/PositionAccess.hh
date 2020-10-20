#ifndef POSITION_ACCESS_H
#define POSITION_ACCESS_H

#include "node.hh"

namespace SNode
{

class PositionAccess : public Expression {
public: 
    Identifier& id;
    Position& position;
    PositionAccess(Identifier& id, Position& position) :
        id(id), position(position) {}
    // virtual llvm::Value* codeGen(CodeGenContext& context) { }
    void print(size_t tabs = 0) const override
    {
        printTabs(tabs);
        std::cout << "PositionAccess: " << std::endl;

        id.print(tabs + 1);

        position.print(tabs + 1);
    }
    inline Datatype getExpressionType() const override
    {
        if(!position.validPosition())
            std::cout << "Error: invalid position" << std::endl;
        return Datatype::UNKNOWN;
    }
};

}

#endif // POSITION_ACCESS_H