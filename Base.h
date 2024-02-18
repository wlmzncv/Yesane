#pragma once
#ifndef BASE_H
#define BASE_H



namespace Yesane
{
    class Util;
    class Value;
    class fnt;
    class dlont;
    class nbyte;
    
    enum class accuracy
    {
        exact,//结果没有精度损失
        noexact,//有精度损失
    };
}

#endif