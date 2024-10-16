/*
 * @FilePath     : \LearnGit-CMake\CMakeProject-2\search\main.cpp
 * @Date         : 2024-10-16 11:49:05
 * @author       : foreverferrysun
 * @LastEditTime : 2024-10-16 14:55:16
 * @LastEditors  : foreverferrysun
 * @FileDescription:  
 */
// 查找算法
#include <iostream>
#include "BinarySearch.h"
#include "InsertionSearch.h"
#include "SequentialSearch.h"
using namespace Search;
int main()
{
    // 有序序列
    vector<int> vecRaw = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int arr[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    // vector<int> vecRaw = {0, 5, 7, 9, 6, 3, 4, 5, 2, 8, 6, 9, 2, 1};
    // int arr[14] = {0, 5, 7, 9, 6, 3, 4, 5, 2, 8, 6, 9, 2, 1};

    BinarySearch binarysearch;
    int index = binarysearch.BinarySearch_(vecRaw, 5, 0, vecRaw.size());
    cout << "BinarySearch:" << endl;
    cout << "index:" << index << endl;

    InsertionSearch insertionsort;
    index=insertionsort.InsertionSearch_(arr, 5, 0, 14);
    cout << "InsertionSearch:" << endl;
    cout << "index:" << index << endl;

    SequentialSearch sequentialsearch;
    index = sequentialsearch.SequentialSearch_(vecRaw, 5);
    cout << "SequentialSearch:" << endl;
    cout << "index:" << index << endl;

    return 0;
}
