#ifndef DATA_STRUCTURE_H
#define DATA_STRUCTURE_H

#include "node.hh"

namespace SNode
{

class DataStructure : public Expression {
};

class List : public DataStructure {
public:
    std::vector<Value> values;
    List() {}
    // virtual llvm::Value* codeGen(CodeGenContext& context) { }
    void print(size_t tabs = 0) const override
    {
        printTabs(tabs);
        std::cout << "List" << std::endl;
    }
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
        row(row), col(col) { }
    // virtual llvm::Value* codeGen(CodeGenContext& context) { }
    void print(size_t tabs = 0) const override
    {
        printTabs(tabs);
        std::cout << "Matrix: " << std::endl;

        printTabs(tabs + 1);
        std::cout << "Row:" << std::endl;
        row->print(tabs + 1);

        printTabs(tabs + 1);
        std::cout << "Col:" << std::endl;
        col->print(tabs + 1);
    }
    inline Datatype getExpressionType() const override
    {
        return Datatype::MATRIX;
    }
};

}

#endif // DATA_STRUCTURE_H