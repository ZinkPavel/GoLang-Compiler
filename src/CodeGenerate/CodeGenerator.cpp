#include "CodeGenerator.h"

CodeGenerator::CodeGenerator () { outPath = "output/output.s"; }

void CodeGenerator::generate () {
    genPrologue();

    // gen programm
    
    genEpilogue();
    write();
}

void CodeGenerator::write () {
    std::ofstream output(outPath);
    for (const std::string& str : outData) output << str << "\n";
    output.close();
}

void CodeGenerator::genPrologue () {
    outData.push_back(".intel_syntax noprefix");
    outData.push_back(".globl main\n");
    outData.push_back("main:");
    outData.push_back("\tpush rbp");
    outData.push_back("\tmov rbp, rsp");
}

void CodeGenerator::genEpilogue () {
    outData.push_back("\tpop rbp");
    outData.push_back("\tret");
}