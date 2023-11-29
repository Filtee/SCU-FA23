#ifndef TEST_TESTREVERSEPOLISH_H
#define TEST_TESTREVERSEPOLISH_H

#include "formula/ReversePolish.h"
#include "doctest/doctest.h"
#include "ADT/Queue.h"

/*
 * 逆波兰式的转换单元测试
 */
TEST_CASE("Test ReversePolish.h") {
    SUBCASE("Test1") {
        string a = "-1 + (6 + 2) * 3";

        string actual = ReversePolish::convertToString(a);
        string expect = "n-1n6n2o+n3o*o+";

        CHECK_EQ(expect, actual);
    }

    SUBCASE("Test2") {
        string a = "-12/ (-23) ^ (-6 + 2)*3";

        string actual = ReversePolish::convertToString(a);
        string expect = "n-12n-23n-6n2o+o^o/n3o*";

        CHECK_EQ(expect, actual);
    }

    SUBCASE("Test3") {
        string a = "-1948/784-112+(-65 + 32) /45";

        string actual = ReversePolish::convertToString(a);
        string expect = "n-1948n784o/n112o-n-65n32o+n45o/o+";

        CHECK_EQ(expect, actual);
    }
}

#endif //TEST_TESTREVERSEPOLISH_H
