#include "Semantics.h"

Semantics::Semantics () {}

void Semantics::addVarByExpr (Expression& expr) {
    bool blockDetected = false;
    Var newVar(expr);
    size_t placeVar = newVar.row;

    for (auto& block : blocks) {
        if (block.start < placeVar && block.end > placeVar) {
            blockDetected = true;
            block.vars.push_back(newVar);
        }
    }
    if (!blockDetected) throw std::runtime_error("Var. Wrong declaration.");
}

void Semantics::callReturnCheck (Expression& expr) {
    bool blockDetected = false, varDetected = false;
    size_t placeReturn = expr.actualTokenSeq[0].row;
    Block expectedBlock;
    
    for (auto& block : blocks) {
        if (block.start < placeReturn && block.end > placeReturn) {
            blockDetected = true;
            expectedBlock = block;
        }
    }
    if (!blockDetected) throw std::runtime_error("Return. Wrong declaration.");

    if (!expectedBlock.hasReturn) throw std::runtime_error("Return. This block returns nothing.");
    
    for (auto& var : expectedBlock.vars) {
        if (expr.actualTokenSeq[1].litteral == var.litteral) {
            varDetected = true;
            if (var.dataType != expectedBlock.returnType) throw std::runtime_error("Return. Type mismatch.");
        }
    }
    if (!varDetected) throw std::runtime_error("Return. return value not found.");
}

void Semantics::analysis (const std::vector<std::shared_ptr<Expression>>& exprs) {
    std::vector<std::shared_ptr<Expression>> mathExprs, returnExprs, importExprs, packageExprs, ifExprs, whileExprs, funcDeclareExprs, varDefinitionExprs, varDeclarationExprs, funcCallExprs;

    // classification
    for (const auto& expr : exprs) {
        switch (expr->type)
        {
        case 1: mathExprs.push_back(expr); break;
        case 2: returnExprs.push_back(expr); break; // IN PROCESS
        case 3: importExprs.push_back(expr); break;
        case 4: packageExprs.push_back(expr); break;
        case 5: ifExprs.push_back(expr); break; // ...
        case 6: whileExprs.push_back(expr); break; // ...
        case 7: funcDeclareExprs.push_back(expr); break; // OK
        case 8: varDefinitionExprs.push_back(expr); break; // ...
        case 9: varDeclarationExprs.push_back(expr); break; // OK
        case 10: funcCallExprs.push_back(expr); break; // ...
        default: break;
        }
    }

    for (auto& expr : funcDeclareExprs) {
        blocks.push_back({*expr});
        blocks.back().multipleDeclarationCheck();
    }

    for (auto& varDecl : varDeclarationExprs) addVarByExpr(*varDecl);
    for (auto& callReturn : returnExprs) callReturnCheck(*callReturn);
}

/* Operators */

std::ostream& operator << (std::ostream& os, Semantics& semantics) {
    if (semantics.blocks.size() > 0) for (auto& block : semantics.blocks) os << block << "\n";    
    return os;
}

/* void semCheckVarDeclaration (std::vector<std::shared_ptr<Expression>> varDeclarationExprs, std::vector<std::pair<std::shared_ptr<Expression>, std::vector<Token>>>& blocksByVars) {
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
} */

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

