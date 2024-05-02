/*
PROGRAMMER: Marlene Habib
PROGRAM#: 5
DUE DATE: Wednesday, 4/03/2024
INSTRUCTOR: Dr. Dong
DESCRIPTION OF PROGRAM:
This program is for printing the interpreter of the symbol table and abstract syntax tree in c++.
*/

#include <algorithm>
#include "slp.h"


using namespace std;

// Interprets the compound statement
void CompoundStm::interp(SymbolTable& symbols) {

    // Interpret the first statement
    stm1->interp(symbols);

    // Then interpret the second statement
    stm2->interp(symbols);
}

// Interprets the assignment statement
void AssignStm::interp(SymbolTable& symbols) {

    // Evaluate the expression and assign the result in the symbol table
    symbols[id] = exp->interp(symbols);
}

// Interprets the print statement
void PrintStm::interp(SymbolTable& symbols) {

    // Interpret the expression list and print the results
    exps->interp(symbols);

    // End the print with a newline
    cout << endl;
}

// Interprets the identifier expression
int IdExp::interp(SymbolTable& symbols) {

    // Return the value of the variable from the symbol table
    return symbols[id];
}

// Interprets the numeric expression
int NumExp::interp(SymbolTable& symbols) {

    // Just return number
    return num;
}

// Interprets the operation expression
int OpExp::interp(SymbolTable& symbols) {

    // Evaluate the left expression
    int leftValue = left->interp(symbols);

    // Evaluate the right expression
    int rightValue = right->interp(symbols);

    // Use the if loop to apply operator to the results of the left and right expressions
    if (oper == PLUS) {
        return leftValue + rightValue;
    }
    else if (oper == MINUS) {
        return leftValue - rightValue;
    }
    else if (oper == TIMES) {
        return leftValue * rightValue;
    }
    else if (oper == DIV) {

        // Check the division by zero
        if (rightValue == 0) {
            // Return 0 if there's a error
            return 0;
        }
        return leftValue / rightValue;
    }
    else {

        // Return 0 if the no operator
        return 0;
    }
}

// Interprets the EseqExp
int EseqExp::interp(SymbolTable& symbols) {

    // First interpret the statement
    stm->interp(symbols);

    // Then interpret the expression and return the result
    return exp->interp(symbols);
}

// Interprets the pair expression list
void PairExpList::interp(SymbolTable& symbols) {

    // Print the result 
    cout << head->interp(symbols) << " ";

    // Then interpret the tail expression list
    tail->interp(symbols);
}

// Interprets the last expression list
void LastExpList::interp(SymbolTable& symbols) {

    // Print the result of interpreting the head (and only) expression
    cout << head->interp(symbols);
}

