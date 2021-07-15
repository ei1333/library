#include "../graph-template.hpp"
#include "../others/low-link.hpp"

/**
 * @brief Bi Connected Components(二重頂点連結成分分解)
 * @docs docs/bi-connected-components.md
 */
template< typename T = int >
struct BiConnectedComponents : LowLink< T > {
public:
  using LowLink< T >::LowLink;
  using LowLink< T >::g;
  using LowLink< T >::ord;
  using LowLink< T >::low;

  vector< vector< Edge< T > > > bc;

  void build() override {
    LowLink< T >::build();
    used.assign(g.size(), 0);
    for(int i = 0; i < (int)used.size(); i++) {
      if(!used[i]) dfs(i, -1);
    }
  }

  explicit BiConnectedComponents(const Graph< T > &g) : Graph< T >(g) {}

private:
  vector< int > used;
  vector< Edge< T > > tmp;

  void dfs(int idx, int par) {
    used[idx] = true;
    bool beet = false;
    for(auto &to : g[idx]) {
      if(to == par && !exchange(beet, true)) continue;
      if(!used[to] || ord[to] < ord[idx]) {
        tmp.emplace_back(to);
      }
      if(!used[to]) {
        dfs(to, idx);
        if(low[to] >= ord[idx]) {
          bc.emplace_back();
          for(;;) {
            auto e = tmp.back();
            bc.back().emplace_back(e);
            tmp.pop_back();
            if(e.idx == to.idx) break;
          }
        }
      }
    }
  }
};
