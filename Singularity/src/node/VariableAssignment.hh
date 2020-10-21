#ifndef VARIABLE_ASSIGNMENT_H
#define VARIABLE_ASSIGNMENT_H

#include "node.hh"

namespace SNode
{

class VariableAssignment : public Statement {
public:
    Identifier& id;
    Expression* assignmentExpr;
    VariableAssignment(Identifier& id, Expression* assignmentExpr) :
        id(id), assignmentExpr(assignmentExpr) { }
    virtual llvm::Value* codeGen(CodeGenContext& context);
    void print(size_t tabs = 0) const override;
    void createSymbolTable(SymbolTable& table, std::string, size_t*) const override;
};

}

#endif // VARIABLE_ASSIGNMENT_H