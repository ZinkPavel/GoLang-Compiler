#include "TestsParser.h"

#include "TestController.h"

void TestsParser () {
    TestRunner tr;
    // RUN_TEST(tr, PanicModeTest);
    // RUN_TEST(tr, ExprWithNegativeSignTest);
    // RUN_TEST(tr, DoubleSignExprTest);
    // RUN_TEST(tr, BasicExprTest);
    RUN_TEST(tr, ReturnExprTest);
    RUN_TEST(tr, FuncDeclareTest);
    RUN_TEST(tr, ImportExprTest);
    RUN_TEST(tr, PackageExprTest);
    RUN_TEST(tr, CommentExprTest);
}

/* void PanicModeTest () {
    
} */

/* void ExprWithNegativeSignTest () {
    INIT_TEST_ENVAIRONMENT("tests/parser/math_exprs/ExprsWithNegativeSign.txt");

    { ASSERT_STATUS(0, false, true); }
} */

/* void DoubleSignExprTest () {
    INIT_TEST_ENVAIRONMENT("tests/parser/math_exprs/DoubleSignExprs.txt");

    { ASSERT_EQUAL(exprs.size(), 2u); }

    // test '&&' exprs
    {
        { ASSERT_STATUS(0, false, true); }
    }

    // test '||' exprs
    {
        { ASSERT_STATUS(1, false, true); }
    }
} */

/* void BasicExprTest () {
    INIT_TEST_ENVAIRONMENT("tests/parser/math_exprs/BasicExprs.txt");

    { ASSERT_EQUAL(exprs.size(), 28u); }

    // test exprs format 'identifier' -sign- 'identifier'
    {
        { ASSERT_STATUS(0, false, true); }
        { ASSERT_STATUS(1, false, true); }
        { ASSERT_STATUS(2, false, true); }
        { ASSERT_STATUS(3, false, true); }
        { ASSERT_STATUS(4, false, true); }
        { ASSERT_STATUS(5, false, true); }
        { ASSERT_STATUS(6, false, true); }
    }

    // test exprs format 'num' -sign- 'num'
    {
        { ASSERT_STATUS(7, false, true); }
        { ASSERT_STATUS(8, false, true); }
        { ASSERT_STATUS(9, false, true); }
        { ASSERT_STATUS(10, false, true); }
        { ASSERT_STATUS(11, false, true); }
        { ASSERT_STATUS(12, false, true); }
        { ASSERT_STATUS(13, false, true); }
    }

    // test exprs format 'identifier' -sign- 'num'
    {
        { ASSERT_STATUS(14, false, true); }
        { ASSERT_STATUS(15, false, true); }
        { ASSERT_STATUS(16, false, true); }
        { ASSERT_STATUS(17, false, true); }
        { ASSERT_STATUS(18, false, true); }
        { ASSERT_STATUS(19, false, true); }
        { ASSERT_STATUS(20, false, true); }
    }

    // test exprs format 'num' -sign- 'identifier'
    {
        { ASSERT_STATUS(21, false, true); }
        { ASSERT_STATUS(22, false, true); }
        { ASSERT_STATUS(23, false, true); }
        { ASSERT_STATUS(24, false, true); }
        { ASSERT_STATUS(25, false, true); }
        { ASSERT_STATUS(26, false, true); }
        { ASSERT_STATUS(27, false, true); }
    }
} */

void ReturnExprTest () {
    INIT_TEST_ENVAIRONMENT("tests/parser/ReturnExprs.txt");

    ASSERT_EQUAL(exprs.size(), 5u);
    
    ASSERT_STATUS(0, false, true);
    ASSERT_STATUS(1, true, true);
    ASSERT_STATUS(2, true, true);
    ASSERT_STATUS(3, true, true);
    ASSERT_STATUS(4, false, true);

    ASSERT_EQUAL((*exprs[0]).actualTokenSeq[0].type, "return");
    ASSERT_EQUAL((*exprs[0]).actualTokenSeq[1].type, "identifier");
    ASSERT_EQUAL((*exprs[0]).actualTokenSeq[2].type, "SEMI");

    ASSERT_EQUAL((*exprs[1]).actualTokenSeq[0].type, "return");
    ASSERT_EQUAL((*exprs[1]).actualTokenSeq[1].type, "identifier");

    ASSERT_EQUAL((*exprs[2]).actualTokenSeq[0].type, "return");
    ASSERT_EQUAL((*exprs[2]).actualTokenSeq[1].type, "numeric_const");

    ASSERT_EQUAL((*exprs[3]).actualTokenSeq[0].type, "return");
    ASSERT_EQUAL((*exprs[3]).actualTokenSeq[1].type, "undefined");

    ASSERT_EQUAL((*exprs[4]).actualTokenSeq[0].type, "return");
    ASSERT_EQUAL((*exprs[4]).actualTokenSeq[1].type, "numeric_const");
    ASSERT_EQUAL((*exprs[4]).actualTokenSeq[2].type, "SEMI");
}

