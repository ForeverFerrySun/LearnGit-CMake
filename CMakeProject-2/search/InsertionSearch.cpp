/*
 * @FilePath     : \LearnGit-CMake\CMakeProject-2\search\InsertionSearch.cpp
 * @Date         : 2024-05-15 22:08:07
 * @author       : foreverferrysun
 * @LastEditTime : 2024-05-16 00:24:56
 * @LastEditors  : foreverferrysun
 * @FileDescription:
 */
#include "InsertionSearch.h"
namespace Search
{
    // 插值查找
    int InsertionSearch::InsertionSearch_(int a[], int value, int low, int high)
    {
        int mid = low + (value - a[low]) / (a[high] - a[low]) * (high - low);
        if (a[mid] == value)
            return mid;
        if (a[mid] > value)
            return InsertionSearch_(a, value, low, mid - 1);
        if (a[mid] < value)
            return InsertionSearch_(a, value, mid + 1, high);
        return -1;
    }
}
