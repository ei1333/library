#pragma once

#include <algorithm>
#include <cassert>
#include <deque>
#include <numeric>
#include <utility>
#include <vector>

template <typename T, typename Weight = long long>
struct RangeWeightedLongestIncreasingSubsequence {
 private:
  struct Witness {
    Weight weight;
    int left, right;
  };

  struct Node {
    Weight last;
    int left, right, suffix;
  };

  // Delay copying a function root until the view is retained in the result.
  struct View {
    int root, suffix;
  };

  int n;
  // Segmented storage avoids reallocating and copying the entire node pool.
  std::deque<Witness> witnesses;
  std::deque<Node> nodes;
  std::vector<int> roots;

  int concatenate(int left, int right) {
    if (left == 0) return right;
    if (right == 0) return left;
    witnesses.push_back(
        {witnesses[left].weight + witnesses[right].weight, left, right});
    return (int)witnesses.size() - 1;
  }

  int append(int root, int suffix) {
    if (suffix == 0) return root;
    // Copy the root to keep every saved version immutable.
    Node node = nodes[root];
    node.last = node.last + witnesses[suffix].weight;
    node.suffix = concatenate(node.suffix, suffix);
    nodes.push_back(node);
    return (int)nodes.size() - 1;
  }

  Weight last(View view) const {
    return nodes[view.root].last + witnesses[view.suffix].weight;
  }

  int materialize(View view) { return append(view.root, view.suffix); }

  std::pair<View, View> children(View view) {
    Node node = nodes[view.root];
    int suffix = concatenate(node.suffix, view.suffix);
    return {{node.left, suffix}, {node.right, suffix}};
  }

  int join(int left, int right) {
    if (left == 0 && right == 0) return 0;
    nodes.push_back({nodes[right].last, left, right, 0});
    return (int)nodes.size() - 1;
  }

  int prefix_append(View view, int end, int suffix, int left, int right) {
    if (end <= left) return materialize(view);
    if (right <= end) {
      return append(view.root, concatenate(view.suffix, suffix));
    }
    auto [a, b] = children(view);
    int mid = left + (right - left) / 2;
    if (end <= mid) {
      return join(prefix_append(a, end, suffix, left, mid), materialize(b));
    }
    int updated = append(a.root, concatenate(a.suffix, suffix));
    return join(updated, prefix_append(b, end, suffix, mid, right));
  }

  // f's endpoint values precede g's. The strict comparison g > f holds
  // on a prefix, so only the half containing its boundary needs recursion.
  View merge_view(View f, View g, int left, int right) {
    if ((f.root == g.root && f.suffix == g.suffix) ||
        (g.root == 0 && g.suffix == 0)) {
      return f;
    }
    if ((f.root == 0 && f.suffix == 0) || last(f) < last(g)) {
      return g;
    }
    if (left + 1 == right) return f;
    // Equal children mean the two functions differ only by a constant suffix
    // weight. This also stops at constant intervals, without expanding them.
    if (nodes[f.root].left == nodes[g.root].left &&
        nodes[f.root].right == nodes[g.root].right) {
      return f;
    }
    auto [fl, fr] = children(f);
    auto [gl, gr] = children(g);
    int mid = left + (right - left) / 2;
    // Reuse the original view when both halves select the same input.
    if (last(fl) < last(gl)) {
      View result = merge_view(fr, gr, mid, right);
      if (result.root == gr.root && result.suffix == gr.suffix) return g;
      return {join(materialize(gl), materialize(result)), 0};
    }
    View result = merge_view(fl, gl, left, mid);
    if (result.root == fl.root && result.suffix == fl.suffix) return f;
    return {join(materialize(result), materialize(fr)), 0};
  }

  int merge(View f, View g, int left, int right) {
    return materialize(merge_view(f, g, left, right));
  }

