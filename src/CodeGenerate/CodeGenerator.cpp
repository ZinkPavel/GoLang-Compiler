#include "CodeGenerator.h"

CodeGenerator::CodeGenerator () { 
    pendingBranch = false;
    nestingLevel = 0;
    numBranches = 1;
    numStr = 0;
    shift = 0;
    point = 0;
    outPath = "output/output.s";
}

std::vector<Token>& CodeGenerator::getVars () { return vars; }

void CodeGenerator::generate (Semantics& semantics, const std::vector<std::shared_ptr<Expression>>& exprs) {
    std::vector<std::stringstream> streams(1);

    Block& mainBlock = *std::find_if(semantics.blocks.begin(), semantics.blocks.end(), [] (const Block& block) -> bool {
        return block.name == "main";
    });
    
    std::queue<size_t> branches;
    for (auto& expr : exprs) {
        switch (expr->type)
        {
        case 5: branches.push(BRNCH::IF); break;
        case 6: branches.push(BRNCH::WHILE); break;
        default: break;
        }    
    }

    genPrologue(streams.back());

    for (auto& expr : exprs) {
        switch (expr->type)
        {
        case 2: genReturn(streams, mainBlock, *expr); break;
        case 5: genIf(streams, mainBlock, *expr); break;
        case 6: genWhile(streams, mainBlock, *expr); break;
        case 8: genVarDefiniton(streams, mainBlock, *expr); break;
        case 9: genVarDeclaration(streams, mainBlock, *expr); break;
        case 11: genPrint(streams, mainBlock, *expr); break;
        case 12: genScan(streams, mainBlock, *expr); break;
        default: break;
        }
    }

    if (pendingBranch) {
        streams.push_back(std::stringstream());
        streams.back() << ".L" << numBranches << ":\n";
        pendingBranch = false;
    }  
    
    genEpilogue(streams.back());
    write(streams, lcStream);
}

void CodeGenerator::write (std::vector<std::stringstream>& streams, std::stringstream& strStream) {
    std::ofstream output(outPath);
    output << ".intel_syntax noprefix\n";
    output << ".globl main\n\n";
    output << strStream.str();

    for (auto& stream : streams) output << stream.str();
    
    output << std::endl;
    output.close();
}

void CodeGenerator::genPrologue (std::stringstream& ss) {
    ss << "\nmain:\n";
    ss << "\tpush rbp\n";
    ss << "\tmov rbp, rsp\n";
    ss << "\tsub rsp, 16\n";
    nestingLevel++;
}

void CodeGenerator::genEpilogue (std::stringstream& ss) {
    ss << "\tleave\n";
    ss << "\tret\n";
}

void CodeGenerator::genReturn (std::vector<std::stringstream>& streams, const Block& block, Expression& expr) {
    if (pendingBranch && expr.actualTokenSeq.front().row > point) {
        streams.push_back(std::stringstream());
        streams.back() << ".L" << numBranches << ":\n";
        pendingBranch = false;
    }
    
    std::stringstream& ss = streams.back();
    
    for (size_t i = 0; i < nestingLevel; i++) ss << "\t";
    ss << "mov " << "eax, ";
    Token& var = expr.actualTokenSeq[1];
    
    if (var.type == "identifier") ss << "DWORD PTR [rbp-" << (*std::find_if(vars.begin(), vars.end(), [expr, var](Token& token) {
        return var.litteral == token.litteral;
    })).shift << "]\n";
    else if (var.type == "numeric_const") ss << var.litteral << "\n";
    else throw std::runtime_error("Type mismatch");
}

