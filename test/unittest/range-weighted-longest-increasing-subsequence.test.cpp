// competitive-verifier: STANDALONE

#include "../../dp/range-weighted-longest-increasing-subsequence.hpp"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <limits>
#include <numeric>
#include <random>
#include <string>
#include <vector>

template <typename T, typename Weight>
void check_all_ranges(const std::vector<T>& values,
                      const std::vector<Weight>& weights) {
  const int n = (int)values.size();
  const RangeWeightedLongestIncreasingSubsequence<T, Weight> lis(values,
                                                                 weights);
  for (int left = n; left >= 0; --left) {
    Weight expected{};
    std::vector<Weight> dp(n);
    for (int right = left; right <= n; ++right) {
      if (left < right) {
        const int last = right - 1;
        Weight predecessor{};
        for (int j = left; j < last; ++j) {
          if (values[j] < values[last] && predecessor < dp[j]) {
            predecessor = dp[j];
          }
        }
        dp[last] = predecessor + weights[last];
        if (expected < dp[last]) expected = dp[last];
      }

      const auto actual = lis.prod(left, right);
      assert(!(actual < expected) && !(expected < actual));
      const auto indices = lis.restore(left, right);
      Weight total{};
      int previous = left - 1;
      for (int index : indices) {
        assert(left <= index && index < right);
        assert(previous < index);
        if (previous >= left) assert(values[previous] < values[index]);
        total = total + weights[index];
        previous = index;
      }
      assert(!(total < expected) && !(expected < total));
      assert(indices.empty() == (left == right));
    }
  }

  // Revisit early versions after querying later right endpoints.
  for (int right = n; right > 0; --right) {
    const auto indices = lis.restore(right - 1, right);
    assert((indices == std::vector<int>{right - 1}));
  }
}

void check(const std::vector<int>& values,
           const std::vector<long long>& weights) {
  check_all_ranges(values, weights);
}

struct OrderedValue {
  int value;

  friend bool operator<(const OrderedValue& a, const OrderedValue& b) {
    return a.value < b.value;
  }
};

struct ExactWeight {
  long long value;

  explicit ExactWeight(long long value = 0) : value(value) {}

  friend ExactWeight operator+(const ExactWeight& a, const ExactWeight& b) {
    return ExactWeight(a.value + b.value);
  }

  friend bool operator<(const ExactWeight& a, const ExactWeight& b) {
    return a.value < b.value;
  }
};

void check_unit_weights(const std::vector<int>& values) {
  const int n = (int)values.size();
  const RangeWeightedLongestIncreasingSubsequence<int> lis(values);
  for (int left = 0; left <= n; ++left) {
    std::vector<int> tails;
    for (int right = left; right <= n; ++right) {
      if (left < right) {
        int value = values[right - 1];
        auto it = std::lower_bound(tails.begin(), tails.end(), value);
        if (it == tails.end()) {
          tails.push_back(value);
        } else {
          *it = value;
        }
      }
      assert(lis.prod(left, right) == (long long)tails.size());
      const auto indices = lis.restore(left, right);
      assert(indices.size() == tails.size());
      for (int j = 0; j < (int)indices.size(); ++j) {
        assert(left <= indices[j] && indices[j] < right);
        if (j) {
          assert(indices[j - 1] < indices[j]);
          assert(values[indices[j - 1]] < values[indices[j]]);
        }
      }
    }
  }
}

int main() {
  check({}, {});
  check({5}, {7});
  check({1, 1}, {5, 1});
  check({1, 1}, {1, 5});
  check({7, 7, 7, 7, 7}, {3, 9, 1, 9, 2});
  check({1, 2, 3, 4, 5}, {1, 2, 3, 4, 5});
  check({5, 4, 3, 2, 1}, {1, 2, 3, 4, 5});
  check({5, 4, 3, 2, 1}, {5, 4, 3, 2, 1});
  check({0, 2, 3, 1}, {1, 1, 1, 1});
  check({3, 1, 2}, {100, 1, 1});
  check({3, 1, 2, 3, 2, 4, 1}, {2, 1, 5, 2, 10, 1, 7});
  check({2, 0, 3, 1, 4, 2, 5, 3, 6}, {1, 9, 2, 8, 3, 7, 4, 6, 5});
  check({std::numeric_limits<int>::max(), std::numeric_limits<int>::min(),
         std::numeric_limits<int>::min(), 0, std::numeric_limits<int>::max()},
        {1, 2, 3, 4, 5});
  check({0, 1, 2, 3, 4},
        std::vector<long long>(5, std::numeric_limits<long long>::max() / 5));
  check_all_ranges<int, std::uint64_t>(
      {2, 0, 1, 3},
      {4000000000ULL, 3000000000ULL, 2000000000ULL, 1000000000ULL});
  check_all_ranges<std::string, long long>({"b", "a", "b", "aa", "c"},
                                           {2, 4, 7, 6, 1});
  check_all_ranges<OrderedValue, ExactWeight>(
      {{2}, {1}, {1}, {3}, {0}, {4}},
      {ExactWeight(3), ExactWeight(4), ExactWeight(2), ExactWeight(5),
       ExactWeight(8), ExactWeight(1)});

  // Exhaust all sequences of length at most five over three values and two
  // positive weights, including duplicates and equal optimum scores.
  for (int n = 0, count = 1; n <= 5; ++n, count *= 6) {
    for (int code = 0; code < count; ++code) {
      std::vector<int> values(n);
      std::vector<long long> weights(n);
      int remaining = code;
      for (int i = 0; i < n; ++i) {
        values[i] = remaining % 3;
        weights[i] = remaining / 3 % 2 + 1;
        remaining /= 6;
      }
      check(values, weights);
    }
  }

  std::mt19937 random(123456789);
  for (int n = 0; n <= 40; ++n) {
    for (int trial = 0; trial < 10; ++trial) {
      std::vector<int> values(n);
      std::vector<long long> weights(n);
      for (int i = 0; i < n; ++i) {
        values[i] = (int)(random() % 17) - 8;
        weights[i] = random() % 1000000000 + 1;
      }
      check(values, weights);
      if (trial == 0) check_unit_weights(values);
    }
  }

  // A long optimum exercises witness expansion without recursive traversal of
  // a potentially very deep concatenation tree.
  const int n = 16384;
  std::vector<int> increasing(n);
  std::iota(increasing.begin(), increasing.end(), 0);
  const RangeWeightedLongestIncreasingSubsequence<int> lis(increasing);
  for (int left : {0, 1, 123, n / 2, n - 1, n}) {
    assert(lis.prod(left, n) == n - left);
    const auto indices = lis.restore(left, n);
    assert((int)indices.size() == n - left);
    for (int i = 0; i < (int)indices.size(); ++i)
      assert(indices[i] == left + i);
  }
  assert(lis.prod(3, 113) == 110);
  const auto early = lis.restore(3, 113);
  assert(early.front() == 3 && early.back() == 112 && early.size() == 110);
}
