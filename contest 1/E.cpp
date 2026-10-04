#include <algorithm>
#include <iostream>
#include <vector>

using Table = std::vector<std::vector<int>>;

struct Placement {
  int total_cost = 0;
  std::vector<int> points{};
};

void optimize_input() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
}

std::vector<int> read_houses(int n) {
  std::vector<int> houses(n + 1, 0);
  for (int i = 1; i <= n; ++i) {
    std::cin >> houses[i];
  }
  return houses;
}

Table build_group_costs(const std::vector<int>& houses) {
  const int n = static_cast<int>(houses.size()) - 1;
  std::vector<int> prefix(n + 1, 0);
  for (int i = 1; i <= n; ++i) {
    prefix[i] = prefix[i - 1] + houses[i];
  }
  Table cost(n + 1, std::vector<int>(n + 1, 0));
  for (int left = 1; left <= n; ++left) {
    for (int right = left; right <= n; ++right) {
      const int median = (left + right) / 2;
      cost[left][right] = houses[median] * (median - left + 1)
                          - (prefix[median] - prefix[left - 1]) + prefix[right]
                          - prefix[median] - houses[median] * (right - median);
    }
  }
  return cost;
}

std::vector<int> restore_points(const std::vector<int>& houses,
                                const Table& split, int m) {
  std::vector<int> points{};
  int right = static_cast<int>(houses.size()) - 1;
  for (int groups = m; groups > 0; --groups) {
    const int left = split[groups][right];
    points.push_back(houses[(left + 1 + right) / 2]);
    right = left;
  }
  std::reverse(points.begin(), points.end());
  return points;
}

Placement choose_points(const std::vector<int>& houses, int m) {
  constexpr int INF = 1000000000;
  const int n = static_cast<int>(houses.size()) - 1;
  const auto cost = build_group_costs(houses);
  Table dp(m + 1, std::vector<int>(n + 1, INF));
  Table split(m + 1, std::vector<int>(n + 1, 0));
  dp[0][0] = 0;
  for (int groups = 1; groups <= m; ++groups) {
    for (int right = groups; right <= n; ++right) {
      for (int left = groups - 1; left < right; ++left) {
        const int candidate = dp[groups - 1][left] + cost[left + 1][right];
        if (candidate < dp[groups][right]) {
          dp[groups][right] = candidate;
          split[groups][right] = left;
        }
      }
    }
  }
  return {dp[m][n], restore_points(houses, split, m)};
}

void print_placement(const Placement& placement) {
  std::cout << placement.total_cost << '\n';
  for (int coordinate : placement.points) {
    std::cout << coordinate << ' ';
  }
  std::cout << '\n';
}

int main() {
  optimize_input();

  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  const auto houses = read_houses(n);
  print_placement(choose_points(houses, m));
}
