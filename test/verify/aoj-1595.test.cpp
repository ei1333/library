#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1595"

#include "../../template/template.cpp"

#include "../../graph/tree/rerooting.cpp"

const int INF = 1 << 30;
using pi = pair< int, int >;

int main() {
  int N, D;
  cin >> N >> D;

  auto f1 = [](pi a, pi b) {
    return pi(a.first + b.first, max(a.second, b.second));
  };
  auto f2 = [](pi a, pi data) {
    a.first += data.second;
    a.second += data.first;
    return a;
  };

  ReRooting< pi, pi > g(N, f1, f2, {0, 0});
  for(int i = 1; i < N; i++) {
    int s, t, w;
    cin >> s >> t >> w;
    --s, --t;
    g.add_edge_bi(s, t, pi(w, true), pi(w, false));
  }

  int ret = INF;
  for(auto &p : g.build()) {
    if(p.second <= D) ret = min(ret, p.first);
  }
  if(ret >= INF) ret = -1;
  cout << ret << endl;
}

