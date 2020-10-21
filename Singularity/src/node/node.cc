#include "ArithmeticOperation.hh"
#include "BooleanOperation.hh"
#include "ComparisonOperation.hh"
#include "node.hh"

std::ostream& SNode::operator<<(std::ostream& out, SNode::ArithmeticOperator value){
    const char* s = 0;
    switch(value){
        PROCESS_VAL(addition)
        PROCESS_VAL(substraction)
        PROCESS_VAL(multiplication)
        PROCESS_VAL(division)
        PROCESS_VAL(modulo)
    }

    return out << s;
}

std::ostream& SNode::operator<<(std::ostream& out, SNode::ComparisonOperator value){
    const char* s = 0;
    switch(value){
        PROCESS_VAL(leq)
        PROCESS_VAL(geq)
        PROCESS_VAL(greater)
        PROCESS_VAL(less)
        PROCESS_VAL(equals)
        PROCESS_VAL(isNot)
    }

    return out << s;
}

std::ostream& SNode::operator<<(std::ostream& out, SNode::BooleanOperator value){
    const char* s = 0;
    switch(value){
        PROCESS_VAL(bAnd)
        PROCESS_VAL(bOr)
        PROCESS_VAL(bXor)
    }

    return out << s;
}

SNode::Expression* SNode::createOperation(SNode::Expression& left, int op, SNode::Expression& right)
{
    if(SNode::OperationType::ARITHMETIC_OP <= op && op < SNode::OperationType::COMPARISON_OP)
        return new ArithmeticOperation(left, (SNode::ArithmeticOperator)op, right);
    else if(SNode::OperationType::COMPARISON_OP <= op && op < SNode::OperationType::BOOLEAN_OP)
        return new ComparisonOperation(left, (SNode::ComparisonOperator)op, right);
    else if(op >= SNode::OperationType::BOOLEAN_OP)
        return new BooleanOperation(left, (SNode::BooleanOperator)op, right);
    return nullptr;
}