void CodeGenerator::genIf(std::vector<std::stringstream>& streams, const Block& block, Expression& expr) {
    if (pendingBranch && expr.actualTokenSeq.front().row > point) {
        streams.push_back(std::stringstream());
        streams.back() << ".L" << numBranches << ":\n";
        pendingBranch = false;
    }
    
    std::stringstream& ss = (expr.actualTokenSeq.begin()->row < point ? streams[streams.size()-2] : streams.back());

    point = expr.actualTokenSeq.back().row > point ? expr.actualTokenSeq.back().row : point;

    std::string sign = expr.actualTokenSeq[2].type;
    std::vector<std::string> varValues;
    {
        if (expr.actualTokenSeq[1].type == "identifier") { 
            varValues.push_back(std::to_string((*std::find_if(vars.begin(), vars.end(), [expr](Token& var) {
                return expr.actualTokenSeq[1].litteral == var.litteral;
            })).shift));
        } else varValues.push_back(expr.actualTokenSeq[1].litteral);

        if (expr.actualTokenSeq[3].type == "identifier") { 
            varValues.push_back(std::to_string((*std::find_if(vars.begin(), vars.end(), [expr](Token& var) {
                return expr.actualTokenSeq[3].litteral == var.litteral;
            })).shift));
        } else varValues.push_back(expr.actualTokenSeq[3].litteral);
    }
    
    branches.pop();
    numBranches = (branches.front() > 0 && branches.front() == BRNCH::WHILE) ? numBranches + 2 : numBranches + 1;
    
    ss << "\tmov eax, " << ((expr.actualTokenSeq[1].type == "identifier") ? "DWORD PTR [rbp-" + varValues[0] + "]" : varValues[0]) << "\n";
    ss << "\tcmp eax, " << ((expr.actualTokenSeq[3].type == "identifier") ? "DWORD PTR [rbp-" + varValues[1] + "]" : varValues[1]) << "\n";
    
    if (sign == "MORE") ss << "\tjle ";
    else if (sign == "LESS") ss << "\tjge ";
    else if (sign == "EQUAL") ss << "\tjne ";
    else if (sign == "NOT_EQUAL") ss << "\tje ";
    
    ss << ".L" << ++numBranches << "\n";

    pendingBranch = true;
}

void CodeGenerator::genWhile(std::vector<std::stringstream>& streams, const Block& block, Expression& expr) {
    if (pendingBranch && expr.actualTokenSeq.front().row > point) pendingBranch = false;

    std::stringstream& ss = (expr.actualTokenSeq.begin()->row < point ? streams[streams.size()-2] : streams.back());

    point = expr.actualTokenSeq.back().row > point ? expr.actualTokenSeq.back().row : point;

    std::string sign = expr.actualTokenSeq[2].type;
    std::vector<std::string> varValues;
    {
       if (expr.actualTokenSeq[1].type == "identifier") { 
            varValues.push_back(std::to_string((*std::find_if(vars.begin(), vars.end(), [expr](Token& var) {
                return expr.actualTokenSeq[1].litteral == var.litteral;
            })).shift));
        } else varValues.push_back(expr.actualTokenSeq[1].litteral);

        if (expr.actualTokenSeq[3].type == "identifier") { 
            varValues.push_back(std::to_string((*std::find_if(vars.begin(), vars.end(), [expr](Token& var) {
                return expr.actualTokenSeq[3].litteral == var.litteral;
            })).shift));
        } else varValues.push_back(expr.actualTokenSeq[3].litteral);
    }

    numBranches = (branches.front() > 0 && branches.front() == BRNCH::WHILE) ? numBranches + 2 : numBranches + 1;
    ss << "\tjmp .L" << numBranches-1 << "\n";
    
    streams.push_back(std::stringstream());
    streams.back() << ".L" << numBranches << ":\n";
    
    streams.push_back(std::stringstream());
    streams.back() << ".L" << numBranches-1 << ":\n";
    streams.back() << "\tmov eax, " << ((expr.actualTokenSeq[1].type == "identifier") ? "DWORD PTR [rbp-" + varValues[0] + "]" : varValues[0]) << "\n";
    streams.back() << "\tcmp eax, " << ((expr.actualTokenSeq[3].type == "identifier") ? "DWORD PTR [rbp-" + varValues[1] + "]" : varValues[1]) << "\n";

    if (sign == "MORE") streams.back() << "\tjg ";
    else if (sign == "LESS") streams.back() << "\tjl ";
    else if (sign == "EQUAL") streams.back() << "\tje ";
    else if (sign == "NOT_EQUAL") streams.back() << "\tjne ";
    
    streams.back() << ".L" << numBranches << "\n";
}

