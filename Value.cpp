#include "Value.h"

namespace Yesane{
    Value::Value(const string& s)
    {
        std::istringstream is(s);
        char c;
        if (s.find("/") != string::npos)
        {
            is >> numerator >> c >> denominator;
        }
        else
        {
            is >> numerator;
            denominator = 1;
        }
    }
    std::string Value::toString() const 
    {
        std::stringstream ss;
        if(denominator == 1){
            ss << numerator;
            return ss.str();
        }else {
            ss << numerator << "/" << denominator;
            std::string s = ss.str();
            if(s.length()>MAX_SIZE){ //超过最大字符长度，则转为小数
                return Value(toDouble(), 1).toString();
            }else
                return s;
        }
    }
    Value& Value::operator=(const Value &v)
    {
        numerator = v.numerator;
        denominator = v.denominator;
        return *this;
    }
    Value& Value::operator+=(const Value &v)
    {
        numerator = numerator * v.denominator + v.numerator * denominator;
        denominator *= v.denominator;
        selfReduction();
        return *this;
    }
    Value operator+(const Value &v1, const Value &v2)
    {
        Value t(v1);
        t += v2;
        return t;
    }
    Value &Value::operator-=(const Value &v)
    {
        numerator = numerator * v.denominator - v.numerator * denominator;
        denominator *= v.denominator;
        selfReduction();
        return *this;
    }
    Value operator-(const Value &v1, const Value &v2)
    {
        Value t(v1);
        t -= v2;
        return t;
    }
    Value &Value::operator*=(const Value &v)
    {
        denominator *= v.denominator;
        numerator *= v.numerator;
        selfReduction();
        return *this;
    }
    Value operator*(const Value &v1, const Value &v2)
    {
        Value t(v1);
        t *= v2;
        return t;
    }
    Value &Value::operator/=(const Value &v)
    {
        denominator *= v.numerator;
        numerator *= v.denominator;
        selfReduction();
        return *this;
    }
    Value operator/(const Value &v1, const Value &v2)
    {
        Value t(v1);
        t /= v2;
        return t;
    }
    bool operator>(const Value &v1, const Value &v2)
    {
        return v1.toDouble() > v2.toDouble();
    }
    bool operator<(const Value &v1, const Value &v2)
    {
        return v1.toDouble() < v2.toDouble();
    }
    bool operator==(const Value &v1, const Value &v2)
    {
        return v1.toDouble() == v2.toDouble();
    }
    bool operator!=(const Value &v1, const Value &v2)
    {
        return v1.toDouble() != v2.toDouble();
    }
    bool operator>=(const Value &v1, const Value &v2){
        return v1.toDouble() >= v2.toDouble();
    }
    bool operator<=(const Value &v1, const Value &v2){
        return v1.toDouble() <= v2.toDouble();
    }
    std::ostream &operator<<(std::ostream &os, const Value &v){
        os << v.toString();
        return os;
    }
    std::istream &operator>>(std::istream &is, Value &v){
        string s;
        is >> s;
        v = Value(s);
        return is;
    }
}

