/*
 * @FilePath     : \LearnGit-CMake\CMakeProject-2\sort\CountSort.cpp
 * @Date         : 2024-05-16 08:49:07
 * @author       : foreverferrysun
 * @LastEditTime : 2024-05-16 09:07:05
 * @LastEditors  : foreverferrysun
 * @FileDescription:  
 */
#include "CountSort.h"
namespace Sort
{ // 计数排序
	void CountSort::CountSort_(vector<int> &vecRaw, vector<int> &vecObj)
	{
		// 确保待排序容器非空
		if (vecRaw.size() == 0)
			return;

		// 使用 vecRaw 的最大值 + 1 作为计数容器 countVec 的大小
		int vecCountLength = (*max_element(begin(vecRaw), end(vecRaw))) + 1;
		vector<int> vecCount(vecCountLength, 0);

		// 统计每个键值出现的次数
		for (int i = 0; i < vecRaw.size(); i++)
			vecCount[vecRaw[i]]++;

		// 后面的键值出现的位置为前面所有键值出现的次数之和
		for (int i = 1; i < vecCountLength; i++)
			vecCount[i] += vecCount[i - 1];

		// 将键值放到目标位置
		for (int i = vecRaw.size(); i > 0; i--) // 此处逆序是为了保持相同键值的稳定性
			vecObj[--vecCount[vecRaw[i - 1]]] = vecRaw[i - 1];
	}
}
