#include "Block.h"

Block::Block () {}

Block::Block (Expression& expr) {
    if (expr.type == 7) {
        std::vector<Token>& tokenSeq = expr.actualTokenSeq;
        std::string strTokens = expr.getStrTokensType(' ');
        name = tokenSeq[1].litteral;
        start = expr.actualTokenSeq.front().row;
        end = expr.actualTokenSeq.back().row;
        if (std::regex_search(strTokens, std::regex("L_PAREN (identifier (COMMA identifier)?\\s?(int|string|bool)) R_PAREN"))) hasArgs = true;
        if (std::regex_search(strTokens, std::regex("(int|bool|string) L_BRACE"))) hasReturn = true;
        if (hasReturn) returnType = (tokenSeq[tokenSeq.size() - 3]).litteral;

        if (hasArgs) {
            auto it = std::find_if(tokenSeq.rbegin(), tokenSeq.rend(), [](Token& token) -> bool {
                return token.type == "R_PAREN";
            });
            
            argsType = (it + 1)->type;
            for (; it->type != "L_PAREN"; it++) {
                if (it->type == "identifier") {
                    it->dataType = argsType;
                    vars.push_back({*it});
                }
            }
        }
         
    } else throw std::runtime_error("Block constructor: wrong expression type. Expected FuncDeclarationExpression.");
}

void Block::multipleDeclarationCheck () {
    for (auto& var : vars) {
        size_t count = std::count_if(vars.begin(), vars.end(), [var](Var& _var) -> bool {
            return var.litteral == _var.litteral;
        });
        if (count > 1) throw std::runtime_error("Multiple declaration error");
    }
}

/* Operators */

std::ostream& operator << (std::ostream& os, Block& block) {
    os << "<" << block.start << ":" << block.end << ">";
    os << "Name = " << block.name << "; ";
    if (block.hasArgs) os << "ArgsType = " << block.argsType << "; ";
    if (block.hasReturn) os << "BlockReturnType = " << block.returnType << "; ";
    os << "\n";
    if (block.vars.size() > 0) for (auto& var : block.vars) os << var << "\n"; 
    return os;
}