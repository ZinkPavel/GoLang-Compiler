#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

class CodeGenerator {    
public:
    std::string outPath;
    std::vector<std::string> outData;

    CodeGenerator ();

    void generate ();
    void write ();
    void genPrologue ();
    void genEpilogue ();

};