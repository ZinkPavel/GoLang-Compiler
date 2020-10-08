#pragma once

#define TEST_INIT(filePath) \
    Compiler comp(filePath, true, true); \
    const std::vector<std::shared_ptr<Expression>>& exprs = comp.getParserExprs()

#define ASSERT_VAR(lhs, rhs) \
    ASSERT_EQUAL(lhs.row, rhs.row) \
    ASSERT_EQUAL(lhs.col, rhs.col) \
    ASSERT_EQUAL(lhs.litteral, rhs.litteral) \
    ASSERT_EQUAL(lhs.dataType, rhs.dataType) \
    ASSERT_EQUAL(lhs.value, rhs.value)
    
void TestsSemantics ();

void VarConstructorByExpressionTest ();
void BlockConstructorTest ();