#ifndef WHILE_H
#define WHILE_H

#include "node.hh"

namespace SNode
{

class While : public Statement {
public:
    Expression& condition;
    Block& block;
    While(Expression& condition, Block& block) :
        condition(condition), block(block) { }
    // virtual llvm::Value* codeGen(CodeGenContext& context) { }
    void print(size_t tabs = 0) const override
    {
        printTabs(tabs);
        std::cout << "While: " << std::endl;

        printTabs(tabs + 1);
        std::cout << "Condition:" << std::endl;
        condition.print(tabs + 1);

        block.print(tabs + 1);
    }
    void createSymbolTable(SymbolTable& table, std::string name, size_t* subtableCounter) const override
    {
        Datatype conditionType = condition.getExpressionType();
        if( conditionType == Datatype::BOOLEAN || conditionType == Datatype::UNKNOWN )
        {
            name += "_" + std::to_string( (*subtableCounter)++);
            table.initializeScope(name);

            size_t* newSubtableCounter = new size_t(0);
            block.createSymbolTable(table, name, newSubtableCounter);
            delete newSubtableCounter;
            table.finalizeScope();
        }
        else
        {
            std::cout << "Error: while needs a boolean expression as its condition." << std::endl;
        }
    }
};

}

#endif // WHILE_H