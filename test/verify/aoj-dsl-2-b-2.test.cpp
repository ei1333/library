#define PROBLEM \
  "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B"

#include "../../structure/trie/binary-trie.hpp"
#include "../../template/template.hpp"

int main() {
  int N, Q;
  cin >> N >> Q;
  BinaryTrie< int, 20 > bt;
  for (int i = 0; i < Q; i++) {
    int c, x, y;
    cin >> c >> x >> y;
    if (c == 0) {
      bt.add(x, -1, y);
    } else if (c == 1) {
      cout << bt.count_less(y + 1) - bt.count_less(x) << "\n";
    }
  }
}
