#include <iostream>
#include <string>
#include "token.h"

#define DEFAULT_FILE "eval1.txt"

int main(int argc, char *argv[])
{
    RecursiveToken tok(argc == 2 ? argv[1] : DEFAULT_FILE);
    RecursiveParsing parse(tok);
    parse.run();

	return 0;
}
