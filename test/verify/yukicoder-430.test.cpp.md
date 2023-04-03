---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: string/aho-corasick.hpp
    title: "Aho-Corasick(\u30A8\u30A4\u30DB\u2013\u30B3\u30E9\u30B7\u30C3\u30AF\u6CD5\
      )"
  - icon: ':heavy_check_mark:'
    path: structure/trie/trie.hpp
    title: structure/trie/trie.hpp
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
    PROBLEM: https://yukicoder.me/problems/no/430
    links:
    - https://yukicoder.me/problems/no/430
  bundledCode: "#line 1 \"test/verify/yukicoder-430.test.cpp\"\n#define PROBLEM \"\
    https://yukicoder.me/problems/no/430\"\n\n#line 1 \"template/template.hpp\"\n\
    #include<bits/stdc++.h>\n\nusing namespace std;\n\nusing int64 = long long;\n\
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
    \ MFP(F &&f) {\n  return FixPoint< F >{forward< F >(f)};\n}\n#line 4 \"test/verify/yukicoder-430.test.cpp\"\
    \n\n#line 1 \"structure/trie/trie.hpp\"\ntemplate< int char_size >\nstruct TrieNode\
    \ {\n  int nxt[char_size];\n\n  int exist;\n  vector< int > accept;\n\n  TrieNode()\
    \ : exist(0) {\n    memset(nxt, -1, sizeof(nxt));\n  }\n};\n\ntemplate< int char_size,\
    \ int margin >\nstruct Trie {\n  using Node = TrieNode< char_size >;\n\n  vector<\
    \ Node > nodes;\n  int root;\n\n  Trie() : root(0) {\n    nodes.push_back(Node());\n\
    \  }\n\n  void update_direct(int node, int id) {\n    nodes[node].accept.push_back(id);\n\
    \  }\n\n  void update_child(int node, int child, int id) {\n    ++nodes[node].exist;\n\
    \  }\n\n  void add(const string &str, int str_index, int node_index, int id) {\n\
    \    if(str_index == str.size()) {\n      update_direct(node_index, id);\n   \
    \ } else {\n      const int c = str[str_index] - margin;\n      if(nodes[node_index].nxt[c]\
    \ == -1) {\n        nodes[node_index].nxt[c] = (int) nodes.size();\n        nodes.push_back(Node());\n\
    \      }\n      add(str, str_index + 1, nodes[node_index].nxt[c], id);\n     \
    \ update_child(node_index, nodes[node_index].nxt[c], id);\n    }\n  }\n\n  void\
    \ add(const string &str, int id) {\n    add(str, 0, 0, id);\n  }\n\n  void add(const\
    \ string &str) {\n    add(str, nodes[0].exist);\n  }\n\n  void query(const string\
    \ &str, const function< void(int) > &f, int str_index, int node_index) {\n   \
    \ for(auto &idx : nodes[node_index].accept) f(idx);\n    if(str_index == str.size())\
    \ {\n      return;\n    } else {\n      const int c = str[str_index] - margin;\n\
    \      if(nodes[node_index].nxt[c] == -1) return;\n      query(str, f, str_index\
    \ + 1, nodes[node_index].nxt[c]);\n    }\n  }\n\n  void query(const string &str,\
    \ const function< void(int) > &f) {\n    query(str, f, 0, 0);\n  }\n\n  int count()\
    \ const {\n    return (nodes[0].exist);\n  }\n\n  int size() const {\n    return\
    \ ((int) nodes.size());\n  }\n};\n#line 6 \"test/verify/yukicoder-430.test.cpp\"\
    \n\n#line 1 \"string/aho-corasick.hpp\"\n/**\n * @brief Aho-Corasick(\u30A8\u30A4\
    \u30DB\u2013\u30B3\u30E9\u30B7\u30C3\u30AF\u6CD5)\n * @docs docs/aho-corasick.md\n\
    \ */\ntemplate< int char_size, int margin >\nstruct AhoCorasick : Trie< char_size\
    \ + 1, margin > {\n  using Trie< char_size + 1, margin >::Trie;\n\n  const int\
    \ FAIL = char_size;\n  vector< int > correct;\n\n  void build(bool heavy = true)\
    \ {\n    correct.resize(this->size());\n    for(int i = 0; i < this->size(); i++)\
    \ {\n      correct[i] = (int) this->nodes[i].accept.size();\n    }\n    queue<\
    \ int > que;\n    for(int i = 0; i <= char_size; i++) {\n      if(~this->nodes[0].nxt[i])\
    \ {\n        this->nodes[this->nodes[0].nxt[i]].nxt[FAIL] = 0;\n        que.emplace(this->nodes[0].nxt[i]);\n\
    \      } else {\n        this->nodes[0].nxt[i] = 0;\n      }\n    }\n    while(!que.empty())\
    \ {\n      auto &now = this->nodes[que.front()];\n      int fail = now.nxt[FAIL];\n\
    \      correct[que.front()] += correct[fail];\n      que.pop();\n      for(int\
    \ i = 0; i < char_size; i++) {\n        if(~now.nxt[i]) {\n          this->nodes[now.nxt[i]].nxt[FAIL]\
    \ = this->nodes[fail].nxt[i];\n          if(heavy) {\n            auto &u = this->nodes[now.nxt[i]].accept;\n\
    \            auto &v = this->nodes[this->nodes[fail].nxt[i]].accept;\n       \
    \     vector< int > accept;\n            set_union(begin(u), end(u), begin(v),\
    \ end(v), back_inserter(accept));\n            u = accept;\n          }\n    \
    \      que.emplace(now.nxt[i]);\n        } else {\n          now.nxt[i] = this->nodes[fail].nxt[i];\n\
    \        }\n      }\n    }\n  }\n\n  map< int, int > match(const string &str,\
    \ int now = 0) {\n    map< int, int > result;\n    for(auto &c : str) {\n    \
    \  now = this->nodes[now].nxt[c - margin];\n      for(auto &v : this->nodes[now].accept)\
    \ result[v] += 1;\n    }\n    return result;\n  }\n\n  pair< int64_t, int > move(const\
    \ char &c, int now = 0) {\n    now = this->nodes[now].nxt[c - margin];\n    return\
    \ {correct[now], now};\n  }\n\n  pair< int64_t, int > move(const string &str,\
    \ int now = 0) {\n    int64_t sum = 0;\n    for(auto &c : str) {\n      auto nxt\
    \ = move(c, now);\n      sum += nxt.first;\n      now = nxt.second;\n    }\n \
    \   return {sum, now};\n  }\n};\n#line 8 \"test/verify/yukicoder-430.test.cpp\"\
    \n\nint main() {\n  string S;\n  int M;\n  cin >> S;\n  cin >> M;\n  AhoCorasick<\
    \ 26, 'A' > aho;\n  for(int i = 0; i < M; i++) {\n    string T;\n    cin >> T;\n\
    \    aho.add(T);\n  }\n  aho.build();\n  cout << aho.move(S).first << endl;\n\
    }\n"
  code: "#define PROBLEM \"https://yukicoder.me/problems/no/430\"\n\n#include \"../../template/template.hpp\"\
    \n\n#include \"../../structure/trie/trie.hpp\"\n\n#include \"../../string/aho-corasick.hpp\"\
    \n\nint main() {\n  string S;\n  int M;\n  cin >> S;\n  cin >> M;\n  AhoCorasick<\
    \ 26, 'A' > aho;\n  for(int i = 0; i < M; i++) {\n    string T;\n    cin >> T;\n\
    \    aho.add(T);\n  }\n  aho.build();\n  cout << aho.move(S).first << endl;\n\
    }\n"
  dependsOn:
  - template/template.hpp
  - structure/trie/trie.hpp
  - string/aho-corasick.hpp
  isVerificationFile: true
  path: test/verify/yukicoder-430.test.cpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/verify/yukicoder-430.test.cpp
layout: document
redirect_from:
- /verify/test/verify/yukicoder-430.test.cpp
- /verify/test/verify/yukicoder-430.test.cpp.html
title: test/verify/yukicoder-430.test.cpp
---
