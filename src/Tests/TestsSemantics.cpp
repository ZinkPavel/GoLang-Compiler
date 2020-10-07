#include "TestsSemantics.h"

#include "TestController.h"

void TestsSemantics () {
    TestRunner tr;
    RUN_TEST(tr, VarContructorTest);
}

void VarContructorTest () {
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
