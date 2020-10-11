#include "CodeGenerator.h"

CodeGenerator::CodeGenerator () { 
    nestingLevel = 0;
    outPath = "output/output.s";
}

void CodeGenerator::generate (const Semantics& semantics, const std::vector<std::shared_ptr<Expression>>& exprs) {
    std::stringstream ss;
    const Block& mainBlock = *std::find_if(semantics.blocks.begin(), semantics.blocks.end(), [] (const Block& block) -> bool {
        return block.name == "main";
    });
    
    genPrologue(ss);

    for (auto& expr : exprs) {
        switch (expr->type)
        {
        case 2: genReturn(ss, mainBlock, *expr); break;
        default: break;
        }
    }    
    
    genEpilogue(ss);
    write(ss);
}

void CodeGenerator::write (std::stringstream& ss) {
    std::ofstream output(outPath);
    output << ss.str() << std::endl;
    output.close();
}

void CodeGenerator::genPrologue (std::stringstream& ss) {
    ss << ".intel_syntax noprefix\n";
    ss << ".globl main\n";
    ss << "\nmain:\n";
    ss << "\tpush rbp\n";
    ss << "\tmov rbp, rsp\n";
    nestingLevel++;
}

void CodeGenerator::genEpilogue (std::stringstream& ss) {
    ss << "\tpop rbp\n";
    ss << "\tret\n";
}

void CodeGenerator::genReturn (std::stringstream& ss, const Block& block, Expression& expr) {
    for (size_t i = 0; i < nestingLevel; i++) ss << "\t";
    ss << "mov " << "eax, ";
    
    if (expr.actualTokenSeq[1].type == "identifier") {
        auto it = std::find_if(block.vars.begin(), block.vars.end(), [expr](const Var& var) -> bool {
            return expr.actualTokenSeq[1].litteral == var.litteral;
        });
        ss << it->value << "\n";
    } else if (expr.actualTokenSeq[1].type == "numeric_const") {
        ss << expr.actualTokenSeq[1].litteral << "\n";
    } else {
        throw std::runtime_error("Type mismatch");
    }
}