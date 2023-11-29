#ifndef TEST_INTELLICALC_H
#define TEST_INTELLICALC_H

#include "string"
using namespace std;

/*
 * TODO: 充满智慧的算法
 *  继承自愚蠢算法, 即若实在无法实现, 就将其删掉, 保证愚蠢算法的基本功能
 *  无需实例化
 *  工作原理：
 *      将输入的两个{string}类型的变量, 将它们转换为double类型进行充满
 *      智慧的加、减、乘、除、整除、模、开根号、幂乘、阶乘运算(均未完成)
 *      返回值均为{string}类型
 *      可以利用的算法有: 高精度加减乘除算法、快速傅立叶变换(FFT)算法等
 *
 */
class IntelliCalc : public Calc {
public:
    // TODO: 加法运算
    static string add(const string &strA, const string &strB) {
        return nullptr;
    }

    // TODO: 减法运算
    static string sub(const string &strA, const string &strB) {
        return nullptr;
    }

    // TODO: 乘法运算
    static string mul(const string &strA, const string &strB) {
        return nullptr;
    }

    // TODO: 除法运算
    static string dev(const string &strA, const string &strB) {
        return nullptr;
    }

    // TODO: 整除运算
    static string fDev(const string &strA, const string &strB) {
        return nullptr;
    }

    // TODO: 模运算
    static string mod(const string &strA, const string &strB) {
        return nullptr;
    }

    // TODO: 开根号(二阶/三阶/...)
    static string root(const string &strA, const string &strB) {
        return nullptr;
    }

    // TODO: 幂乘运算
    static string pow(const string &strA, const string &strB) {
        return nullptr;
    }

    // TODO: 阶乘运算
    static string fac(const string &strA) {
        return nullptr;
    }
};

#endif //TEST_INTELLICALC_H
