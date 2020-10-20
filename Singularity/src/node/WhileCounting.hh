#ifndef WHILE_COUNTING_H
#define WHILE_COUNTING_H

#include "node.hh"

namespace SNode
{

class WhileCounting : public Statement {
public:
    Identifier& counter;
    Expression& beginValue;
    Expression& endValue;
    Block& block;
    WhileCounting(Identifier& counter, Expression& beginValue, Expression& endValue, Block& block) :
        counter(counter), beginValue(beginValue), endValue(endValue), block(block) { }
    // virtual llvm::Value* codeGen(CodeGenContext& context) { }
    void print(size_t tabs = 0) const override
    {
        printTabs(tabs);
        std::cout << "WhileCounting: " << std::endl;

        printTabs(tabs + 1);
        std::cout << "Counter:" << std::endl;
        counter.print(tabs + 1);

        printTabs(tabs + 1);
        std::cout << "BeginValue:" << std::endl;
        beginValue.print(tabs + 1);

        printTabs(tabs + 1);
        std::cout << "EndValue:" << std::endl;
        endValue.print(tabs + 1);

        block.print(tabs + 1);
    }

    void createSymbolTable(SymbolTable& table, std::string name, size_t* subtableCounter) const override
    {
        Datatype beginType = beginValue.getExpressionType();
        Datatype endType = endValue.getExpressionType();
        if( (beginType == Datatype::INTEGER || beginType == Datatype::UNKNOWN) 
            && (endType == Datatype::INTEGER || endType == Datatype::UNKNOWN) )
        {
            name += "_" + std::to_string( (*subtableCounter)++);
            table.initializeScope(name);

            table.insertToCurrentSubtable(counter.name, Datatype::INTEGER);

            size_t* newSubtableCounter = new size_t(0);
            block.createSymbolTable(table, name, newSubtableCounter);
            delete newSubtableCounter;
            table.finalizeScope();
        }
        else
        {
            std::cout << "Error: range of values in while counting must be defined by integers." << std::endl;
        }
    }
};

}

#endif // WHILE_COUNTING_H