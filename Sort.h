#pragma once
#ifndef SORT_H
#define SORT_H

namespace Yesane {
    using size_4 = unsigned int;
    using std::swap;
    //冒泡排序 升序 需要随机访问迭代器
    template <typename ListType>
    void bubbleSort(typename ListType::iterator first,
                   typename ListType::iterator last) {
        bool exchanged = true;
        for (auto i = first; exchanged && i < last-1; i++) {
            exchanged = false;
            for (auto j = first; j < last-(i-first+1); j++) {
                if (*j > *(j + 1)) {
                    swap(*j, *(j + 1));
                    exchanged = true;
                }
            }
        }
    }

    //选择排序 升序 需要随机访问迭代器
    template <typename ListType>
    void selectionSort(typename ListType::iterator first,
                   typename ListType::iterator last) {
        typename ListType::iterator minIndex; //最小的元素的下标
        for (auto i = first; i < last; ++i) {
            minIndex = i;
            for (auto j = i + 1; j < last; ++j) {
                if (*j < *minIndex) {
                    minIndex = j;
                }
            }
            swap(*i, *minIndex);
        }
    }

    //插入排序 升序 需要随机访问迭代器 在中间插入元素效率低
    template <typename ListType>
    void insertionSort(typename ListType::iterator first,
                   typename ListType::iterator last) {
        for (auto i = first; i < last; ++i){
            auto j = i + 1; //已排序中的最后一个元素的下标加1
            auto temp = *j;
            while(j>first && *(j-1)>temp){
                *j = *(j - 1);
                j--;
            }
            *j = temp;
        }
    }

    // 希尔排序 升序 需要随机访问迭代器
    template <typename ListType>
    void shellSort(typename ListType::iterator first,
                   typename ListType::iterator last) {
        size_4 len = last - first;
        for (size_4 gap = len / 2; gap > 0; gap/=2){ //相距gap的元素为一组
            for (auto i = first + gap; i < last; ++i){ //i为未排序元素的第1个
                auto temp = *i;
                auto j = i;
                while(j>=first+gap&&*(j-gap)>temp){
                    *j = *(j - gap);
                    j -= gap;
                }
                *j = temp;
            }
        }
    }

    // 快速排序 升序 需要随机访问迭代器 应为闭区间
    template <typename ListType>
    void quickSort(typename ListType::iterator left,
                   typename ListType::iterator right) {
        --right;
        if(left < right){
            auto pivot = *right;
            auto i = left; //指向第1个不小于pivot的元素
            for (auto j = left; j < right; ++j){
                if(*j < pivot){
                    swap(*i,*j);
                    ++i;
                }
            }
            swap(*i, *right);
            quickSort<ListType>(left, i);
            quickSort<ListType>(i + 1, right+1);
        }
    }
}

#endif