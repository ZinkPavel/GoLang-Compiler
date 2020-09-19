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

    if (expectedTokenTypes.find(actualTokenType) == expectedTokenTypes.end()) {
        return {true, true};
    } else {
        indexInExpSeq++;
    }
    
    // finished token
    if (checkByRegexMask()) {
        newStatus.waitingNewExpr = true;
        if (!hasBraceSeq) {
            completeExpr = true;
        }
    }

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

IfExpr::IfExpr () {
    expectedSeq = {
        {"if"},
        numericVars,
        arithmeticSings,
        numericVars,
        {"L_BRACE"}
    };

    regexMask = "if"
        "\\s?(identifier|numeric_const|bin_const|octal_const|hex_const)"
        "\\s?(PLUS|MINUS|PROC|STAR|SLASH|LESS|MORE|AND|OR)"
        "\\s?(identifier|numeric_const|bin_const|octal_const|hex_const)"
        "\\s?L_BRACE";

    hasBraceSeq = true;
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

// Checks

bool isMathExpr (const Token& newToken) {
    return possibleSings.find(newToken.type) != possibleSings.end() || numericVars.find(newToken.type) != numericVars.end();
}

bool isReturnExpr (const Token& newToken) {
    return newToken.type == "return";
}

bool isImportExpr (const Token& newToken) { 
    return newToken.type == "import"; 
}

bool isPackageExpr (const Token& newToken) { 
    return  newToken.type == "package"; 
}

bool isIfExpr (const Token& newToken) {
    return newToken.type == "if";
}

/* bool isFuncDeclareExpr (const Token& newToken) {
    return newToken.type == "func"; 
} */