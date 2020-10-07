#include "Semantics.h"

Var::Var (Expression& expr) {
    if (expr.type == 9) {
        row = expr.actualTokenSeq[1].row;
        col = expr.actualTokenSeq[1].col;
        litteral = expr.actualTokenSeq[1].litteral;
        dataType = expr.actualTokenSeq[2].litteral;
        value = expr.actualTokenSeq[4].litteral;
    } else throw std::runtime_error("Var contructor: wrong expression type");
}

std::ostream& operator << (std::ostream& os, Var& var) {
    os << "<" << var.row << ":" << var.col << "> " << var.litteral << " " << var.dataType << " = " << var.value;
    return os;
}

void semanticsAnalysis (const std::vector<std::shared_ptr<Expression>>& exprs) {
    std::vector<std::shared_ptr<Expression>> mathExprs, returnExprs, importExprs, packageExprs, ifExprs, whileExprs, funcDeclareExprs, varDefinitionExprs, varDeclarationExprs, funcCallExprs;
    std::vector<std::pair<std::shared_ptr<Expression>, std::vector<Token>>> blocksByVars;

    for (const auto& expr : exprs) {
        switch (expr->type)
        {
        case 1: mathExprs.push_back(expr); break;
        case 2: returnExprs.push_back(expr); break; // ...
        case 3: importExprs.push_back(expr); break;
        case 4: packageExprs.push_back(expr); break;
        case 5: ifExprs.push_back(expr); break; // ...
        case 6: whileExprs.push_back(expr); break; // ...
        case 7: funcDeclareExprs.push_back(expr); break; // OK
        case 8: varDefinitionExprs.push_back(expr); break; // OK
        case 9: varDeclarationExprs.push_back(expr); break; // OK
        case 10: funcCallExprs.push_back(expr); break; // ...
        default: break;
        }
    }

    for (auto& expr : funcDeclareExprs) blocksByVars.push_back({expr, {}});

    semCheckFuncDeclare(blocksByVars);
    semCheckVarDeclaration(varDeclarationExprs, blocksByVars);
    semCheckVarDefinition(varDefinitionExprs, blocksByVars);
    semCheckReturn(returnExprs, blocksByVars);

    /* std::stringstream ss;
    for (auto& [block, vars] : blocksByVars) {
        ss << "BLOCK\n" << Join(block->actualTokenSeq, ' ') << '\n' << Join(vars, '\n') << "\n\n";
    }
    std::cout << ss.str() << std::endl; */
}

void semCheckFuncDeclare (std::vector<std::pair<std::shared_ptr<Expression>, std::vector<Token>>>& blocksByVars) {
    for (auto& [block, vars] : blocksByVars) {
        if (block->type != 7) continue;
        
        std::string strTokens = block.get()->getStrTokensType(' ');
        std::regex regex("L_PAREN (identifier (COMMA identifier)?\\s?(int|string|bool)) R_PAREN");

        if (!std::regex_search(strTokens, regex)) continue; // has not args

        std::string typeArgs;
        auto it = std::find_if(block->actualTokenSeq.rbegin(), block->actualTokenSeq.rend(), [](Token& token) -> bool {
            return token.type == "R_PAREN";
        });

        typeArgs = (it + 1)->type;
        for (; it->type != "L_PAREN"; it++) {
            if (it->type == "identifier") {
                it->dataType = typeArgs;
                vars.push_back(*it);
            }
        }
    }
    semCheckMultipleDeclaration(blocksByVars);
}

void semCheckVarDeclaration (std::vector<std::shared_ptr<Expression>> varDeclarationExprs, std::vector<std::pair<std::shared_ptr<Expression>, std::vector<Token>>>& blocksByVars) {
    for (auto& varDecl : varDeclarationExprs) {
        bool blockExpect = false;
        size_t placeDeclCurVar = varDecl->actualTokenSeq[0].row;

        for (auto& [block, vars] : blocksByVars) {
            if (block->actualTokenSeq.front().row < placeDeclCurVar && block->actualTokenSeq.back().row > placeDeclCurVar) {
                Token& newVar = varDecl->actualTokenSeq[1];
                newVar.dataType = varDecl->actualTokenSeq.back().dataType;
                newVar.value = varDecl->actualTokenSeq.back().litteral;
                vars.push_back(newVar);
                blockExpect = true;
                break;
            }
        }
        if (!blockExpect) throw std::runtime_error("VAR Declaration error");
    }
    semCheckMultipleDeclaration(blocksByVars);
}

void semCheckVarDefinition (std::vector<std::shared_ptr<Expression>> varDefinitionExprs, std::vector<std::pair<std::shared_ptr<Expression>, std::vector<Token>>>& blocksByVars) {
    for (auto& varDef : varDefinitionExprs) {        
        bool blockExpect = false;
        size_t placeDefCurVar = varDef->actualTokenSeq[0].row;
        auto& var = varDef->actualTokenSeq[0];
        std::vector values = {varDef->actualTokenSeq[2], varDef->actualTokenSeq[4]};

        for (auto& [block, vars] : blocksByVars) {
            if (block->actualTokenSeq.front().row < placeDefCurVar && block->actualTokenSeq.back().row > placeDefCurVar) {
                
                auto it = std::find_if(vars.begin(), vars.end(), [var](Token& token) -> bool {
                    return token.litteral == var.litteral;
                });

                if (it != vars.end()) {
                    
                    if (values[0].dataType == it->dataType && values[1].dataType == it->dataType) {
                        blockExpect = true;
                    } else throw std::runtime_error("type mismatch");
                    break;
                }
            }
        }
        if (!blockExpect) throw std::runtime_error("Var do not decalre");
    }
}

void semCheckReturn (std::vector<std::shared_ptr<Expression>> returnExprs, std::vector<std::pair<std::shared_ptr<Expression>, std::vector<Token>>>& blocksByVars) {
    /* for (auto& expr : returnExprs) {
        bool blockExpect = false;
        size_t placeDefCurVar = expr->actualTokenSeq[0].row;

        for (auto& [block, vars] : blocksByVars) {
            if (block->actualTokenSeq.front().row < placeDefCurVar && block->actualTokenSeq.back().row > placeDefCurVar) {
                blockExpect = true;
                std::string& blockReturnType = block->actualTokenSeq[]

            }
        }
        if (!blockExpect) throw std::runtime_error("Мы не в блоке");
    } */
}

void semCheckMultipleDeclaration (std::vector<std::pair<std::shared_ptr<Expression>, std::vector<Token>>>& blocksByVars) {
    for (auto& blockByVar : blocksByVars) {
        for (auto& var : blockByVar.second) {
            size_t result = std::count_if(blockByVar.second.begin(), blockByVar.second.end(), [var](Token& token) -> bool {
                return token.litteral == var.litteral;
            });
            if (result > 1) throw std::runtime_error("Multiple declaration error");
        }
    }  
}