#include <cstdint>
#include <iostream>
#include <vector>

void optimize_input() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
}

std::uint64_t count_peaceful_sets(int n) {
  const int width = n + 1;
  std::vector<std::uint64_t> dp(width * width, 0);
  for (int limit = 0; limit <= n; ++limit) {
    dp[limit] = 1;
  }
  for (int sum = 1; sum <= n; ++sum) {
    for (int limit = 1; limit <= n; ++limit) {
      dp[sum * width + limit] = dp[sum * width + limit - 1];
      if (sum >= limit) {
        dp[sum * width + limit] += dp[(sum - limit) * width + limit / 2];
      }
    }
  }
  return dp[n * width + n];
}

int main() {
  optimize_input();

  int n = 0;
  std::cin >> n;
  std::cout << count_peaceful_sets(n) << '\n';
}
