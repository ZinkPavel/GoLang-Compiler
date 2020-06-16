#include "Expression.h"
// #include "Parser.h"

Expression::Expression () {}

Status Expression::checkExpr () {
    Status newStatus(false, actualTokenSeq.size() == expectedSeq.size());

    for (size_t i = 0; i < actualTokenSeq.size(); i++) {
        const std::set<std::string>& expectedTokenTypes = expectedSeq[i];
        const std::string& actualTokenType = actualTokenSeq[i].type;

        if (expectedTokenTypes.find(actualTokenType) == expectedTokenTypes.end()) {
            newStatus.panicMode = true;
            newStatus.waitingNewExpr = true;
            return newStatus;
        } 
    }
    
    if (newStatus.waitingNewExpr) completeExpr = true;
    
    return newStatus;
}

// Exprs

/* MathExpr::MathExpr () {
    expectedSeq = {
        numericVars,
        arithmeticSings,
        numericVars,
    };
} */

ReturnExpr::ReturnExpr () {
    expectedSeq = {
        {"return"},
        numericVars,
        {"SEMI"},
    };
}

FuncDeclareExpr::FuncDeclareExpr () {
    expectedSeq = {
        {"func"},
        {"identifier"},
        {"L_PAREN"},
        {"identifier"},
        dataTypes,
        {"R_PAREN"},
        dataTypes,
    };
    
    multipleReference = {false, false, false, true, false, false, true};
}

ImportExpr::ImportExpr () {
    expectedSeq = {
        {"import"},
        {"string_litteral"},
    };
}

PackageExpr::PackageExpr () {
    expectedSeq = {
        {"package"},
        {"identifier"},
    };
}

CommentExpr::CommentExpr () {
    expectedSeq = {
        {"comment"}
    };
}

// Checks

/* bool isMathExpr (const std::vector<Token>& undefinedTokenList) {
    size_t newStatus = 0;

    for (const auto& token : undefinedTokenList) {
        if (numericVars.find(token.type) != numericVars.end()) newStatus++;
        if (arithmeticSings.find(token.type) != arithmeticSings.end()) newStatus++;
    }
    
    return newStatus == undefinedTokenList.size(); // all elements belong to math expr
} */

bool isReturnExpr (const Token& newToken) {
    return newToken.type == "return";
}

bool isFuncDeclareExpr (const Token& newToken) {
    return newToken.type == "func"; 
}

bool isImportExpr (const Token& newToken) { 
    return newToken.type == "import"; 
}

bool isPackageExpr (const Token& newToken) { 
    return  newToken.type == "package"; 
}

bool isCommentExpr (const Token& newToken) {
    return newToken.type == "comment";
}