#pragma once

#define TEST_INIT(filePath) \
    Compiler comp(filePath, true, true); \
    const std::vector<std::shared_ptr<Expression>>& exprs = comp.getParserExprs()

void TestsSemantics ();

void VarContructorTest ();