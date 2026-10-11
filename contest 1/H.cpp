#include <algorithm>
#include <array>
#include <cstdint>
#include <iostream>
#include <vector>

constexpr int MAX_LENGTH = 60;
using ChainRow = std::array<int, MAX_LENGTH + 1>;

void optimize_input() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
}

std::vector<std::uint64_t> read_missions() {
  int n = 0;
  std::cin >> n;
  std::vector<std::uint64_t> missions(n, 0);
  for (auto& difficulty : missions) {
    std::cin >> difficulty;
  }
  return missions;
}

std::vector<std::uint64_t> repeat_circle(
    const std::vector<std::uint64_t>& missions) {
  auto repeated = missions;
  repeated.insert(repeated.end(), missions.begin(), missions.end());
  return repeated;
}

std::vector<int> restore_chain(const std::vector<ChainRow>& previous, int last,
                               int length, int n) {
  std::vector<int> answer{};
  int i = last;
  for (int len = length; len > 0; --len) {
    answer.push_back(i % n + 1);
    i = previous[i][len];
  }
  std::reverse(answer.begin(), answer.end());
  return answer;
}

std::vector<int> longest_mission_chain(
    const std::vector<std::uint64_t>& missions) {
  const int n = static_cast<int>(missions.size());
  const auto a = repeat_circle(missions);
  ChainRow empty_row{};
  empty_row.fill(-1);
  std::vector<ChainRow> start(2 * n, empty_row);
  std::vector<ChainRow> previous(2 * n, empty_row);
  std::vector<int> length(2 * n, 1);
  int best_length = 1;
  int best_end = 0;
  for (int i = 0; i < 2 * n; ++i) {
    start[i][1] = i;
    for (int j = std::max(0, i - n + 1); j < i; ++j) {
      if (a[i] <= a[j] || a[i] % a[j] != 0) {
        continue;
      }
      for (int len = 1; len <= length[j] && len < MAX_LENGTH; ++len) {
        if (start[j][len] <= i - n) {
          continue;
        }
        if (start[j][len] > start[i][len + 1]) {
          start[i][len + 1] = start[j][len];
          previous[i][len + 1] = j;
          length[i] = std::max(length[i], len + 1);
        }
      }
    }
    if (length[i] > best_length) {
      best_length = length[i];
      best_end = i;
    }
  }
  return restore_chain(previous, best_end, best_length, n);
}

void print_missions(const std::vector<int>& missions) {
  std::cout << missions.size() << '\n';
  for (int mission : missions) {
    std::cout << mission << ' ';
  }
  std::cout << '\n';
}

int main() {
  optimize_input();

  const auto missions = read_missions();
  print_missions(longest_mission_chain(missions));
}
