int64_t mod_log(int64_t a, int64_t b, int64_t p) {
  int64_t ok = p, ng = -1;
  while(ok - ng > 1) {
    auto mid = (ok + ng) / 2;
    if(mid * mid >= p) ok = mid;
    else ng = mid;
  }
 
  unordered_map< int64_t, int64_t > baby;
  baby.reserve(ok);
  int64_t factor = 1;
  for(int64_t i = 0, e = b; i < ok; i++) {
    baby[e] = i;
    (factor *= a) %= p;
    (e *= a) %= p;
  }
  for(int64_t i = 1, e = factor; i <= ok; i++) {
    auto it = baby.find(e);
    if(it != end(baby)) return i * ok - it->second;
    (e *= factor) %= p;
  }
  return -1;
}
