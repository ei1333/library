// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/frequency_table_of_tree_distance

#include "../../template/template.hpp"

#include "../../graph/tree/centroid-decomposition.hpp"

#include "../../math/fft/fast-fourier-transform.hpp"

int main() {
  int N;
  cin >> N;
  CentroidDecomposition< int > g(N);
  g.read(N - 1, 0);
  int root = g.build();
  vector< int > used(N);
  vector< int64 > dist(N);
  MFP([&](auto rec, int centroid) -> void {
    used[centroid] = true;
    vector< int > cnt{1};
    for(auto &ch : g.g[centroid]) {
      if(used[ch]) continue;
      vector< int > num;
      queue< tuple< int, int, int > > que;
      que.emplace(ch, centroid, 1);
      while(!que.empty()) {
        int idx, par, dep;
        tie(idx, par, dep) = que.front();
        que.pop();
        if(cnt.size() <= dep) cnt.resize(dep + 1, 0);
        if(num.size() <= dep) num.resize(dep + 1, 0);
        cnt[dep]++;
        num[dep]++;
        for(auto &to : g.g[idx]) {
          if(to == par || used[to]) continue;
          que.emplace(to.to, idx, dep + 1);
        }
      }
      auto ret = FastFourierTransform::multiply(num, num);
      for(int i = 0; i < ret.size(); i++) dist[i] -= ret[i];
    }
    auto ret = FastFourierTransform::multiply(cnt, cnt);
    for(int i = 0; i < ret.size(); i++) dist[i] += ret[i];
    for(auto &to : g.tree.g[centroid]) rec(to);
  })(root);
  dist.erase(begin(dist));
  for(auto &p : dist) p /= 2;
  cout << dist << "\n";
}

