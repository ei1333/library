/**
 * @brief Square-Matrix(正方行列)
 */
template< class T, size_t N >
struct SquareMatrix {
  array< array< T, N >, N > A;

  SquareMatrix() : A{{}} {}

  size_t size() const { return N; }

  inline const array< T, N > &operator[](int k) const {
    return (A.at(k));
  }

  inline array< T, N > &operator[](int k) {
    return (A.at(k));
  }

  static SquareMatrix add_identity() {
    return SquareMatrix();
  }

  static SquareMatrix mul_identity() {
    SquareMatrix mat;
    for(size_t i = 0; i < N; i++) mat[i][i] = 1;
    return mat;
  }

  SquareMatrix &operator+=(const SquareMatrix &B) {
    for(size_t i = 0; i < N; i++) {
      for(size_t j = 0; j < N; j++) {
        (*this)[i][j] += B[i][j];
      }
    }
    return *this;
  }

  SquareMatrix &operator-=(const SquareMatrix &B) {
    for(size_t i = 0; i < N; i++) {
      for(size_t j = 0; j < N; j++) {
        (*this)[i][j] -= B[i][j];
      }
    }
    return *this;
  }

  SquareMatrix &operator*=(const SquareMatrix &B) {
    array< array< T, N >, N > C;
    for(size_t i = 0; i < N; i++) {
      for(size_t j = 0; j < N; j++) {
        for(size_t k = 0; k < N; k++) {
          C[i][j] = (C[i][j] + (*this)[i][k] * B[k][j]);
        }
      }
    }
    A.swap(C);
    return (*this);
  }

  SquareMatrix &operator^=(uint64_t k) {
    SquareMatrix B = SquareMatrix::mul_identity();
    while(k > 0) {
      if(k & 1) B *= *this;
      *this *= *this;
      k >>= 1LL;
    }
    A.swap(B.A);
    return *this;
  }

  SquareMatrix operator+(const SquareMatrix &B) const {
    return SquareMatrix(*this) += B;
  }

  SquareMatrix operator-(const SquareMatrix &B) const {
    return SquareMatrix(*this) -= B;
  }

  SquareMatrix operator*(const SquareMatrix &B) const {
    return SquareMatrix(*this) *= B;
  }

  SquareMatrix operator^(uint64_t k) const {
    return SquareMatrix(*this) ^= k;
  }

  friend ostream &operator<<(ostream &os, SquareMatrix &p) {
    for(int i = 0; i < N; i++) {
      os << "[";
      for(int j = 0; j < N; j++) {
        os << p[i][j] << (j + 1 == N ? "]\n" : ",");
      }
    }
    return os;
  }
};
