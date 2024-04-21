// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/two_edge_connected_components

#include "../../template/template.hpp"

#include "../../graph/connected-components/incremental-bridge-connectivity.hpp"

int main() {
  int n, m;
  cin >> n >> m;
  IncrementalBridgeConnectivity ibc(n);
  for(int i = 0; i < m; i++) {
    int a, b;
    cin >> a >> b;
    ibc.add_edge(a, b);
  }
  vector< int > id(n, -1);
  int k = 0;
  vector< vector< int > > ans(n);
  for(int i = 0; i < n; i++) {
    int r = ibc.find(i);
    if(id[r] == -1) {
      id[r] = k;
      k += 1;
    }
    ans[id[r]].push_back(i);
  }
  cout << k << "\n";
  for(int i = 0; i < k; i++) {
    cout << ans[i].size() << " " << ans[i] << "\n";
  }
}
