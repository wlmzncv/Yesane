#pragma once
#ifndef NBYTE_H
#define NBYTE_H

#include "Base.h"
#include <vector>
#include <iostream>
#include <string>

using std::vector;
using std::string;
using std::istream;
using std::cout;
using std::size_t;

class Yesane::nbyte {
public:
    struct nchar
    {
        unsigned char cha;
        int value(){
            return int(cha);
        }
    };
    struct resultcode
    {
        unsigned int code;
        string description;
    };

    

public:
    nbyte(){};
    nbyte(istream& is);
    ~nbyte(){};

    void showRaw(); //调试用，打印每一个字节的整型值
    void readFromFile(const std::string& fileName); //读取一个文件中的数据
    bool findIt(unsigned char v, size_t& pos, size_t begin=0); //找到指定字符的位置
    void clearData() { //清空内存中的数据，并还原标记值
        data.clear();
        flag_end1 = true;
        flag_end2 = true;
        flag_end3 = true;
    }
    bool isBasicPrintable(size_t begin, size_t end); //检查是否全为32~126区间内的基本可打印字符，32空格可打印，其他空白字符不可
    bool isPrintable(size_t begin, size_t end);      // 检查是否全为用单个字节表示的单个可打印字符，32空格可打印，其他空白字符不可
    bool isAdvancePrintable(size_t begin, size_t end); //检查是否全为可打印的内容，不带样式
    bool isCode(size_t begin, size_t end); //检查是否为合法代码 仅限包含ASCII码中可打印字符和换行符\n
    bool isValid(size_t begin, size_t end, size_t &err); // 检查此区域中是否有不合法的成分
private:
    bool isBigNum(size_t begin, size_t &end); // 检查是否为大自然数
    bool isValidNum(size_t begin, size_t end, unsigned long long &value); // 检查是否为自然数 并提取值
private: 
    vector<nchar> data;
    bool flag_end1 = true; //为true时可遇到与通用结束标记相配的开始标记；为false时只能遇到通用结束标记；遇到合法标记则改变值
    bool flag_end2 = true; //为true时可遇到公式开始标记，为false时可遇到公式结束标记
    bool flag_end3 = true; //为true时可遇到替换开始标记，为false时可遇到替换结束标记
};

namespace Yesane
{
    std::istream &operator>>(std::istream &is, nbyte::nchar &v);
}

#endif