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
    // virtual llvm::Value* codeGen(CodeGenContext& context) { }
    void print(size_t tabs = 0) const override
    {
        printTabs(tabs);
        std::cout << "VariableAssignment: " << std::endl;

        id.print(tabs + 1);

        printTabs(tabs + 1);
        std::cout << "Expression:" << std::endl;
        assignmentExpr->print(tabs + 1);
    }
    void createSymbolTable(SymbolTable& table, std::string, size_t*) const override
    {
        table.insertToCurrentSubtable(id.name, assignmentExpr->getExpressionType());
    }
};

}

#endif // VARIABLE_ASSIGNMENT_H