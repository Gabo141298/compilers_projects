#include <iostream>
#include <string>

#include "exceptions.hh"

void handleException(SingularityException exception)
{
    std::string errorMessage;
    switch(exception.type)
    {
        case UNKNOWN_ERROR:
            errorMessage = "Unknown error";
            break;
        case UNDECLARED_VARIABLE:
            errorMessage = "Error: undeclared variable";
            break;
        case ARITH_EXPR_BOOLEAN_USE:
            errorMessage = "Error: can't use a boolean expression as an arithmetic expression.";
            break;
        case ARITH_EXPR_FUNCTION_USE:
            errorMessage = "Error: can't use a function name as an arithmetic expression.";
            break;
        case ARITH_EXPR_LIST_USE:
            errorMessage = "Error: can't use a list name as an arithmetic expression.";
            break;
        case ARITH_EXPR_MATRIX_USE:
            errorMessage = "Error: can't use a matrix name as an arithmetic expression.";
            break;
        case ARITH_EXPR_STRING_USE:
            errorMessage = "Error: can't use a string as an arithmetic expression.";
            break;
        case BOOL_EXPR_FUNCTION_USE:
            errorMessage = "Error: can't use a function name as a boolean expression.";
            break;
        case BOOL_EXPR_LIST_USE:
            errorMessage = "Error: can't use a list name as a boolean expression.";
            break;
        case BOOL_EXPR_MATRIX_USE:
            errorMessage = "Error: can't use a matrix name as a boolean expression.";
            break;
        case BOOL_EXPR_STRING_USE:
            errorMessage = "Error: can't use a string as a boolean expression.";
            break;
        case BOOL_EXPR_NUM_USE:
            errorMessage = "Error: can't use a numeric value as a boolean expression.";
            break;
        case COMP_EXPR_BOOL_USE:
            errorMessage = "Error: can't check if a boolean expression is greater or lesser than other.";
            break;
        case COMP_EXPR_FUNCTION_USE:
            errorMessage = "Error: can't use a function name as an expression.";
            break;
        case COMP_EXPR_LIST_USE:
            errorMessage = "Error: can't use a list name as an expression.";
            break;
        case COMP_EXPR_MATRIX_USE:
            errorMessage = "Error: can't use a matrix name as an expression.";
            break;
        case COMP_EXPR_STRING_NUM:
            errorMessage = "Error: can't compare a string with a numeric expression";
            break;
        case NOT_EXPR_INTEGER:
            errorMessage = "Error: can't use an integer as a boolean expression.";
            break;
        case NOT_EXPR_DOUBLE:
            errorMessage = "Error: can't use a double as a boolean expression.";
            break;
        case NOT_EXPR_STRING:
            errorMessage = "Error: can't use a string as a boolean expression.";
            break;
        case NOT_EXPR_FUNCTION:
            errorMessage = "Error: can't use a function name as a boolean expression.";
            break;
        case NOT_EXPR_LIST:
            errorMessage = "Error: can't use a list name as a boolean expression.";
            break;
        case NOT_EXPR_MATRIX:
            errorMessage = "Error: can't use a matrix name as a boolean expression.";
            break;
        case VAR_CALLED_AS_FUNCTN:
            errorMessage = "Error: a symbol of variable type cannot be invoked as a function";
            break;
        case INVALID_ARG_COUNT:
            errorMessage = "Error: method called with invalid amount of arguments";
            break;
        case INFINITE_RECURSION:
            errorMessage = "Error: Infinite recursion detected";
            break;
        case LIST_POSITION_BOOLEAN:
            errorMessage = "Error: can't use a boolean to index a list.";
            break;
        case LIST_POSITION_DOUBLE:
            errorMessage = "Error: can't use a double to index a list.";
            break;
        case LIST_POSITION_STRING:
            errorMessage = "Error: can't use a string to index a list.";
            break;
        case LIST_POSITION_FUNCTION:
            errorMessage = "Error: can't use an function name to index a list.";
            break;
        case LIST_POSITION_LIST:
            errorMessage = "Error: can't use an list name to index a list.";
            break;
        case LIST_POSITION_MATRIX:
            errorMessage = "Error: can't use an matrix name to index a list.";
            break;
        case MATRIX_POSITION_BOOLEAN:
            errorMessage = "Error: can't index a matrix with a boolean.";
            break;
        case MATRIX_POSITION_DOUBLE:
            errorMessage = "Error: can't index a matrix with a double.";
            break;
        case MATRIX_POSITION_STRING:
            errorMessage = "Error: can't index a matrix with a string.";
            break;
        case MATRIX_POSITION_FUNCTION:
            errorMessage = "Error: can't index a matrix with a function name.";
            break;
        case MATRIX_POSITION_LIST:
            errorMessage = "Error: can't index a matrix with a list name.";
            break;
        case MATRIX_POSITION_MATRIX:
            errorMessage = "Error: can't index a matrix with a matrix name.";
            break;
        case WHILE_CONDITION:
            errorMessage = "Error: while needs a boolean expression as its condition.";
            break;
        case IF_CONDITION:
            errorMessage = "Error: if needs a boolean expression as its condition.";
            break;
        case WHILE_COUNTING_RANGE:
            errorMessage = "Error: range of values in while counting must be defined by integers.";
            break;
        case MATR_INDEX_EXCP:
            errorMessage = "Error: trying to index as a matrix something that isn't a matrix.";
            break;
        case LIST_INDEX_EXCP:
            errorMessage = "Error: trying to index as a list something that isn't a list.";
            break;
        default:
            break;
    }
    std::cout << errorMessage << std::endl;

    if(exception.customMessage.size() > 0)
        std::cout << "\t" << exception.customMessage << std::endl;
}