#include "Parser.h"

#include <string>
#include <exception>

Parser::Parser () {}

void Parser::update (const std::vector<Token>& tokenListFromLexer) {
    if (tokenListFromLexer.size() == numOfReadTokens) return; // found insignificant sign

    const Token& newToken = tokenListFromLexer.back();

    if (currentRow != newToken.row) {
        Expression& lastExpr = *exprs.back();

        if (!lastExpr.completeExpr && !lastExpr.hasBraceSeq) {
            lastExpr.endingStatus = {true, true}; // exception
            // lastExpr.endingStatus = status; // ?
        }

        currentRow = newToken.row;
        status.panicMode = false;
        status.waitingNewExpr = true;
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

        if (isMathExpr(newToken)) exprs.push_back(std::make_shared<MathExpr>());
        else if (isReturnExpr(newToken)) exprs.push_back(std::make_shared<ReturnExpr>());
        else if (isImportExpr(newToken)) exprs.push_back(std::make_shared<ImportExpr>());
        else if (isPackageExpr(newToken)) exprs.push_back(std::make_shared<PackageExpr>());
        else if (isIfExpr(newToken)) exprs.push_back(std::make_shared<IfExpr>());
        else if (isWhileLoopExpr(newToken)) exprs.push_back(std::make_shared<WhileLoopExpr>());
        else if (isFuncDeclareExpr(newToken)) exprs.push_back(std::make_shared<FuncDeclareExpr>());
        else status.waitingNewExpr = true;

        // if tokenamount > 1 && match --- > 
    }

    // Add tokens in new expression

    if (!status.waitingNewExpr) {
        Expression& lastExpr = *exprs.back();

        lastExpr.actualTokenSeq.push_back(newToken);
        status = lastExpr.checkExpr();

        if (lastExpr.hasBraceSeq && !status.panicMode && status.waitingNewExpr) {
            braceStack.push(exprs.back());
        }
        lastExpr.endingStatus = status; // exclusevly for tests
    }

    numOfReadTokens++;
}

const std::vector<std::shared_ptr<Expression>>& Parser::getExprs () const {
    return exprs;
}

const Status& Parser::getComplitionStatus () const {
    return status;
}