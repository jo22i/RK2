#include <iostream>
#include <gtest/gtest.h>
#include "../bubble_sort/bubble_sort.h"

TEST(Sort, bubble) 
{
  double array[] = { 5, 3, 3.5, 7, 4, 9, 2, -1 };
  bubble_sort(array, sizeof(array)/sizeof(*array));
  
  ASSERT_EQ(array[0], -1);
  ASSERT_EQ(array[1], 2);
  ASSERT_EQ(array[2], 3);
  ASSERT_EQ(array[3], 3.5);
  ASSERT_EQ(array[4], 4);
  ASSERT_EQ(array[5], 5);
  ASSERT_EQ(array[6], 7);
  ASSERT_EQ(array[7], 9);
}
