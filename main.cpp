#include <algorithm>
#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include "headers.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using Yesane::bubbleSort;
using Yesane::fnt;
using Yesane::Util;
using Yesane::Value;
using Yesane::nbyte;

void fun1() {
    vector<Value> vs{-8, string("-5/3"), 18.34, "-3/23"};
    vector<int> vi{40, 6, 2, 1, -4, -7, -15, -80};
    cout << Util::printList(vs.begin(), vs.end()) << "\n"
         << Util::printList(vi.begin(), vi.end());
    cout << "\nafter sort\n";
    Yesane::bubbleSort<vector<Value>>(vs.begin(), vs.end());
    Yesane::bubbleSort<vector<int>>(vi.begin(), vi.end());
    cout << Util::printList(vs.begin(), vs.end()) << "\n"
         << Util::printList(vi.begin(), vi.end());
}

struct T {
    friend std::istream& operator>>(std::istream& is, T& v);
    fnt a;
    string b;
    double c;
    T() {}
};

std::istream& operator>>(std::istream& is, T& v) {
    is >> v.a;
    is >> v.c;
    getline(is, v.b, '%'); //遇到%号才结束字符串的读取
    return is;
}

//测试结构化数据的读取
void test() {
    std::fstream fs("C:/Users/wlmzn/Desktop/00.txt", std::fstream::binary | std::fstream::in);
    nbyte cs(fs);
    cs.showRaw();
    // char c[7];
    // fs.read(c,7);
    // for(int i=0;i<7;++i){
    //     cout << int((unsigned char)(c[i])) << ", ";
    // }
    // int c;
    // while((c=fs.get())!=EOF){
    //     cout << (int)(unsigned char)c <<", ";
    // }
}

int main() {
    //Util::showDataInfo();
    try {
        //fun1();
        test();
        unsigned int a = -1; //4294967295
        size_t d = size_t(a)+1;
        int b = a;
        int c = d>a;
        cout << a << ", " << b << " d>a? " << c;
    } catch (std::exception e) {
        std::cerr << e.what();
    }

    return 0;
}
