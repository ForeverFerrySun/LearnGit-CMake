/*
 * @FilePath     : \LearnGit-CMake\CMakeProject-2\sort\QuickSort.h
 * @Date         : 2024-05-15 22:05:16
 * @author       : foreverferrysun
 * @LastEditTime : 2024-05-15 23:49:34
 * @LastEditors  : foreverferrysun
 * @FileDescription:  
 */
#ifndef QUICKSORT_H
#define QUICKSORT_H
/**
 * 快速排序（小数，基准元素，大数）。
 * 在区间中随机挑选一个元素作基准，将小于基准的元素放在基准之前，大于基准的元素放在基准之后，再分别对小数区与大数区进行排序。
 *
 * 快速排序思路：
 * 1. 选取第一个数为基准
 * 2. 将比基准小的数交换到前面，比基准大的数交换到后面
 * 3. 对左右区间重复第二步，直到各区间只有一个数
 * */

#include <iostream>
#include <vector>
using namespace std;
namespace Sort
{
    class QuickSort
    {
    private:
        /* data */
    public:
        // 快速排序（递归）
        void QuickSort_(vector<int> &v, int low, int high);

        // 模板实现快速排序（递归）
        template <typename T>
        void quick_sort_recursive(T arr[], int start, int end);

        template <typename T> // 整数或浮点数都可以使用，如果要使用对象（类），则必须设置 "小于"（<）、"大于"（>）、"不小于"（>=）的运算符功能。
        void quick_sort(T arr[], int len);
    };

} // namespace Sort

#endif // QUICKSORT_H
