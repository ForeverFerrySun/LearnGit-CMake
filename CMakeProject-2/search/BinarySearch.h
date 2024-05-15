#ifndef BINARYSEARCH_H
#define BINARYSEARCH_H
// 二分查找（折半查找）：对于已排序，若无序，需要先排序
/**
 * 二分查找：
 * 1.递归和非递归
 * 2.空间复杂度：O(logn)
 * 3.时间复杂度：O(logn)
 * 步骤：
 * 1.将数组分为左右两部分
 * 2.比较中间值与目标值，若相等，则返回中间值下标
 * 3.若中间值小于目标值，则继续在右半部分查找
 * 4.若中间值大于目标值，则继续在左半部分查找
 * 5.若中间值大于右边界，则返回-1
 * 6.若中间值小于左边界，则返回-1
*/
#include <vector>
#include <iostream>
using namespace std;
namespace Search
{
	class BinarySearch
	{
	private:
	public:
		// 非递归
		int BinarySearch_(vector<int> v, int value, int low, int high);

		// 递归
		int BinarySearch2(vector<int> v, int value, int low, int high);
	};
} // namespace Search
#endif // BINARYSEARCH_H
