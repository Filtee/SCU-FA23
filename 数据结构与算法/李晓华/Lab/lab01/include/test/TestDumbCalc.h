#ifndef TEST_TESTCALC_H
#define TEST_TESTCALC_H

#include "string"
using namespace std;

#include "doctest/doctest.h"
#include "calc/Calc.h"

/*
 * TODO: 愚蠢算法 {calc.h} 单元测试
 */
TEST_CASE("Test DumbCalc") {
    SUBCASE("Test DumbCalc with integers") {
        int a = 432135;
        int b = 111;
        SUBCASE("Test func {add}") {
            CHECK_EQ(to_string(a + b), Calc::add(to_string(a), to_string(b)));
        }
        SUBCASE("Test func {sub}") {
            CHECK_EQ(to_string(a - b), Calc::sub(to_string(a), to_string(b)));
        }
        SUBCASE("Test func {mul}") {
            CHECK_EQ(to_string(a * b), Calc::mul(to_string(a), to_string(b)));
        }
        SUBCASE("Test func {fDev}") {
            CHECK_EQ(to_string((int) a / b), Calc::fDev(to_string(a), to_string(b)));
        }
        SUBCASE("Test func {dev}") {
            CHECK_EQ(to_string(a / b), Calc::fDev(to_string(a), to_string(b)));
        }
    }

    SUBCASE("Test DumbCalc with doubles") {
        double a = 43213.435;
        double b = 111.1245;
        SUBCASE("Test func {add}") {
            CHECK_EQ(to_string(a + b), Calc::add(to_string(a), to_string(b)));
        }
        SUBCASE("Test func {sub}") {
            CHECK_EQ(to_string(a - b), Calc::sub(to_string(a), to_string(b)));
        }
        SUBCASE("Test func {mul}") {
            CHECK_EQ(to_string(a * b), Calc::mul(to_string(a), to_string(b)));
        }
        SUBCASE("Test func {dev}") {
            CHECK_EQ(to_string(a / b), Calc::dev(to_string(a), to_string(b)));
        }
    }
}

#endif //TEST_TESTCALC_H