 public:
  RangeWeightedLongestIncreasingSubsequence(const std::vector<T>& a,
                                            const std::vector<Weight>& w)
      : n((int)a.size()), roots(n + 1, 0) {
    assert(a.size() == w.size());
    // Handle zero represents an empty witness / an all-zero function on any
    // interval. Passing interval bounds preserves the common subdivision.
    witnesses.push_back({Weight{}, 0, 0});
    nodes.push_back({Weight{}, 0, 0, 0});
    if (n == 0) return;

    std::vector<int> order(n), rank(n);
    std::iota(order.begin(), order.end(), 0);
    std::sort(order.begin(), order.end(), [&](int i, int j) {
      if (a[i] < a[j]) return true;
      if (a[j] < a[i]) return false;
      // Equal values cannot extend a strictly increasing sequence.
      return i > j;
    });
    for (int i = 0; i < n; ++i) rank[order[i]] = i;

    int size = 1;
    while (size < n) size <<= 1;
    std::vector<int> outer(2 * size, 0), latest(2 * size, -1);
    for (int i = 0; i < n; ++i) {
      assert(Weight{} < w[i]);
      int predecessor = 0, predecessor_latest = -1;
      // Canonical intervals are visited from right to left; prepend each
      // lower-value envelope to keep merge arguments in value order.
      for (int k = size + rank[i]; k > 1; k >>= 1) {
        if (k & 1) {
          // A later endpoint in the higher-value set can extend every
          // lower-value witness, so that envelope already dominates.
          if (predecessor_latest < latest[k - 1]) {
            predecessor = merge({outer[k - 1], 0}, {predecessor, 0}, 0, n);
            predecessor_latest = latest[k - 1];
          }
        }
      }
      witnesses.push_back({w[i], 0, i});
      int endpoint = prefix_append({predecessor, 0}, i + 1,
                                   (int)witnesses.size() - 1, 0, n);
      int k = size + rank[i];
      outer[k] = endpoint;
      latest[k] = i;
      while (k > 1) {
        if (k & 1) {
          // The newest endpoint is in the right set. Every left-set witness
          // can append it, so the right envelope dominates the left envelope.
          outer[k >> 1] = outer[k];
        } else {
          outer[k >> 1] = merge({outer[k], 0}, {outer[k + 1], 0}, 0, n);
        }
        k >>= 1;
        latest[k] = i;
      }
      roots[i + 1] = outer[1];
    }
  }

  explicit RangeWeightedLongestIncreasingSubsequence(const std::vector<T>& a)
      : RangeWeightedLongestIncreasingSubsequence(
            a, std::vector<Weight>(a.size(), Weight{1})) {}

  Weight prod(int l, int r) const {
    assert(0 <= l && l <= r && r <= n);
    Weight result{};
    if (l == r) return result;
    int root = roots[r], left = 0, right = n;
    while (root != 0) {
      const Node& node = nodes[root];
      result = result + witnesses[node.suffix].weight;
      if (left + 1 == right) break;
      int mid = left + (right - left) / 2;
      if (l < mid) {
        root = node.left;
        right = mid;
      } else {
        root = node.right;
        left = mid;
      }
    }
    return result;
  }

  std::vector<int> restore(int l, int r) const {
    assert(0 <= l && l <= r && r <= n);
    std::vector<int> result, pending;
    if (l == r) return result;
    int root = roots[r], left = 0, right = n;
    while (root != 0) {
      const Node& node = nodes[root];
      if (node.suffix != 0) pending.push_back(node.suffix);
      if (left + 1 == right) break;
      int mid = left + (right - left) / 2;
      if (l < mid) {
        root = node.left;
        right = mid;
      } else {
        root = node.right;
        left = mid;
      }
    }
    // Expand suffixes from leaf to root, each concatenation left to right.
    // Witness trees can have linear depth, so expansion must be iterative.
    while (!pending.empty()) {
      int id = pending.back();
      pending.pop_back();
      const Witness& witness = witnesses[id];
      if (witness.left == 0) {
        result.push_back(witness.right);
      } else {
        pending.push_back(witness.right);
        pending.push_back(witness.left);
      }
    }
    return result;
  }
};
