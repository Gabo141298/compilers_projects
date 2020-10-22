#ifndef FUNCTION_H
#define FUNCTION_H

#include "Block.hh"
#include "node.hh"

namespace SNode
{

class Function : public Node {
public:
    const Identifier& id;
    VariableList arguments;
    Block& block;
    Function(const Identifier& id, Block& block) :
        Node(NodeTypes::Function), id(id), block(block) { }
    Function(const Identifier& id, 
            const VariableList& arguments, Block& block) :
        Node(NodeTypes::Function), id(id), arguments(arguments), block(block){ }
    virtual llvm::Value* codeGen(CodeGenContext& context);
    void print(size_t tabs = 0) const override;

    void createSymbolTable(SymbolTable& table) const;
};

}

#endif // FUNCTION_H