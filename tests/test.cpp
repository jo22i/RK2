#include <iostream>
#include <gtest/gtest.h>
#include "../QuickSort/QuickSort.h"

TEST(QuickSort, NormalVector) 
{
    std::vector<int> vec{5, 1, 3, 2, 4};
    std::vector<int> sample{1, 2, 3, 4, 5};
    
    QuickSort(vec, 0, vec.size()-1);
    
    ASSERT_EQ(vec, sample);
}

TEST(QuickSort, NullVector) 
{
    std::vector<int> vec{};
    std::vector<int> sample{};
    
    QuickSort(vec, 0, vec.size()-1);
    
    ASSERT_EQ(vec, sample);
}

TEST(QuickSort, JustOne) 
{
    std::vector<int> vec{9, 9, 9, 9, 9, 9, 9, 1};
    std::vector<int> sample{1, 9, 9, 9, 9, 9, 9, 9;
    
    QuickSort(vec, 0, vec.size()-1);
    
    ASSERT_EQ(vec, sample);
}
