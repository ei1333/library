// competitive-verifier: PROBLEM https://yukicoder.me/problems/no/1002

#include "../../template/template.hpp"

#include "../../graph/tree/centroid-decomposition.hpp"

int main() {
  int N, K;
  cin >> N >> K;
  CentroidDecomposition< int > g(N);
  g.read(N - 1, -1, true);
  int root = g.build();
  int64 ret = 0;
  vector< int > used(N);

  map< pair< int, int >, int > mp;
  int all;
  map< int, int > mp2;
  map< int, int > mp3;


  auto get_vec = MFP([&](auto get_vec, int idx, int par, int a, int b) -> void {
    if(b == -1) {
      ret += all - mp2[a];
      ret += mp3[a];
    } else {
      ret++;
      ret += mp2[a] + mp2[b];
      ret += mp[minmax(a, b)];
    }
    for(auto &e : g.g[idx]) {
      if(e.to == par) continue;
      if(used[e.to]) continue;
      if(a == e.cost) {
        get_vec(e.to, idx, e.cost, b);
      } else if(b == -1 || b == e.cost) {
        get_vec(e.to, idx, a, e.cost);
      }
    }
  });

  auto add_vec = MFP([&](auto add_vec, int idx, int par, int a, int b) -> void {
    if(b == -1) {
      mp2[a]++;
      all++;
    } else {
      mp[minmax(a, b)]++;
      mp3[a]++;
      mp3[b]++;
    }
    for(auto &e : g.g[idx]) {
      if(e.to == par) continue;
      if(used[e.to]) continue;
      if(a == e.cost) {
        add_vec(e.to, idx, e.cost, b);
      } else if(b == -1 || b == e.cost) {
        add_vec(e.to, idx, a, e.cost);
      }
    }
  });

  auto rec = MFP([&](auto rec, int idx) -> void {
    used[idx] = true;
    mp.clear();
    mp2.clear();
    mp3.clear();
    all = 0;
    for(auto &e : g.g[idx]) {
      if(used[e.to]) continue;
      get_vec(e.to, idx, e.cost, -1);
      add_vec(e.to, idx, e.cost, -1);
    }
    for(auto &to : g.tree.g[idx]) {
      rec(to);
    }
    used[idx] = false;
  });
  rec(root);
  cout << ret << endl;
}
