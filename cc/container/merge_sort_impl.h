#pragma once

// Merge sort implementation.

#include <functional>
#include <vector>

namespace container {

namespace internal {

template<class KeyT, class ComparatorT>
void MergeSortImpl(typename std::vector<KeyT>::iterator src_begin_iter,
                   typename std::vector<KeyT>::iterator src_end_iter,
                   typename std::vector<KeyT>::iterator dst_begin_iter,
                   typename std::vector<KeyT>::iterator dst_end_iter,
                   const ComparatorT& comparator) {
  std::size_t size = src_end_iter - src_begin_iter;
  if (size < 1) {
    return;
  }
  if (size == 1) {
    *dst_begin_iter = *src_begin_iter;
    return;
  }
  if (size == 2) {
    typename std::vector<KeyT>::iterator src_iter = src_begin_iter;
    ++src_iter;
    typename std::vector<KeyT>::iterator dst_iter = dst_begin_iter;
    ++dst_iter;
    if (comparator(*src_begin_iter, *src_iter)) {
      *dst_begin_iter = *src_begin_iter;
      *dst_iter = *src_iter;
    } else {
      *dst_begin_iter = *src_iter;
      *dst_iter = *src_begin_iter;
    }
    return;
  }

  std::size_t mid = size / 2;
  typename std::vector<KeyT>::iterator src_mid_iter = src_begin_iter + mid;
  typename std::vector<KeyT>::iterator dst_mid_iter = dst_begin_iter + mid;

  MergeSortImpl<KeyT, ComparatorT>(
      dst_begin_iter, dst_mid_iter, src_begin_iter, src_mid_iter, comparator);
  MergeSortImpl<KeyT, ComparatorT>(
      dst_mid_iter, dst_end_iter, src_mid_iter, src_end_iter, comparator);

  typename std::vector<KeyT>::iterator dst_iter = dst_begin_iter;
  typename std::vector<KeyT>::iterator src_left_iter = src_begin_iter;
  typename std::vector<KeyT>::iterator src_right_iter = src_mid_iter;
  while (src_left_iter != src_mid_iter && src_right_iter != src_end_iter) {
    if (comparator(*src_right_iter, *src_left_iter)) {
      *dst_iter = *src_right_iter;
      ++src_right_iter;
    } else {
      *dst_iter = *src_left_iter;
      ++src_left_iter;
    }
    ++dst_iter;
  }
  for (; src_left_iter != src_mid_iter; ++src_left_iter) {
    *dst_iter = *src_left_iter;
    ++dst_iter;
  }
  for (; src_right_iter != src_end_iter; ++src_right_iter) {
    *dst_iter = *src_right_iter;
    ++dst_iter;
  }
}

}  // namespace internal

template<class KeyT, class ComparatorT>
void MergeSort(typename std::vector<KeyT>::iterator begin_iter,
               typename std::vector<KeyT>::iterator end_iter,
               const ComparatorT& comparator /* = std::less<KeyT>() */) {
  if (begin_iter == end_iter) {
    return;
  }

  std::vector<KeyT> buffer(begin_iter, end_iter);

  internal::MergeSortImpl<KeyT, ComparatorT>(
      buffer.begin(), buffer.end(), begin_iter, end_iter, comparator);
}

}  // namespace container
