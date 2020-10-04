#include "TestsLexer.h"
#include "TestController.h"

void TestsLexer () {
    TestRunner tr;
    RUN_TEST(tr, DoubleSignTest);
    RUN_TEST(tr, IdentifierTest);
    RUN_TEST(tr, DecimalTest);
    RUN_TEST(tr, BinaryTest);
    RUN_TEST(tr, OctalTest);
    RUN_TEST(tr, HexademicalTest);
    RUN_TEST(tr, DQuotesTest);
}

void DoubleSignTest() {
    Compiler comp ("tests/lexer/double_sign.txt", false, true);
    std::vector<Token>& tokenList = comp.getTokenList();

    ASSERT_EQUAL(tokenList[1], Token("OR", "||"));
    ASSERT_EQUAL(tokenList[4], Token("AND", "&&"));
    ASSERT_EQUAL(tokenList[7], Token("AND", "&&"));
    ASSERT_EQUAL(tokenList[8], Token("AND", "&&"));
    ASSERT_EQUAL(tokenList[10], Token("OR", "||"));
    ASSERT_EQUAL(tokenList[13], Token("OR", "||"));
}

void IdentifierTest () {
    Compiler comp ("tests/lexer/identifier.txt", false, true);
    std::vector<Token>& tokenList = comp.getTokenList();

    ASSERT_EQUAL(tokenList[3], Token("identifier", "test_text_0"));
    ASSERT_EQUAL(tokenList[5], Token("identifier", "test_text_1"));
    ASSERT_EQUAL(tokenList[7], Token("identifier", "test_text_3"));
    ASSERT_EQUAL(tokenList[9], Token("identifier", "test_text_5"));
}

void DecimalTest () {
    Compiler comp ("tests/lexer/digit.txt", false, true);
    std::vector<Token>& tokenList = comp.getTokenList();

    ASSERT_EQUAL(tokenList[0], Token("numeric_const", "12345"));
    ASSERT_EQUAL(tokenList[1], Token("numeric_const", "22"));
    ASSERT_EQUAL(tokenList[3], Token("numeric_const", "98"));
    ASSERT_EQUAL(tokenList[6], Token("numeric_const", "31"));
}

void BinaryTest () {
    Compiler comp ("tests/lexer/digit.txt", false, true);
    std::vector<Token>& tokenList = comp.getTokenList();

    ASSERT_EQUAL(tokenList[7], Token("bin_const", "0b0101"));
    ASSERT_EQUAL(tokenList[10], Token("undefined", "0b00120"));
}

void OctalTest () {
    Compiler comp ("tests/lexer/digit.txt", false, true);
    std::vector<Token>& tokenList = comp.getTokenList();

    ASSERT_EQUAL(tokenList[8], Token("undefined", "0o7787"));
    ASSERT_EQUAL(tokenList[11], Token("octal_const", "0o563"))
}

void HexademicalTest () {
    Compiler comp ("tests/lexer/digit.txt", false, true);
    std::vector<Token>& tokenList = comp.getTokenList();

    ASSERT_EQUAL(tokenList[9], Token("hex_const", "0xFFFF"));
    ASSERT_EQUAL(tokenList[12], Token("undefined", "0xFFKF"));
}

void DQuotesTest () {
    Compiler comp ("tests/lexer/dquotes.txt", false, true);
    std::vector<Token>& tokenList = comp.getTokenList();
    
    ASSERT_EQUAL(tokenList[0], Token("string_litteral", "\"test_text_0\""));
    ASSERT_EQUAL(tokenList[2], Token("undefined", "\"test_text_1"));
}