#include "point.hpp"
#include "polygon.hpp"

namespace geometry {
  // http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_4_B
  pair< int, int > convex_polygon_diameter(const Polygon &p) {
    int N = (int) p.size();
    int is = 0, js = 0;
    for(int i = 1; i < N; i++) {
      if(imag(p[i]) > imag(p[is])) is = i;
      if(imag(p[i]) < imag(p[js])) js = i;
    }
    Real maxdis = norm(p[is] - p[js]);

    int maxi, maxj, i, j;
    i = maxi = is;
    j = maxj = js;
    do {
      if(cross(p[(i + 1) % N] - p[i], p[(j + 1) % N] - p[j]) >= 0) {
        j = (j + 1) % N;
      } else {
        i = (i + 1) % N;
      }
      if(norm(p[i] - p[j]) > maxdis) {
        maxdis = norm(p[i] - p[j]);
        maxi = i;
        maxj = j;
      }
    } while(i != is || j != js);
    return minmax(maxi, maxj);
  }
}
