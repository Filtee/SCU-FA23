#ifndef TEST_TESTINTELLICALC_H
#define TEST_TESTINTELLICALC_H

#include "doctest/doctest.h"
#include "calc/IntelliCalc.h"

/*
 * TODO: 聪明算法 {IntelliCalc.h} 单元测试
 */
TEST_CASE("TestIntelliCalc.h") {
    SUBCASE("Test IntelliCalc.h with integers") {
        string a = "356739701237489999238175681203";
        string b = "909871854780841705718882133";

        SUBCASE("Test func {add}") {
            CHECK_EQ("357649573092270840943894563336",
                     IntelliCalc::add(a, b));
        }
        SUBCASE("Test func {sub}") {
            CHECK_EQ("355829829382709157532456799070",
                     IntelliCalc::sub(a, b));
        }
        SUBCASE("Test func {mul}") {
            CHECK_EQ("324587413638918356725223592910861910580595079846940645999",
                     IntelliCalc::mul(a, b));
        }
        SUBCASE("Test func {dev}") {
            CHECK_EQ("392",
                     IntelliCalc::fDev(a, b));
        }
    }

    SUBCASE("Test IntelliCalc.h with doubles") {
        string a = "35673970123748.9999238175681203";
        string b = "90987.1854780841705718882133";

        SUBCASE("Test func {add}") {
            CHECK_EQ("35673970214736.1854019017386921882133",
                     IntelliCalc::add(a, b));
        }
        SUBCASE("Test func {sub}") {
            CHECK_EQ("35673970032761.8144457333975484117867",
                     IntelliCalc::sub(a, b));
        }
        SUBCASE("Test func {mul}") {
            CHECK_EQ("3245874136389183567.252235929108619105805950798469",
                     IntelliCalc::mul(a, b));
        }
        SUBCASE("Test func {dev}") {
            CHECK_EQ("392076861.552572032732160255938904450266",
                     IntelliCalc::dev(a, b));
        }
    }
}

#endif //TEST_TESTINTELLICALC_H
