#include "TestsParser.h"
#include "TestsLexer.h"
#include "TestsSemantics.h"

#include "TestController.h"

void AllTests () {
    TestsLexer();
    TestsParser();
    TestsSemantics();
}