#ifndef IF_H
#define IF_H

#include "node.hh"

namespace SNode
{

class If : public Statement {
public:
    Expression& condition;
    Block& block;
    Statement* otherwise;
    If(Expression& condition, Block& block, Statement* otherwise = nullptr) :
        condition(condition), block(block), otherwise(otherwise) { }
    // virtual llvm::Value* codeGen(CodeGenContext& context) { }
    void print(size_t tabs = 0) const override
    {
        printTabs(tabs);
        std::cout << "If: " << std::endl;

        printTabs(tabs + 1);
        std::cout << "Condition:" << std::endl;
        condition.print(tabs + 1);

        block.print(tabs + 1);

        if (otherwise)
            otherwise->print(tabs);

        block.print(tabs + 1);
    }

    void createSymbolTable(SymbolTable& table, std::string name, size_t* subtableCounter) const override
    {
        Datatype conditionType = condition.getExpressionType();
        if( conditionType == Datatype::BOOLEAN || conditionType == Datatype::UNKNOWN )
        {
            std::string newName = name + "_" + std::to_string( (*subtableCounter)++);
            table.initializeScope(newName);

            size_t* newSubtableCounter = new size_t(0);
            block.createSymbolTable(table, newName, newSubtableCounter);
            delete newSubtableCounter;
            table.finalizeScope();

            if(otherwise)
                otherwise->createSymbolTable(table, name, subtableCounter);
        }
        else
        {
            std::cout << "Error: if needs a boolean expression as its condition." << std::endl;
        }
    }
};

}

#endif // IF_H