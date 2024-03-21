#pragma once
#ifndef BASE_H
#define BASE_H



namespace Yesane
{
    class Util; //工具类
    class Value; //分数类
    class fnt; //大整数类
    class dlont; //更大整数类 待实现
    class nbyte; //新型单字节编码
    class YFileSys; //新型文件系统
    
    enum class accuracy
    {
        exact,//结果没有精度损失
        noexact,//有精度损失
    };
}

#endif