void CodeGenerator::genVarDeclaration (std::vector<std::stringstream>& streams, Block& block, Expression& expr) {
    if (pendingBranch && expr.actualTokenSeq.front().row > point) {
        streams.push_back(std::stringstream());
        streams.back() << ".L" << numBranches << ":\n";
        pendingBranch = false;
    }
    
    std::stringstream& ss = (expr.actualTokenSeq.begin()->row < point ? streams[streams.size()-2] : streams.back());
    
    for (size_t i = 0; i < nestingLevel; i++) ss << "\t";
    Token& var = expr.actualTokenSeq[1];

    if (var.dataType == "int") {
        shift = shift + 4;
        var.shift = shift;
    }

    vars.push_back(var);
    ss << "mov " << "DWORD PTR [rbp-" << var.shift << "], " << var.value << "\n";
}

void CodeGenerator::genVarDefiniton (std::vector<std::stringstream>& streams, Block& block, Expression& expr) {
    if (pendingBranch && expr.actualTokenSeq.front().row > point) {
        streams.push_back(std::stringstream());
        streams.back() << ".L" << numBranches << ":\n";
        pendingBranch = false;
    }
    
    std::stringstream& ss = (streams.size() > 2 && expr.actualTokenSeq.begin()->row < point ? streams[streams.size()-2] : streams.back());

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

void CodeGenerator::genPrint (std::vector<std::stringstream>& streams, Block& block, Expression& expr) {
    if (pendingBranch && expr.actualTokenSeq.front().row > point) {
        streams.push_back(std::stringstream());
        streams.back() << ".L" << numBranches << ":\n";
        pendingBranch = false;
    }

    size_t varValue = std::find_if(vars.begin(), vars.end(), [expr](Token& var) {
        return expr.actualTokenSeq[4].litteral == var.litteral;
    })->shift;  

    std::stringstream& ss = (streams.size() > 2 && expr.actualTokenSeq.begin()->row < point ? streams[streams.size()-2] : streams.back());

    lcStream << ".LC" << numStr << ":\n";
    lcStream << "\t.string " << expr.actualTokenSeq[2].litteral << "\n";

    ss << "\tmov eax, DWORD PTR [rbp-" << varValue << "]\n";
    ss << "\tmov esi, eax\n";
    ss << "\tmov edi, OFFSET FLAT:.LC0\n";
    ss << "\tmov eax, 0\n";
    ss << "\tcall printf\n";
}

void CodeGenerator::genScan (std::vector<std::stringstream>& streams, Block& block, Expression& expr) {
    if (pendingBranch && expr.actualTokenSeq.front().row > point) {
        streams.push_back(std::stringstream());
        streams.back() << ".L" << numBranches << ":\n";
        pendingBranch = false;
    }

    size_t varValue = std::find_if(vars.begin(), vars.end(), [expr](Token& var) {
        return expr.actualTokenSeq[4].litteral == var.litteral;
    })->shift;  

    std::stringstream& ss = (streams.size() > 2 && expr.actualTokenSeq.begin()->row < point ? streams[streams.size()-2] : streams.back());

    lcStream << ".LC" << numStr << ":\n";
    lcStream << "\t.string " << expr.actualTokenSeq[2].litteral << "\n";

    ss << "\tmov eax, DWORD PTR [rbp-" << varValue << "]\n";
    ss << "\tmov esi, eax\n";
    ss << "\tmov edi, OFFSET FLAT:.LC0\n";
    ss << "\tmov eax, 0\n";
    ss << "\tcall __isoc99_scanf\n";
}
