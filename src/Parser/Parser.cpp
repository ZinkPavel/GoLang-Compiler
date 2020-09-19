#include "Parser.h"

#include <string>
#include <exception>

Parser::Parser () {}

void Parser::update (const std::vector<Token>& tokenListFromLexer) {
    if (tokenListFromLexer.size() == numOfReadTokens) return; // found insignificant sign

    /* if (exprs.size() > 0) {
        Expression& lastExpr = *exprs.back();
        if (lastExpr.completeExpr) {
            lastExpr.endingStatus = status;
        }
    } */
    // if ((*exprs.back().completeExpr) {}

    const Token& newToken = tokenListFromLexer.back();

    if (currentRow != newToken.row) {
        { // exclusivly for tests
            Expression& lastExpr = *exprs.back();
            if (!lastExpr.completeExpr) {
                lastExpr.endingStatus = {true, true};
            }
        }
        std::cout << "NEW LINE" << std::endl;
        currentRow = newToken.row;
        status.panicMode = false;
        status.waitingNewExpr = true;
    }

    if (status.panicMode) {
        numOfReadTokens++;
        return;
    }

    // Add new expression

    if (status.waitingNewExpr) {
        status.waitingNewExpr = false;

        if (isMathExpr(newToken)) exprs.push_back(std::make_shared<MathExpr>());
        else if (isReturnExpr(newToken)) exprs.push_back(std::make_shared<ReturnExpr>());
        else if (isImportExpr(newToken)) exprs.push_back(std::make_shared<ImportExpr>());
        // if (isCommentExpr(newToken)) exprs.push_back(std::make_shared<CommentExpr>());
        // else if (isPackageExpr(newToken)) exprs.push_back(std::make_shared<PackageExpr>());
        // else if (isFuncDeclareExpr(newToken)) exprs.push_back(std::make_shared<FuncDeclareExpr>());
        // else if (isMathExpr(newToken)) exprs.push_back(std::make_shared<MathExpr>()); // make for newToken
        // else if (isMathExpr(undefinedTokenList)) exprs.push_back(std::make_shared<MathExpr>());
        else status.waitingNewExpr = true;

        // if tokenamount > 1 && match --- > 
    }

    // Add tokens in new expression

    if (!status.waitingNewExpr) {
        Expression& lastExpr = *exprs.back();
        lastExpr.actualTokenSeq.push_back(newToken);

        status = lastExpr.checkExpr();
        // std::cout << status.panicMode << " " << status.waitingNewExpr << std::endl;
        lastExpr.endingStatus = status; // exclusevly for tests
    } /* else if (status.waitingNewExpr && exprs.size() > 0) { // waitingNewExpr and push_back ? what ? 
        Expression& lastExpr = *exprs.back();
        lastExpr.actualTokenSeq.push_back(newToken);

        if (!lastExpr.completeExpr && !lastExpr.checkByRegexMask()) {
            lastExpr.actualTokenSeq.pop_back();
            lastExpr.completeExpr = true;
        }
    } */

    numOfReadTokens++;
}

const std::vector<std::shared_ptr<Expression>>& Parser::getExprs () const {
    return exprs;
}

const Status& Parser::getComplitionStatus () const {
    return status;
}