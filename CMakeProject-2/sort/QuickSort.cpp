#include "QuickSort.h"
namespace Sort
{
    // 快速排序（递归）
    void QuickSort::QuickSort_(vector<int> &v, int low, int high)
    {
        if (low >= high) // 结束标志
            return;
        int first = low;    // 低位下标
        int last = high;    // 高位下标
        int key = v[first]; // 设第一个为基准

        while (first < last)
        {
            // 将比第一个小的移到前面
            while (first < last && v[last] >= key)
                last--;
            if (first < last)
                v[first++] = v[last];

            // 将比第一个大的移到后面
            while (first < last && v[first] <= key)
                first++;
            if (first < last)
                v[last--] = v[first];
        }
        // 基准置位
        v[first] = key;
        // 前半递归
        QuickSort_(v, low, first - 1);
        // 后半递归
        QuickSort_(v, first + 1, high);
    }

    // ----------------------------------------------------

    // 模板实现快速排序（递归）
    template <typename T>
    void QuickSort::quick_sort_recursive(T arr[], int start, int end)
    {
        if (start >= end)
            return;
        T mid = arr[end];
        int left = start, right = end - 1;
        while (left < right)
        {
            while (arr[left] < mid && left < right)
                left++;
            while (arr[right] >= mid && left < right)
                right--;
            std::swap(arr[left], arr[right]);
        }
        if (arr[left] >= arr[end])
            std::swap(arr[left], arr[end]);
        else
            left++;
        quick_sort_recursive(arr, start, left - 1);
        quick_sort_recursive(arr, left + 1, end);
    }
    template <typename T> // 整數或浮點數皆可使用,若要使用物件(class)時必須設定"小於"(<)、"大於"(>)、"不小於"(>=)的運算子功能
    void QuickSort::quick_sort(T arr[], int len)
    {
        quick_sort_recursive(arr, 0, len - 1);
    }
}