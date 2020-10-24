#ifndef FUNCTION_CALL_H
#define FUNCTION_CALL_H

#include "node.hh"

namespace SNode
{

class FunctionCall : public Expression {
public:
    const Identifier& id;
    SymbolTable& symbolTable;
    ExpressionList parameters;
    FunctionCall(const Identifier& id, SymbolTable& symbolTable) :
        Expression(NodeTypes::FunctionCall), id(id), symbolTable(symbolTable) { }
    FunctionCall(const Identifier& id, SymbolTable& symbolTable, const ExpressionList& parameters) :
        Expression(NodeTypes::FunctionCall), id(id), symbolTable(symbolTable), parameters(parameters) { }
    virtual llvm::Value* codeGen(CodeGenContext& context);
    void print(size_t tabs = 0) const override;
    Datatype getExpressionType() const override;
    std::vector<std::string> getFunctionCalls() override;

};

}

#endif // FUNCTION_CALL_H