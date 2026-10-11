#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using Table = std::vector<std::vector<int>>;

struct CommonDance {
  std::vector<int> first{};
  std::vector<int> second{};
};

void optimize_input() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
}

Table build_lcs_table(const std::string& a, const std::string& b) {
  const int n = static_cast<int>(a.size());
  const int m = static_cast<int>(b.size());
  Table dp(n + 1, std::vector<int>(m + 1, 0));
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      if (a[i - 1] == b[j - 1]) {
        dp[i][j] = dp[i - 1][j - 1] + 1;
      } else {
        dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
      }
    }
  }
  return dp;
}

CommonDance restore_dance(const std::string& a, const std::string& b,
                          const Table& dp) {
  CommonDance dance{};
  int i = static_cast<int>(a.size());
  int j = static_cast<int>(b.size());
  while (i > 0 && j > 0) {
    if (a[i - 1] == b[j - 1]) {
      dance.first.push_back(i);
      dance.second.push_back(j);
      --i;
      --j;
    } else if (dp[i - 1][j] >= dp[i][j - 1]) {
      --i;
    } else {
      --j;
    }
  }
  std::reverse(dance.first.begin(), dance.first.end());
  std::reverse(dance.second.begin(), dance.second.end());
  return dance;
}

void print_indices(const std::vector<int>& indices) {
  for (int index : indices) {
    std::cout << index << ' ';
  }
  std::cout << '\n';
}

void print_dance(const CommonDance& dance) {
  std::cout << dance.first.size() << '\n';
  print_indices(dance.first);
  print_indices(dance.second);
}

int main() {
  optimize_input();

  std::string a{};
  std::string b{};
  std::cin >> a >> b;
  const auto dp = build_lcs_table(a, b);
  print_dance(restore_dance(a, b, dp));
}
