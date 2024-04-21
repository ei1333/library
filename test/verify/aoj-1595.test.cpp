// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1595

#include "../../template/template.hpp"

#include "../../graph/tree/rerooting.hpp"

int main() {
  int N;
  cin >> N;

  auto f1 = [](int a, int b) {
    return max(a, b);
  };

  auto f2 = [](int a, int data) {
    return a + data;
  };

  ReRooting< int, int > g(N, f1, f2, 0);
  for(int i = 1; i < N; i++) {
    int s, t;
    cin >> s >> t;
    --s, --t;
    g.add_edge(s, t, 1);
  }
  for(auto &p : g.build()) {
    cout << (N - 1) * 2 - p << endl;
  }
}
