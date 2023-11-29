#ifndef TEST_FORMULA_H
#define TEST_FORMULA_H

#include "string"
#include "iostream"
#include "stdexcept"

using namespace std;

#include "ADT/Stack.h"
#include "calc/Calc.h"
#include "ReversePolish.h"

/*
 * 公式计算类
 *  实例化: 调用 {Formula()} / {Formula(str)} 以生成实例
 *  工作原理:
 *  1. 调用 {formula->store(str)} 来存储输入的公式
 *      1> 输入的字符串将先被转换成逆波兰式(以Stack的形式返回)后, 存储为私有空间中的 {element}
 *          若{element}原先不为null, 则先销毁先前存储的{ADT}, 再将得到的逆波兰式栈存入
 *      2> 存入后进行计算, 运算过程交给{calc.h}或{IntelliCalc.h}头文件中包含的计算公式, 调
 *          用语法如{calc::Add(strA, strB)}; 输入的两个参数均为{string}类型, 返回的结果也
 *          为{string}类型
 *  2. 调用 {formula->result()} 来获取公式计算结果
 */
class Formula {
private:
    // 存储的逆波兰式
    Stack<string> *formula;
    // 计算得到的结果
    string result;

    /*
     * 调用逆波兰式进行计算
     *  运算过程交给{calc.h}或{IntelliCalc.h}头文件中包含的计算公式,
     *  调用语法如{calc::Add(strA, strB)}; 输入的两个参数均为{string}
     *  类型, 返回的结果也为{string}类型
     */
    void proceed() {
        // 定义一个用来存储运算过程的栈
        auto *tempOperator = new Stack<string>;

        while (formula->length() != 0) {
            string str = formula->pop();
            // 判断该字符串为数字还是操作符并进行操作
            if (NorO(str)) {
                str.erase(0, 1);
                tempOperator->push(str);
            } else {
                // 遇到符号，就从栈中提数
                // 由于逆波兰式中前两个数（对应这里的字符串）一定是数，故不用担心提不出两个数的问题
                string num1 = tempOperator->pop();
                string num2 = tempOperator->pop();
                str.erase(0, 1);

                // 声明函数模版
                function<string(string, string)> func;
                // 根据运算符选择对应运算函数
                switch (str.at(0)) {
                    case '+':
                        func = Calc::add;
                        break;
                    case '-':
                        func = Calc::sub;
                        swap(num1, num2);
                        break;
                    case '*':
                        func = Calc::mul;
                        break;
                    case '/':
                        // 除法运算这里暂时选用精度更高的dev()，保证后续不出错
                        func = Calc::dev;
                        swap(num1, num2);
                        break;
                    case '%':
                        func = Calc::mod;
                        swap(num1, num2);
                        break;
                    case '&':
                        func = Calc::root;
                        swap(num1, num2);
                        break;
                    case '^':
                        func = Calc::power;
                        swap(num1, num2);
                        break;
                    case '!':
                        break;
                    default:
                        // 抛出非法输入异常
                        throw runtime_error("非法字符输入!");
                }

                // 执行对应的运算
                try {
                    tempOperator->push(func(num1, num2));
                } catch (const runtime_error &e) {
                    throw e;
                }
            }
        }
        //弹出栈里最后仅剩的string，即运算结果
        result.append(tempOperator->pop());
    }

    //如果是n，返回1，说明接下来的部分是数字；
    //如果不是n,是o，返回0，说明接下来的部分是运算符
    bool NorO(string str) {
        return str[0] == 'n';
    };

public:
    // Constructor
    Formula(string str = nullptr) {
        try {
            store(str);
            formula = new Stack<string>();
        } catch (const runtime_error &e) {
            throw e;
        }
    }

    // Destructor
    ~Formula() {
        clear();
    }

    void clear() {
        formula->clear();
        result = nullptr;
    }

    // 存储转换后的逆波兰式
    void store(const string &str) {
        try {
            delete formula;
            formula = ReversePolish::convert(str);
            // 运算
            proceed();
        } catch (const runtime_error &e) {
            throw e;
        }
    }

    // 返回运算结果
    string getResult() {
        return result;
    }
};


#endif //TEST_FORMULA_H
