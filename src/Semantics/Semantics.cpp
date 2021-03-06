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
    
    if (expr.actualTokenSeq[1].type == "identifier") {
        for (auto& var : expectedBlock.vars) {
            if (expr.actualTokenSeq[1].litteral == var.litteral) {
                varDetected = true;
                if (var.dataType != expectedBlock.returnType) throw std::runtime_error("Return. Type mismatch.[1]");
            }
        }
        if (!varDetected) throw std::runtime_error("Return. Return value not found.");
    } else if (expr.actualTokenSeq[1].dataType != expectedBlock.returnType) throw std::runtime_error("Return. Type mismatch.[2]");
}

void Semantics::varDefinitionCheck (Expression& expr) {
    bool blockDetected = false;
    size_t placeDefinition = expr.actualTokenSeq[0].row;
    Block expectedBlock;
    
    for (auto& block : blocks) {
        if (block.start < placeDefinition && block.end > placeDefinition) {
            blockDetected = true;
            expectedBlock = block;
        }
    }
    if (!blockDetected) throw std::runtime_error("Var definition. Var not found.");

    auto it = std::find_if(expectedBlock.vars.begin(), expectedBlock.vars.end(), [expr] (const Var& var) {
        return var.litteral == expr.actualTokenSeq[0].litteral;
    });
    if (it == expectedBlock.vars.end()) throw std::runtime_error("Var definition. Var not exist.");

    for (auto ptr = expr.actualTokenSeq.begin() + 1; ptr != expr.actualTokenSeq.end(); ptr++) {
        if (ptr->litteral == "identifier") {
            if (std::find_if(expectedBlock.vars.begin(), expectedBlock.vars.end(), [ptr] (const Var& var) {
                return var.litteral == ptr->litteral && var.dataType == ptr->dataType;
            }) == expectedBlock.vars.end()) throw std::runtime_error("Var definition. Type mismatch");
        }
    }
}

void Semantics::callFunctionCheck (Expression& expr) {
    size_t placeCall = expr.actualTokenSeq[0].row, numArgs = -1;;
    std::vector<Var> args;
    Block expectedBlock, callableBlock;
    
    for (auto& block : blocks) {
        if (block.start < placeCall && block.end > placeCall) expectedBlock = block;
        if (block.name == expr.actualTokenSeq[0].litteral) callableBlock = block;
    }

    std::regex regex("(identifier|numeric_const|string_litteral|true|false)");
    for (auto& token : expr.actualTokenSeq) if (std::regex_search(token.type, regex)) numArgs++;
    if (callableBlock.numArgs != numArgs) throw std::runtime_error("Call function. Wrong num arguments.");

    for (size_t i = 1; i <= numArgs; i++) {
        auto it = std::find_if(expectedBlock.vars.begin(), expectedBlock.vars.end(), [i, expr](Var& var) -> bool {
            return expr.actualTokenSeq[i * 2].litteral == var.litteral;
        });
        if (it == expectedBlock.vars.end()) throw std::runtime_error("Call function. Arg not found.");
        args.push_back(*it);
    }

    for (auto& arg : args) {
        if (arg.dataType != callableBlock.argsType) throw std::runtime_error("Call function. Type mismatch.");
    }
}

void Semantics::ifCheck (Expression& expr) {
    bool blockDetected = false;
    size_t placeIf = expr.actualTokenSeq[0].row, ifStart = expr.actualTokenSeq[0].row, ifEnd = expr.actualTokenSeq[0].row;
    size_t expectedNumArgs = 0;
    std::vector<Var> args;
    Block expectedBlock;

    for (auto& block : blocks) {
        if (block.start < placeIf && block.end > placeIf) {
            expectedBlock = block;
            blockDetected = true;
        }
    }
    if (!blockDetected) throw std::runtime_error("If declaration. Wrong declaration place.");

    for (auto& token : expr.actualTokenSeq) {
        if (std::regex_search(token.type, std::regex("(identifier|numeric_const|string_litteral|int|false|true)"))) {
            expectedNumArgs++;
            if (token.type == "identifier") {
                auto it = std::find_if(expectedBlock.vars.begin(), expectedBlock.vars.end(), [token, ifStart, ifEnd] (Var& var) -> bool {
                    return (var.row < ifStart || var.row > ifEnd) && var.litteral == token.litteral;
                });
                if (it != expectedBlock.vars.end()) args.push_back(*it);
            } else args.push_back({token});           
        }
    }
    if (expectedNumArgs != args.size()) throw std::runtime_error("If declare. Some variables could not be found.");

    if (!std::all_of(args.begin(), args.end(), [args] (Var& arg) -> bool {
        return arg.dataType == args[0].dataType;
    })) throw std::runtime_error("If declaration. Args type mismatch");
}

