#pragma once

// Quick sort implementation.

#include <functional>
#include <utility>
#include <vector>

namespace container {

template<class KeyT, class ComparatorT>
void QuickSort(typename std::vector<KeyT>::iterator begin_iter,
               typename std::vector<KeyT>::iterator end_iter,
               const ComparatorT& comparator /* = std::less<KeyT>() */) {
  std::size_t size = end_iter - begin_iter;
  if (size < 2) {
    return;
  }
  typename std::vector<KeyT>::iterator pivot_iter = end_iter - 1;
  if (size == 2) {
    if (comparator(*pivot_iter, *begin_iter)) {
      std::swap(*begin_iter, *pivot_iter);
    }
    return;
  }
  // Pick the middle element as the pivot.
  typename std::vector<KeyT>::iterator mid_iter = begin_iter + (size / 2);
  // Swap the pivot to the far right.
  std::swap(*mid_iter, *pivot_iter);
  typename std::vector<KeyT>::iterator left_iter = begin_iter;
  typename std::vector<KeyT>::iterator right_iter = pivot_iter - 1;
  while (left_iter != right_iter) {
    if (comparator(*pivot_iter, *left_iter)) {
      // Swap the element to the right side of the pivot.
      std::swap(*left_iter, *right_iter);
      --right_iter;
    } else {
      // Keep the element in the left side of the pivot.
      ++left_iter;
    }
  }
  // Test the last element and move the pivot to the splitting point.
  if (comparator(*pivot_iter, *left_iter)) {
    // The element is in the right side, so swap it with the pivot.
  } else {
    // Keep the element in the left side of the pivot, and swap the next element.
    ++left_iter;
  }
  std::swap(*left_iter, *pivot_iter);

  QuickSort<KeyT, ComparatorT>(begin_iter, left_iter, comparator);
  QuickSort<KeyT, ComparatorT>(left_iter + 1, end_iter, comparator);
}

}  // namespace container
