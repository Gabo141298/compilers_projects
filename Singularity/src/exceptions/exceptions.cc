#include <iostream>

#include "exceptions.hh"

void handleException(SingularityException exception)
{
    switch(exception)
    {
        case UNKNOWN_ERROR:
            std::cout << "Unknown error" << std::endl;
            break;
        case UNDECLARED_VARIABLE:
            std::cout << "Error: undeclared variable" << std::endl;
            break;
        case ARITH_EXPR_BOOLEAN_USE:
            std::cout << "Error: can't use a boolean expression as an arithmetic expression." << std::endl;
            break;
        case ARITH_EXPR_FUNCTION_USE:
            std::cout << "Error: can't use a function name as an arithmetic expression." << std::endl;
            break;
        case ARITH_EXPR_LIST_USE:
            std::cout << "Error: can't use a list name as an arithmetic expression." << std::endl;
            break;
        case ARITH_EXPR_MATRIX_USE:
            std::cout << "Error: can't use a matrix name as an arithmetic expression." << std::endl;
            break;
        case ARITH_EXPR_STRING_USE:
            std::cout << "Error: can't use a string as an arithmetic expression." << std::endl;
            break;
        case BOOL_EXPR_FUNCTION_USE:
            std::cout << "Error: can't use a function name as a boolean expression." << std::endl;
            break;
        case BOOL_EXPR_LIST_USE:
            std::cout << "Error: can't use a list name as a boolean expression." << std::endl;
            break;
        case BOOL_EXPR_MATRIX_USE:
            std::cout << "Error: can't use a matrix name as a boolean expression." << std::endl;
            break;
        case BOOL_EXPR_STRING_USE:
            std::cout << "Error: can't use a string as a boolean expression." << std::endl;
            break;
        case BOOL_EXPR_NUM_USE:
            std::cout << "Error: can't use a numeric value as a boolean expression." << std::endl;
            break;
        case COMP_EXPR_BOOL_USE:
            std::cout << "Error: can't use a boolean expression to compare." << std::endl;
            break;
        case COMP_EXPR_FUNCTION_USE:
            std::cout << "Error: can't use a function name as an expression." << std::endl;
            break;
        case COMP_EXPR_LIST_USE:
            std::cout << "Error: can't use a list name as an expression." << std::endl;
            break;
        case COMP_EXPR_MATRIX_USE:
            std::cout << "Error: can't use a matrix name as an expression." << std::endl;
            break;
        case COMP_EXPR_STRING_NUM:
            std::cout << "Error: can't compare a string with a numeric expression" << std::endl;
            break;
        default:
            break;
    }
}