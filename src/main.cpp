#include "Tests/TestController.h"

#include <iostream>
#include <string>
#include <vector>

int main (int argc, char *argv[]) {
    std::vector<std::string> params (argv + 1, argv + argc);
    
    AllTests();
    
    // Compiler comp ("tests/prog.go");
    // comp.dumpTokens();
    // std::cout << comp.getParserExprs().size() << std::endl;
    
    /* if (params[0] == "--tests") AllTests();

    if (params.size() == 2) {
        Compiler comp (params[1]);
        if (params[0] == "--dump-tokens") comp.dumpTokens();
    } */

    return 0;
}