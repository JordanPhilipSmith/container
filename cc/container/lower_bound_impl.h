#pragma once

// Lower bound implementation using binary search.

#include <functional>
#include <vector>

namespace container {

template<class KeyT, class ComparatorT>
typename std::vector<KeyT>::const_iterator LowerBound(
    typename std::vector<KeyT>::const_iterator begin_iter,
    typename std::vector<KeyT>::const_iterator end_iter,
    const KeyT& key,
    const ComparatorT& comparator /* = std::less<KeyT>() */) {
  std::size_t size = end_iter - begin_iter;
  if (size < 1) {
    return end_iter;
  }
  typename std::vector<KeyT>::const_iterator left_iter = begin_iter;
  typename std::vector<KeyT>::const_iterator right_iter = end_iter;
  while (left_iter != right_iter) {
    size = right_iter - left_iter;
    typename std::vector<KeyT>::const_iterator mid_iter = left_iter + (size / 2);
    if (comparator(*mid_iter, key)) {
      left_iter = mid_iter + 1;
    } else {
      right_iter = mid_iter;
    }
  }
  return left_iter;
}

}  // namespace container
