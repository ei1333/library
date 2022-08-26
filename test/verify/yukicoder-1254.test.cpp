#define PROBLEM "https://yukicoder.me/problems/no/1254"

#include "../../graph/others/namori-graph.hpp"
#include "../../template/template.hpp"

int main() {
  int N;
  cin >> N;
  NamoriGraph< int > g(N);
  g.read(N);
  g.build();
  vector< int > ans;
  for (auto &e: g.loop_edges) {
    ans.emplace_back(e.idx + 1);
  }
  sort(begin(ans), end(ans));
  cout << ans.size() << "\n";
  cout << ans << "\n";
}
