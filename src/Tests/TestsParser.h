#pragma once

#define INIT_TEST_ENVAIRONMENT(filePath) \
    Compiler comp(filePath); \
    const std::vector<std::shared_ptr<Expression>>& exprs = comp.getParserExprs(); \
    Expression expr; \
    Status status

#define ASSERT_STATUS(index, fBool, sBool) \
    expr = *exprs[index]; \
    status = expr.endingStatus; \
    ASSERT_EQUAL(status.panicMode, fBool); \
    ASSERT_EQUAL(status.waitingNewExpr, sBool)

void TestsParser ();

void MathExprTest ();
void ReturnExprTest ();
void ImportExprTest ();
void PackageExprTest ();
void IfExprTest ();
void WhileLoopExprTest ();
void FuncDeclareExprTest ();
void AssignExprTest ();

void ProgramTest();
