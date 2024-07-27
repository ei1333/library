// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1040

#include "../../template/template.hpp"

#include "../../graph/others/minimum-steiner-tree.hpp"

int main() {
  int H, W;
  while(cin >> H >> W, H) {
    Graph< int > g(H * W);
    vector< int > terminal;
    for(int i = 0; i < H; i++) {
      for(int j = 0; j < W; j++) {
        int t;
        cin >> t;
        if(i > 0) {
          g.add_edge(i * W + j, i * W + j - W, 1);
        }
        if(j > 0) {
          g.add_edge(i * W + j, i * W + j - 1, 1);
        }
        if(t == 1) {
          terminal.emplace_back(i * W + j);
        }
      }
    }
    cout << H * W - MinimumSteinerTree(g, terminal).cost - 1 << endl;
  }
}
