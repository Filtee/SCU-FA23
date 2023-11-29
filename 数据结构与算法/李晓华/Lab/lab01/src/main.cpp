#include "string"
#include "formula/Formula.h"
#include "iostream"

using namespace std;

/*
 * 主函数写在这里
 *  注：运行测试时请在 {main} 前面加上 {_} 即：修改为 {_main}
 *      否则 doctest 将无法运行
 * */
int main() {
    bool ifCountinue = true;
    string inputStr;
    char judge;

    while (ifCountinue) {
        cout << "支持的运算符：+ - * / ^ & ( )" << endl;
        cout << "请输入算式(以'='结束)：" << endl;
        getline(cin, inputStr);

        try {
            auto *formula1 = new Formula(inputStr);
            cout << formula1->getResult() << endl;
        } catch (const runtime_error::exception &e) {
            cout << "输入错误，请重新输入!" << endl;
            cin.get();
            continue;
        }

//        cout << "是否继续（Y/N）?" << endl;
//        cin >> judge;
//        ifCountinue = judge == ('Y' | 'y');
        // 刷新
        cin.get();
    }

    return 0;
}
