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
class VariableDeclaration;
class Function;

typedef std::vector<Statement*> StatementList;
typedef std::vector<Expression*> ExpressionList;
typedef std::vector<VariableDeclaration*> VariableList;
typedef std::vector<Function*> FunctionList;

class Node {
public:
    virtual ~Node() {}
    virtual llvm::Value* codeGen(CodeGenContext& context) { }
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
};

class Double : public Value {
public:
    double value;
    Double(double value) : value(value) { }
    virtual llvm::Value* codeGen(CodeGenContext& context){};
};

class String : public Value {
public:
    std::string value;
    String(const std::string& value) : value(value) { }
    virtual llvm::Value* codeGen(CodeGenContext& context){};
};

class Identifier : public Value {
public:
    std::string name;
    Identifier(const std::string& name) : name(name) { }
    virtual llvm::Value* codeGen(CodeGenContext& context){};
};

class Boolean : public Value {
public:
    bool value;
    Boolean(bool value) : value(value) { }
    virtual llvm::Value* codeGen(CodeGenContext& context){};
};

class Program {
public:
    FunctionList functions;
    Program() {}
    virtual llvm::Value* codeGen(CodeGenContext& context){};
};

class Body : public Expression {
public:
    StatementList statements;
    Body() {}
    virtual llvm::Value* codeGen(CodeGenContext& context){};
};

class Block : public Expression {
public:
    Body& body;
    Block(Body& body) :
        body(body) { }
    virtual llvm::Value* codeGen(CodeGenContext& context){};
};

class Function {
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
};

class MethodCall : public Expression {
public:
    const Identifier& id;
    ExpressionList arguments;
    MethodCall(const Identifier& id, ExpressionList& arguments) :
        id(id), arguments(arguments) { }
    MethodCall(const Identifier& id) : id(id) { }
    virtual llvm::Value* codeGen(CodeGenContext& context){};
};

class ArithmeticOperator : public Expression {
public:
    Operation op;
    Expression& left;
    Expression& right;
    ArithmeticOperator(Expression& left, Operation op, Expression& right) :
        left(left), right(right), op(op) { }
    virtual llvm::Value* codeGen(CodeGenContext& context){};
};

class ComparisonOperator : public Expression {
public:
    ComparisonOperation op;
    Expression& left;
    Expression& right;
    ComparisonOperator(Expression& left, ComparisonOperation op, Expression& right) :
        left(left), right(right), op(op) { }
    virtual llvm::Value* codeGen(CodeGenContext& context){};
};

class BooleanOperator : public Expression {
public:
    BooleanOperation op;
    Expression& left;
    Expression& right;
    BooleanOperator(Expression& left, BooleanOperation op, Expression& right) :
        left(left), right(right), op(op) { }
    virtual llvm::Value* codeGen(CodeGenContext& context){};
};

class NotOperator : public Expression {
public:
    Expression& expression;
    NotOperator(Expression& expression) :
        expression(expression) { }
    virtual llvm::Value* codeGen(CodeGenContext& context){};
};

/*class ExpressionStatement : public Statement {
public:
    Expression& expression;
    ExpressionStatement(Expression& expression) : 
        expression(expression) { }
    virtual llvm::Value* codeGen(CodeGenContext& context);
};*/

class VariableAssignment : public Statement {
public:
    Identifier& id;
    Expression *assignmentExpr;
    VariableAssignment(Identifier& id, Expression *assignmentExpr) :
        id(id), assignmentExpr(assignmentExpr) { }
    virtual llvm::Value* codeGen(CodeGenContext& context){};
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
};

class MatrixPosition : public Position {
public:
    Value& row;
    Value& col;
    MatrixPosition(Value& row, Value& col) :
        row(row), col(col) { }
    virtual llvm::Value* codeGen(CodeGenContext& context){};
};

class DataPositionAssignment : public Expression {
public:
    Position& position;
    Expression& expression;
    DataPositionAssignment(Position& position, Expression& expression) : 
        position(position), expression(expression) { }
    virtual llvm::Value* codeGen(CodeGenContext& context){};
};

class List : public DataStructure {
public:
    std::vector<Value> values;
    List() {}
    virtual llvm::Value* codeGen(CodeGenContext& context){};
};

class Matrix : public DataStructure {
public:
    Value* row;
    Value* col;
    std::vector<std::vector<Value>> matrix;
    Matrix(Value* row, Value* col) :
        row(row), col(col) { }
    virtual llvm::Value* codeGen(CodeGenContext& context){};
};

class Read : public Statement {
public:
    Identifier& identifier;
    Read(const std::string& identifier) :
        identifier(*(new SNode::Identifier(identifier))) { }
    virtual llvm::Value* codeGen(CodeGenContext& context){};
};

class Print : public Statement {
public:
    Expression& expression;
    Print(Expression& expression) :
        expression(expression) { }
    virtual llvm::Value* codeGen(CodeGenContext& context){};
};

class If : public Statement {
public:
    Expression& condition;
    Block& block;
    If(Expression& condition, Block& block) :
        condition(condition), block(block) { }
    virtual llvm::Value* codeGen(CodeGenContext& context){};
};

class While : public Statement {
public:
    Expression& condition;
    Block& block;
    While(Expression& condition, Block& block) :
        condition(condition), block(block) { }
    virtual llvm::Value* codeGen(CodeGenContext& context){};
};
}