#pragma once

// Minimum heap.

#include <functional>
#include <vector>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/strings/str_cat.h"

namespace container {
  
template <class KeyT, class ValueT, class ComparatorT>
class Heap {
 public:
  struct KeyValue {
    KeyT key;
    ValueT value;
  };  // struct KeyValue

  Heap(ComparatorT comparator = std::less<KeyT>()) : size_(0), comparator_(comparator) {}

  bool IsEmpty() const {
    return size_ == 0;
  }

  const KeyValue& PeekMin() const {
    CHECK(!this->IsEmpty());
    return nodes_[0];
  }

  void Insert(const KeyT& key, const ValueT& value) {
    if (static_cast<int>(this->nodes_.size()) <= this->size_) {
      this->nodes_.push_back({.key = key, .value = value});
    } else {
      this->nodes_[this->size_].key = key;
      this->nodes_[this->size_].value = value;
    }
    ++(this->size_);
    this->HeapifyUp(this->size_ - 1);  
  }

  void RemoveMin() {
    CHECK(!this->IsEmpty());
    --(this->size_);
    this->nodes_[0] = this->nodes_[size_];
    this->HeapifyDown(0);  
  }

  std::string Display() const {
    std::string buffer;

    absl::StrAppend(&buffer, "BEGIN: Heap");
    int level = 0;
    int level_begin = 0;
    for (int i = 0; i < this->size_; ++i) {
      if (i == level_begin) {
        absl::StrAppend(&buffer, "\n", level, ":");
        level_begin += (0x1 << level);
        ++level;
      }
      absl::StrAppend(&buffer, " ", this->nodes_[i].key);
    }
    absl::StrAppend(&buffer, "\nEND  : Heap\n");

    return buffer;
  }
  
 private:
  void HeapifyUp(int child_index) {
    if (child_index == 0) {
      // Root node.
      return;
    }
    const int parent_index = this->GetParent(child_index);
    if (this->comparator_(this->nodes_[child_index].key, this->nodes_[parent_index].key)) {
      // The child key is less than the parent key.
      std::swap(this->nodes_[child_index], this->nodes_[parent_index]);
      this->HeapifyUp(parent_index);
    }    
  }

  void HeapifyDown(int parent_index) {
    if (this->size_ <= parent_index) {
      // Below the leaf nodes.
      return;
    }

    int min_child_index = this->GetLeftChild(parent_index);
    if (this->size_ <= min_child_index) {
      // Leaf node.
      return;
    }
    const int sibling_index = min_child_index + 1;
    if (sibling_index < this->size_) {
      if (this->comparator_(this->nodes_[sibling_index].key, this->nodes_[min_child_index].key)) {
        min_child_index = sibling_index;
      }
    }
    
    if (this->comparator_(this->nodes_[min_child_index].key, this->nodes_[parent_index].key)) {
      // The child key is less than the parent key.
      std::swap(this->nodes_[parent_index], this->nodes_[min_child_index]);
      this->HeapifyDown(min_child_index);
    }    
  }

  int GetParent(int child_index) const {
    return (child_index - 1) >> 1;
  }

  int GetLeftChild(int parent_index) const {
    return (parent_index << 1) + 1;
  }

  int GetRightChild(int parent_index) const {
    return this->GetLeftChild(parent_index) + 1;
  }

  int size_;
  ComparatorT comparator_;
  std::vector<KeyValue> nodes_;
}; // class Heap

}  // namespace container
