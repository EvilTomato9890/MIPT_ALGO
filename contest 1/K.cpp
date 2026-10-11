#include <algorithm>
#include <iostream>
#include <vector>

void optimize_input() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
}

std::vector<int> read_sequence(int size) {
  std::vector<int> sequence(size, 0);
  for (int& value : sequence) {
    std::cin >> value;
  }
  return sequence;
}

int common_increasing_length(const std::vector<int>& a,
                             const std::vector<int>& b) {
  const int m = static_cast<int>(b.size());
  std::vector<int> dp(m, 0);
  for (int value : a) {
    int best = 0;
    for (int j = 0; j < m; ++j) {
      if (b[j] < value) {
        best = std::max(best, dp[j]);
      } else if (b[j] == value) {
        dp[j] = std::max(dp[j], best + 1);
      }
    }
  }
  return *std::max_element(dp.begin(), dp.end());
}

int main() {
  optimize_input();

  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  const auto a = read_sequence(n);
  const auto b = read_sequence(m);
  std::cout << common_increasing_length(a, b) << '\n';
}
