#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <string>

enum ExceptionType
{
    UNKNOWN_ERROR,
    UNDECLARED_VARIABLE,

    // Arithmetic operation exceptions
    ARITH_EXPR_BOOLEAN_USE,
    ARITH_EXPR_FUNCTION_USE,
    ARITH_EXPR_LIST_USE,
    ARITH_EXPR_MATRIX_USE,
    ARITH_EXPR_STRING_USE,

    // Boolean operation exceptions
    BOOL_EXPR_FUNCTION_USE,
    BOOL_EXPR_LIST_USE,
    BOOL_EXPR_MATRIX_USE,
    BOOL_EXPR_STRING_USE,
    BOOL_EXPR_NUM_USE,

    // Comparison operation exceptions
    COMP_EXPR_BOOL_USE,
    COMP_EXPR_FUNCTION_USE,
    COMP_EXPR_LIST_USE,
    COMP_EXPR_MATRIX_USE,
    COMP_EXPR_STRING_NUM,
    VAR_CALLED_AS_FUNCTN,
    INVALID_ARG_COUNT,
    INFINITE_RECURSION,

    // Not operation exceptions
    NOT_EXPR_INTEGER,
    NOT_EXPR_DOUBLE,
    NOT_EXPR_STRING,
    NOT_EXPR_FUNCTION,
    NOT_EXPR_LIST,
    NOT_EXPR_MATRIX,

    // List position exceptions
    LIST_POSITION_BOOLEAN,
    LIST_POSITION_DOUBLE,
    LIST_POSITION_STRING,
    LIST_POSITION_FUNCTION,
    LIST_POSITION_LIST,
    LIST_POSITION_MATRIX,

    // Matrix position exceptions
    MATRIX_POSITION_BOOLEAN,
    MATRIX_POSITION_DOUBLE,
    MATRIX_POSITION_STRING,
    MATRIX_POSITION_FUNCTION,
    MATRIX_POSITION_LIST,
    MATRIX_POSITION_MATRIX,

    // Error in conditions
    WHILE_CONDITION,
    IF_CONDITION,
    WHILE_COUNTING_RANGE,

    // Error indexing a data structure
    MATR_INDEX_EXCP,
    LIST_INDEX_EXCP
};

struct SingularityException
{
    ExceptionType type;
    std::string customMessage;
    SingularityException(ExceptionType type, std::string customMessage = "")
        : type(type), customMessage(customMessage)
    {
    }
};

void handleException(SingularityException exception);

#endif // EXCEPTIONS_H