void FuncDeclareTest () {
    INIT_TEST_ENVAIRONMENT("tests/parser/FuncDeclareExprs.txt");

    ASSERT_EQUAL(exprs.size(), 7u);

    ASSERT_STATUS(0, false, true);
    ASSERT_STATUS(1, true, true);
    ASSERT_STATUS(2, true, true);
    ASSERT_STATUS(3, true, true);
    ASSERT_STATUS(4, true, true);
    ASSERT_STATUS(5, true, true);
    // ASSERT_STATUS(6, false, true);

    ASSERT_EQUAL((*exprs[0]).actualTokenSeq[0].type, "func");
    ASSERT_EQUAL((*exprs[0]).actualTokenSeq[1].type, "identifier");
    ASSERT_EQUAL((*exprs[0]).actualTokenSeq[2].type, "L_PAREN");
    ASSERT_EQUAL((*exprs[0]).actualTokenSeq[3].type, "identifier");
    ASSERT_EQUAL((*exprs[0]).actualTokenSeq[4].type, "int");
    ASSERT_EQUAL((*exprs[0]).actualTokenSeq[5].type, "R_PAREN");
    ASSERT_EQUAL((*exprs[0]).actualTokenSeq[6].type, "bool");

    ASSERT_EQUAL((*exprs[1]).actualTokenSeq[0].type, "func");
    ASSERT_EQUAL((*exprs[1]).actualTokenSeq[1].type, "identifier");
    ASSERT_EQUAL((*exprs[1]).actualTokenSeq[2].type, "L_PAREN");
    ASSERT_EQUAL((*exprs[1]).actualTokenSeq[3].type, "identifier");
    ASSERT_EQUAL((*exprs[1]).actualTokenSeq[4].type, "string_litteral");

    ASSERT_EQUAL((*exprs[2]).actualTokenSeq[0].type, "func");
    ASSERT_EQUAL((*exprs[2]).actualTokenSeq[1].type, "numeric_const");

    ASSERT_EQUAL((*exprs[3]).actualTokenSeq[0].type, "func");
    ASSERT_EQUAL((*exprs[3]).actualTokenSeq[1].type, "comment");

    ASSERT_EQUAL((*exprs[4]).actualTokenSeq[0].type, "func");
    ASSERT_EQUAL((*exprs[4]).actualTokenSeq[1].type, "string_litteral");

    ASSERT_EQUAL((*exprs[5]).actualTokenSeq[0].type, "func");
    ASSERT_EQUAL((*exprs[5]).actualTokenSeq[1].type, "undefined");

    ASSERT_EQUAL((*exprs[6]).actualTokenSeq[0].type, "func");
    ASSERT_EQUAL((*exprs[6]).actualTokenSeq[1].type, "identifier");
    ASSERT_EQUAL((*exprs[6]).actualTokenSeq[2].type, "L_PAREN");
    ASSERT_EQUAL((*exprs[6]).actualTokenSeq[3].type, "R_PAREN");
}

void ImportExprTest () {
    INIT_TEST_ENVAIRONMENT("tests/parser/ImportExprs.txt");

    ASSERT_EQUAL(exprs.size(), 3u);

    ASSERT_STATUS(0, false, true);
    ASSERT_STATUS(1, true, true);
    ASSERT_STATUS(2, false, true);

    ASSERT_EQUAL((*exprs[0]).actualTokenSeq[0].type, "import");
    ASSERT_EQUAL((*exprs[0]).actualTokenSeq[1].type, "string_litteral");

    ASSERT_EQUAL((*exprs[1]).actualTokenSeq[0].type, "import");
    ASSERT_EQUAL((*exprs[1]).actualTokenSeq[1].type, "undefined");

    ASSERT_EQUAL((*exprs[2]).actualTokenSeq[0].type, "import");
    ASSERT_EQUAL((*exprs[2]).actualTokenSeq[1].type, "string_litteral");
}

void PackageExprTest () {
    INIT_TEST_ENVAIRONMENT("tests/parser/PackageExprs.txt");

    ASSERT_EQUAL(exprs.size(), 3u);

    ASSERT_STATUS(0, false, true);
    ASSERT_STATUS(1, true, true);
    ASSERT_STATUS(2, false, true);

    ASSERT_EQUAL((*exprs[0]).actualTokenSeq[0].type, "package");
    ASSERT_EQUAL((*exprs[0]).actualTokenSeq[1].type, "identifier");

    ASSERT_EQUAL((*exprs[1]).actualTokenSeq[0].type, "package");
    ASSERT_EQUAL((*exprs[1]).actualTokenSeq[1].type, "string_litteral");
    
    ASSERT_EQUAL((*exprs[2]).actualTokenSeq[0].type, "package");
    ASSERT_EQUAL((*exprs[2]).actualTokenSeq[1].type, "identifier");
}

void CommentExprTest () {
    INIT_TEST_ENVAIRONMENT("tests/parser/CommentExprs.txt");

    ASSERT_EQUAL(exprs.size(), 3u);

    ASSERT_STATUS(0, false, true);
    ASSERT_STATUS(1, false, true);
    ASSERT_STATUS(2, false, true);

    ASSERT_EQUAL((*exprs[0]).actualTokenSeq[0].type, "comment");

    ASSERT_EQUAL((*exprs[1]).actualTokenSeq[0].type, "return");
    ASSERT_EQUAL((*exprs[1]).actualTokenSeq[1].type, "numeric_const");
    ASSERT_EQUAL((*exprs[1]).actualTokenSeq[2].type, "SEMI");

    ASSERT_EQUAL((*exprs[2]).actualTokenSeq[0].type, "comment");
}