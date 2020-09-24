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

std::string testFunc (const Token& token) {
    return token.type;
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

/* Operators */

std::ostream& operator << (std::ostream& os, Expression& expr) {
    os << Join(expr.actualTokenSeq, '\n');
    return os;
}

/* Exprs */

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
        "(identifier\\s?(COMMA\\s?identifier)?\\s"
        "(L_SQ_BRACE\\s?R_SQ_BRACE)?\\s?(int|float|double|string|bool))?\\s?"
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
        "ASSIGN\\s?"
        "(identifier|numeric_const|bin_const|octal_const|hex_const)\\s?"
        "(NOT_EQUAL|DOUBLE_EQUAL|OR|AND|PLUS|MINUS|STAR|SLASH|PROC|LESS|MORE)\\s?"
        "(identifier|numeric_const|bin_const|octal_const|hex_const)\\s?"
    };
}

bool Expression::exprIdentification (const std::vector<Token>& undefineTokenSeq) {
    size_t counter;

    for (counter = 0; counter < undefineTokenSeq.size(); counter++) {
        if (expectedSeq[counter].find(undefineTokenSeq[counter].type) == expectedSeq[counter].end()) break;
    }  

    return counter == undefineTokenSeq.size();
}

/* Checks */

bool isMathExpr (std::vector<Token>& undefineTokenSeq) {        
    MathExpr instance;
    return instance.exprIdentification(undefineTokenSeq);
}

bool isReturnExpr (std::vector<Token>& undefineTokenSeq) {
    ReturnExpr instance;
    return instance.exprIdentification(undefineTokenSeq);
}

bool isImportExpr (std::vector<Token>& undefineTokenSeq) { 
    ImportExpr instance;
    return instance.exprIdentification(undefineTokenSeq);
}

bool isPackageExpr (std::vector<Token>& undefineTokenSeq) { 
    PackageExpr instance;
    return instance.exprIdentification(undefineTokenSeq);
}

bool isIfExpr (std::vector<Token>& undefineTokenSeq) {
    IfExpr instance;
    return instance.exprIdentification(undefineTokenSeq);
}

bool isWhileLoopExpr (std::vector<Token>& undefineTokenSeq) {
    WhileLoopExpr instance;
    return instance.exprIdentification(undefineTokenSeq);
}

bool isFuncDeclareExpr (std::vector<Token>& undefineTokenSeq) {
    FuncDeclareExpr instance;
    return instance.exprIdentification(undefineTokenSeq);
}

bool isAssignExpr (std::vector<Token>& undefineTokenSeq) {
    AssignExpr instance;
    return instance.exprIdentification(undefineTokenSeq);
}