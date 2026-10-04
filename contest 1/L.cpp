#include <algorithm>
#include <iostream>
#include <vector>

using Table = std::vector<std::vector<int>>;

struct Missions {
  std::vector<int> weight{};
  std::vector<int> reward{};
};

void optimize_input() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
}

Missions read_missions(int n) {
  Missions missions{std::vector<int>(n + 1, 0), std::vector<int>(n + 1, 0)};
  for (int i = 1; i <= n; ++i) {
    std::cin >> missions.weight[i];
  }
  for (int i = 1; i <= n; ++i) {
    std::cin >> missions.reward[i];
  }
  return missions;
}

Table build_knapsack_table(const Missions& missions, int capacity) {
  const int n = static_cast<int>(missions.weight.size()) - 1;
  Table dp(n + 1, std::vector<int>(capacity + 1, 0));
  for (int i = 1; i <= n; ++i) {
    for (int remaining = 0; remaining <= capacity; ++remaining) {
      dp[i][remaining] = dp[i - 1][remaining];
      if (missions.weight[i] <= remaining) {
        dp[i][remaining] =
            std::max(dp[i][remaining], dp[i - 1][remaining - missions.weight[i]]
                                           + missions.reward[i]);
      }
    }
  }
  return dp;
}

std::vector<int> restore_missions(const Missions& missions, const Table& dp,
                                  int capacity) {
  const int n = static_cast<int>(missions.weight.size()) - 1;
  std::vector<int> answer{};
  int remaining = capacity;
  for (int i = n; i > 0; --i) {
    if (dp[i][remaining] != dp[i - 1][remaining]) {
      answer.push_back(i);
      remaining -= missions.weight[i];
    }
  }
  std::reverse(answer.begin(), answer.end());
  return answer;
}

void print_missions(const std::vector<int>& missions) {
  for (int mission : missions) {
    std::cout << mission << '\n';
  }
}

int main() {
  optimize_input();

  int n = 0;
  int capacity = 0;
  std::cin >> n >> capacity;
  const auto missions = read_missions(n);
  const auto dp = build_knapsack_table(missions, capacity);
  print_missions(restore_missions(missions, dp, capacity));
}
