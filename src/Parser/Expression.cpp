#include <algorithm>
#include <sstream>
#include <iterator>

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

    // if (*expectedTokenTypes.begin() != "BODY" && expectedTokenTypes.find(actualTokenType) == expectedTokenTypes.end()) {
    if (expectedTokenTypes.find(actualTokenType) == expectedTokenTypes.end()) {
        // if (*expectedSeq[indexInExpSeq - 1].begin() != "BODY") {
            return {true, true};
        // }
    } else {
        indexInExpSeq++;
    }
    
    // finished token
    // if (actualTokenSeq.size() == expectedTokenTypes.size()) {
        if (checkByRegexMask()) {
            newStatus.waitingNewExpr = true;
            completeExpr = true;
        }
    // }
    /* if (actualTokenSeq.size() >= minAmountTokens && lastSignificantTokenType.find(actualTokenType) != lastSignificantTokenType.end() &&  checkByRegexMask()) {
        newStatus.waitingNewExpr = true;
        // completeExpr = true;
    } */

    return newStatus;
}

bool Expression::checkByRegexMask () {
    std::stringstream actualSeq;

    for (auto it = actualTokenSeq.begin(); it != actualTokenSeq.end() - 1; ++it) {
        actualSeq << it->type << ' ';
    }
    actualSeq << actualTokenSeq.back().type;

    // std::cout << actualSeq.str() << std::endl;
    return std::regex_match(actualSeq.str(), regexMask);
}

// Exprs
MathExpr::MathExpr () {
    expectedSeq = {
        // possibleSings,
        numericVars,
        arithmeticSings,
        numericVars,
    };

    regexMask = "(EXCLAMATION)?\\s?"
        "(identifier|numeric_const|bin_const|octal_const|hex_const)"
        "\\s?(PLUS|MINUS|PROC|STAR|SLASH|LESS|MORE|AND|OR)\\s?"
        "(EXCLAMATION)?\\s?"
        "(identifier|numeric_const|bin_const|octal_const|hex_const)";
}

ReturnExpr::ReturnExpr () {
    expectedSeq = {
        {"return"},
        numericVars,
        {"SEMI"},
    };

    regexMask = "return"
        "\\s?(identifier|numeric_const|bin_const|octal_const|hex_const)\\s?"
        "SEMI";
}

/* FuncDeclareExpr::FuncDeclareExpr () {
    expectedSeq = {
        {"func"},
        {"identifier"},
        {"L_PAREN"},
        {"BODY"},
        {"R_PAREN"},
        dataTypes,
    };

    minAmountTokens = 4;
    lastSignificantTokenType = {"R_PAREN"};
    regexMask = "func identifier ?L_PAREN ?R_PAREN ?(int|float|double|string|bool)?";
} */

/* ImportExpr::ImportExpr () {
    expectedSeq = {
        {"import"},
        {"string_litteral"},
    };

    lastSignificantTokenType = {expectedSeq.back()};
    regexMask = "import string_litteral";
} */

/* PackageExpr::PackageExpr () {
    expectedSeq = {
        {"package"},
        {"identifier"},
    };

    lastSignificantTokenType = {expectedSeq.back()};
    regexMask = "package identifier";
} */

/* CommentExpr::CommentExpr () {
    expectedSeq = {
        {"comment"}
    };
} */

// Checks

bool isMathExpr (const Token& newToken) {
    return possibleSings.find(newToken.type) != possibleSings.end() || numericVars.find(newToken.type) != numericVars.end();
}

bool isReturnExpr (const Token& newToken) {
    return newToken.type == "return";
}

/* bool isFuncDeclareExpr (const Token& newToken) {
    return newToken.type == "func"; 
} */

/* bool isImportExpr (const Token& newToken) { 
    return newToken.type == "import"; 
} */

/* bool isPackageExpr (const Token& newToken) { 
    return  newToken.type == "package"; 
} */

/* bool isCommentExpr (const Token& newToken) {
    return newToken.type == "comment";
} */