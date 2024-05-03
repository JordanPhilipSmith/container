#pragma once

// Array sorting algorithms and utilities.

#include <functional>
#include <vector>

#include "cc/container/heap.h"

namespace container {

// Finds an iterator to first element that is not less than the key (i.e. the position to insert
// the value).
// Parameters:
//   begin_iter - Beginning of the sorted array.
//   end_iter - Off the end of the sorted array.
//   key - Key to search for the position.
//   comparator - Ordering comparator (e.g. std::less).
// Returns end_iter if the key is greater than all elements.
template<class KeyT, class ComparatorT>
typename std::vector<KeyT>::const_iterator LowerBound(
    typename std::vector<KeyT>::const_iterator begin_iter,
    typename std::vector<KeyT>::const_iterator end_iter,
    const KeyT& key,
    const ComparatorT& comparator = std::less<KeyT>());

template<class KeyT, class ComparatorT>
void HeapSort(typename std::vector<KeyT>::iterator begin_iter,
              typename std::vector<KeyT>::iterator end_iter,
              const ComparatorT& comparator = std::less<KeyT>());

template<class KeyT, class ComparatorT>
void MergeSort(typename std::vector<KeyT>::iterator begin_iter,
               typename std::vector<KeyT>::iterator end_iter,
               const ComparatorT& comparator = std::less<KeyT>());

template<class KeyT, class ComparatorT>
void QuickSort(typename std::vector<KeyT>::iterator begin_iter,
               typename std::vector<KeyT>::iterator end_iter,
               const ComparatorT& comparator = std::less<KeyT>());

}  // namespace container

// Implementation.

#include "heap_sort_impl.h"
#include "lower_bound_impl.h"
#include "merge_sort_impl.h"
#include "quick_sort_impl.h"
