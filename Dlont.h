#pragma once
#ifndef DLONT_H
#define DLONT_H

#include "Base.h"

//1bit符号位 8bit指数位(0~255) 23位有效数字
//指数位全1表示无穷大或无穷小或NaN 与float类似
//指数位全0 则有效位小数点前为0
//指数位非全0且非全1 有效位小数点前为1 省略不存储
class Yesane::dlont {
};

#endif