---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: structure/trie/binary-trie.hpp
    title: Binary-Trie
  - icon: ':heavy_check_mark:'
    path: template/template.hpp
    title: template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/set_xor_min
    links:
    - https://judge.yosupo.jp/problem/set_xor_min
  bundledCode: "#line 1 \"test/verify/yosupo-set-xor-min.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/set_xor_min\"\n\n#line 1 \"template/template.hpp\"\
    \n#include<bits/stdc++.h>\n\nusing namespace std;\n\nusing int64 = long long;\n\
    const int mod = 1e9 + 7;\n\nconst int64 infll = (1LL << 62) - 1;\nconst int inf\
    \ = (1 << 30) - 1;\n\nstruct IoSetup {\n  IoSetup() {\n    cin.tie(nullptr);\n\
    \    ios::sync_with_stdio(false);\n    cout << fixed << setprecision(10);\n  \
    \  cerr << fixed << setprecision(10);\n  }\n} iosetup;\n\ntemplate< typename T1,\
    \ typename T2 >\nostream &operator<<(ostream &os, const pair< T1, T2 >& p) {\n\
    \  os << p.first << \" \" << p.second;\n  return os;\n}\n\ntemplate< typename\
    \ T1, typename T2 >\nistream &operator>>(istream &is, pair< T1, T2 > &p) {\n \
    \ is >> p.first >> p.second;\n  return is;\n}\n\ntemplate< typename T >\nostream\
    \ &operator<<(ostream &os, const vector< T > &v) {\n  for(int i = 0; i < (int)\
    \ v.size(); i++) {\n    os << v[i] << (i + 1 != v.size() ? \" \" : \"\");\n  }\n\
    \  return os;\n}\n\ntemplate< typename T >\nistream &operator>>(istream &is, vector<\
    \ T > &v) {\n  for(T &in : v) is >> in;\n  return is;\n}\n\ntemplate< typename\
    \ T1, typename T2 >\ninline bool chmax(T1 &a, T2 b) { return a < b && (a = b,\
    \ true); }\n\ntemplate< typename T1, typename T2 >\ninline bool chmin(T1 &a, T2\
    \ b) { return a > b && (a = b, true); }\n\ntemplate< typename T = int64 >\nvector<\
    \ T > make_v(size_t a) {\n  return vector< T >(a);\n}\n\ntemplate< typename T,\
    \ typename... Ts >\nauto make_v(size_t a, Ts... ts) {\n  return vector< decltype(make_v<\
    \ T >(ts...)) >(a, make_v< T >(ts...));\n}\n\ntemplate< typename T, typename V\
    \ >\ntypename enable_if< is_class< T >::value == 0 >::type fill_v(T &t, const\
    \ V &v) {\n  t = v;\n}\n\ntemplate< typename T, typename V >\ntypename enable_if<\
    \ is_class< T >::value != 0 >::type fill_v(T &t, const V &v) {\n  for(auto &e\
    \ : t) fill_v(e, v);\n}\n\ntemplate< typename F >\nstruct FixPoint : F {\n  explicit\
    \ FixPoint(F &&f) : F(forward< F >(f)) {}\n\n  template< typename... Args >\n\
    \  decltype(auto) operator()(Args &&... args) const {\n    return F::operator()(*this,\
    \ forward< Args >(args)...);\n  }\n};\n \ntemplate< typename F >\ninline decltype(auto)\
    \ MFP(F &&f) {\n  return FixPoint< F >{forward< F >(f)};\n}\n#line 4 \"test/verify/yosupo-set-xor-min.test.cpp\"\
    \n\n#line 1 \"structure/trie/binary-trie.hpp\"\n/**\n * @brief Binary-Trie\n *\
    \ @docs docs/binary-trie.md\n */\ntemplate< typename T, int MAX_LOG, typename\
    \ D = int >\nstruct BinaryTrie {\npublic:\n  struct Node {\n    Node *nxt[2];\n\
    \    D exist;\n    vector< int > accept;\n\n    Node() : nxt{nullptr, nullptr},\
    \ exist(0) {}\n  };\n\n  Node *root;\n\n  explicit BinaryTrie() : root(new Node())\
    \ {}\n\n  explicit BinaryTrie(Node *root) : root(root) {}\n\n  void add(const\
    \ T &bit, int idx = -1, D delta = 1, T xor_val = 0) {\n    root = add(root, bit,\
    \ idx, MAX_LOG, delta, xor_val);\n  }\n\n  void erase(const T &bit, T xor_val\
    \ = 0) {\n    add(bit, -1, -1, xor_val);\n  }\n\n  Node *find(const T &bit, T\
    \ xor_val = 0) {\n    return find(root, bit, MAX_LOG, xor_val);\n  }\n\n  D count(const\
    \ T &bit, T xor_val = 0) {\n    auto node = find(bit, xor_val);\n    return node\
    \ ? node->exist : 0;\n  }\n\n  pair< T, Node * > min_element(T xor_val = 0) {\n\
    \    assert(root->exist > 0);\n    return kth_element(0, xor_val);\n  }\n\n  pair<\
    \ T, Node * > max_element(T xor_val = 0) {\n    assert(root->exist > 0);\n   \
    \ return kth_element(root->exist - 1, xor_val);\n  }\n\n  pair< T, Node * > kth_element(D\
    \ k, T xor_val = 0) { // 0-indexed\n    assert(0 <= k && k < root->exist);\n \
    \   return kth_element(root, k, MAX_LOG, xor_val);\n  }\n\n  D count_less(const\
    \ T &bit, T xor_val = 0) { // < bit\n    return count_less(root, bit, MAX_LOG,\
    \ xor_val);\n  }\n\nprivate:\n\n  virtual Node *clone(Node *t) { return t; }\n\
    \n  Node *add(Node *t, T bit, int idx, int depth, D x, T xor_val, bool need =\
    \ true) {\n    if(need) t = clone(t);\n    if(depth == -1) {\n      t->exist +=\
    \ x;\n      if(idx >= 0) t->accept.emplace_back(idx);\n    } else {\n      bool\
    \ f = (xor_val >> depth) & 1;\n      auto &to = t->nxt[f ^ ((bit >> depth) & 1)];\n\
    \      if(!to) to = new Node(), need = false;\n      to = add(to, bit, idx, depth\
    \ - 1, x, xor_val, need);\n      t->exist += x;\n    }\n    return t;\n  }\n\n\
    \  Node *find(Node *t, T bit, int depth, T xor_val) {\n    if(depth == -1) {\n\
    \      return t;\n    } else {\n      bool f = (xor_val >> depth) & 1;\n     \
    \ auto &to = t->nxt[f ^ ((bit >> depth) & 1)];\n      return to ? find(to, bit,\
    \ depth - 1, xor_val) : nullptr;\n    }\n  }\n\n  pair< T, Node * > kth_element(Node\
    \ *t, D k, int bit_index, T xor_val) { // 0-indexed\n    if(bit_index == -1) {\n\
    \      return {0, t};\n    } else {\n      bool f = (xor_val >> bit_index) & 1;\n\
    \      if((t->nxt[f] ? t->nxt[f]->exist : 0) <= k) {\n        auto ret = kth_element(t->nxt[f\
    \ ^ 1], k - (t->nxt[f] ? t->nxt[f]->exist : 0), bit_index - 1, xor_val);\n   \
    \     ret.first |= T(1) << bit_index;\n        return ret;\n      } else {\n \
    \       return kth_element(t->nxt[f], k, bit_index - 1, xor_val);\n      }\n \
    \   }\n  }\n\n  D count_less(Node *t, const T &bit, int bit_index, T xor_val)\
    \ {\n    if(bit_index == -1) return 0;\n    D ret = 0;\n    bool f = (xor_val\
    \ >> bit_index) & 1;\n    if((bit >> bit_index & 1) and t->nxt[f]) ret += t->nxt[f]->exist;\n\
    \    if(t->nxt[f ^ (bit >> bit_index & 1)]) ret += count_less(t->nxt[f ^ (bit\
    \ >> bit_index & 1)], bit, bit_index - 1, xor_val);\n    return ret;\n  }\n};\n\
    #line 6 \"test/verify/yosupo-set-xor-min.test.cpp\"\n\nint main() {\n  int Q;\n\
    \  cin >> Q;\n  BinaryTrie< int, 29 > trie;\n  for(int i = 0; i < Q; i++) {\n\
    \    int t, x;\n    cin >> t >> x;\n    if(t == 0) {\n      if(trie.count(x) ==\
    \ 0) trie.add(x);\n    } else if(t == 1) {\n      if(trie.count(x) != 0) trie.erase(x);\n\
    \    } else {\n      cout << trie.min_element(x).first << \"\\n\";\n    }\n  }\n\
    }\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/set_xor_min\"\n\n#include\
    \ \"../../template/template.hpp\"\n\n#include \"../../structure/trie/binary-trie.hpp\"\
    \n\nint main() {\n  int Q;\n  cin >> Q;\n  BinaryTrie< int, 29 > trie;\n  for(int\
    \ i = 0; i < Q; i++) {\n    int t, x;\n    cin >> t >> x;\n    if(t == 0) {\n\
    \      if(trie.count(x) == 0) trie.add(x);\n    } else if(t == 1) {\n      if(trie.count(x)\
    \ != 0) trie.erase(x);\n    } else {\n      cout << trie.min_element(x).first\
    \ << \"\\n\";\n    }\n  }\n}\n"
  dependsOn:
  - template/template.hpp
  - structure/trie/binary-trie.hpp
  isVerificationFile: true
  path: test/verify/yosupo-set-xor-min.test.cpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/verify/yosupo-set-xor-min.test.cpp
layout: document
redirect_from:
- /verify/test/verify/yosupo-set-xor-min.test.cpp
- /verify/test/verify/yosupo-set-xor-min.test.cpp.html
title: test/verify/yosupo-set-xor-min.test.cpp
---
