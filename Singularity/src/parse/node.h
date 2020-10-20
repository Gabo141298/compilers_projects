#ifndef NODE_H
#define NODE_H

/**
 * Código basado en https://gnuu.org/2009/09/18/writing-your-own-toy-compiler/
 */

#include <iostream>
#include <string>
#include <vector>
#include <llvm/IR/Value.h>

#include "symbol_table.hh"

#ifndef PROCESS_VAL
#define PROCESS_VAL(p) case(p): s = #p; break;
#endif

namespace SNode
{

enum OperationType
{
    ARITHMETIC_OP = 0x100,
    COMPARISON_OP = 0x200,
    BOOLEAN_OP = 0x300
};

enum Operation
{
    addition = ARITHMETIC_OP,
    substraction,
    multiplication,
    division,
    modulo
};

std::ostream& operator<<(std::ostream& out, Operation value);

enum ComparisonOperation
{
    leq = COMPARISON_OP,
    geq,
    greater,
    less,
    equals,
    isNot
};

std::ostream& operator<<(std::ostream& out, ComparisonOperation value);

enum BooleanOperation
{
    bAnd = BOOLEAN_OP,
    bOr,
    bXor
};

std::ostream& operator<<(std::ostream& out, BooleanOperation value);

class CodeGenContext;
class Statement;
class Expression;
class Identifier;
class Function;
class VariableAssignment;

typedef std::vector<Statement*> StatementList;
typedef std::vector<Expression*> ExpressionList;
typedef std::vector<Identifier*> VariableList;
typedef std::vector<Function*> FunctionList;
typedef std::vector<VariableAssignment*> GlobalList;

class Node {
public:
    virtual ~Node() {}
    // virtual llvm::Value* codeGen(CodeGenContext& context) { }
    virtual void print(size_t tabs) const { (void)tabs; }
protected:
    void printTabs(size_t tabs = 0) const
    {
        for(size_t index = 0; index < tabs; ++index)
            std::cout << '\t';
    }
};

class Expression : public Node {
public:
    virtual inline Datatype getExpressionType() const { return Datatype::UNKNOWN; }
};

class Statement : public Node {
};

class Value : public Expression{
};

class Integer : public Value {
public:
    long long value;
    Integer(long long value) : value(value) { }
    // virtual llvm::Value* codeGen(CodeGenContext& context) { }
    void print(size_t tabs = 0) const override
    {
        printTabs(tabs);
        std::cout << "Integer: " << value << std::endl;
    }
    inline Datatype getExpressionType() const override
    {
        return Datatype::INTEGER;
    }
};

class Double : public Value {
public:
    double value;
    Double(double value) : value(value) { }
    // virtual llvm::Value* codeGen(CodeGenContext& context) { }
    void print(size_t tabs = 0) const override
    {
        printTabs(tabs);
        std::cout << "Double: " << value << std::endl;
    }
    inline Datatype getExpressionType() const override
    {
        return Datatype::DOUBLE;
    }
};

class String : public Value {
public:
    std::string value;
    String(const std::string& value) : value(value) { }
    // virtual llvm::Value* codeGen(CodeGenContext& context) { }
    void print(size_t tabs = 0) const override
    {
        printTabs(tabs);
        std::cout << "String: " << value << std::endl;
    }
    inline Datatype getExpressionType() const override
    {
        return Datatype::STRING;
    }
};

class Identifier : public Value {
public:
    std::string name;
    Identifier(const std::string& name) : name(name) { }
    // virtual llvm::Value* codeGen(CodeGenContext& context) { }
    void print(size_t tabs = 0) const override
    {
        printTabs(tabs);
        std::cout << "Identifier: " << name << std::endl;
    }
    inline Datatype getExpressionType() const override
    {
        // Lookup table to check if variable has a type.
        return Datatype::UNKNOWN;
    }
};

class Boolean : public Value {
public:
    bool value;
    Boolean(bool value) : value(value) { }
    // virtual llvm::Value* codeGen(CodeGenContext& context) { }
    void print(size_t tabs = 0) const override
    {
        printTabs(tabs);
        std::cout << "Boolean: " << value << std::endl;
    }
    inline Datatype getExpressionType() const override
    {
        return Datatype::BOOLEAN;
    }
};

class Body : public Node {
public:
    StatementList statements;
    Body() {}
    // virtual llvm::Value* codeGen(CodeGenContext& context) { }
    void print(size_t tabs = 0) const override
    {
        printTabs(tabs);
        std::cout << "Body:" << std::endl;

        printTabs(tabs + 1);
        std::cout << "Statements:" << std::endl;
        for(size_t index = 0; index < statements.size(); ++index)
            statements[index]->print(tabs + 1);
    }
};

class Block : public Node {
public:
    Body& body;
    Block(Body& body) :
        body(body) { }
    // virtual llvm::Value* codeGen(CodeGenContext& context) { }
    void print(size_t tabs = 0) const override
    {
        printTabs(tabs);
        std::cout << "Block: " << std::endl;
        body.print(tabs + 1);
    }
};

class Function : public Node {
public:
    const Identifier& id;
    VariableList arguments;
    Block& block;
    Function(const Identifier& id, Block& block) :
        id(id), block(block) { }
    Function(const Identifier& id, 
            const VariableList& arguments, Block& block) :
        id(id), arguments(arguments), block(block) { }
    // virtual llvm::Value* codeGen(CodeGenContext& context) { }
    void print(size_t tabs = 0) const override
    {
        printTabs(tabs);
        std::cout << "Function:" << std::endl;

        printTabs(tabs + 1);
        std::cout << "FunctionName:" << std::endl;
        id.print(tabs + 1);

        if(arguments.size() > 0)
        {
            printTabs(tabs + 1);
            std::cout << "Arguments:" << std::endl;
            for(size_t index = 0; index < arguments.size(); ++ index)
                arguments[index]->print(tabs + 1);
        }

        block.print(tabs + 1);
    }
};

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

class Answer : public Statement {
public:
    Expression& returnExpression;
    Answer(Expression& returnExpression) :
        returnExpression(returnExpression) {}
    // virtual llvm::Value* codeGen(CodeGenContext& context) { }
    void print(size_t tabs = 0) const override
    {
        printTabs(tabs);
        std::cout << "Answer:" << std::endl;

        printTabs(tabs + 1);
        std::cout << "Expression:" << std::endl;
        returnExpression.print(tabs + 1);
    }
};

class ExpressionStatement : public Statement {
public:
    Expression& expression;
    ExpressionStatement(Expression& expression) : 
        expression(expression) { }
    // virtual llvm::Value* codeGen(CodeGenContext& context) { }
    void print(size_t tabs = 0) const override
    {
        printTabs(tabs);
        std::cout << "ExpressionStatement:" << std::endl;

        printTabs(tabs + 1);
        std::cout << "Expression:" << std::endl;
        expression.print(tabs + 1);
    }
};

class ArithmeticOperator : public Expression {
public:
    Expression& left;
    Operation op;
    Expression& right;
    ArithmeticOperator(Expression& left, Operation op, Expression& right) :
        left(left), op(op), right(right) { }
    // virtual llvm::Value* codeGen(CodeGenContext& context) { }
    void print(size_t tabs = 0) const override
    {
        printTabs(tabs);
        std::cout << "ArithmeticOperator: op - " << op << std::endl;

        printTabs(tabs + 1);
        std::cout << "LeftExpression:" << std::endl;
        left.print(tabs + 1);

        printTabs(tabs + 1);
        std::cout << "RightExpression:" << std::endl;
        right.print(tabs + 1);
    }
    Datatype getExpressionType() const override
    {
        Datatype leftType = left.getExpressionType();
        Datatype rightType = right.getExpressionType();

        // If any of the expressions is boolean, throw an error
        if(leftType == Datatype::BOOLEAN || rightType == Datatype::BOOLEAN)
            std::cout << "Error: can't use a boolean expression as an arithmetic operation." << std::endl;
        // If any of the expressions is a function, throw an error
        else if(leftType == Datatype::FUNCTION || rightType == Datatype::FUNCTION)
            std::cout << "Error: can't use a function name as an arithmetic expression." << std::endl;
        // If any of the expressions is a list name, throw an error
        else if(leftType == Datatype::LIST || rightType == Datatype::LIST)
            std::cout << "Error: can't use a list name as an arithmetic expression." << std::endl;
        // If any of the expressions is a matrix name, throw an error
        else if(leftType == Datatype::MATRIX || rightType == Datatype::MATRIX)
            std::cout << "Error: can't use a matrix name as an arithmetic expression." << std::endl;
        // If any of the expressions is a string, throw an error.
        else if(leftType == Datatype::STRING || rightType == Datatype::STRING)
            std::cout << "Error: can't use a string as an arithmetic expression." << std::endl;
        // If any of the two expressions is unknown, then the resulting expression is unknown.
        else if(leftType == Datatype::UNKNOWN || rightType == Datatype::UNKNOWN)
            return Datatype::UNKNOWN;
        // If any of the two expressions is a double, then the resulting expression is a double.
        else if(leftType == Datatype::DOUBLE || rightType == Datatype::DOUBLE)
            return Datatype::DOUBLE;
        else
            return Datatype::INTEGER;

        return Datatype::UNKNOWN;
    }
};

class ComparisonOperator : public Expression {
public:
    Expression& left;
    ComparisonOperation op;
    Expression& right;
    ComparisonOperator(Expression& left, ComparisonOperation op, Expression& right) :
        left(left), op(op), right(right) { }
    // virtual llvm::Value* codeGen(CodeGenContext& context) { }
    void print(size_t tabs = 0) const override
    {
        printTabs(tabs);
        std::cout << "ComparisonOperator: op - " << op << std::endl;

        printTabs(tabs + 1);
        std::cout << "LeftExpression:" << std::endl;
        left.print(tabs + 1);

        printTabs(tabs + 1);
        std::cout << "RightExpression:" << std::endl;
        right.print(tabs + 1);
    }
    Datatype getExpressionType() const override
    {
        Datatype leftType = left.getExpressionType();
        Datatype rightType = right.getExpressionType();

        // If any of the expressions is boolean, throw an error
        if(leftType == Datatype::BOOLEAN || rightType == Datatype::BOOLEAN)
            std::cout << "Error: can't use a boolean expression to compare." << std::endl;
        // If any of the expressions is a function, throw an error
        else if(leftType == Datatype::FUNCTION || rightType == Datatype::FUNCTION)
            std::cout << "Error: can't use a function name as an expression." << std::endl;
        // If any of the expressions is a list name, throw an error
        else if(leftType == Datatype::LIST || rightType == Datatype::LIST)
            std::cout << "Error: can't use a list name as an expression." << std::endl;
        // If any of the expressions is a matrix name, throw an error
        else if(leftType == Datatype::MATRIX || rightType == Datatype::MATRIX)
            std::cout << "Error: can't use a matrix name as an expression." << std::endl;
        // If any of the two expressions is unknown, then the resulting expression is unknown.
        else if(leftType == Datatype::UNKNOWN || rightType == Datatype::UNKNOWN)
            return Datatype::UNKNOWN;
        else if(leftType == Datatype::STRING && rightType == Datatype::STRING)
            return Datatype::BOOLEAN;
        // If any of the expressions is a string, throw an error.
        else if(leftType == Datatype::STRING || rightType == Datatype::STRING)
            std::cout << "Error: can't compare a string with a numeric expression" << std::endl;
        else
            return Datatype::BOOLEAN;

        return Datatype::UNKNOWN;
    }
};

class BooleanOperator : public Expression {
public:
    Expression& left;
    BooleanOperation op;
    Expression& right;
    BooleanOperator(Expression& left, BooleanOperation op, Expression& right) :
        left(left), op(op), right(right) { }
    // virtual llvm::Value* codeGen(CodeGenContext& context) { }
    void print(size_t tabs = 0) const override
    {
        printTabs(tabs);
        std::cout << "BooleanOperator: op - " << op << std::endl;

        printTabs(tabs + 1);
        std::cout << "LeftExpression:" << std::endl;
        left.print(tabs + 1);

        printTabs(tabs + 1);
        std::cout << "RightExpression:" << std::endl;
        right.print(tabs + 1);
    }
    Datatype getExpressionType() const override
    {
        Datatype leftType = left.getExpressionType();
        Datatype rightType = right.getExpressionType();

        // If any of the expressions is a function, throw an error
        if(leftType == Datatype::FUNCTION || rightType == Datatype::FUNCTION)
            std::cout << "Error: can't use a function name as a boolean expression." << std::endl;
        // If any of the expressions is a list name, throw an error
        else if(leftType == Datatype::LIST || rightType == Datatype::LIST)
            std::cout << "Error: can't use a list name as a boolean expression." << std::endl;
        // If any of the expressions is a matrix name, throw an error
        else if(leftType == Datatype::MATRIX || rightType == Datatype::MATRIX)
            std::cout << "Error: can't use a matrix name as a boolean expression." << std::endl;
        // If any of the expressions is a string, throw an error.
        else if(leftType == Datatype::STRING || rightType == Datatype::STRING)
            std::cout << "Error: can't use a string as a boolean expression." << std::endl;
        else if(leftType == Datatype::DOUBLE || rightType == Datatype::DOUBLE 
            || leftType == Datatype::INTEGER || rightType == Datatype::INTEGER)
            std::cout << "Error: can't use a numeric value as a boolean expression." << std::endl;
        // If any of the two expressions is unknown, then the resulting expression is unknown.
        else if(leftType == Datatype::UNKNOWN || rightType == Datatype::UNKNOWN)
            return Datatype::UNKNOWN;
        else
            return Datatype::BOOLEAN;

        return Datatype::UNKNOWN;
    }
};

class NotOperator : public Expression {
public:
    Expression& expression;
    NotOperator(Expression& expression) :
        expression(expression) { }
    // virtual llvm::Value* codeGen(CodeGenContext& context) { }
    void print(size_t tabs = 0) const override
    {
        printTabs(tabs);
        std::cout << "NotOperator:" << std::endl;

        printTabs(tabs + 1);
        std::cout << "Expression:" << std::endl;
        expression.print(tabs + 1);
    }
    Datatype getExpressionType() const override
    {
        Datatype type = expression.getExpressionType();
        switch(type)
        {
            case Datatype::UNKNOWN: return Datatype::UNKNOWN;
            case Datatype::BOOLEAN: return Datatype::BOOLEAN;
            case Datatype::INTEGER: std::cout << "Error: can't use an integer as a boolean expression." << std::endl; break;
            case Datatype::DOUBLE: std::cout << "Error: can't use a double as a boolean expression." << std::endl; break;
            case Datatype::STRING: std::cout << "Error: can't use a string as a boolean expression." << std::endl; break;
            case Datatype::FUNCTION: std::cout << "Error: can't use a function name as a boolean expression." << std::endl; break;
            case Datatype::LIST: std::cout << "Error: can't use a list name as a boolean expression." << std::endl; break;
            case Datatype::MATRIX: std::cout << "Error: can't use a matrix name as a boolean expression." << std::endl; break;
            default: break;
        }
        return Datatype::UNKNOWN;
    }
};

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
};

