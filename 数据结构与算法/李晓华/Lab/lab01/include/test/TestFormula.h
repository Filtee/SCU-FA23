#ifndef TEST_TESTFORMULA_H
#define TEST_TESTFORMULA_H

#include "doctest/doctest.h"
#include "calc/Calc.h"
#include "formula/Formula.h"

/*
 * TODO: 整个式子计算结果单元测试
 */
    TEST_CASE("Test Formula.h") {
    SUBCASE("Test1") {
        string a = "107.6+13-26.57";

        Formula *formula = new Formula(a);
        string actual = formula->getResult();
        string expect = Calc::convert("94.03");

        CHECK_EQ(expect, actual);
    }

    SUBCASE("Test2") {
        string a = "6.2*70.5/18.3";

        Formula *formula = new Formula(a);
        string actual = formula->getResult();
        string expect = Calc::convert("23.8852459");

        CHECK_EQ(expect, actual);
    }

    SUBCASE("Test3") {
        string a = "14.2+5^3";

        Formula *formula = new Formula(a);
        string actual = formula->getResult();
        string expect = Calc::convert("139.2");

        CHECK_EQ(expect, actual);
    }
    SUBCASE("Test4") {
        string a = "14.2+27.5*5^3";

        Formula *formula = new Formula(a);
        string actual = formula->getResult();
        string expect = Calc::convert("3451.7");

        CHECK_EQ(expect, actual);
    }
    SUBCASE("Test5") {
        string a = "-32.76 + (8-5) ^ 2 * 102.67/(8%3) ";

        Formula *formula = new Formula(a);
        string actual = formula->getResult();
        string expect = Calc::convert("429.255");

        CHECK_EQ(expect, actual);
    }
    SUBCASE("Test6") {
        string a = "-32.76 + 102.67*78.934/ (8.2-5.3) ^ 2 ";

        Formula *formula = new Formula(a);
        string actual = formula->getResult();
        string expect = Calc::convert("930.8730297265");

        CHECK_EQ(expect, actual);
    }
    SUBCASE("Test7") {
        string a = "-32.76 + 102.67*78.934/ (8.2-5.3) ^ 2 ";

        Formula *formula = new Formula(a);
        string actual = formula->getResult();
        string expect = Calc::convert("930.8730297265");

        CHECK_EQ(expect, actual);
    }
    SUBCASE("Test8") {
        string a = "-32.76 + 102.67*78.934/ (8.2-5.3) ^ 2 ";

        Formula *formula = new Formula(a);
        string actual = formula->getResult();
        string expect = Calc::convert("930.8730297265");

        CHECK_EQ(expect, actual);
    }
}

#endif //TEST_TESTFORMULA_H
