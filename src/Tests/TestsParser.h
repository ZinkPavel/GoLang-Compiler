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

// void PanicModeTest ();
// void ExprWithNegativeSignTest ();
// void DoubleSignExprTest ();
// void BasicExprTest ();
void ReturnExprTest ();
void FuncDeclareTest ();
void ImportExprTest ();
void PackageExprTest ();
void CommentExprTest ();

void TestsParser ();