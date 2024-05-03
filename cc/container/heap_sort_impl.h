#pragma once

// Heap sort implementation.

#include <functional>
#include <vector>

#include "cc/container/heap.h"

namespace container {

template<class KeyT, class ComparatorT>
void HeapSort(typename std::vector<KeyT>::iterator begin_iter,
              typename std::vector<KeyT>::iterator end_iter,
              const ComparatorT& comparator /* = std::less<KeyT>() */) {
  Heap<KeyT, std::int8_t, ComparatorT> heap(comparator);
  for (typename std::vector<KeyT>::iterator iter = begin_iter; iter != end_iter; ++iter) {
    heap.Insert(*iter, 0);
  }
  for (typename std::vector<KeyT>::iterator iter = begin_iter; iter != end_iter; ++iter) {
    *iter = heap.PeekMin().key;
    heap.RemoveMin();
  }
}

}  // namespace container
