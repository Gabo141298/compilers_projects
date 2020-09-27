/**
 * Código basado en https://gnuu.org/2009/09/18/writing-your-own-toy-compiler/
 */

#include <iostream>
#include <string>
#include <vector>
#include <llvm/Value.h>

namespace SNode
{
class CodeGenContext;
class Statement;
class Expression;
class VariableDeclaration;

typedef std::vector<Statement*> StatementList;
typedef std::vector<Expression*> ExpressionList;
typedef std::vector<VariableDeclaration*> VariableList;
typedef std::vector<Function*> FunctionList;

class Node {
public:
    virtual ~Node() {}
    virtual llvm::Value* codeGen(CodeGenContext& context) { }
};

class Program {
public:
    FunctionList functions;
    Program() {}
    virtual llvm::Value* codeGen(CodeGenContext& context);
}

class Function {
public:
    const Identifier& type;
    const Identifier& id;
    VariableList arguments;
    Block& block;
    Function(const Identifier& type, const Identifier& id, 
            const VariableList& arguments, NBlock& block) :
        type(type), id(id), arguments(arguments), block(block) { }
    virtual llvm::Value* codeGen(CodeGenContext& context);
};

class Expression : public Node {
};

class Statement : public Node {
};

class Value : public Expression{
}

class Integer : public Value {
public:
    long long value;
    Integer(long long value) : value(value) { }
    virtual llvm::Value* codeGen(CodeGenContext& context);
};

class Double : public Value {
public:
    double value;
    Double(double value) : value(value) { }
    virtual llvm::Value* codeGen(CodeGenContext& context);
};

class String : public Value {
public:
    std::string value;
    String(const std::string& value) : value(value) { }
    virtual llvm::Value* codeGen(CodeGenContext& context);
};

class Identifier : public Value {
public:
    std::string name;
    Identifier(const std::string& name) : name(name) { }
    virtual llvm::Value* codeGen(CodeGenContext& context);
};

class Boolean : public Value {
    public
    bool value;
    Boolean(bool value) : value(value) { }
    virtual llvm::Value* codeGen(CodeGenContext& context);
}

class MethodCall : public Expression {
public:
    const Identifier& id;
    ExpressionList arguments;
    MethodCall(const Identifier& id, ExpressionList& arguments) :
        id(id), arguments(arguments) { }
    MethodCall(const Identifier& id) : id(id) { }
    virtual llvm::Value* codeGen(CodeGenContext& context);
};

class BinaryOperator : public Expression {
public:
    int op;
    Expression& lhs;
    Expression& rhs;
    BinaryOperator(Expression& lhs, int op, Expression& rhs) :
        lhs(lhs), rhs(rhs), op(op) { }
    virtual llvm::Value* codeGen(CodeGenContext& context);
};

class Assignment : public Expression {
public:
    Identifier& lhs;
    Expression& rhs;
    Assignment(Identifier& lhs, Expression& rhs) : 
        lhs(lhs), rhs(rhs) { }
    virtual llvm::Value* codeGen(CodeGenContext& context);
};

class Body : public Expression {
    StatementList statements;
    Body() {}
    virtual llvm::Value* codeGen(CodeGenContext& context);
}

class Block : public Expression {
public:
    Body* body;
    Block() { }
    virtual llvm::Value* codeGen(CodeGenContext& context);
};

class ExpressionStatement : public Statement {
public:
    Expression& expression;
    ExpressionStatement(Expression& expression) : 
        expression(expression) { }
    virtual llvm::Value* codeGen(CodeGenContext& context);
};

class VariableDeclaration : public Statement {
public:
    Identifier& id;
    Expression *assignmentExpr;
    VariableDeclaration(Identifier& id, Expression *assignmentExpr) :
        id(id), assignmentExpr(assignmentExpr) { }
    virtual llvm::Value* codeGen(CodeGenContext& context);
};

class DataStructure : public Expression {
}

class List : public DataStructure {
    std::vector<Value> values;
    List() {}
    virtual llvm::Value* codeGen(CodeGenContext& context);
}

class Matrix : public DataStructure {
    std::vector<std::vector<Value>> matrix;
    Matrix(Integer* row, Integer* col)
    {
        if(row->value > 0 && col->value > 0)
        {
            this->matrix.resize(row->value);
            for(long long currentCol = 0; currentCol < col->value, ++currentCol)
                this->matrix[currentCol].resize(col->value);
        }
    }
    Matrix(Identifier* row, Identifier* col)
    {
        if(row->value > 0 && col->value > 0)
        {
            this->matrix.resize(row->value);
            for(long long currentCol = 0; currentCol < col->value, ++currentCol)
                this->matrix[currentCol].resize(col->value);
        }
    }
}
}