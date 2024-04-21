// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/enumerate_triangles

#include "../../template/template.hpp"

#include "../../graph/others/enumerate-triangles.hpp"

int main() {
    int N, M;
    cin >> N >> M;
    vector< int > xs(N);
    for(auto& x : xs) cin >> x;
    Graph<> g(N);
    g.read(M, 0);
    auto triangle = enumerate_triangles(g);
    const int MOD = 998244353;
    int ret = 0;
    for(auto& p : triangle) {
        int a, b, c;
        tie(a, b, c) = p;
        ret += 1LL * xs[a] * xs[b] % MOD * xs[c] % MOD;
        if(ret >= MOD) ret -= MOD;
    }
    cout << ret << "\n";
}
