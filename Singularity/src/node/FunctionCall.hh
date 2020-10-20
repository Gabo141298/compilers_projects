#ifndef FUNCTION_CALL_H
#define FUNCTION_CALL_H

#include "node.hh"

namespace SNode
{

class FunctionCall : public Expression {
public:
    const Identifier& id;
    ExpressionList parameters;
    FunctionCall(const Identifier& id) :
        id(id) { }
    FunctionCall(const Identifier& id, const ExpressionList& parameters) :
        id(id), parameters(parameters) { }
    // virtual llvm::Value* codeGen(CodeGenContext& context) { }
    void print(size_t tabs = 0) const override
    {
        printTabs(tabs);
        std::cout << "FunctionCall:" << std::endl;

        id.print(tabs + 1);

        if(parameters.size() > 0)
        {
            printTabs(tabs + 1);
            std::cout << "parameters:" << std::endl;
            for(size_t index = 0; index < parameters.size(); ++ index)
                parameters[index]->print(tabs + 1);
        }
    }
    inline Datatype getExpressionType() const override
    {
        // Se puede inferir en algunos casos, ya veremos
        return Datatype::UNKNOWN;
    }
};

}

#endif // FUNCTION_CALL_H