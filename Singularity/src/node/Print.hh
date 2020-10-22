#ifndef PRINT_H
#define PRINT_H

#include "node.hh"

namespace SNode
{

class Print : public Statement {
public:
    Expression& expression;
    Print(Expression& expression) :
        Statement(NodeTypes::Print), expression(expression) { }
    virtual llvm::Value* codeGen(CodeGenContext& context);
    void print(size_t tabs = 0) const override;
    void createSymbolTable(SymbolTable& table, std::string name, size_t* subtableCounter) const override;
};

}

#endif // PRINT_H