#include "Parser.h"

Parser::Parser () {}

void Parser::update (const std::vector<Token>& tokenListFromLexer, bool isTestPass) {
    if (tokenListFromLexer.size() == numOfReadTokens) return; // found insignificant sign

    const Token& newToken = tokenListFromLexer.back();
    undefineTokenSeq.push_back(tokenListFromLexer.back());

    if (currentRow != newToken.row) {
        Expression& lastExpr = *exprs.back();

        if (!lastExpr.completeExpr && !lastExpr.hasBraceSeq) {
            lastExpr.endingStatus = {true, true};
        }

        currentRow = newToken.row;
        status.panicMode = false;
        status.waitingNewExpr = true;
        undefineTokenSeq.clear();
        undefineTokenSeq.push_back(tokenListFromLexer.back());
    }

    undefineTokenSeq.back().nestingLevel = braceStack.size();

    if (braceStack.size() > 0 && newToken.type == "R_BRACE") {
        Expression& topStackExpr = *braceStack.top();
        topStackExpr.actualTokenSeq.push_back(newToken);
        topStackExpr.actualTokenSeq.back().nestingLevel = braceStack.size() - 1;
        topStackExpr.completeExpr = true;
        braceStack.pop();
    }

    undefineTokenSeq.back().col += undefineTokenSeq.back().nestingLevel * 4;

    // Add new expression

    if (status.waitingNewExpr) {
        status.waitingNewExpr = false;

        size_t counterEntry = 0;
        std::shared_ptr<Expression> newExpression;
        size_t type;

        if (isMathExpr(undefineTokenSeq)) { EXPR_HIT(MathExpr); }
        if (isReturnExpr(undefineTokenSeq)) { EXPR_HIT(ReturnExpr); }
        if (isImportExpr(undefineTokenSeq)) { EXPR_HIT(ImportExpr); }
        if (isPackageExpr(undefineTokenSeq)) { EXPR_HIT(PackageExpr); }
        if (isIfExpr(undefineTokenSeq)) { EXPR_HIT(IfExpr); }
        if (isWhileLoopExpr(undefineTokenSeq)) { EXPR_HIT(WhileLoopExpr); }
        if (isFuncDeclareExpr(undefineTokenSeq)) { EXPR_HIT(FuncDeclarationExpr); }
        if (isVarDefinitionExpr(undefineTokenSeq)) { EXPR_HIT(VarDefinitionExpr); }
        if (isVarDeclarationExpr(undefineTokenSeq)) { EXPR_HIT(VarDeclarationExpr); } 
        if (isFuncCallExpr(undefineTokenSeq)) { EXPR_HIT(FuncCallExpr); }
        if (isPrintExpr(undefineTokenSeq)) { EXPR_HIT(PrintExpr); }
        if (isScanExpr(undefineTokenSeq)) { EXPR_HIT(ScanExpr); } 

        if (counterEntry == 1) {
            newExpression->type = type;
            exprs.push_back(newExpression);
        }
        else status.waitingNewExpr = true;
    }

    // Add tokens in new expression

    if (!status.waitingNewExpr) {
        Expression& lastExpr = *exprs.back();
        
        for (size_t i = 0; i < undefineTokenSeq.size(); i++) {
            lastExpr.actualTokenSeq.push_back(undefineTokenSeq[i]);
            status = lastExpr.checkExpr();

            // expression ?

            if (lastExpr.hasBraceSeq && !status.panicMode && status.waitingNewExpr) {
                braceStack.push(exprs.back());
            }
            lastExpr.endingStatus = status; // exclusevly for tests
        }
        undefineTokenSeq.clear();
    }

    numOfReadTokens++;
}

const std::vector<std::shared_ptr<Expression>>& Parser::getExprs () const {
    return exprs;
}

const Status& Parser::getComplitionStatus () const {
    return status;
}

const std::stack<std::shared_ptr<Expression>>& Parser::getBraceStack () const {
    return braceStack;
}
