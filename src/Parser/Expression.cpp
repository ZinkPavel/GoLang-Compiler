#include "Expression.h"
#include "Parser.h"

Status::Status () {}

Status::Status (bool first, bool second) {
    panicMode = first;
    waitingNewExpr = second;
}

Expression::Expression () {}

Status Expression::checkExpr () {
    Status newStatus(false, false);

    const std::set<std::string>& expectedTokenTypes = expectedSeq[indexInExpSeq];
    const std::string& actualTokenType = actualTokenSeq.back().type;

    if (*expectedTokenTypes.begin() != "BODY" && expectedTokenTypes.find(actualTokenType) == expectedTokenTypes.end()) {
        if (*expectedSeq[indexInExpSeq - 1].begin() != "BODY") {
            newStatus.panicMode = true;
            newStatus.waitingNewExpr = true;
            return newStatus;        
        }
    } else {
        indexInExpSeq++;
    }
    
    if (expectedSeq.back().find(actualTokenType) != expectedSeq.back().end() &&  checkByRegexMask()) {
        newStatus.waitingNewExpr = true;
        completeExpr = true;
    }

    return newStatus;
}

bool Expression::checkByRegexMask () {
    std::string str = "";
    bool first = true;
    for (size_t i = 0; i < actualTokenSeq.size(); i++) {
        if (!first) str += ' ';
        else first = false;
        str += actualTokenSeq[i].type;
    }

    // std::cout << str << std::endl;
    return std::regex_match(str, regexMask);
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
        {"BODY"},
        {"SEMI"},
    };

    regexMask = "return (identifier|numeric_const|bin_const|octal_const|hex_const) *?SEMI";
}

FuncDeclareExpr::FuncDeclareExpr () {
    expectedSeq = {
        {"func"},
        {"identifier"},
        {"L_PAREN"},
        {"BODY"},
        {"R_PAREN"},
        dataTypes,
    };

    regexMask = "func main ?[\x28] ?(identifier( ?, ?identifier)*? (int|float|double|string|bool))? ?[\x29] ?(int|float|double|string|bool)?";
}

ImportExpr::ImportExpr () {
    expectedSeq = {
        {"import"},
        {"string_litteral"},
    };

    regexMask = "import string_litteral";
}

PackageExpr::PackageExpr () {
    expectedSeq = {
        {"package"},
        {"identifier"},
    };

    regexMask = "package identifier";
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