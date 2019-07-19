template< typename T >
struct Diameter {
  T key;
  multiset< T > md1, md2;
  
  T p_max, c_max, length;
  T diameter;
  
  Diameter() : p_max(0), c_max(0), diameter(0), length(0) {
    md1.emplace(0);
    md2.emplace(0);
  }
  
  void set(const T &k) {
    key = p_max = c_max = length = diameter = k;
  }
  
  void merge(const Diameter &parent, const Diameter &child) {
    p_max = max(parent.p_max, parent.length + key + max(*md1.rbegin(), child.p_max));
    c_max = max(child.c_max, child.length + key + max(*md1.rbegin(), parent.c_max));
    length = parent.length + key + child.length;
    diameter = max({child.p_max + key + max(*md1.rbegin(), parent.c_max), parent.c_max + key + *md1.rbegin(), parent.diameter, child.diameter, *md2.rbegin()});
    if(md1.size() >= 2) diameter = max(diameter, *--md1.end() + key + *-- --md1.end());
  }
  
  void reverse() {
    swap(p_max, c_max);
  }
  
  void insert_light(const Diameter &child) {
    md1.emplace(child.p_max);
    md2.emplace(child.diameter);
  }
  
  void erase_light(const Diameter &child) {
    md1.erase(md1.find(child.p_max));
    md2.erase(md2.find(child.diameter));
  }
};
  
int main() {
  int N;
  cin >> N;
  using LCT = LinkCutTreeSubtree< Diameter< int >, int >;
  vector< LCT > vv(N), ee(N);
  for(int i = 1; i < N; i++) {
    int s, t, w;
    cin >> s >> t >> w;
    ee[i].init(w);
    vv[t].evert();
    vv[t].link(&ee[i]);
    ee[i].link(&vv[s]);
  }
  cout << vv[0].query().diameter << endl;
}
