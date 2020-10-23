#ifndef NODE_H
#define NODE_H

/**
 * Código basado en https://gnuu.org/2009/09/18/writing-your-own-toy-compiler/
 */

#include <iostream>
#include <string>
#include <vector>
#include <llvm/IR/Value.h>

#include "../exceptions/exceptions.hh"
#include "../parse/symbol_table.hh"

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

enum ArithmeticOperator
{
    addition = ARITHMETIC_OP,
    substraction,
    multiplication,
    division,
    modulo
};

std::ostream& operator<<(std::ostream& out, ArithmeticOperator value);

enum ComparisonOperator
{
    leq = COMPARISON_OP,
    geq,
    greater,
    less,
    equals,
    isNot
};

std::ostream& operator<<(std::ostream& out, ComparisonOperator value);

enum BooleanOperator
{
    bAnd = BOOLEAN_OP,
    bOr,
    bXor
};

enum class NodeTypes
{
    Node, Expression, ArithmeticOperation, BooleanOperation, ComparisonOperation,
    DataStructure, List, Matrix, FunctionCall, NotOperation, Position,
    ListPosition, MatrixPosition, PositionAccesss, Value, Boolean,
    Double, Identifier, Integer, String, Function, Program, Statement,
    Answer, Block, DataPositionAssignment, ExpressionStatement, If,
    Otherwise, Otherwiseif, Print, Read, VariableAssignment, While, WhileCounting
};

std::ostream& operator<<(std::ostream& out, BooleanOperator value);

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
    virtual llvm::Value* codeGen(CodeGenContext&) { return nullptr; }
    virtual void print(size_t tabs) const { (void)tabs; }
    Node(NodeTypes type = NodeTypes::Node) : nodeType(type){};
    inline NodeTypes getType() {return this->nodeType;}
protected:
    NodeTypes nodeType = NodeTypes::Node;
    void printTabs(size_t tabs = 0) const
    {
        for(size_t index = 0; index < tabs; ++index)
            std::cout << '\t';
    }
};

class Expression : public Node {
public:
    Expression(NodeTypes type = NodeTypes::Expression)
        : Node(type)
    {        
    }

    virtual inline Datatype getExpressionType() const { return Datatype::UNKNOWN; }
};

class Statement : public Node {
public:
    Statement(NodeTypes type = NodeTypes::Statement)
        : Node(type)
    {        
    }
    virtual void createSymbolTable(SymbolTable&, std::string, size_t*) const { }
};

class Value : public Expression{
public:
    Value(NodeTypes type = NodeTypes::Value)
        : Expression(type)
    {        
    }
};

class Integer : public Value {
public:
    long long value;
    Integer(long long value) 
    : Value(NodeTypes::Integer ) 
    , value(value)     
    {        
    }

    virtual llvm::Value* codeGen(CodeGenContext&) { return nullptr; }
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
    Double(double value) : Value(NodeTypes::Double ), value(value) { }
    virtual llvm::Value* codeGen(CodeGenContext&) { return nullptr; }
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
    String(const std::string& value) : Value(NodeTypes::String), value(value) { }
    virtual llvm::Value* codeGen(CodeGenContext&) { return nullptr; }
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
    SymbolTable& symbolTable;
    Identifier(const std::string& name, SymbolTable& symbolTable) : Value(NodeTypes::Identifier), name(name), symbolTable(symbolTable)  { }
    virtual llvm::Value* codeGen(CodeGenContext&) { return nullptr; }
    void print(size_t tabs = 0) const override
    {
        printTabs(tabs);
        std::cout << "Identifier: " << name << std::endl;
    }
    inline Datatype getExpressionType() const override
    {
    	TableRow* row = symbolTable.searchCurrentSubtable(this->name);
    	if (row == nullptr){
            throw SingularityException(ExceptionType::UNDECLARED_VARIABLE, name + " was not declared.");
    		return Datatype::UNKNOWN;
    	}
    	
    	return row->getType();	
    }
};

class Boolean : public Value {
public:
    bool value;
    Boolean(bool value) : Value(NodeTypes:: Boolean), value(value) { }
    virtual llvm::Value* codeGen(CodeGenContext&) { return nullptr; }
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

class ExpressionStatement : public Statement {
public:
    Expression& expression;
    ExpressionStatement(Expression& expression) :Statement(NodeTypes::ExpressionStatement), expression(expression) { }
    virtual llvm::Value* codeGen(CodeGenContext&) { return nullptr; }
    void print(size_t tabs = 0) const override
    {
        printTabs(tabs);
        std::cout << "ExpressionStatement:" << std::endl;

        printTabs(tabs + 1);
        std::cout << "Expression:" << std::endl;
        expression.print(tabs + 1);
    }
};

Expression* createOperation(Expression& left, int op, Expression& right);

}

#endif // NODE_H
