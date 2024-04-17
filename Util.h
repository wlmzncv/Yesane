#pragma once
#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <iterator>
#include "Base.h"

using std::abs;
using std::string;
using std::vector;

class Yesane::Util{
    private:
        Util();
    public:
        //static const double error;
        static int gcd(int a, int b);
        static bool isInteger(double a){
            if(a-long(a) == 0) //待改进 double的指数部分大于小数位数则为整数 后52位存储小数
                return true;
            else
                return false;
        }
        //需要随机访问迭代器
        //模板函数要放在头文件中 因为编译器实例化模板时需要知道它的定义
        //元素类型要实现<<运算符
        template <typename Iterator>
        static string printList(const Iterator &begin, const Iterator &end){
            int size = end - begin;
            std::stringstream ss;
            ss << size << ":[ ";
            for (int i = 0; i < size; ++i){
                ss << *(begin + i) << ", ";
            }
            ss << "];";
            return ss.str();
        }
        // 打印内置类型的信息
        static void showDataInfo();
        // 从输入流中读取特定类型的批量数据，返回一个包含数据的vector
        // 该类型要实现输入运算符>>（必要时可识别分隔符）
        template <typename TypeWithInOp>
        static vector<TypeWithInOp> getDataFromText(std::istream &is){
            std::istream_iterator<TypeWithInOp> iter(is),eof;
            vector<TypeWithInOp> vs(iter, eof);
            return vs;
        }
        static vector<unsigned char> strToUChar(const string& a);
};

#endif
