#include "TestRunner.h"

void Assert (bool b, const string& hint) {
    AssertEqual(b, true, hint);
}