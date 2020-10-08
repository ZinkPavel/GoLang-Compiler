#include "TestsSemantics.h"

void TestsSemantics () {
    TestRunner tr;
    RUN_TEST(tr, VarConstructorByExpressionTest);
    RUN_TEST(tr, BlockConstructorTest);
}

void VarConstructorByExpressionTest () {
    TEST_INIT("tests/semantics/VarConstructor.txt");
    std::stringstream ss;
    std::vector<Var> vars;

    for (auto& expr : exprs) vars.push_back(*expr);

    ASSERT_EQUAL(vars.size(), 3u);

    ss.str(std::string());
    ss << vars[0];
    ASSERT_EQUAL(ss.str(), "<1:5> x int = 3");

    ss.str(std::string());
    ss << vars[1];
    ASSERT_EQUAL(ss.str(), "<2:5> y string = \"text\"");

    ss.str(std::string());
    ss << vars[2];
    ASSERT_EQUAL(ss.str(), "<3:5> z bool = false");
}

void BlockConstructorTest () {
    TEST_INIT("tests/semantics/BlockConstructor.txt");
    std::vector<Block> blocks;

    for (auto& expr : exprs) blocks.push_back(*expr);

    ASSERT_EQUAL(blocks.size(), 4u);

    for (auto& block : blocks) ASSERT_EQUAL(block.name, "main");

    ASSERT_EQUAL(blocks[0].hasArgs, true);
    ASSERT_EQUAL(blocks[0].hasReturn, true);
    ASSERT_EQUAL(blocks[0].returnType, "int");
    ASSERT_VAR(blocks[0].vars[0], Var(1u, 14u, "b", "int", ""));
    ASSERT_VAR(blocks[0].vars[1], Var(1u, 12u, "a", "int", ""));
    
    ASSERT_EQUAL(blocks[1].hasArgs, true);
    ASSERT_EQUAL(blocks[1].hasReturn, true);
    ASSERT_EQUAL(blocks[1].returnType, "string");
    ASSERT_VAR(blocks[1].vars[0], Var(2u, 12u, "a", "string", ""));
    
    ASSERT_EQUAL(blocks[2].hasArgs, false);
    ASSERT_EQUAL(blocks[2].hasReturn, true);
    ASSERT_EQUAL(blocks[2].returnType, "bool");

    ASSERT_EQUAL(blocks[3].hasArgs, false);
    ASSERT_EQUAL(blocks[3].hasReturn, false);
    ASSERT_EQUAL(blocks[3].returnType, "");
}