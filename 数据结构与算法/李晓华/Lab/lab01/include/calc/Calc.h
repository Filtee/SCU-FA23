#ifndef TEST_CALC_H
#define TEST_CALC_H

#include "string"
#include "cmath"
#include "stdexcept"

using namespace std;

/*
 * TODO:愚蠢算法
 *  无需实例化
 *  工作原理：
 *      将输入的两个{string}类型的变量, 将它们转换为double类型进行非常
 *      愚蠢简单的加、减、乘、除、整除、模、开根号(未完成)、幂乘(未完成)、
 *      阶乘(未完成)运算
 *      返回值均为{string}类型
 */

class Calc {
private:
    // 所有的 helper functions 在这里


public:
    static string convert(const string &str) {
        return to_string(stod(str));
    }

    // 加法运算
    static string add(const string &strA, const string &strB) {
        try {
            double numA = stod(strA);
            double numB = stod(strB);
            return to_string(numA + numB);
        } catch (const invalid_argument &msg) {
            throw runtime_error("计算式输入错误!");
        }
    }

    // 减法运算
    static string sub(const string &strA, const string &strB) {
        double numA = stod(strA);
        double numB = stod(strB);
        return to_string(numA - numB);
    }

    // 乘法运算
    static string mul(const string &strA, const string &strB) {
        double numA = stod(strA);
        double numB = stod(strB);
        return to_string(numA * numB);
    }

    // 除法运算
    static string dev(const string &strA, const string &strB) {
        double numA = stod(strA);
        double numB = stod(strB);
        return to_string(numA / numB);
    }

    // 模运算
    static string mod(const string &strA, const string &strB) {
        int numA = stoi(strA);
        int numB = stoi(strB);
        return to_string(numA % numB);
    }

    // TODO: 开根号(二阶/三阶/...)
    static string root(const string &strA, const string &strB) {
        double numA = stod(strA);
        double numB = stod(strB);

        return to_string(pow(numA, 1 / numB));
    }

    // TODO: 幂乘运算
    static string power(const string &strA, const string &strB) {
        double numA = stod(strA);
        double numB = stod(strB);
        return to_string(pow(numA, numB));
    }

    // TODO: 阶乘运算
    static string fac(const string &strA) {
        int numA = stoi(strA);
        long long ans = 1;
        if (numA <= 0) {
            throw "This number is not positive";
        }
        for (int i = 1; i < numA; i++) {
            ans *= i;
        }

        return to_string(ans);
    }
};

#endif //TEST_CALC_H
