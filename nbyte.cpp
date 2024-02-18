#include "nbyte.h"
#include <cstdio>
#include <fstream>
#include <math.h>

namespace Yesane{
    std::istream &operator>>(std::istream &is, nbyte::nchar &v)
    {
        int c = is.get(); //CR+LF会被视为一个字符，即换行符
        if (c != EOF) //EOF的值为-1，需用int读取
        {
            v.cha = (unsigned char)c;
        }
        return is;
    }
    void nbyte::readFromFile(const std::string &fileName){
        std::fstream fs(fileName, std::fstream::binary | std::fstream::in);
        nchar s;
        while (fs >> s)
        {
            data.push_back(s);
        }
    }
    nbyte::nbyte(istream& is){
        nchar s;
        while (is >> s)
        {
            data.push_back(s);
        }
    }
    void nbyte::showRaw(){
        cout << data.size() << ":[";
        for (int i = 0; i < data.size(); i = i + 1)
        {
            cout << data[i].value() << ", ";
        }
        cout << "];\n";
    }
    bool nbyte::isBasicPrintable(size_t begin, size_t end){
        for(size_t i=begin; i<end; ++i){
            if(data[i].value()<32 || data[i].value()>126){
                return false;
            }
        }
        return true;
    }
    
    bool nbyte::isPrintable(size_t begin, size_t end){
        for (size_t i = begin; i < end; ++i)
        {
            if (data[i].value() < 32 || data[i].value() > 232 || data[i].value() == 127 || data[i].value() == 128)
            {
                return false;
            }
        }
        return true;
    }

    bool nbyte::isCode(size_t begin, size_t end){
        for (size_t i = begin; i < end; ++i){
            if (data[i].value() < 32 || data[i].value() > 126) {
                if(data[i].value()!=10){
                    return false;
                }
            }
        }
        return true;
    }

    bool nbyte::isAdvancePrintable(size_t begin, size_t end){
        size_t i = begin;
        int t;
        size_t ii;
        while(i < end){
            switch (data[i].value())
            {
            case 11: //大自然数标记
                {
                    if(isBigNum(i+1,ii)){
                        i = ii;
                    }
                    else{
                        return false;
                    }
                }
                break;
            case 16: //上标，后跟isPrint为True的单个字符
            case 17: //下标
            case 242: //全角指示符
                {
                    if(isPrintable(i+1,i+2)){
                        i = i+2;
                    }
                    else{
                        return false;
                    }
                }
                break;
            case 18: //全角空格
                ++i;
                break;
            
            default:
                {
                    t = data[i].value();
                    if(t>=20&&t<=126 || t>=129&&t<=232){
                        ++i;
                    }
                    else{
                        return false;
                    }
                }
            }
        }
        return true;
    }

    bool nbyte::isBigNum(size_t begin, size_t &end){
        //begin为表示的起始位置，不包括标记(11)
        if(data.size()>begin+1){ //首先检查begin之后一个字节可读取
            end = begin+2+data[begin+1].value(); //大自然数后的位置坐标
            if(data.size()>end){
                return true;
            }
        }
        return false;
    }

    bool nbyte::isValidNum(size_t begin, size_t end, unsigned long long &value){
        int v = data[begin].value();
        if(v==11){ //为BigNum
            size_t pos = begin + 3 + data[begin + 2].value();
            if(pos == end){ //BigNum所占字节数吻合
                pos = begin + 1; //字节1位置
                int x = data[pos].value(); //数的单位为2的x次方
                int y = data[pos+1].value(); //后面用y字节表示该数
                if(y>4){ //数过大 不继续处理
                    return false;
                }
                if(y==4&&x>32 || y==3&&x>40 || y==2&&x>48 || y==1&&x>56){ //数过大不处理
                    return false;
                }
                pos = pos + 2;
                unsigned long long t = 0;
                for(int i=0; i<y; ++i){ //读取y字节无符号整数
                    if(i>0){ //不是第1字节，则每次要左移8位
                        t = t << 8;
                    }
                    t += data[pos+i].value();
                }
                value = t*(1<<x);
                return true;
            }else{
                return false;
            }
        }else if(v<=31 && v>=20){
            if(end == begin+1){ //确实为用单个字节表示的10的n次方
                value = pow(10.0,32-v);
                return true;
            }else{
                return false;
            }
        }else if(v>=49 && v<=57){
            if(end>=begin+1 && end<=begin+64){ //为用ASCII码表示的正整数
                unsigned long long t = 0;
                for(size_t i=begin; i<end; ++i){
                    if(i>begin){
                        t = t*10;
                    }
                    t += data[i].value()-48;
                }
                value = t;
                return true;
            }else{
                return false;
            }
        }
        return false;
    }

