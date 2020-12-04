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
    static llvm::Value* callPrintf(CodeGenContext& context, llvm::Value* expr);
    void print(size_t tabs = 0) const override;
    void createSymbolTable(SymbolTable& table, std::string name, size_t* subtableCounter) const override;
};

}

#endif // PRINT_H