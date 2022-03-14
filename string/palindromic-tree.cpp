/**
 * @brief Palindromic Tree(回文木)
 * @see https://math314.hateblo.jp/entry/2016/12/19/005919
 * @docs docs/palindromic-tree.md
 */
template< typename T = char >
struct PalindromicTree {
public:
  struct Node {
    map< T, int > link; // 子のidx
    int suffix_link; // 最長回文接尾辞のidx
    int len; // 対応する回文の長さ
    vector< int > idx; // 対応する回文を最長回文接尾辞とするidx

    Node() = default;

    Node(int suf, int len) : suffix_link(suf), len(len) {}
  };

  vector< Node > ns;
  int ptr;
  vector< T > vs;

private:
  int find_prev_palindrome(int cur) const {
    int pos = (int) vs.size() - 1;
    for(;;) {
      int rev = pos - 1 - ns[cur].len;
      if(rev >= 0 and vs[rev] == vs.back()) break;
      cur = ns[cur].suffix_link;
    }
    return cur;
  }

  bool output_dfs(int v, int id, vector< T > &ret) const {
    if(v == id) return true;
    for(auto &nxt: ns[v].link) {
      if(output_dfs(nxt.second, id, ret)) {
        ret.emplace_back(nxt.first);
        return true;
      }
    }
    return false;
  }

public:
  PalindromicTree() : ptr(0) {
    ns.emplace_back(0, -1); // 長さ -1
    ns.emplace_back(0, 0); // 長さ 0
  }

  PalindromicTree(const string &S) : PalindromicTree() {
    add(S);
  }

  int add(const T &x) {
    int idx = (int) vs.size();
    vs.emplace_back(x);
    int cur = find_prev_palindrome(ptr);
    auto res = ns[cur].link.insert(make_pair(x, (int) ns.size()));
    ptr = res.first->second;
    if(res.second) {
      ns.emplace_back(-1, ns[cur].len + 2);
      ns.back().idx.emplace_back(idx);
      if(ns.back().len == 1) {
        ns.back().suffix_link = 1;
      } else {
        ns.back().suffix_link = ns[find_prev_palindrome(ns[cur].suffix_link)].link[x];
      }
      return ptr;
    } else {
      ns[ptr].idx.emplace_back(idx);
      return ptr;
    }
  }

  void add(const string &s) {
    for(auto &x: s) add(x);
  }

  vector< int > build_frequency() const {
    vector< int > ret(ns.size());
    for(int i = (int) ns.size() - 1; i > 0; i--) {
      ret[i] += (int) ns[i].idx.size();
      ret[ns[i].suffix_link] += ret[i];
    }
    return ret;
  }

  vector< T > output(int idx) const {
    if(idx == 0) return {-1};
    if(idx == 1) return {0};
    vector< T > ret;
    output_dfs(0, idx, ret);
    output_dfs(1, idx, ret);
    int start = (int) ret.size() - 1;
    if(ns[idx].len & 1) --start;
    for(int i = start; i >= 0; i--) {
      ret.emplace_back(ret[i]);
    }
    return ret;
  }

  int size() const {
    return (int) ns.size();
  }

  Node &operator[](int idx) {
    return ns[idx];
  }
};
