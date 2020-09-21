#include "Parser.h"

#include <string>
#include <exception>

Parser::Parser () {}

void Parser::update (const std::vector<Token>& tokenListFromLexer) {
    if (tokenListFromLexer.size() == numOfReadTokens) return; // found insignificant sign

    const Token& newToken = tokenListFromLexer.back();
    undefineTokenSeq.push_back(tokenListFromLexer.back());

    if (currentRow != newToken.row) {
        Expression& lastExpr = *exprs.back();

        if (!lastExpr.completeExpr && !lastExpr.hasBraceSeq) {
            lastExpr.endingStatus = {true, true}; // exception
            // lastExpr.endingStatus = status; // ?
        }

        currentRow = newToken.row;
        status.panicMode = false;
        status.waitingNewExpr = true;
        undefineTokenSeq.clear();
        undefineTokenSeq.push_back(tokenListFromLexer.back());
    }

    if (braceStack.size() > 0 && newToken.type == "R_BRACE") {
        Expression& topStackExpr = *braceStack.top();
        topStackExpr.actualTokenSeq.push_back(newToken);
        topStackExpr.completeExpr = true;
        braceStack.pop();
    }

    // Add new expression

    if (status.waitingNewExpr) {
        status.waitingNewExpr = false;

        size_t counterEntry = 0;
        std::shared_ptr<Expression> newExpression;

        if (isMathExpr(undefineTokenSeq)) { EXPR_HIT(MathExpr); }
        if (isReturnExpr(undefineTokenSeq)) { EXPR_HIT(ReturnExpr); }
        if (isImportExpr(undefineTokenSeq)) { EXPR_HIT(ImportExpr); }
        if (isPackageExpr(undefineTokenSeq)) { EXPR_HIT(PackageExpr); }
        if (isIfExpr(undefineTokenSeq)) { EXPR_HIT(IfExpr); }
        if (isWhileLoopExpr(undefineTokenSeq)) { EXPR_HIT(WhileLoopExpr); }
        if (isFuncDeclareExpr(undefineTokenSeq)) { EXPR_HIT(FuncDeclareExpr); }
        if (isAssignExpr(undefineTokenSeq)) { EXPR_HIT(AssignExpr); }

        // std::cout << "Counter entry = " << counterEntry << std::endl;

        if (counterEntry == 1) exprs.push_back(newExpression);
        else status.waitingNewExpr = true;
    }

    // Add tokens in new expression

    if (!status.waitingNewExpr) {
        Expression& lastExpr = *exprs.back();
        
        for (size_t i = 0; i < undefineTokenSeq.size(); i++) {
            lastExpr.actualTokenSeq.push_back(undefineTokenSeq[i]);
            status = lastExpr.checkExpr();

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