#ifndef DATA_POSITION_ASSIGNMENT_H
#define DATA_POSITION_ASSIGNMENT_H

#include "node.hh"

namespace SNode
{

class DataPositionAssignment : public Statement {
public:
    Identifier& id;
    Position& position;
    Expression& expression;
    DataPositionAssignment(Identifier& id, Position& position, Expression& expression) : 
        id(id), position(position), expression(expression) { }
    // virtual llvm::Value* codeGen(CodeGenContext& context) { }
    void print(size_t tabs = 0) const override
    {
        printTabs(tabs);
        std::cout << "DataPositionAssignment: " << std::endl;

        id.print(tabs + 1);

        printTabs(tabs + 1);
        std::cout << "Position:" << std::endl;
        position.print(tabs + 1);

        printTabs(tabs + 1);
        std::cout << "Expression:" << std::endl;
        expression.print(tabs + 1);
    }
};

}

#endif // DATA_POSITION_ASSIGNMENT_H