#include "../segment-tree/lazy-segment-tree.hpp"

/**
 * @brief Permutation Tree(順列木)
 * 
 * @see https://codeforces.com/blog/entry/78898
 */
struct PermutationTree {
public:
  enum NodeType {
    JOIN_ASC,
    JOIN_DESC,
    LEAF,
    CUT
  };

  struct Node {
    NodeType type;
    int l, r; // [l, r)
    int min_v, max_v; // [min_v, max_v)
    vector< Node * > ch;

    size_t size() const { return r - l; }

    bool is_join() const { return type == JOIN_ASC or type == JOIN_DESC; };

    bool is_leaf() const { return type == LEAF; }

    bool is_cut() const { return type == CUT; }
  };

  using NP = Node *;

  PermutationTree() = default;

private:
  static void add_child(NP t, NP c) {
    t->ch.emplace_back(c);
    t->l = min(t->l, c->l);
    t->r = max(t->r, c->r);
    t->min_v = min(t->min_v, c->min_v);
    t->max_v = max(t->max_v, c->max_v);
  }

public:
  static NP build(vector< int > &A) {
    int n = (int) A.size();

    vector< int > desc{-1};
    vector< int > asc{-1};
    vector< NP > st;

    auto f = [](int a, int b) { return min(a, b); };
    auto g = [](int a, int b) { return a + b; };
    constexpr int lim = (1 << 30) - 1;
    auto seg = get_lazy_segment_tree(vector< int >(n), f, g, g, lim, 0);

    for(int i = 0; i < n; i++) {
      while(~desc.back() and A[i] > A[desc.back()]) {
        seg.apply(desc[desc.size() - 2] + 1, desc.back() + 1, A[i] - A[desc.back()]);
        desc.pop_back();
      }
      while(~asc.back() and A[i] < A[asc.back()]) {
        seg.apply(asc[asc.size() - 2] + 1, asc.back() + 1, A[asc.back()] - A[i]);
        asc.pop_back();
      }
      desc.emplace_back(i);
      asc.emplace_back(i);

      NP t = new Node{LEAF, i, i + 1, A[i], A[i] + 1, {}};
      for(;;) {
        NodeType type = CUT;
        if(not st.empty()) {
          if(st.back()->max_v == t->min_v) {
            type = JOIN_ASC;
          } else if(t->max_v == st.back()->min_v) {
            type = JOIN_DESC;
          }
        }
        if(type != CUT) {
          NP r = st.back();
          if(type != r->type) {
            r = new Node{type, r->l, r->r, r->min_v, r->max_v, {r}};
          }
          add_child(r, t);
          st.pop_back();
          t = r;
        } else if(seg.prod(0, i + 1 - (int) t->size()) == 0) {
          t = new Node{CUT, t->l, t->r, t->min_v, t->max_v, {t}};
          do {
            add_child(t, st.back());
            st.pop_back();
          } while(t->max_v - t->min_v != t->size());
          reverse(begin(t->ch), end(t->ch));
        } else {
          break;
        }
      }
      st.emplace_back(t);
      seg.apply(0, i + 1, -1);
    }
    return st[0];
  }
};
