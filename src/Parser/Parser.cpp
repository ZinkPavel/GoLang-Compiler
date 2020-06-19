#include "Parser.h"

#include <string>
#include <exception>

Parser::Parser () {}

const std::vector<std::shared_ptr<Expression>>& Parser::getExprs () const {
    return exprs;
}

void Parser::update (const std::vector<Token>& tokenListFromLexer) {
    if (tokenListFromLexer.size() == numOfReadTokens) return; // found insignificant sign

    const Token& newToken = tokenListFromLexer.back();

    if (newToken.row != currentRow) {
        { // exclusivly for testing
            Expression& buffer = *exprs.back();
            if (!buffer.completeExpr) {
                buffer.endingStatus.panicMode = true;
                buffer.endingStatus.waitingNewExpr = true;
            }
        }
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

        // if (isCommentExpr(newToken)) exprs.push_back(std::make_shared<CommentExpr>());
        if (isImportExpr(newToken)) exprs.push_back(std::make_shared<ImportExpr>());
        else if (isPackageExpr(newToken)) exprs.push_back(std::make_shared<PackageExpr>());
        // else if (isFuncDeclareExpr(newToken)) exprs.push_back(std::make_shared<FuncDeclareExpr>());
        // else if (isReturnExpr(newToken)) exprs.push_back(std::make_shared<ReturnExpr>());
        else if (isReturnExpr(newToken)) exprs.push_back(std::make_shared<ReturnExpr>());
        // else if (isMathExpr(newToken)) exprs.push_back(std::make_shared<MathExpr>()); // make for newToken
        // else if (isMathExpr(undefinedTokenList)) exprs.push_back(std::make_shared<MathExpr>());
        else status.waitingNewExpr = true;
    }

    // Add tokens in new expression

    if (!status.waitingNewExpr) {
        Expression& lastExpr = *exprs.back();
        lastExpr.actualTokenSeq.push_back(newToken);

        status = lastExpr.checkExpr();
        lastExpr.endingStatus = status; // exclusevly for testing
    }

    numOfReadTokens++;
}