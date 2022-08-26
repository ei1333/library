#define PROBLEM "https://judge.yosupo.jp/problem/tree_diameter"

#include "../../graph/tree/tree-diameter.hpp"
#include "../../template/template.hpp"

int main() {
  int N;
  cin >> N;
  TreeDiameter< int64_t > g(N);
  g.read(N - 1, 0, true);
  cout << g.build() << " ";
  cout << g.path.size() + 1 << "\n";
  cout << g.path[0].from << " " << g.path << "\n";
}
