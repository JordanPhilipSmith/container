#include "cc/container/sort.h"

#include <algorithm>
#include <functional>
#include <vector>

#include "gtest/gtest.h"

namespace container {
namespace {

// Make a sequence counting by delta (e.g. {size = 3, delta = 2} => {0, 2, 4}).
// Parameters:
//   size - Number of elements.
//   delta - Delta between elements.
std::vector<int> MakeCountBy(int size, int delta = 1) {
  std::vector<int> v(size);
  int value = 0;
  for (int i = 0; i < size; ++i, value += delta) {
    v[i] = value;
  }
  return v;
}
  
// Make a count down sequence (e.g. {size = 3} => {2, 1, 0}).
// Parameters:
//   size - Number of elements.
std::vector<int> MakeCountDown(int size) {
  std::vector<int> v(size);
  for (int i = 0; i < size; ++i) {
    v[i] = size - 1 + i;
  }
  return v;
}
  
TEST(LowerBoundTest, Normal) {
  const std::vector<int> sorted = MakeCountBy(10, 2);

  for (int i = -1; i < 20; ++i) {
    typename std::vector<int>::const_iterator iter =
        LowerBound<int, std::less<int>>(sorted.cbegin(), sorted.cend(), i, std::less<int>());

    typename std::vector<int>::const_iterator expected_iter =
      std::lower_bound(sorted.cbegin(), sorted.cend(), i);
    EXPECT_EQ(iter, expected_iter) << "i = " << i;
  }
}
  
TEST(HeapSortTest, Normal) {
  const std::vector<int> unsorted = MakeCountDown(10);

  std::vector<int> sorted = unsorted;
  HeapSort<int, std::less<int>>(sorted.begin(), sorted.end(), std::less<int>());

  std::vector<int> expected_sorted = unsorted;
  std::sort(expected_sorted.begin(), expected_sorted.end());

  EXPECT_EQ(sorted, expected_sorted);
}
  
TEST(MergeSortTest, Normal) {
  const std::vector<int> unsorted = MakeCountDown(10);

  std::vector<int> sorted = unsorted;
  MergeSort<int, std::less<int>>(sorted.begin(), sorted.end(), std::less<int>());

  std::vector<int> expected_sorted = unsorted;
  std::sort(expected_sorted.begin(), expected_sorted.end());

  EXPECT_EQ(sorted, expected_sorted);
}
  
TEST(QuickSortTest, Normal) {
  const std::vector<int> unsorted = MakeCountDown(10);

  std::vector<int> sorted = unsorted;
  QuickSort<int, std::less<int>>(sorted.begin(), sorted.end(), std::less<int>());

  std::vector<int> expected_sorted = unsorted;
  std::sort(expected_sorted.begin(), expected_sorted.end());

  EXPECT_EQ(sorted, expected_sorted);
}
  
}  // namespace
}  // namespace container
