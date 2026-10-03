#include <cstdint>
#include <iostream>
#include <utility>

constexpr std::int64_t MOD = 1000003;

void optimize_input() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
}

std::pair<std::int64_t, std::int64_t> fibonacci(std::uint64_t n) {
  if (n == 0) {
    return {0, 1};
  }
  const auto [a, b] = fibonacci(n / 2);
  const auto c = a * ((2 * b - a + MOD) % MOD) % MOD;
  const auto d = (a * a + b * b) % MOD;
  if (n % 2 == 0) {
    return {c, d};
  }
  return {d, (c + d) % MOD};
}

int main() {
  optimize_input();

  std::uint64_t n = 0;
  std::cin >> n;
  std::cout << fibonacci(n - 1).first << '\n';
}
