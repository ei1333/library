// competitive-verifier: PROBLEM https://yukicoder.me/problems/no/430

#include "../../template/template.hpp"

#include "../../structure/trie/trie.hpp"

#include "../../string/aho-corasick.hpp"

int main() {
  string S;
  int M;
  cin >> S;
  cin >> M;
  AhoCorasick< 26, 'A' > aho;
  for(int i = 0; i < M; i++) {
    string T;
    cin >> T;
    aho.add(T);
  }
  aho.build();
  cout << aho.move(S).first << endl;
}
