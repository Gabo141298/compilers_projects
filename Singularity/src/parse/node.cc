#include "node.h"

std::ostream& SNode::operator<<(std::ostream& out, SNode::Operation value){
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

std::ostream& SNode::operator<<(std::ostream& out, SNode::ComparisonOperation value){
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

std::ostream& SNode::operator<<(std::ostream& out, SNode::BooleanOperation value){
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
        return new ArithmeticOperator(left, (SNode::Operation)op, right);
    else if(SNode::OperationType::COMPARISON_OP <= op && op < SNode::OperationType::BOOLEAN_OP)
        return new ComparisonOperator(left, (SNode::ComparisonOperation)op, right);
    else if(op >= SNode::OperationType::BOOLEAN_OP)
        return new BooleanOperator(left, (SNode::BooleanOperation)op, right);
    return nullptr;
}