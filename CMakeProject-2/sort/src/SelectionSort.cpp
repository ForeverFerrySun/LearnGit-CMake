#include "SelectionSort.h"
namespace Sort
{
    // 选择排序
    void SelectionSort::SelectionSort_(vector<int> &v)
    {
        int min, len = v.size();
        for (int i = 0; i < len - 1; ++i)
        {
            min = i;
            for (int j = i + 1; j < len; ++j)
            {
                if (v[j] < v[min])
                { // 标记最小的
                    min = j;
                }
            }
            if (i != min) // 交换到前面
                swap(v[i], v[min]);
        }
    }

    // 模板实现
    template <typename T>
    void SelectionSort::Selection_Sort(std::vector<T> &arr)
    {
        int len = arr.size();
        for (int i = 0; i < len - 1; i++)
        {
            int min = i;
            for (int j = i + 1; j < len; j++)
                if (arr[j] < arr[min])
                    min = j;
            if (i != min)
                std::swap(arr[i], arr[min]);
        }
    }
} // namespace Srot