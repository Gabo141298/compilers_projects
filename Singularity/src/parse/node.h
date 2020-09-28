/**
 * Código basado en https://gnuu.org/2009/09/18/writing-your-own-toy-compiler/
 */

#include <iostream>
#include <string>
#include <vector>
#include <llvm/IR/Value.h>

namespace SNode
{
enum Operation
{
    addition,
    substraction,
    multiplication,
    division
};

enum ComparisonOperation
{
    leq,
    geq,
    greater,
    less,
    equals,
    isNot
};

enum BooleanOperation
{
    bAnd,
    bOr,
    bXor
};

class CodeGenContext;
class Statement;
class Expression;
class Identifier;
class Function;

typedef std::vector<Statement*> StatementList;
typedef std::vector<Expression*> ExpressionList;
typedef std::vector<Identifier*> VariableList;
typedef std::vector<Function*> FunctionList;

class Node {
public:
    virtual ~Node() {}
    virtual llvm::Value* codeGen(CodeGenContext& context) { }
    virtual void print(size_t tabs) const {};
protected:
    void printTabs(size_t tabs = 0) const
    {
        for(size_t index = 0; index < tabs; ++index)
            std::cout << '\t';
    }
};

class Expression : public Node {
};

class Statement : public Node {
};

class Value : public Expression{
};

class Integer : public Value {
public:
    long long value;
    Integer(long long value) : value(value) { }
    virtual llvm::Value* codeGen(CodeGenContext& context){};
    void print(size_t tabs = 0) const override
    {
        printTabs(tabs);
        std::cout << "Integer: " << value << std::endl;
    }
};

class Double : public Value {
public:
    double value;
    Double(double value) : value(value) { }
    virtual llvm::Value* codeGen(CodeGenContext& context){};
    void print(size_t tabs = 0) const override
    {
        printTabs(tabs);
        std::cout << "Double: " << value << std::endl;
    }
};

class String : public Value {
public:
    std::string value;
    String(const std::string& value) : value(value) { }
    virtual llvm::Value* codeGen(CodeGenContext& context){};
    void print(size_t tabs = 0) const override
    {
        printTabs(tabs);
        std::cout << "String: " << value << std::endl;
    }
};

class Identifier : public Value {
public:
    std::string name;
    Identifier(const std::string& name) : name(name) { }
    virtual llvm::Value* codeGen(CodeGenContext& context){};
    void print(size_t tabs = 0) const override
    {
        printTabs(tabs);
        std::cout << "Identifier: " << name << std::endl;
    }
};

class Boolean : public Value {
public:
    bool value;
    Boolean(bool value) : value(value) { }
    virtual llvm::Value* codeGen(CodeGenContext& context){};
    void print(size_t tabs = 0) const override
    {
        printTabs(tabs);
        std::cout << "Boolean: " << value << std::endl;
    }
};

class Body : public Expression {
public:
    StatementList statements;
    Body() {}
    virtual llvm::Value* codeGen(CodeGenContext& context){};
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

class Block : public Expression {
public:
    Body& body;
    Block(Body& body) :
        body(body) { }
    virtual llvm::Value* codeGen(CodeGenContext& context){};
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
    virtual llvm::Value* codeGen(CodeGenContext& context){};
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
    VariableList parameters;
    FunctionCall(const Identifier& id) :
        id(id) { }
    FunctionCall(const Identifier& id, const VariableList& parameters) :
        id(id), parameters(parameters) { }
    virtual llvm::Value* codeGen(CodeGenContext& context){};
    void print(size_t tabs = 0) const override
    {
        printTabs(tabs);
        std::cout << "FunctionCall:" << std::endl;

        id.print(tabs + 1);

        printTabs(tabs + 1);
        std::cout << "parameters:" << std::endl;
        for(size_t index = 0; index < parameters.size(); ++ index)
            parameters[index]->print(tabs + 1);
    }
};

class Answer : public Statement {
public:
    Expression& returnExpression;
    Answer(Expression& returnExpression) :
        returnExpression(returnExpression) {}
    virtual llvm::Value* codeGen(CodeGenContext& context){};
    void print(size_t tabs = 0) const override
    {
        printTabs(tabs);
        std::cout << "Answer:" << std::endl;

        printTabs(tabs + 1);
        std::cout << "Expression:" << std::endl;
        returnExpression.print(tabs + 1);
    }
};

class ArithmeticOperator : public Expression {
public:
    Operation op;
    Expression& left;
    Expression& right;
    ArithmeticOperator(Expression& left, Operation op, Expression& right) :
        left(left), right(right), op(op) { }
    virtual llvm::Value* codeGen(CodeGenContext& context){};
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
};

class ComparisonOperator : public Expression {
public:
    ComparisonOperation op;
    Expression& left;
    Expression& right;
    ComparisonOperator(Expression& left, ComparisonOperation op, Expression& right) :
        left(left), right(right), op(op) { }
    virtual llvm::Value* codeGen(CodeGenContext& context){};
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
};

class BooleanOperator : public Expression {
public:
    BooleanOperation op;
    Expression& left;
    Expression& right;
    BooleanOperator(Expression& left, BooleanOperation op, Expression& right) :
        left(left), right(right), op(op) { }
    virtual llvm::Value* codeGen(CodeGenContext& context){};
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
};

class NotOperator : public Expression {
public:
    Expression& expression;
    NotOperator(Expression& expression) :
        expression(expression) { }
    virtual llvm::Value* codeGen(CodeGenContext& context){};
    void print(size_t tabs = 0) const override
    {
        printTabs(tabs);
        std::cout << "NotOperator:" << std::endl;

        printTabs(tabs + 1);
        std::cout << "Expression:" << std::endl;
        expression.print(tabs + 1);
    }
};

class VariableAssignment : public Statement {
public:
    Identifier& id;
    Expression* assignmentExpr;
    VariableAssignment(Identifier& id, Expression* assignmentExpr) :
        id(id), assignmentExpr(assignmentExpr) { }
    virtual llvm::Value* codeGen(CodeGenContext& context){};
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
};

class ListPosition : public Position {
public:
    Value& position;
    ListPosition(Value& position) :
        position(position) { }
    virtual llvm::Value* codeGen(CodeGenContext& context){};
    void print(size_t tabs = 0) const override
    {
        printTabs(tabs);
        std::cout << "ListPosition: " << std::endl;

        printTabs(tabs + 1);
        std::cout << "Position:" << std::endl;
        position.print(tabs + 1);
    }
};

class MatrixPosition : public Position {
public:
    Value& row;
    Value& col;
    MatrixPosition(Value& row, Value& col) :
        row(row), col(col) { }
    virtual llvm::Value* codeGen(CodeGenContext& context){};
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
};

class DataPositionAssignment : public Expression {
public:
    Position& position;
    Expression& expression;
    DataPositionAssignment(Position& position, Expression& expression) : 
        position(position), expression(expression) { }
    virtual llvm::Value* codeGen(CodeGenContext& context){};
    void print(size_t tabs = 0) const override
    {
        printTabs(tabs);
        std::cout << "DataPositionAssignment: " << std::endl;

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
    virtual llvm::Value* codeGen(CodeGenContext& context){};
    void print(size_t tabs = 0) const override
    {
        printTabs(tabs);
        std::cout << "List" << std::endl;
    }
};

class Matrix : public DataStructure {
public:
    Value* row;
    Value* col;
    std::vector<std::vector<Value>> matrix;
    Matrix(Value* row, Value* col) :
        row(row), col(col) { }
    virtual llvm::Value* codeGen(CodeGenContext& context){};
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
};

class Read : public Statement {
public:
    Identifier& identifier;
    Read(const std::string& identifier) :
        identifier(*(new SNode::Identifier(identifier))) { }
    virtual llvm::Value* codeGen(CodeGenContext& context){};
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
    virtual llvm::Value* codeGen(CodeGenContext& context){};
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
    If(Expression& condition, Block& block) :
        condition(condition), block(block) { }
    virtual llvm::Value* codeGen(CodeGenContext& context){};
    void print(size_t tabs = 0) const override
    {
        printTabs(tabs);
        std::cout << "If: " << std::endl;

        printTabs(tabs + 1);
        std::cout << "Condition:" << std::endl;
        condition.print(tabs + 1);

        block.print(tabs + 1);
    }
};

class While : public Statement {
public:
    Expression& condition;
    Block& block;
    While(Expression& condition, Block& block) :
        condition(condition), block(block) { }
    virtual llvm::Value* codeGen(CodeGenContext& context){};
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
    Value& beginValue;
    Value& endValue;
    Block& block;
    WhileCounting(Identifier& counter, Value& beginValue, Value& endValue, Block& block) :
        counter(counter), beginValue(beginValue), endValue(endValue), block(block) { }
    virtual llvm::Value* codeGen(CodeGenContext& context){};
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
    Program() {}
    virtual llvm::Value* codeGen(CodeGenContext& context){};
    void print(size_t tabs = 0) const override
    {
        printTabs(tabs);
        std::cout << "Program: " << std::endl;
        for(size_t index = 0; index < functions.size(); ++index)
            functions[index]->print(tabs + 1);
    }
};
}