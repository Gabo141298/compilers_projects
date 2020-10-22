#ifndef DATA_STRUCTURE_H
#define DATA_STRUCTURE_H

#include "node.hh"

namespace SNode
{

class DataStructure : public Expression {
    public:
    DataStructure(NodeTypes type = NodeTypes::DataStructure)
        : Expression(type)
    {}
};

class List : public DataStructure {
public:
    std::vector<Value> values;
    List() : DataStructure(NodeTypes::List) {}
    virtual llvm::Value* codeGen(CodeGenContext& context);
    void print(size_t tabs = 0) const override;
    inline Datatype getExpressionType() const override
    {
        return Datatype::LIST;
    }
};

class Matrix : public DataStructure {
public:
    Value* row;
    Value* col;
    std::vector<std::vector<Value>> matrix;
    Matrix(Value* row, Value* col) :
        DataStructure(NodeTypes::Matrix), row(row), col(col) { }
    virtual llvm::Value* codeGen(CodeGenContext& context);
    void print(size_t tabs = 0) const override;
    inline Datatype getExpressionType() const override
    {
        return Datatype::MATRIX;
    }
};

}

#endif // DATA_STRUCTURE_H