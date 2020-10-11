#include "CodeGenerator.h"

CodeGenerator::CodeGenerator () { outPath = "output/output.s"; }

void CodeGenerator::generate () {
    write();
}

void CodeGenerator::write () {
    std::ofstream output(outPath);
    for (const std::string& str : outData) output << str << "\n";
    output.close();
}

void CodeGenerator::genHeader () {}