#ifndef PROGRAM_H
#define PROGRAM_H

#include "Function.hh"
#include "node.hh"
#include "VariableAssignment.hh"

namespace SNode
{

class Program : public Node {
	llvm::BasicBlock* createMain(CodeGenContext& context);
public:
    FunctionList functions;
    GlobalList globals;
    Program(): Node(NodeTypes::Program) {}
    virtual llvm::Value* codeGen(CodeGenContext& context);
    void print(size_t tabs = 0) const override;
    void createSymbolTable(SymbolTable& table) const;
};

}

#endif // PROGRAM_H