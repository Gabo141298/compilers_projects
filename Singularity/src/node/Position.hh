#ifndef POSITION_H
#define POSITION_H

#include "node.hh"

namespace SNode
{

class Position : public Expression {
public:
    virtual inline bool validPosition() { return false; }
};

class ListPosition : public Position {
public:
    Expression& position;
    ListPosition(Expression& position) :
        position(position) { }
    // virtual llvm::Value* codeGen(CodeGenContext& context) { }
    void print(size_t tabs = 0) const override
    {
        printTabs(tabs);
        std::cout << "ListPosition: " << std::endl;

        printTabs(tabs + 1);
        std::cout << "Position:" << std::endl;
        position.print(tabs + 1);
    }
    bool validPosition()
    {
        Datatype type = position.getExpressionType();
        switch(type)
        {
            case Datatype::UNKNOWN:
            case Datatype::INTEGER: return true;
            case Datatype::BOOLEAN: std::cout << "Error: can't use a boolean to index a list." << std::endl; break;;
            case Datatype::DOUBLE: std::cout << "Error: can't use a double to index a list." << std::endl; break;
            case Datatype::STRING: std::cout << "Error: can't use a string to index a list." << std::endl; break;
            case Datatype::FUNCTION: std::cout << "Error: can't use an function name to index a list." << std::endl; break;
            case Datatype::LIST: std::cout << "Error: can't use an list name to index a list." << std::endl; break;
            case Datatype::MATRIX: std::cout << "Error: can't use an matrix name to index a list." << std::endl; break;
            default: break;
        }
        return false;
    }
};

class MatrixPosition : public Position {
public:
    Expression& row;
    Expression& col;
    MatrixPosition(Expression& row, Expression& col) :
        row(row), col(col) { }
    // virtual llvm::Value* codeGen(CodeGenContext& context) { }
    void print(size_t tabs = 0) const override
    {
        printTabs(tabs);
        std::cout << "MatrixPosition: " << std::endl;

        printTabs(tabs + 1);
        std::cout << "Row:" << std::endl;
        row.print(tabs + 1);

        printTabs(tabs + 1);
        std::cout << "Col:" << std::endl;
        col.print(tabs + 1);
    }
    bool validPosition()
    {
        Datatype rowType = row.getExpressionType();
        Datatype colType = col.getExpressionType();

        std::string typeError;

        // If any of the expressions is boolean, throw an error
        if(rowType == Datatype::BOOLEAN || colType == Datatype::BOOLEAN)
            typeError = "boolean";
        // If any of the expressions is a function, throw an error
        else if(rowType == Datatype::FUNCTION || colType == Datatype::FUNCTION)
            typeError = "function name";
        // If any of the expressions is a list name, throw an error
        else if(rowType == Datatype::LIST || colType == Datatype::LIST)
            typeError = "list name";
        // If any of the expressions is a matrix name, throw an error
        else if(rowType == Datatype::MATRIX || colType == Datatype::MATRIX)
            typeError = "matrix name";
        // If any of the expressions is a string, throw an error.
        else if(rowType == Datatype::STRING || colType == Datatype::STRING)
            typeError = "string";
        // If any of the two expressions is a double, throw an error.
        else if(rowType == Datatype::DOUBLE || colType == Datatype::DOUBLE)
            typeError = "double";
        // If any of the two expressions is unknown, then assume it's valid.
        else
            return true;

        std::cout << "Error: can't index a matrix with a " << typeError << "." << std::endl;
        return false;
    }
};

}

#endif // POSITION_H