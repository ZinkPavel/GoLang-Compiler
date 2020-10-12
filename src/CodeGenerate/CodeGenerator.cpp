#include "CodeGenerator.h"

CodeGenerator::CodeGenerator () { 
    nestingLevel = 0;
    numBranches = 0;
    shift = 0;
    outPath = "output/output.s";
}

std::vector<Token>& CodeGenerator::getVars () { return vars; }

void CodeGenerator::generate (Semantics& semantics, const std::vector<std::shared_ptr<Expression>>& exprs) {
    std::stringstream ss;
    Block& mainBlock = *std::find_if(semantics.blocks.begin(), semantics.blocks.end(), [] (const Block& block) -> bool {
        return block.name == "main";
    });
    
    genPrologue(ss);

    for (auto& expr : exprs) {
        switch (expr->type)
        {
        case 2: genReturn(ss, mainBlock, *expr); break;
        case 8: genVarDefiniton(ss, mainBlock, *expr); break;
        case 9: genVarDeclaration(ss, mainBlock, *expr); break;
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
    Token& var = expr.actualTokenSeq[1];
    
    if (var.type == "identifier") ss << "DWORD PTR [rbp-" << (*std::find_if(vars.begin(), vars.end(), [expr, var](Token& token) {
        return var.litteral == token.litteral;
    })).shift << "]\n";
    else if (var.type == "numeric_const") ss << var.litteral << "\n";
    else throw std::runtime_error("Type mismatch");
}

void CodeGenerator::genVarDeclaration (std::stringstream& ss, Block& block, Expression& expr) {
    for (size_t i = 0; i < nestingLevel; i++) ss << "\t";
    Token& var = expr.actualTokenSeq[1];

    if (var.dataType == "int") {
        shift = shift + 4;
        var.shift = shift;
    }

    vars.push_back(var);
    ss << "mov " << "DWORD PTR [rbp-" << var.shift << "], " << var.value << "\n";
}

void CodeGenerator::genVarDefiniton (std::stringstream& ss, Block& block, Expression& expr) {
    std::string sign = expr.actualTokenSeq[3].litteral, tabulation;
    tabulation.insert(tabulation.begin(), nestingLevel, '\t');

    std::vector<std::pair<bool, std::string>> varValues;
    {
        varValues.push_back({true, std::to_string((*std::find_if(vars.begin(), vars.end(), [expr](Token& var) {
            return expr.actualTokenSeq[0].litteral == var.litteral;
        })).shift)});

        if (expr.actualTokenSeq[2].type == "identifier") {
            varValues.push_back({true, std::to_string((*std::find_if(vars.begin(), vars.end(), [expr](Token& var) {
                return expr.actualTokenSeq[2].litteral == var.litteral;
            })).shift)});
        } else varValues.push_back({false, expr.actualTokenSeq[2].litteral});

        if (expr.actualTokenSeq[4].type == "identifier") {
            varValues.push_back({true, std::to_string((*std::find_if(vars.begin(), vars.end(), [expr](Token& var) {
                return expr.actualTokenSeq[4].litteral == var.litteral;
            })).shift)});
        } else varValues.push_back({false, expr.actualTokenSeq[4].litteral});
    }

    if (sign == "+") {
        ss << tabulation << "mov edx, " << (varValues[1].first ? "DWORD PTR [rbp-" + varValues[1].second + "]" : varValues[1].second) << "\n";
        ss << tabulation << "mov eax, " << (varValues[2].first ? "DWORD PTR [rbp-" + varValues[2].second + "]" : varValues[2].second) << "\n";
        ss << tabulation << "add eax, edx\n";
        ss << tabulation << "mov " << (varValues[0].first ? "DWORD PTR [rbp-" + varValues[0].second + "]" : varValues[0].second) << ", eax\n";
    }
    else if (sign == "-") {
        ss << tabulation << "mov eax, " << (varValues[1].first ? "DWORD PTR [rbp-" + varValues[1].second + "]" : varValues[1].second) << "\n";
        ss << tabulation << "sub eax, " << (varValues[2].first ? "DWORD PTR [rbp-" + varValues[2].second + "]" : varValues[2].second) << "\n";;
        ss << tabulation << "mov " << (varValues[0].first ? "DWORD PTR [rbp-" + varValues[0].second + "]" : varValues[0].second) << ", eax\n";
    }
    else if (sign == "/") {
        ss << tabulation << "mov eax, " << (varValues[1].first ? "DWORD PTR [rbp-" + varValues[1].second + "]" : varValues[1].second) << "\n";
        ss << tabulation << "cdq\n";
        ss << tabulation << "idiv " << (varValues[2].first ? "DWORD PTR [rbp-" + varValues[2].second + "]" : varValues[2].second) << "\n";
        ss << tabulation << "mov " << (varValues[0].first ? "DWORD PTR [rbp-" + varValues[0].second + "]" : varValues[0].second) << ", eax\n";
    }
    else if (sign == "*") {
        ss << tabulation << "mov eax, " << (varValues[1].first ? "DWORD PTR [rbp-" + varValues[1].second + "]" : varValues[1].second) << "\n";
        ss << tabulation << "imul eax, " << (varValues[2].first ? "DWORD PTR [rbp-" + varValues[2].second + "]" : varValues[2].second) << "\n";
        ss << tabulation << "mov " << (varValues[0].first ? "DWORD PTR [rbp-" + varValues[0].second + "]" : varValues[0].second) << ", eax\n";
    }
}