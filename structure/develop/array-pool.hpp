template< class T, size_t V >
struct ArrayPool {
  array< T, V > pool;
  array< T *, V > stock;
  int ptr;

  ArrayPool() { clear(); }

  inline T *alloc() {
    return stock[--ptr];
  }

  inline void free(T *t) {
    stock[ptr++] = t;
  }

  void clear() {
    ptr = (int) pool.size();
    for(int i = 0; i < pool.size(); i++) stock[i] = &pool[i];
  }
};
