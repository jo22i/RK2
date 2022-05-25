# Рубежный контроль № 2 по предмету "Технологии и методы программирования"

## Выполнил: Мельников Егор группа ИУ8-22

## Вариант № 3

### Задание

1. Реализовать алгоритм сортировки (в данном варианте: Быстрая сортировка)
2. Сделать файл сборки CMakeLists.txt для автоматизированной сборки алгоритма
3. Провести тесты, используя GTest.
4. Использовать возможности GitHub Actions для автоматической сборки и проверки алгоритма.

### Решение

1. Пишем программу, реализующую быстрый алгоритм сортировки.

```cpp
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
```

2. Пишем сборочный CMakeLists.txt для этой программы

```cmake
cmake_minimum_required(VERSION 3.22)

project(QuickSort)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(QuickSort STATIC QuickSort.cpp QuickSort.h)
```

3. Пишем тесты для GTest

```cpp
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
    std::vector<int> sample{1, 9, 9, 9, 9, 9, 9, 9};
    
    QuickSort(vec, 0, vec.size()-1);
    
    ASSERT_EQ(vec, sample);
}
```

4. Пишем сборочный файл CMakeLists.txt для полной сборки проекта, его тестов и проверки с помощью сервиса *Coveralls.io*.

```cmake
cmake_minimum_required(VERSION 3.4)

SET(COVERAGE OFF CACHE BOOL "Coverage")
SET(CMAKE_CXX_COMPILER "/usr/bin/g++")

project(TestRunning)

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/third-party/gtest" "gtest")

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/QuickSort)

add_executable(RunTest ${CMAKE_CURRENT_SOURCE_DIR}/tests/test.cpp)

if (COVERAGE)
    target_compile_options(RunTest PRIVATE --coverage)
    target_link_libraries(RunTest PRIVATE --coverage)
endif()

target_include_directories(RunTest PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/QuickSort)

target_link_libraries(RunTest PRIVATE gtest gtest_main gmock_main QuickSort)
```

5. Пишем .yml файл для автоматической сборки, тестов и проверки покрытия тестов с помощью Github Actions.

```yml
name: RK2_test
on:
  push:
  
jobs:
  Build:
      runs-on: ubuntu-latest
      steps:
        - uses: actions/checkout@v3
        - name: build bubble_sort
          shell: bash
          run: |
            git submodule update --init
            cd QuickSort   
            cmake -H. -B_build
            cmake --build _build
          
  CovTest:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v3
      
      - name: update
        run:  |
          git submodule update --init
          sudo apt install lcov
          sudo apt install g++-7
      
      - name: test
        shell: bash
        run: |
          mkdir _build && cd _build
          CXX=/usr/bin/g++-7 cmake -DCOVERAGE=1 ..
          cmake --build .
          ./RunTest
          lcov -t "bubble_sort" -o lcov.info -c -d .
          lcov --remove lcov.info '/home/runner/work/RK_2/RK_2/third-party/gtest/*' -o lcov.info ###
          lcov --remove lcov.info '/usr/include/*' -o lcov.info
          
      - name: CovBeg
        uses: coverallsapp/github-action@master
        with:
          github-token: ${{ secrets.github_token }}
          parallel: true
          path-to-lcov: ./_build/lcov.info
          coveralls-endpoint: https://coveralls.io
          
      - name: CovFin
        uses: coverallsapp/github-action@master
        with:
         github-token: ${{ secrets.github_token }}
         parallel-finished: true
```
