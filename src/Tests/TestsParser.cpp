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
    RUN_TEST(tr, FuncDeclareExprTest);
    // RUN_TEST(tr, AssignExprTest);
}

void MathExprTest () {
    INIT_TEST_ENVAIRONMENT("tests/parser/MathExprs.txt");

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
    INIT_TEST_ENVAIRONMENT("tests/parser/ReturnExprs.txt");

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
    INIT_TEST_ENVAIRONMENT("tests/parser/ImportExprs.txt");

    ASSERT_EQUAL(exprs.size(), 3u);

    ASSERT_STATUS(0, false, true);
    ASSERT_STATUS(1, true, true);
    ASSERT_STATUS(2, false, true);
}

void PackageExprTest () {
    INIT_TEST_ENVAIRONMENT("tests/parser/PackageExprs.txt");

    ASSERT_EQUAL(exprs.size(), 3u);

    ASSERT_STATUS(0, false, true);
    ASSERT_STATUS(1, true, true);
    ASSERT_STATUS(2, false, true);
}

void IfExprTest () {
    INIT_TEST_ENVAIRONMENT("tests/parser/IfExprs.txt");

    ASSERT_EQUAL(exprs.size(), 3u);

    ASSERT_STATUS(0, false, true);
    ASSERT_EQUAL(expr.completeExpr, true);
    ASSERT_STATUS(1, false, true);
    ASSERT_EQUAL(expr.completeExpr, true);
    ASSERT_STATUS(2, false, true);
    ASSERT_EQUAL(expr.completeExpr, true);
}

void WhileLoopExprTest () {
    INIT_TEST_ENVAIRONMENT("tests/parser/WhileLoopExprs.txt");

    ASSERT_EQUAL(exprs.size(), 4u);

    ASSERT_STATUS(0, false, true);
    ASSERT_EQUAL(expr.completeExpr, true);
    ASSERT_STATUS(1, false, true);
    ASSERT_EQUAL(expr.completeExpr, true);
    ASSERT_STATUS(2, false, true);
    ASSERT_EQUAL(expr.completeExpr, true);
    ASSERT_STATUS(3, false, true);
    ASSERT_EQUAL(expr.completeExpr, true);
}

void FuncDeclareExprTest () {
    INIT_TEST_ENVAIRONMENT("tests/parser/FuncDeclareExprs.txt");

    ASSERT_EQUAL(exprs.size(), 3u);

    ASSERT_STATUS(0, false, true);
    ASSERT_STATUS(1, false, true);
    ASSERT_STATUS(2, false, true);
}

void AssignExprTest () {
    INIT_TEST_ENVAIRONMENT("tests/parser/AssignExprs.txt");

    ASSERT_EQUAL(exprs.size(), 1u);

    ASSERT_STATUS(0, false, true);
}