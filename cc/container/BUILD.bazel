package(default_visibility = ["//visibility:public"])

cc_library(
  name = "heap",
  hdrs = [
    "heap.h",
  ],
  deps = [
    "@abseil-cpp//absl/log",
    "@abseil-cpp//absl/log:check",
    "@abseil-cpp//absl/strings",
  ],
)

cc_library(
  name = "sort",
  hdrs = [
    "heap_sort_impl.h",
    "lower_bound_impl.h",
    "merge_sort_impl.h",
    "quick_sort_impl.h",
    "sort.h",
  ],
  deps = [
    ":heap",
  ],
)

cc_test(
  name = "sort_test",
  srcs = [
    ":tests/sort_test.cc",
  ],
  deps = [
    ":sort",
    "@com_google_googletest//:gtest_main",
  ],
)