void Semantics::whileCheck (Expression& expr) {
    bool blockDetected = false;
    size_t placeWhile = expr.actualTokenSeq[0].row, whileStart = expr.actualTokenSeq[0].row, whileEnd = expr.actualTokenSeq[0].row;
    size_t expectedNumArgs = 0;
    std::vector<Var> args;
    Block expectedBlock;

    for (auto& block : blocks) {
        if (block.start < placeWhile && block.end > placeWhile) {
            expectedBlock = block;
            blockDetected = true;
        }
    }
    if (!blockDetected) throw std::runtime_error("While declaration. Wrong declaration place.");

    for (auto& token : expr.actualTokenSeq) {
        if (std::regex_search(token.type, std::regex("(identifier|numeric_const|string_litteral|int|false|true)"))) {
            expectedNumArgs++;
            if (token.type == "identifier") {
                auto it = std::find_if(expectedBlock.vars.begin(), expectedBlock.vars.end(), [token, whileStart, whileEnd] (Var& var) -> bool {
                    return (var.row < whileStart || var.row > whileEnd) && var.litteral == token.litteral;
                });
                if (it != expectedBlock.vars.end()) args.push_back(*it);
            } else args.push_back({token});           
        }
    }
    if (expectedNumArgs != args.size()) throw std::runtime_error("While declaration. Some variables could not be found.");

    if (!std::all_of(args.begin(), args.end(), [args] (Var& arg) -> bool {
        return arg.dataType == args[0].dataType;
    })) throw std::runtime_error("While declaration. Args type mismatch");
}

void Semantics::analysis (const std::vector<std::shared_ptr<Expression>>& exprs) {
    std::vector<std::shared_ptr<Expression>> mathExprs, returnExprs, importExprs, packageExprs, ifExprs, whileExprs, funcDeclareExprs, varDefinitionExprs, varDeclarationExprs, funcCallExprs;

    // classification
    for (const auto& expr : exprs) {
        switch (expr->type)
        {
        case 1: mathExprs.push_back(expr); break;
        case 2: returnExprs.push_back(expr); break;
        case 3: importExprs.push_back(expr); break;
        case 4: packageExprs.push_back(expr); break;
        case 5: ifExprs.push_back(expr); break;
        case 6: whileExprs.push_back(expr); break;
        case 7: funcDeclareExprs.push_back(expr); break;
        case 8: varDefinitionExprs.push_back(expr); break;
        case 9: varDeclarationExprs.push_back(expr); break;
        case 10: funcCallExprs.push_back(expr); break;
        default: break;
        }
    }

    for (auto& expr : funcDeclareExprs) {
        blocks.push_back({*expr});
        blocks.back().multipleDeclarationCheck();
    }

    for (auto& varDecl : varDeclarationExprs) addVarByExpr(*varDecl);
    for (auto& callReturn : returnExprs) callReturnCheck(*callReturn);
    for (auto& varDef : varDefinitionExprs) varDefinitionCheck(*varDef);
    for (auto& callFunc : funcCallExprs) callFunctionCheck(*callFunc);
    for (auto& ifDecl : ifExprs) ifCheck(*ifDecl);
    for (auto& whileDecl : whileExprs) whileCheck(*whileDecl);
}

/* Operators */

std::ostream& operator << (std::ostream& os, Semantics& semantics) {
    if (semantics.blocks.size() > 0) for (auto& block : semantics.blocks) os << block << "\n";    
    return os;
}