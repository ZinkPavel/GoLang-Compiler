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
        /* read while str != end && actualTokenSeq++ .. ++  */
        return {true, false};
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
        vars,
        arithmeticSings,
        vars,
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
        vars,
    };

    regexMask = "return"
        "\\s?(identifier|numeric_const|bin_const|octal_const|hex_const)\\s?";
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
        vars,
        arithmeticSings,
        vars,
        {"L_BRACE"}
    };

    regexMask = "if"
        "\\s?(identifier|numeric_const|bin_const|octal_const|hex_const)"
        "\\s?(PLUS|MINUS|PROC|STAR|SLASH|LESS|MORE|AND|OR)"
        "\\s?(identifier|numeric_const|bin_const|octal_const|hex_const)"
        "\\s?L_BRACE";

    hasBraceSeq = true;
}

WhileLoopExpr::WhileLoopExpr () {
    expectedSeq = {
        {"while"},
        vars,
        arithmeticSings,
        vars,
        {"L_BRACE"}
    };

    regexMask = "while"
        "\\s?(identifier|numeric_const|bin_const|octal_const|hex_const)"
        "\\s?(PLUS|MINUS|PROC|STAR|SLASH|LESS|MORE|AND|OR)"
        "\\s?(identifier|numeric_const|bin_const|octal_const|hex_const)"
        "\\s?L_BRACE";

    hasBraceSeq = true;
}

FuncDeclareExpr::FuncDeclareExpr () {
    expectedSeq = {
        {"func"},
        {"identifier"},
        {"L_PAREN"},
        {"R_PAREN"},
        {"L_BRACE"}
    };

    regexMask = "func\\s"
        "identifier\\s?"
        "L_PAREN\\s?"
        "(identifier\\s(int|float|double|string|bool))?\\s?"
        "R_PAREN\\s?"
        "(int|float|double|string|bool)?\\s?"
        "L_BRACE";

    hasBraceSeq = true;
}

AssignExpr::AssignExpr () {
    expectedSeq = {
        {"identifier"},
        assignSings,
        vars,
        arithmeticSings,
        vars,
    };

    regexMask = {
        "identifier\\s?"
        "EQUAL\\s?"
        "(identifier|numeric_const|bin_const|octal_const|hex_const)\\s?"
        "(NOT_EQUAL|DOUBLE_EQUAL|OR|AND|PLUS|MINUS|STAR|SLASH|PROC|LESS|MORE)\\s?"
        "(identifier|numeric_const|bin_const|octal_const|hex_const)\\s?"
    };
}

bool Expression::exprIdentification (const std::vector<Token>& undefineTokenSeq) {
    size_t counter = 0;
    
    for (const auto& it = expectedSeq.begin(); it != expectedSeq.end(); next(it)) {
        if ((*it).find(undefineTokenSeq[counter].type) != (*it).end()) counter++;
    }

    return counter == undefineTokenSeq.size();
}

// Checks

bool isMathExpr (std::vector<Token>& undefineTokenSeq) {    
    if (undefineTokenSeq.size() == 1) {
        return possibleSings.find(undefineTokenSeq.back().type) != possibleSings.end() || vars.find(undefineTokenSeq.back().type) != vars.end();
    }
    return false;
}

bool isReturnExpr (std::vector<Token>& undefineTokenSeq) {
    if (undefineTokenSeq.size() == 1) {
        return undefineTokenSeq.back().type == "return";
    }
    return false;
}

bool isImportExpr (std::vector<Token>& undefineTokenSeq) { 
    if (undefineTokenSeq.size() == 1) {
        return undefineTokenSeq.back().type == "import"; 
    }
    return false;
}

bool isPackageExpr (std::vector<Token>& undefineTokenSeq) { 
    if (undefineTokenSeq.size() == 1) {
        return  undefineTokenSeq.back().type == "package";
    }
    return false;
}

bool isIfExpr (std::vector<Token>& undefineTokenSeq) {
    if (undefineTokenSeq.size() == 1) {
        return undefineTokenSeq.back().type == "if";
    }
    return false;
}

bool isWhileLoopExpr (std::vector<Token>& undefineTokenSeq) {
    if (undefineTokenSeq.size() == 1) {
        return undefineTokenSeq.back().type == "while";
    }
    return false;
}

bool isFuncDeclareExpr (std::vector<Token>& undefineTokenSeq) {
    if (undefineTokenSeq.size() == 1) {
        return undefineTokenSeq.back().type == "func"; 
    }
    return false;
}

bool isAssignExpr (std::vector<Token>& undefineTokenSeq) {
    if (undefineTokenSeq.size() == 1) {
        return undefineTokenSeq.back().type == "identifier";
    }
    return false;
}