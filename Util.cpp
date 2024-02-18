#include "Util.h"
#include "Value.h"
#include "Base.h"
#include <iostream>
#include <stdexcept>
#include <limits>

using std::cout;
using std::endl;
using std::numeric_limits;

namespace Yesane{
    //const double Util::error = 0.0000000001;
    int Util::gcd(int a, int b)
    {
        if (a < 0)
            a = -a;
        if (b < 0)
            b = -b;
        if (a < b)
        {
            std::swap(a, b);
        }
        if (b == 0)
            return a;
        int r = a % b;
        while (r)
        {
            a = b;
            b = r;
            r = a % b;
        }
        return b;
    }
    void Util::showDataInfo()
    {
        //这里\t的作用是使得前面的字符加上\t后为8的整数倍
        //不超过8字符的用\t\t 超过8字符的用\t 则保证至少占16字符
        //输出单字符前写+可将其转为数字输出
        cout << "type\t\t| Bytes\t| max()\t\t| min()\t\t| lowest()\n"
             << "----------------------------------------------------\n"
             << "bool\t\t| "
             << sizeof(bool) << "\t| "
             << numeric_limits<bool>::max() << "\t\t| "
             << numeric_limits<bool>::min() << "\t\t| "
             << numeric_limits<bool>::lowest() << '\n'
             << "char\t\t| "
             << sizeof(char) << "\t| "
             << +numeric_limits<char>::max() << "\t\t| "
             << +numeric_limits<char>::min() << "\t\t| "
             << +numeric_limits<char>::lowest() << '\n'
             << "signed char\t| "
             << sizeof(signed char) << "\t| "
             << +numeric_limits<signed char>::max() << "\t\t| "
             << +numeric_limits<signed char>::min() << "\t\t| "
             << +numeric_limits<signed char>::lowest() << '\n'
             << "unsigned char\t| "
             << sizeof(unsigned char) << "\t| "
             << +numeric_limits<unsigned char>::max() << "\t\t| "
             << +numeric_limits<unsigned char>::min() << "\t\t| "
             << +numeric_limits<unsigned char>::lowest() << '\n'
             << "wchar_t\t\t| "
             << sizeof(wchar_t) << "\t| "
             << numeric_limits<wchar_t>::max() << "\t\t| "
             << numeric_limits<wchar_t>::min() << "\t\t| "
             << numeric_limits<wchar_t>::lowest() << '\n'
             //<< "char8_t\t\t| "
             //<< sizeof(char8_t) << "\t| "
             //<< numeric_limits<char8_t>::max() << "\t\t| "
             //<< numeric_limits<char8_t>::min() << "\t\t| "
             //<< numeric_limits<char8_t>::lowest() << '\n'
             << "char16_t\t| "
             << sizeof(char16_t) << "\t| "
             << numeric_limits<char16_t>::max() << "\t\t| "
             << numeric_limits<char16_t>::min() << "\t\t| "
             << numeric_limits<char16_t>::lowest() << '\n'
             << "char32_t\t| "
             << sizeof(char32_t) << "\t| "
             << numeric_limits<char32_t>::max() << "\t| "
             << numeric_limits<char32_t>::min() << "\t\t| "
             << numeric_limits<char32_t>::lowest() << '\n'
             << "short\t\t| "
             << sizeof(short) << "\t| "
             << numeric_limits<short>::max() << "\t\t| "
             << numeric_limits<short>::min() << "\t| "
             << numeric_limits<short>::lowest() << '\n'
             << "unsigned short\t| "
             << sizeof(unsigned short) << "\t| "
             << numeric_limits<unsigned short>::max() << "\t\t| "
             << numeric_limits<unsigned short>::min() << "\t\t| "
             << numeric_limits<unsigned short>::lowest() << '\n'
             << "int\t\t| "
             << sizeof(int) << "\t| "
             << numeric_limits<int>::max() << "\t| "
             // 2147483647
             << numeric_limits<int>::min() << "\t| "
             << numeric_limits<int>::lowest() << '\n'
             << "unsigned int\t| "
             << sizeof(unsigned int) << "\t| "
             << numeric_limits<unsigned int>::max() << "\t| "
             // 4294967295
             << numeric_limits<unsigned int>::min() << "\t\t| "
             << numeric_limits<unsigned int>::lowest() << '\n'
             << "long\t\t| "
             << sizeof(long) << "\t| "
             << numeric_limits<long>::max() << "\t| "
             << numeric_limits<long>::min() << "\t| "
             << numeric_limits<long>::lowest() << '\n'
             << "unsigned long\t| "
             << sizeof(unsigned long) << "\t| "
             << numeric_limits<unsigned long>::max() << "\t| "
             << numeric_limits<unsigned long>::min() << "\t\t| "
             << numeric_limits<unsigned long>::lowest() << '\n'
             << "long long\t| "
             << sizeof(long long) << "\t| "
             << numeric_limits<long long>::max() << "\t| "
             // 9223372036854775807
             << numeric_limits<long long>::min() << "\t| "
             << numeric_limits<long long>::lowest() << '\n'
             << "unsigned long long | "
             << sizeof(unsigned long long) << "\t| "
             << numeric_limits<unsigned long long>::max() << "\t| "
             // 18446744073709551615
             << numeric_limits<unsigned long long>::min() << "\t\t\t| "
             << numeric_limits<unsigned long long>::lowest() << '\n'
             << "float\t\t| "
             << sizeof(float) << "\t| "
             << numeric_limits<float>::max() << "\t\t| "
             // 3.40282e+038
             << numeric_limits<float>::min() << "\t\t| "
             // 1.17549e-038
             << numeric_limits<float>::lowest() << '\n'
             // -3.40282e+038
             << "double\t\t| "
             << sizeof(double) << "\t| "
             << numeric_limits<double>::max() << "\t\t| "
             // 1.79769e+308
             << numeric_limits<double>::min() << "\t\t| "
             // 2.22507e-308
             << numeric_limits<double>::lowest() << '\n'
             // -1.79769e+308
             << "long double\t| "
             << sizeof(long double) << "\t| "
             << numeric_limits<long double>::max() << "\t\t| "
             // 1.18973e+4932
             << numeric_limits<long double>::min() << "\t\t| "
             // 3.3621e-4932
             << numeric_limits<long double>::lowest() << '\n';
             // -1.18973e+4932
    }
}