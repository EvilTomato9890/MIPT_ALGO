#include <cstdint>
#include <iostream>
#include <vector>

constexpr std::int64_t MOD = 1000003;
constexpr int MATRIX_SIZE = 5;

class Matrix {
 private:
  int size_ = 0;
  std::vector<std::vector<std::int64_t>> data_{};

 public:
  explicit Matrix(int size)
      : size_(size), data_(size, std::vector<std::int64_t>(size, 0)) {}

  std::vector<std::int64_t>& operator[](int row) { return data_[row]; }

  const std::vector<std::int64_t>& operator[](int row) const {
    return data_[row];
  }

  static Matrix identity(int size) {
    Matrix result(size);
    for (int i = 0; i < size; ++i) {
      result[i][i] = 1;
    }
    return result;
  }

  Matrix operator*(const Matrix& other) const {
    Matrix result(size_);
    for (int i = 0; i < size_; ++i) {
      for (int j = 0; j < size_; ++j) {
        std::int64_t sum = 0;
        for (int k = 0; k < size_; ++k) {
          sum = (sum + data_[i][k] * other[k][j]) % MOD;
        }
        result[i][j] = sum;
      }
    }
    return result;
  }

  Matrix power(std::uint64_t exponent) const {
    Matrix base = *this;
    Matrix result = identity(size_);
    while (exponent > 0) {
      if (exponent & 1) {
        result = result * base;
      }
      base = base * base;
      exponent >>= 1;
    }
    return result;
  }
};

void optimize_input() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
}

Matrix transition_matrix() {
  Matrix result(MATRIX_SIZE);
  for (int i = 0; i < MATRIX_SIZE; ++i) {
    result[0][i] = 1;
    if (i > 0) {
      result[i][i - 1] = 1;
    }
  }
  return result;
}

int main() {
  optimize_input();

  std::uint64_t n = 0;
  std::cin >> n;
  std::cout << transition_matrix().power(n - 1)[0][0] << '\n';
}