class DataStructure : public Expression {
};

class Position : public Expression {
public:
    virtual inline bool validPosition() { return false; }
};

class PositionAccess : public Expression {
public: 
    Identifier& id;
    Position& position;
    PositionAccess(Identifier& id, Position& position) :
        id(id), position(position) {}
    // virtual llvm::Value* codeGen(CodeGenContext& context) { }
    void print(size_t tabs = 0) const override
    {
        printTabs(tabs);
        std::cout << "PositionAccess: " << std::endl;

        id.print(tabs + 1);

        position.print(tabs + 1);
    }
    inline Datatype getExpressionType() const override
    {
        if(!position.validPosition())
            std::cout << "Error: invalid position" << std::endl;
        return Datatype::UNKNOWN;
    }
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

class DataPositionAssignment : public Statement {
public:
    Identifier& id;
    Position& position;
    Expression& expression;
    DataPositionAssignment(Identifier& id, Position& position, Expression& expression) : 
        id(id), position(position), expression(expression) { }
    // virtual llvm::Value* codeGen(CodeGenContext& context) { }
    void print(size_t tabs = 0) const override
    {
        printTabs(tabs);
        std::cout << "DataPositionAssignment: " << std::endl;

        id.print(tabs + 1);

        printTabs(tabs + 1);
        std::cout << "Position:" << std::endl;
        position.print(tabs + 1);

        printTabs(tabs + 1);
        std::cout << "Expression:" << std::endl;
        expression.print(tabs + 1);
    }
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

class Read : public Statement {
public:
    Identifier& identifier;
    Read(const std::string& identifier) :
        identifier(*(new SNode::Identifier(identifier))) { }
    // virtual llvm::Value* codeGen(CodeGenContext& context) { }
    void print(size_t tabs = 0) const override
    {
        printTabs(tabs);
        std::cout << "Read: " << std::endl;
        identifier.print(tabs + 1);
    }
};

class Print : public Statement {
public:
    Expression& expression;
    Print(Expression& expression) :
        expression(expression) { }
    // virtual llvm::Value* codeGen(CodeGenContext& context) { }
    void print(size_t tabs = 0) const override
    {
        printTabs(tabs);
        std::cout << "Print: " << std::endl;
        expression.print(tabs + 1);
    }
};

class If : public Statement {
public:
    Expression& condition;
    Block& block;
    Statement* otherwise;
    If(Expression& condition, Block& block, Statement* otherwise = nullptr) :
        condition(condition), block(block), otherwise(otherwise) { }
    // virtual llvm::Value* codeGen(CodeGenContext& context) { }
    void print(size_t tabs = 0) const override
    {
        printTabs(tabs);
        std::cout << "If: " << std::endl;

        printTabs(tabs + 1);
        std::cout << "Condition:" << std::endl;
        condition.print(tabs + 1);

        if (otherwise)
            otherwise->print(tabs + 1);

        block.print(tabs + 1);
    }
};

class OtherwiseIf : public Statement {
public:
    If& if_statement;
    OtherwiseIf(If& if_statement) : 
        if_statement( if_statement ) { }
    // virtual llvm::Value* codeGen(CodeGenContext& context) { }
    void print(size_t tabs = 0) const override
    {
        printTabs(tabs);
        std::cout << "Otherwise if: " << std::endl;

        if_statement.print(tabs + 1);
    }   
};

class Otherwise : public Statement {
public:
    Block& block;
    Otherwise(Block& block) :  
         block(block) { }
    // virtual llvm::Value* codeGen(CodeGenContext& context) { }
    void print(size_t tabs = 0) const override
    {
        printTabs(tabs);
        std::cout << "Otherwise: " << std::endl;

        block.print(tabs + 1);
    }
};

class While : public Statement {
public:
    Expression& condition;
    Block& block;
    While(Expression& condition, Block& block) :
        condition(condition), block(block) { }
    // virtual llvm::Value* codeGen(CodeGenContext& context) { }
    void print(size_t tabs = 0) const override
    {
        printTabs(tabs);
        std::cout << "While: " << std::endl;

        printTabs(tabs + 1);
        std::cout << "Condition:" << std::endl;
        condition.print(tabs + 1);

        block.print(tabs + 1);
    }
};

class WhileCounting : public Statement {
public:
    Identifier& counter;
    Expression& beginValue;
    Expression& endValue;
    Block& block;
    WhileCounting(Identifier& counter, Expression& beginValue, Expression& endValue, Block& block) :
        counter(counter), beginValue(beginValue), endValue(endValue), block(block) { }
    // virtual llvm::Value* codeGen(CodeGenContext& context) { }
    void print(size_t tabs = 0) const override
    {
        printTabs(tabs);
        std::cout << "WhileCounting: " << std::endl;

        printTabs(tabs + 1);
        std::cout << "Counter:" << std::endl;
        counter.print(tabs + 1);

        printTabs(tabs + 1);
        std::cout << "BeginValue:" << std::endl;
        beginValue.print(tabs + 1);

        printTabs(tabs + 1);
        std::cout << "EndValue:" << std::endl;
        endValue.print(tabs + 1);

        block.print(tabs + 1);
    }
};

class Program : public Node {
public:
    FunctionList functions;
    GlobalList globals;
    Program() {}
    // virtual llvm::Value* codeGen(CodeGenContext& context) { }
    void print(size_t tabs = 0) const override
    {
        printTabs(tabs);
        std::cout << "Program: " << std::endl;
        for(size_t index = 0; index < functions.size(); ++index)
            functions[index]->print(tabs + 1);
        for(size_t index = 0; index < globals.size(); ++index)
            globals[index]->print(tabs + 1);
    }
};

Expression* createOperation(Expression& left, int op, Expression& right);

}

#endif // NODE_H