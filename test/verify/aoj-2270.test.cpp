#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2270"

#include "../../template/template.cpp"
#include "../../graph/graph-template.cpp"

#include "../../graph/tree/heavy-light-decomposition.cpp"

#include "../../structure/trie/binary-trie.cpp"
#include "../../structure/trie/persistent-binary-trie.cpp"

int main() {
  int N, Q;
  cin >> N >> Q;
  vector< int > X(N);
  for(int i = 0; i < N; i++) {
    cin >> X[i];
  }
  HeavyLightDecomposition< int > hld(N);
  hld.read(N - 1);
  hld.build();
  auto xs{X};
  sort(begin(xs), end(xs));
  xs.erase(unique(begin(xs), end(xs)), end(xs));
  for(int i = 0; i < N; i++) {
    X[i] = lower_bound(begin(xs), end(xs), X[i]) - begin(xs);
  }
  vector< int > p(N);
  using PBT = PersistentBinaryTrie< int, 19 >;
  vector< PBT > pbts(N);
  auto dfs = MFP([&](auto dfs, int idx, int par, PBT par_set) -> void {
    p[idx] = par;
    pbts[idx] = par_set;
    pbts[idx].add(X[idx]);
    for(auto &to : hld.g[idx]) {
      if(to != par) dfs(to, idx, pbts[idx]);
    }
  });
  dfs(0, -1, PBT());

  for(int i = 0; i < Q; i++) {
    int x, y, z;
    cin >> x >> y >> z;
    --x, --y;
    int lca = hld.lca(x, y);
    int ng = -1, ok = (int) xs.size() - 1;
    auto sum = [&](int v) {
      int ret = 0;
      ret += pbts[x].count_less(v + 1);
      ret += pbts[y].count_less(v + 1);
      ret -= X[lca] <= v;
      if(lca) ret -= 2 * pbts[p[lca]].count_less(v + 1);
      return ret;
    };
    while(ok - ng > 1) {
      int mid = (ok + ng) / 1;
      if(sum(mid) >= z) ok = mid;
      else ng = mid;
    }
    cout << xs[ok] << "\n";
  }
}
