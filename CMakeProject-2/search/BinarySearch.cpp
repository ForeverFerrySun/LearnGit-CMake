/*
 * @FilePath     : \LearnGit-CMake\CMakeProject-2\search\BinarySearch.cpp
 * @Date         : 2024-05-15 22:08:07
 * @author       : foreverferrysun
 * @LastEditTime : 2024-05-15 22:30:47
 * @LastEditors  : foreverferrysun
 * @FileDescription:
 */
#include "BinarySearch.h"
namespace Search
{
    int BinarySearch::BinarySearch_(vector<int> v, int value, int low, int high)
    {
        if (v.size() <= 0)
        {
            return -1;
        }
        while (low <= high)
        {
            int mid = low + (high - low) / 2;
            if (v[mid] == value)
            {
                return mid;
            }
            else if (v[mid] > value)
            {
                high = mid - 1;
            }
            else
            {
                low = mid + 1;
            }
        }

        return -1;
    }
    // 递归
    int BinarySearch::BinarySearch2(vector<int> v, int value, int low, int high)
    {
        if (low > high)
            return -1;
        int mid = low + (high - low) / 2;
        if (v[mid] == value)
            return mid;
        else if (v[mid] > value)
            return BinarySearch2(v, value, low, mid - 1);
        else
            return BinarySearch2(v, value, mid + 1, high);
    }

}
