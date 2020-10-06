#include "TestsParser.h"

#include "TestController.h"

void TestsParser () {
    TestRunner tr;
    RUN_TEST(tr, MathExprTest);
    RUN_TEST(tr, ReturnExprTest);
    RUN_TEST(tr, ImportExprTest);
    RUN_TEST(tr, PackageExprTest);
    RUN_TEST(tr, IfExprTest);
    RUN_TEST(tr, WhileLoopExprTest);
    RUN_TEST(tr, FuncDeclarationExprTest);
    RUN_TEST(tr, VarDefinitionExprTest);
    RUN_TEST(tr, VarDeclarationTest);
    RUN_TEST(tr, FuncCallTest);

    RUN_TEST(tr, ProgramTest);

    RUN_TEST(tr, SerializeTokenTest);
}

void MathExprTest () {
    INIT_TEST_ENVAIRONMENT("tests/parser/MathExprs.txt", true, true);

    status = comp.getParserComplitionStatus();
    expr = *exprs.back();

    {        
        ASSERT_EQUAL(exprs.size(), 15u);
        ASSERT_EQUAL(expr.checkByRegexMask(), true);
        ASSERT_EQUAL(status.panicMode, false);
        ASSERT_EQUAL(status.waitingNewExpr, true);
    }
}

void ReturnExprTest () {
    INIT_TEST_ENVAIRONMENT("tests/parser/ReturnExprs.txt", true, true);

    {
        status = comp.getParserComplitionStatus();
        expr = *exprs.back();

        ASSERT_EQUAL(exprs.size(), 3u);
        ASSERT_EQUAL(expr.checkByRegexMask(), true);
        ASSERT_EQUAL(status.panicMode, false);
        ASSERT_EQUAL(status.waitingNewExpr, true);
    }
    
    {
        ASSERT_STATUS(0, false, true);
        ASSERT_STATUS(1, true, true);
        ASSERT_STATUS(2, false, true);
    }
}

void ImportExprTest () {
    INIT_TEST_ENVAIRONMENT("tests/parser/ImportExprs.txt", true, true);

    ASSERT_EQUAL(exprs.size(), 3u);

    ASSERT_STATUS(0, false, true);
    ASSERT_STATUS(1, true, true);
    ASSERT_STATUS(2, false, true);
}

void PackageExprTest () {
    INIT_TEST_ENVAIRONMENT("tests/parser/PackageExprs.txt", true, true);

    ASSERT_EQUAL(exprs.size(), 3u);

    ASSERT_STATUS(0, false, true);
    ASSERT_STATUS(1, true, true);
    ASSERT_STATUS(2, false, true);
}

void IfExprTest () {
    INIT_TEST_ENVAIRONMENT("tests/parser/IfExprs.txt", true, true);

    ASSERT_EQUAL(exprs.size(), 3u);

    ASSERT_STATUS(0, false, true);
    ASSERT_EQUAL(expr.completeExpr, true);
    ASSERT_STATUS(1, false, true);
    ASSERT_EQUAL(expr.completeExpr, true);
    ASSERT_STATUS(2, false, true);
    ASSERT_EQUAL(expr.completeExpr, true);

    for (const auto& expr : exprs) {
        ASSERT_EQUAL((*expr).completeExpr, true);
    }
}

void WhileLoopExprTest () {
    INIT_TEST_ENVAIRONMENT("tests/parser/WhileLoopExprs.txt", true, true);

    ASSERT_EQUAL(exprs.size(), 4u);

    ASSERT_STATUS(0, false, true);
    ASSERT_EQUAL(expr.completeExpr, true);
    ASSERT_STATUS(1, false, true);
    ASSERT_EQUAL(expr.completeExpr, true);
    ASSERT_STATUS(2, false, true);
    ASSERT_EQUAL(expr.completeExpr, true);
    ASSERT_STATUS(3, false, true);
    ASSERT_EQUAL(expr.completeExpr, true);

    for (const auto& expr : exprs) {
        ASSERT_EQUAL((*expr).completeExpr, true);
    }
}

void FuncDeclarationExprTest () {
    INIT_TEST_ENVAIRONMENT("tests/parser/FuncDeclarationExprs.txt", true, true);

    ASSERT_EQUAL(exprs.size(), 5u);

    ASSERT_STATUS(0, false, true);
    ASSERT_STATUS(1, false, true);
    ASSERT_STATUS(2, false, true);
    ASSERT_STATUS(3, false, true);
    ASSERT_STATUS(4, false, true);

    for (const auto& expr : exprs) {
        ASSERT_EQUAL((*expr).completeExpr, true);
    }
}

void VarDefinitionExprTest () {
    INIT_TEST_ENVAIRONMENT("tests/parser/VarDefinitionExprs.txt", true, true);

    ASSERT_EQUAL(exprs.size(), 1u);

    ASSERT_STATUS(0, false, true);
}

void VarDeclarationTest () {
    INIT_TEST_ENVAIRONMENT("tests/parser/VarDeclarationExprs.txt", true, true);

    ASSERT_EQUAL(exprs.size(), 4u);

    ASSERT_STATUS(0, false, true);
    ASSERT_STATUS(1, false, true);
    ASSERT_STATUS(2, false, true);
    ASSERT_STATUS(3, false, true);

    for (const auto& expr : comp.getParserExprs()) {
        ASSERT_EQUAL((*expr).completeExpr, true);
    }
}

void FuncCallTest () {
    INIT_TEST_ENVAIRONMENT("tests/parser/FuncCallExprs.txt", true, true);

    ASSERT_EQUAL(exprs.size(), 4u);

    ASSERT_STATUS(0, false, true);
    ASSERT_STATUS(1, false, true);
    ASSERT_STATUS(2, false, true);
    ASSERT_STATUS(3, false, true);

    for (const auto& expr : comp.getParserExprs()) {
        ASSERT_EQUAL((*expr).completeExpr, true);
    }
}

void ProgramTest () {
    INIT_TEST_ENVAIRONMENT("tests/prog.go", true, true);

    ASSERT_EQUAL(exprs.size(), 9u);

    for (size_t i = 0; i < exprs.size(); i++) {
        ASSERT_STATUS(i, false, true);
    }

    for (const auto& expr : exprs) {
        ASSERT_EQUAL((*expr).completeExpr, true);
    }
}

void SerializeTokenTest () {
    Compiler comp("tests/prog.go");
    const std::vector<std::shared_ptr<Expression>>& exprs = comp.getParserExprs();

    std::stringstream tokenSeqStream;
    std::vector<std::string> tokenSeqs;

    for (size_t i = 0; i < exprs.size(); i++) {
        Expression& expr = *exprs[0];

        for (auto it = expr.actualTokenSeq.begin(); it != expr.actualTokenSeq.end(); ++it) {
            if (it == expr.actualTokenSeq.begin()) tokenSeqStream << it->type;
            else tokenSeqStream << ' ' << it->type;
        }

        tokenSeqs.push_back(tokenSeqStream.str());
        tokenSeqStream.clear();
    }

    ASSERT_EQUAL(exprs.size(), 9u);

    ASSERT_EQUAL(tokenSeqs[0], "package identifier");
}