#include "Compiler.h"

/* Constructors && Destructors */

Compiler::Compiler (std::string filePath) {
    input.open(filePath);
    if (input) readFile();
    else throw std::runtime_error("Opening file failed: \"" + filePath + "\" not available");
}

Compiler::~Compiler () {
    input.close();
}

/* Compiler */

void Compiler::readFile () {
    char ch;
    std::string str, foundSequence;
    std::string::iterator begin;

    size_t currentRow = 0, currentCol = 0;

    if (input) {
        while (getline(input, str)) {
            currentRow++;
            for (auto it = str.begin(); it != str.end(); it++) {
                currentCol = it - str.begin();
                ch = *it;
                begin = it;

                if (isLetter(ch)) {
                    SEARCH_WHILE((++it != str.end()) && (isLetter(*it) || isdigit(*it)), foundSequence);
                    auto isKeyword = find(keywords.begin(), keywords.end(), foundSequence);
                    NEW_TOKEN(isKeyword != keywords.end() ? std::string{*isKeyword} : "identifier", foundSequence);

                } else if (isdigit(ch)) {
                    SEARCH_WHILE((++it != str.end()) && (isdigit(*(it)) || isLetter(*it)), foundSequence);
                    if (isDec(foundSequence)) NEW_TOKEN("numeric_const", foundSequence);
                    else if (isBinary(foundSequence)) NEW_TOKEN("bin_const", foundSequence);
                    else if (isOctal(foundSequence)) NEW_TOKEN("octal_const", foundSequence);
                    else if (isHex(foundSequence)) NEW_TOKEN("hex_const", foundSequence);
                    else NEW_TOKEN("undefined", foundSequence);
                    
                } else {
                    switch (ch)
                    {
                    case CH::SLASH:
                        if (*(it + 1) == CH::SLASH) {
                            foundSequence = {begin, ++it + 1};
                            NEW_TOKEN("comment", foundSequence);
                            it = str.end() - 1;
                        }
                        else NEW_CH_TOKEN(PIPE, ch);
                        break;
                    
                    case CH::L_BRACE: NEW_CH_TOKEN(L_BRACE, ch);                  
                    case CH::R_BRACE: NEW_CH_TOKEN(R_BRACE, ch);                  

                    case CH::L_SQ_BRACE: NEW_CH_TOKEN(L_SQ_BRACE, ch);
                    case CH::R_SQ_BRACE: NEW_CH_TOKEN(R_SQ_BRACE, ch);

                    case CH::L_PAREN: NEW_CH_TOKEN(L_PAREN, ch);
                    case CH::R_PAREN: NEW_CH_TOKEN(R_PAREN, ch);

                    case CH::QUOTES: NEW_CH_TOKEN(QUOTES, ch);
                    case CH::DQUOTES:
                        while (++it != str.end() && !isDQuotes(*(it)));
                        if (it != str.end()) {
                            foundSequence = {begin, it + 1};
                            NEW_TOKEN("string_litteral", foundSequence);
                        } else {
                            foundSequence = {begin, it--};
                            NEW_TOKEN("undefined", foundSequence);
                        }
                        break;

                    case CH::AMPERSAND: 
                        if (*(it + 1) == CH::AMPERSAND) {
                            foundSequence = {begin, ++it + 1};
                            NEW_TOKEN("AND", foundSequence);
                        }
                        else NEW_CH_TOKEN(AMPERSAND, ch);
                        break;

                    case CH::PIPE:
                        if (*(it + 1) == CH::PIPE) {
                            foundSequence = {begin, ++it + 1};
                            NEW_TOKEN("OR", foundSequence);
                        }
                        else NEW_CH_TOKEN(PIPE, ch);
                        break;
                        
                    case CH::EQUAL: 
                        if (*(it + 1) == CH::EQUAL) {
                            foundSequence = {begin, ++it + 1};
                            NEW_TOKEN("DOUBLE_EQUAL", foundSequence);
                        } 
                        else NEW_CH_TOKEN(EQUAL, ch)
                        break;

                    case CH::EXCLAMATION: 
                        if (*(it + 1) == CH::EQUAL) {
                            foundSequence = {begin, ++it + 1};
                            NEW_TOKEN("NOT_EQUAL", foundSequence);
                        } 
                        else NEW_CH_TOKEN(EXCLAMATION, ch)
                        break;

                    case CH::COLON: 
                        if (*(it + 1) == CH::EQUAL) {
                            foundSequence = {begin, ++it + 1};
                            NEW_TOKEN("ASSIGN", foundSequence);
                        } 
                        else NEW_CH_TOKEN(COLON, ch)
                        break;;

                    case CH::PROC: NEW_CH_TOKEN(PROC, ch);
                    case CH::STAR: NEW_CH_TOKEN(STAR, ch);
                    case CH::LESS: NEW_CH_TOKEN(LESS, ch);
                    case CH::MORE: NEW_CH_TOKEN(MORE, ch);
                    case CH::PLUS: NEW_CH_TOKEN(PLUS, ch);
                    case CH::MINUS: NEW_CH_TOKEN(MINUS, ch);

                    case CH::SEMI: NEW_CH_TOKEN(SEMI, ch);
                    case CH::COMMA: NEW_CH_TOKEN(COMMA, ch);
                    case CH::DOLLAR: NEW_CH_TOKEN(DOLLAR, ch);
                    case CH::DOT: NEW_CH_TOKEN(DOT, ch);
                    case CH::BACKSLASH: NEW_CH_TOKEN(BACKSLASH, ch);
                    
                    case CH::SPACE: break;
                    case '\n': break;
                    case '\t': break;

                    default: NEW_CH_TOKEN(undefined, ch);
                    }
                }
                foundSequence.clear();
                parser.update(tokenList);
            }
        }
    }
    tree.build(getParserExprs());
}

void Compiler::dumpTokens () {
    std::ofstream out ("dump-token.txt");
    
    std::stringstream ss;
    for (const auto& token : tokenList) ss << token << '\n';
    out << ss.str();

    out.close();
}

void Compiler::dumpAst () {
    std::ofstream out ("dump-ast.txt");

    std::stringstream ss;
    printASTree(ss, tree.root);
    out << ss.str();

    out.close();
}

void Compiler::dumpSymbolTable () {
    std::ofstream out ("dump-symbol-table.txt");

    std::stringstream ss;
    printSymbolTable(ss, tree.root);
    out << ss.str();

    out.close();
}

std::vector<Token>& Compiler::getTokenList () {
    return tokenList;
}

const std::vector<std::shared_ptr<Expression>>& Compiler::getParserExprs () const {
    return parser.getExprs();
}

const Status& Compiler::getParserComplitionStatus() const {
    return parser.getComplitionStatus();
}

/* Checks */

inline bool isDQuotes (const char& ch) {
    return ch == CH::DQUOTES;
}

inline bool isLetter (const char& ch) { 
    return (ch > 64 && ch < 91) || (ch > 96 && ch < 123) || ch == 95; 
}

inline bool isBinary (const std::string& str) {
    return std::regex_match(str, std::regex{"0b[0-1]+"});
}

inline bool isOctal (const std::string& str) {
    return std::regex_match(str, std::regex{"0o[0-7]+"});
}

inline bool isDec (const std::string& str) {
    return std::regex_match(str, std::regex{"[0-9]+"});
}

inline bool isHex (const std::string& str) {
    return std::regex_match(str, std::regex{"0x([A-F]|[0-9])+"});
}
