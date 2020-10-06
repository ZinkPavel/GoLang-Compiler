#include "Semantics.h"

/* std::shared_ptr<Expression> classification (Expression& expr) {
    std::shared_ptr<Expression> newExpression;

    

    return newExpression;
} */

void semanticsAnalysis (const std::vector<std::shared_ptr<Expression>>& exprs) {
    std::vector<std::shared_ptr<Expression>> mathExprs, returnExprs, ifExprs, whileExprs, funcDeclareExprs, definitionExprs, varDeclareExprs, funcCallExprs;

    for (auto& expr : exprs) {
        if (isMathExpr((*expr).actualTokenSeq)) { mathExprs.push_back(std::make_shared<MathExpr>()); }
        else if (isReturnExpr((*expr).actualTokenSeq)) { returnExprs.push_back(std::make_shared<ReturnExpr>()); }
        else if (isIfExpr((*expr).actualTokenSeq)) { ifExprs.push_back(std::make_shared<IfExpr>()); }
        else if (isWhileLoopExpr((*expr).actualTokenSeq)) { whileExprs.push_back(std::make_shared<WhileLoopExpr>()); }
        else if (isVarDefinitionExpr((*expr).actualTokenSeq)) { varDeclareExprs.push_back(std::make_shared<VarDeclarationExpr>()); }
        else if (isAssignExpr((*expr).actualTokenSeq)) { definitionExprs.push_back(std::make_shared<VarDefinitionExpr>()); }
        else if (isFuncDeclareExpr((*expr).actualTokenSeq)) { funcDeclareExprs.push_back(std::make_shared<FuncDeclarationExpr>()); }
        else if (isFuncCallExpr((*expr).actualTokenSeq)) { funcCallExprs.push_back(std::make_shared<FuncCallExpr>()); }
    }

}
