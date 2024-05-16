#ifndef SEQUENTIALSEARCH_H
#define SEQUENTIALSEARCH_H
/**
 * 顺序查找：
 * 1. 顺序查找是一种最简单的查找算法，它的基本思想是：将给定值与序列中的元素逐个比较，直到找出满足条件的元素为止。
 * 2. 顺序查找的时间复杂度为O(n)，其中n为序列的长度。
 * 步骤：
 * 1. 将给定值与序列中的第一个元素比较。
 * 2. 如果相等，则查找成功，返回序列中该元素的索引。
 * 3. 如果不相等，则将给定值与序列中的第二个元素比较。
 * 4. 重复上述步骤，直到找到满足条件的元素或遍历完整个序列。
 * 5. 如果未找到满足条件的元素，则查找失败，返回-1。
 * 复杂度分析：
 * 1. 平均时间复杂度为O(n)，最坏时间复杂度为O(n)，空间复杂度为O(1)。
*/
#include <vector>
#include <iostream>

using namespace std;
namespace Search
{
    class SequentialSearch
    {
    public:
        // 顺序查找
        int SequentialSearch_(vector<int>& v, int k);
        /*以下是仅执行的Sentinel搜索算法每个循环迭代中只进行一次测试，从而降低时间复杂性*/
        int BetterSequentialSearch(vector<int> &v, int k);
    };

} // namespace Search

#endif // SEQUENTIALSEARCH_H
