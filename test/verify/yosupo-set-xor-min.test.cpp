#define PROBLEM "https://judge.yosupo.jp/problem/set_xor_min"

#include "../../template/template.cpp"

#include "../../structure/trie/binary-trie.cpp"

int main() {
  int Q;
  cin >> Q;
  BinaryTrie< int, 29 > trie;
  for(int i = 0; i < Q; i++) {
    int t, x;
    cin >> t >> x;
    if(t == 0) {
      if(trie.count(x) == 0) trie.add(x);
    } else if(t == 1) {
      if(trie.count(x) != 0) trie.erase(x);
    } else {
      cout << trie.min_element(x).first << "\n";
    }
  }
}
