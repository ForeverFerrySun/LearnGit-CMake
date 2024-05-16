/*
 * @FilePath     : \LearnGit-CMake\CMakeProject-2\search\SequentialSearch.cpp
 * @Date         : 2024-05-15 22:09:19
 * @author       : foreverferrysun
 * @LastEditTime : 2024-05-16 09:34:08
 * @LastEditors  : foreverferrysun
 * @FileDescription:
 * */
#include "SequentialSearch.h"
namespace Search
{
    // 顺序查找
    int SequentialSearch::SequentialSearch_(vector<int> &v, int k)
    {
        for (int i = 0; i < v.size(); ++i)
            if (v[i] == k)
                return i;
        return -1;
    }

    // 以下是仅执行的Sentinel搜索算法每个循环迭代中只进行一次测试，从而降低时间复杂性
    int SequentialSearch::BetterSequentialSearch(vector<int> &v, int k)
    {
        int last = v[v.size() - 1];
        v[v.size() - 1] = k;
        int i = 0;
        while (v[i] != k)
            i++;
        v[v.size() - 1] = last;
        if (i < v.size() - 1 || v[v.size() - 1] == k)
            return i;
        return -1;
    }
}