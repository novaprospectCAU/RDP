#pragma once
#include <iostream>

using namespace std;

enum Token
{
    NONE,

    PROGRAM,
    STATEMENTS,
    STATEMENT,
	EXPRESSION,
	TERM,
	TERM_TAIL,
	FACTOR,
	FACTOR_TAIL,
	CONST,              //any decimal numbers
	IDENT,              //any names conforming to C identifier rules

	ASSIGNMENT_OP,		//:=
	SEMI_COLON = ';',

	ADD_OPERATOR = '+',
	SUB_OPERATOR = '-',
	MULTI_OPERATOR = '*',
	DIVID_OPERATOR = '/',

	LEFT_PAREN = '(',
	RIGHT_PAREN = ')',
};

class RecursiveToken {
private:

public:

};
