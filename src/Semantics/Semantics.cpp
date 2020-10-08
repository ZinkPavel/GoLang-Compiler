#include "Semantics.h"

Var::Var (size_t _row, size_t _col, std::string _literral, std::string _dataType, std::string _value) 
    : row(_row), col(_col), litteral(_literral), dataType(_dataType), value(_value) {}

Var::Var (Token& token) {
    row = token.row;
    col = token.col;
    litteral = token.litteral;
    dataType = token.dataType;
}

Var::Var (Expression& expr) {
    if (expr.type == 9) {
        row = expr.actualTokenSeq[1].row;
        col = expr.actualTokenSeq[1].col;
        litteral = expr.actualTokenSeq[1].litteral;
        dataType = expr.actualTokenSeq[2].litteral;
        value = expr.actualTokenSeq[4].litteral;
    } else throw std::runtime_error("Var contructor: wrong expression type. Expected VarDeclarationExpression.");
}

Block::Block (Expression& expr) {
    if (expr.type == 7) {
        std::vector<Token>& tokenSeq = expr.actualTokenSeq;
        std::string strTokens = expr.getStrTokensType(' ');
        name = tokenSeq[1].litteral;
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

std::ostream& operator << (std::ostream& os, Var& var) {
    os << "<" << var.row << ":" << var.col << "> " << var.litteral << " " << var.dataType << " = " << var.value;
    return os;
}

bool operator == (Var& lhs, Var& rhs) {
    return tie(lhs.row, lhs.col, lhs.litteral, lhs.dataType, lhs.value) == tie(rhs.row, rhs.col, rhs.litteral, rhs.dataType, rhs.value);
}

void semanticsAnalysis (const std::vector<std::shared_ptr<Expression>>& exprs) {
    std::vector<std::shared_ptr<Expression>> mathExprs, returnExprs, importExprs, packageExprs, ifExprs, whileExprs, funcDeclareExprs, varDefinitionExprs, varDeclarationExprs, funcCallExprs;
    // std::vector<std::pair<std::shared_ptr<Expression>, std::vector<Token>>> blocksByVars;
    std::vector<Block> blocks;

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
        case 8: varDefinitionExprs.push_back(expr); break; // ...
        case 9: varDeclarationExprs.push_back(expr); break; // ...
        case 10: funcCallExprs.push_back(expr); break; // ...
        default: break;
        }
    }

    for (auto& expr : funcDeclareExprs) {
        blocks.push_back({*expr});
        blocks.back().multipleDeclarationCheck();
    }
    // std::cout << blocks.size() << std::endl;
    // for (auto& expr : funcDeclareExprs) blocksByVars.push_back({expr, {}});

    // semCheckFuncDeclare(blocksByVars);
    // semCheckVarDeclaration(varDeclarationExprs, blocksByVars);
    // semCheckVarDefinition(varDefinitionExprs, blocksByVars);
    // semCheckReturn(returnExprs, blocksByVars);

    /* std::stringstream ss;
    for (auto& [block, vars] : blocksByVars) {
        ss << "BLOCK\n" << Join(block->actualTokenSeq, ' ') << '\n' << Join(vars, '\n') << "\n\n";
    }
    std::cout << ss.str() << std::endl; */
}

// void semCheckVarDeclaration (std::vector<std::shared_ptr<Expression>> varDeclarationExprs, std::vector<std::pair<std::shared_ptr<Expression>, std::vector<Token>>>& blocksByVars) {
//     for (auto& varDecl : varDeclarationExprs) {
//         bool blockExpect = false;
//         size_t placeDeclCurVar = varDecl->actualTokenSeq[0].row;

//         for (auto& [block, vars] : blocksByVars) {
//             if (block->actualTokenSeq.front().row < placeDeclCurVar && block->actualTokenSeq.back().row > placeDeclCurVar) {
//                 Token& newVar = varDecl->actualTokenSeq[1];
//                 newVar.dataType = varDecl->actualTokenSeq.back().dataType;
//                 newVar.value = varDecl->actualTokenSeq.back().litteral;
//                 vars.push_back(newVar);
//                 blockExpect = true;
//                 break;
//             }
//         }
//         if (!blockExpect) throw std::runtime_error("VAR Declaration error");
//     }
//     semCheckMultipleDeclaration(blocksByVars);
// }

// void semCheckVarDefinition (std::vector<std::shared_ptr<Expression>> varDefinitionExprs, std::vector<std::pair<std::shared_ptr<Expression>, std::vector<Token>>>& blocksByVars) {
//     for (auto& varDef : varDefinitionExprs) {        
//         bool blockExpect = false;
//         size_t placeDefCurVar = varDef->actualTokenSeq[0].row;
//         auto& var = varDef->actualTokenSeq[0];
//         std::vector values = {varDef->actualTokenSeq[2], varDef->actualTokenSeq[4]};

//         for (auto& [block, vars] : blocksByVars) {
//             if (block->actualTokenSeq.front().row < placeDefCurVar && block->actualTokenSeq.back().row > placeDefCurVar) {
                
//                 auto it = std::find_if(vars.begin(), vars.end(), [var](Token& token) -> bool {
//                     return token.litteral == var.litteral;
//                 });

//                 if (it != vars.end()) {
                    
//                     if (values[0].dataType == it->dataType && values[1].dataType == it->dataType) {
//                         blockExpect = true;
//                     } else throw std::runtime_error("type mismatch");
//                     break;
//                 }
//             }
//         }
//         if (!blockExpect) throw std::runtime_error("Var do not decalre");
//     }
// }

// void semCheckReturn (std::vector<std::shared_ptr<Expression>> returnExprs, std::vector<std::pair<std::shared_ptr<Expression>, std::vector<Token>>>& blocksByVars) {
//     /* for (auto& expr : returnExprs) {
//         bool blockExpect = false;
//         size_t placeDefCurVar = expr->actualTokenSeq[0].row;

//         for (auto& [block, vars] : blocksByVars) {
//             if (block->actualTokenSeq.front().row < placeDefCurVar && block->actualTokenSeq.back().row > placeDefCurVar) {
//                 blockExpect = true;
//                 std::string& blockReturnType = block->actualTokenSeq[]

//             }
//         }
//         if (!blockExpect) throw std::runtime_error("Мы не в блоке");
//     } */
// }

