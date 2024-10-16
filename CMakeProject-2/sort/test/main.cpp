/*
 * @FilePath     : \LearnGit-CMake\CMakeProject-2\main.cpp
 * @Date         : 2024-05-15 20:23:15
 * @author       : foreverferrysun
 * @LastEditTime : 2024-10-16 16:27:35
 * @LastEditors  : foreverferrysun
 * @FileDescription:
 */
// 排序算法
// #include <iostream>
// #include "sort/BucketSort.h"
// #include "sort/CountSort.h"
// #include "sort/QuickSort.h"
// #include "sort/SelectionSort.h"
// using namespace Sort;
// int main()
// {
//     vector<int> vecRaw = {0, 5, 7, 9, 6, 3, 4, 5, 2, 8, 6, 9, 2, 1};
//     vector<int> vecObj;

//     int arr[14] = {0, 5, 7, 9, 6, 3, 4, 5, 2, 8, 6, 9, 2, 1};

//     BucketSort bucketsort;
//     bucketsort.BucketSort_(14, arr);
//     cout << "BucketSort:" << endl;
//     for (int i = 0; i < 14; i++)
//         cout << arr[i] << "  ";
//     cout << endl;

//     CountSort countsort;
//     countsort.CountSort_(vecRaw, vecObj);
//     cout << "CountSort:" << endl;
//     for (int i = 0; i < vecObj.size(); i++)
//         cout << vecObj[i] << "  ";
//     cout << endl;

//     QuickSort quicksort;
//     quicksort.QuickSort_(vecRaw, 0, static_cast<int>(vecRaw.size()));
//     cout << "QuickSort:" << endl;
//     for (int i = 0; i < vecRaw.size(); ++i)
//         cout << vecRaw[i] << "  ";
//     cout << endl;

//     SelectionSort selectionsort;
//     selectionsort.SelectionSort_(vecRaw);
//     cout << "SelectionSort:" << endl;
//     for (int i = 0; i < vecRaw.size(); ++i)
//         cout << vecRaw[i] << "  ";
//     cout << endl;

//     return 0;
// }

// // 查找算法
// #include <iostream>
// #include "search/BinarySearch.h"
// #include "search/InsertionSearch.h"
// #include "search/SequentialSearch.h"
// using namespace Search;
// int main()
// {
//     // 有序序列
//     vector<int> vecRaw = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
//     int arr[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
//     // vector<int> vecRaw = {0, 5, 7, 9, 6, 3, 4, 5, 2, 8, 6, 9, 2, 1};
//     // int arr[14] = {0, 5, 7, 9, 6, 3, 4, 5, 2, 8, 6, 9, 2, 1};

//     BinarySearch binarysearch;
//     int index = binarysearch.BinarySearch_(vecRaw, 5, 0, vecRaw.size());
//     cout << "BinarySearch:" << endl;
//     cout << "index:" << index << endl;

//     InsertionSearch insertionsort;
//     index=insertionsort.InsertionSearch_(arr, 5, 0, 14);
//     cout << "InsertionSearch:" << endl;
//     cout << "index:" << index << endl;

//     SequentialSearch sequentialsearch;
//     index = sequentialsearch.SequentialSearch_(vecRaw, 5);
//     cout << "SequentialSearch:" << endl;
//     cout << "index:" << index << endl;

//     return 0;
// }
