---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/verify/yukicoder-430.test.cpp
    title: test/verify/yukicoder-430.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"structure/trie/trie.hpp\"\ntemplate< int char_size >\nstruct\
    \ TrieNode {\n  int nxt[char_size];\n\n  int exist;\n  vector< int > accept;\n\
    \n  TrieNode() : exist(0) {\n    memset(nxt, -1, sizeof(nxt));\n  }\n};\n\ntemplate<\
    \ int char_size, int margin >\nstruct Trie {\n  using Node = TrieNode< char_size\
    \ >;\n\n  vector< Node > nodes;\n  int root;\n\n  Trie() : root(0) {\n    nodes.push_back(Node());\n\
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
    \ ((int) nodes.size());\n  }\n};\n"
  code: "template< int char_size >\nstruct TrieNode {\n  int nxt[char_size];\n\n \
    \ int exist;\n  vector< int > accept;\n\n  TrieNode() : exist(0) {\n    memset(nxt,\
    \ -1, sizeof(nxt));\n  }\n};\n\ntemplate< int char_size, int margin >\nstruct\
    \ Trie {\n  using Node = TrieNode< char_size >;\n\n  vector< Node > nodes;\n \
    \ int root;\n\n  Trie() : root(0) {\n    nodes.push_back(Node());\n  }\n\n  void\
    \ update_direct(int node, int id) {\n    nodes[node].accept.push_back(id);\n \
    \ }\n\n  void update_child(int node, int child, int id) {\n    ++nodes[node].exist;\n\
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
    \ ((int) nodes.size());\n  }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: structure/trie/trie.hpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/verify/yukicoder-430.test.cpp
documentation_of: structure/trie/trie.hpp
layout: document
redirect_from:
- /library/structure/trie/trie.hpp
- /library/structure/trie/trie.hpp.html
title: structure/trie/trie.hpp
---
