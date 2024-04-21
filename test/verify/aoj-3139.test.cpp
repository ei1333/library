// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=3139

#include "../../template/template.hpp"

#include "../../structure/union-find/union-find.hpp"

#include "../../graph/others/block-cut-tree.hpp"
#include "../../graph/tree/centroid-decomposition.hpp"

int main() {
  int N, M;
  cin >> N >> M;
  BlockCutTree< int > g(N);
  Graph<> h(N);
  UnionFind uf(N);
  vector< int > A(M), B(M), C(M);
  for(int i = 0; i < M; i++) {
    cin >> A[i] >> B[i] >> C[i];
    --A[i], --B[i];
    g.add_edge(A[i], B[i], C[i]);
    if(uf.unite(A[i], B[i])) h.add_edge(A[i], B[i], C[i]);
  }
  g.build();

  vector< int > sum(N);
  MFP([&](auto rec, int idx, int par) -> void {
    for(auto &to : h.g[idx]) {
      if(to != par) {
        sum[to] = sum[idx] ^ to.cost;
        rec(to, idx);
      }
    }
  })(0, -1);

  auto &t = g.tree;
  vector< int > weight(t.size());

  Graph< int > tree(t);
  CentroidDecomposition< int > cpd(tree);
  int root = cpd.build();
  auto &ushitapunichia = cpd.tree;


  {
    for(int i = 0; i < g.bc.size(); i++) {
      for(auto &e : g.bc[i]) weight[i] ^= e.cost;
    }
    for(int i = 0; i < t.size(); i++) {
      if(i < g.bc.size() && g.bc[i].size() >= 2) continue;
      weight[i] = 0;
    }
  }

  using vi = vector< int >;

  auto f = [](vi &a, int b) {
    for(int y : a) chmin(b, b ^ y);
    if(b) a.emplace_back(b);
  };

  int Q;
  cin >> Q;
  vector< int > X(Q), Y(Q), K(Q), Z(Q);
  for(int i = 0; i < Q; i++) {
    cin >> X[i] >> Y[i] >> K[i];
    --X[i], --Y[i], --K[i];
    Z[i] = sum[X[i]] ^ sum[Y[i]];
    X[i] = g[X[i]];
    Y[i] = g[Y[i]];
  }

  vector< vector< int > > ev(t.size());
  for(int i = 0; i < Q; i++) {
    ev[X[i]].emplace_back(i);
    ev[Y[i]].emplace_back(i);
  }
  vector< int > used(t.size());
  vector< vector< int > > cash(t.size());
  vector< int > last(Q);
  int ptr = 1;
  vector< int > ans(Q);


  auto calc_ans = [&](const vector< int > &a, vector< int > b, int k, int base) {
    for(int x : a) {
      if(b.size() >= 30) break;
      for(int y : b) chmin(x, x ^ y);
      if(x) b.emplace_back(x);
    }
    auto &tap = b;
    if(1 << tap.size() <= k) {
      return -1;
    } else {
      sort(tap.begin(), tap.end());
      for(int j = (int) tap.size() - 1; j >= 0; j--) {
        if(k < (1 << j)) {
          chmin(base, base ^ tap[j]);
        } else {
          k -= 1 << j;
          chmax(base, base ^ tap[j]);
        }
      }
      return base;
    }
  };

  auto add_dfs = MFP([&](auto add_dfs, int idx, int par, vector< int > base, int Left, int id) -> void {
    if(weight[idx]) f(base, weight[idx]);
    cash[idx] = base;

    for(auto &q : ev[idx]) {
      if(Left <= last[q] && last[q] < id) ans[q] = calc_ans(cash[X[q]], cash[Y[q]], K[q], Z[q]);
      last[q] = id;
    }

    for(auto &to : t.g[idx]) {
      if(to == par) continue;
      if(used[to]) continue;
      add_dfs(to, idx, base, Left, id);
    }
  });


  MFP([&](auto dfs, int centroid) -> void {
    used[centroid] = true;

    vector< int > base;
    int Left = ptr;
    if(weight[centroid]) base.emplace_back(weight[centroid]);
    for(auto &q : ev[centroid]) {
      if(last[q] == ptr) ans[q] = calc_ans(base, base, K[q], Z[q]);
      last[q] = ptr;
    }
    cash[centroid] = base;
    ++ptr;

    for(auto &to : t.g[centroid]) {
      if(used[to]) continue;
      add_dfs(to, centroid, base, Left, ptr++);
    }

    for(auto &to : ushitapunichia.g[centroid]) {
      dfs(to);
    }
    used[centroid] = false;
  })(root);


  for(auto &p : ans) cout << p << "\n";
}