    bool nbyte::isValid(size_t begin, size_t end, size_t& err){
        size_t i = begin, end_pos, j, pos_1, pos_2;
        int t;
        size_t ii;
        unsigned long long largeNum;
        while (i < end){
            switch (data[i].value())
            {
                case 0:
                case 1: //空字符 处理时可忽略
                    ++i;
                    break;
                case 2: //组合语义开始标记
                    {
                        for(j=i+1; j<=i+65;++j){ //数最多占64字节，其后应紧跟语义字符
                            t = data[j].value();
                            if(t>=243 && t<=247){ //遇到语义字符
                                if(j==i+1){ //缺少开始处的自然数
                                    return false;
                                }
                                pos_1 = j;
                                if(!isValidNum(i+1,pos_1,largeNum)){
                                    return false;
                                }
                                //自然数检查合格 退出循环
                                break;
                            }
                            if(j==i+65 && (t<243||t>247)){
                                //缺少语义字符 退出
                                return false;
                            }
                        }
                        if(pos_1 == j){
                            //正常读取了自然数
                            while(data[j].value()>=243 && data[j].value()<=247){
                                j = j+1;
                            }
                            if(data[j].value()!=3){
                                //不为语义结束标记 则说明含有可打印字符说明
                                if(findIt(3,pos_2,j)){ //找到结束标记
                                    if(isBasicPrintable(j,pos_2)){
                                        i = pos_2+largeNum+1; //检查合法
                                    }else{
                                        return false;
                                    }
                                }else{
                                    return false;
                                }
                            }else{
                                i=j+largeNum+1;
                            }
                        }else {
                            return false;
                        }
                    }
                    break;
                case 4: //样式开始标记
                    {
                        if(findIt(19,end_pos,i+1)){ //需找到通用结束标记
                            //读取合法的样式符
                            ++i; //从下一字符开始可能为样式符
                            while(data[i].value()==5){ //粗体
                                ++i;
                            }
                            while(data[i].value()==6){ //斜体
                                ++i;
                            }
                            while(data[i].value()==7){ //下划线
                                ++i;
                            }
                            while(data[i].value()==8){ //删除线
                                ++i;
                            }
                            //合法样式符到此结束 可以不包含任何样式
                            if(isAdvancePrintable(i,end_pos)){
                                i=end_pos+1;
                            }
                            else {
                                err = i;
                                return false;
                            }
                        }
                        else {
                            err = i;
                            return false;
                        }
                    }
                    break;
                case 9: //换段键
                case 10: //换行键 可在最外层单独或连续出现
                    ++i;
                    break;
                case 12: //可打印字符开始标记 isAdvancePrintable为True
                    {
                        if(findIt(19,end_pos,i+1)){ //需找到通用结束标记
                            if(isAdvancePrintable(i+1,end_pos)){
                                i=end_pos+1;
                            }
                            else {
                                err = i;
                                return false;
                            }
                        }
                        else {
                            err = i;
                            return false;
                        }
                    }
                    break;
                case 13: //小一号字体开始标记
                    {
                        t=0;
                        while(data[i].value()==13){
                            ++i;
                            ++t;
                        }
                        ii = t;
                        if(findIt(19,end_pos,i)){
                            while(t>0){
                                if(data[end_pos+t-1].value()!=19){
                                    break;
                                }
                                --t;
                            }
                            if(t!=0){ //提前退出循环 缺乏足够的结束标记
                                return false;
                            }
                            if(isAdvancePrintable(i,end_pos)){
                                i=end_pos+ii;
                            }
                            else {
                                err = i;
                                return false;
                            }
                        }else{
                            err = i;
                            return false;
                        }
                    }
                    break;
                case 14: //大一号字体开始标记
                    {
                        t=0;
                        while(data[i].value()==14){
                            ++i;
                            ++t;
                        }
                        ii = t;
                        if(findIt(19,end_pos,i)){
                            while(t>0){
                                if(data[end_pos+t-1].value()!=19){
                                    break;
                                }
                                --t;
                            }
                            if(t!=0){ //提前退出循环 缺乏足够的结束标记
                                return false;
                            }
                            if(isAdvancePrintable(i,end_pos)){
                                i=end_pos+ii;
                            }
                            else {
                                err = i;
                                return false;
                            }
                        }else{
                            err = i;
                            return false;
                        }
                    }
                    break;
                case 15: //代码开始标记
                    {
                        if(findIt(19,end_pos,i+1)){ //需找到通用结束标记
                            if(isCode(i+1,end_pos)){
                                i=end_pos+1;
                            }
                            else {
                                err = i;
                                return false;
                            }
                        }
                        else {
                            err = i;
                            return false;
                        }
                    }
                    break;
                case 127: //公式开始标记
                    {
                        if(findIt(128,end_pos,i+1)){ //需找到公式结束标记
                            if(isPrintable(i+1,end_pos)){
                                i=end_pos+1;
                            }
                            else {
                                err = i;
                                return false;
                            }
                        }
                        else {
                            err = i;
                            return false;
                        }
                    }
                    break;
                case 234: //ASCII编码开始 待补充编码的识别
                    break;
                case 235: //UTF-8编码开始
                    break;
                case 236: //UTF-16编码开始
                    break;
                case 237: //UTF-32编码开始
                    break;
                case 238: //单个ASCII字符
                    i = i+2;
                    break;
                case 239: //单个UTF-8编码
                    break;
                case 240: //单个UTF-16编码
                    break;
                case 241: //单个UTF-32编码
                    i = i+5;
                    break;
                case 248: //替换开始标记
                    {
                        for(j=i+1; j<=i+65;++j){ //数最多占64字节，其后应紧跟替换字符
                            t = data[j].value();
                            if(t>=250 && t<=254 && j>i+1){ //遇到替换字符
                                pos_1 = j;
                                if(j==i+1){
                                    //没有数，只包含替换字符
                                    break;
                                }
                                if(!isValidNum(i+1,pos_1,largeNum)){
                                    return false;
                                }
                                //自然数检查合格 退出循环
                                break;
                            }
                            if(j==i+65 && (t<250||t>254)){
                                //缺少替换字符 退出
                                return false;
                            }
                        }
                        if(pos_1 == j){
                            while(data[j].value()>=250 && data[j].value()<=254){
                                j = j+1;
                            }
                            if(data[j].value()==249){
                                if(pos_1==i+1){
                                    i = j+1; //不包含数据
                                }else{
                                    i = j+largeNum+1;
                                }
                            }else{
                                return false;
                            }
                        }else{
                            return false;
                        }
                    }
                    break;
                case 233:
                case 255: //这两个值不被使用
                    {
                        err = i;
                        return false;
                    }
                    break;
                default:
                    {
                        return false;
                    }
            }
        }
        return true;
    }

    bool nbyte::findIt(unsigned char v, size_t &pos, size_t begin = 0){
        if(begin>=0 && begin<data.size()){
            for(size_t i=begin; i<data.size(); ++i){
                if(data[i].cha == v){
                    pos = i;
                    return true;
                }
            }
        }
        return false;
    }
}
