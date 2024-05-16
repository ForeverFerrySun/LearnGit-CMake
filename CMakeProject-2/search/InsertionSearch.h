#ifndef INSERTIONSEARCH_H
#define INSERTIONSEARCH_H
/**
 * 插入排序:
 * 1. 插入排序是一种简单直观的排序算法。
 * 2. 平均时间复杂度：O(n2)
 * 3. 空间复杂度：O(1)
 * 步骤：
 * 1. 从第一个元素开始，该元素可以认为已经被排序
 * 2. 取出下一个元素，在已经排序的元素序列中从后向前扫描
 * 3. 如果该元素（已排序）大于新元素，将该元素移到下一位置
 * 4. 重复步骤3，直到找到已排序的元素小于或者等于新元素的位置
 * 5. 将新元素插入到该位置后
 * 6. 重复步骤2~5
*/
#include <iostream>
using namespace std;
namespace Search
{
    class InsertionSearch
    {
    private:
        /* data */
    public:
        // 插值查找
        int InsertionSearch_(int a[], int value, int low, int high);
    };
} // namespace Search

#endif // INSERTIONSEARCH_H
