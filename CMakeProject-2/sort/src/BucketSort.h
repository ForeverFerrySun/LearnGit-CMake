#ifndef _BUCKETSORT_H_
#define _BUCKETSORT_H_
/**
 * 桶排序：将值为i的元素放入i号桶，最后依次把桶里的元素倒出来。
 *
 * 桶排序序思路：
 * 1. 设置一个定量的数组当作空桶子。
 * 2. 寻访序列，并且把项目一个一个放到对应的桶子去。
 * 3. 对每个不是空的桶子进行排序。
 * 4. 从不是空的桶子里把项目再放回原来的序列中。
 *
 * 假设数据分布在[0，100)之间，每个桶内部用链表表示，在数据入桶的同时插入排序，然后把各个桶中的数据合并。
 * */

#include <iterator>
#include <iostream>
#include <vector>
using std::vector;

namespace Sort
{
    const int BUCKET_NUM = 10;

    struct ListNode
    {
        explicit ListNode(int i = 0) : mData(i), mNext(NULL) {}
        ListNode *mNext;
        int mData;
    };
    class BucketSort
    {
    private:
        /* data */
        ListNode *insert(ListNode *head, int val);

        ListNode *Merge(ListNode *head1, ListNode *head2);

    public:
        void BucketSort_(int n, int arr[]);
    };

} // namespace Sort

#endif // _BUCKETSORT_H_