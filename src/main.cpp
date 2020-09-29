#include "Tests/TestController.h"

#include <iostream>
#include <string>
#include <vector>

int main (int argc, char *argv[]) {
    std::vector<std::string> params (argv + 1, argv + argc);

    Compiler comp("tests/prog.go");

    if (params.size() == 1) {
        if (params[0] == "--dump-tokens") comp.dumpTokens();
        else if (params[0] == "--dump-ast") comp.dumpAst();
        else if (params[0] == "--tests") AllTests();
    }

    return 0;
}