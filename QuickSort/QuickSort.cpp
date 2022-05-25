#include <iostream>
#include <vector>

int partition(std::vector<int>& vec, int low, int high)
{
    int pivot = vec[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {
        if (vec[j] <= pivot)
        {
            i++;
            std::swap(vec[i], vec[j]);
        }
    }
    std::swap(vec[i + 1], vec[high]);
    return (i + 1);
}

void QuickSort(std::vector<int>& vec, int low, int high)
{
    if (low < high)
    {
        int pivot = partition(vec, low, high);

        QuickSort(vec, low, pivot - 1);
        QuickSort(vec, pivot + 1, high);
    }
}
