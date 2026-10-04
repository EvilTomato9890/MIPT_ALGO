#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

void optimize_input() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
}

std::vector<int> read_sequence() {
  int n = 0;
  std::cin >> n;
  std::vector<int> sequence(n, 0);
  for (int& value : sequence) {
    std::cin >> value;
  }
  return sequence;
}

std::vector<int> restore_indices(const std::vector<int>& previous, int last) {
  std::vector<int> indices{};
  for (int i = last; i != -1; i = previous[i]) {
    indices.push_back(i + 1);
  }
  std::reverse(indices.begin(), indices.end());
  return indices;
}

std::vector<int> longest_nonincreasing_subsequence(
    const std::vector<int>& sequence) {
  const int n = static_cast<int>(sequence.size());
  std::vector<int> tails{};
  std::vector<int> tail_index{};
  std::vector<int> previous(n, -1);
  for (int i = 0; i < n; ++i) {
    const int value = sequence[i];
    const int position = static_cast<int>(
        std::upper_bound(tails.begin(), tails.end(), value, std::greater<int>())
        - tails.begin());
    if (position > 0) {
      previous[i] = tail_index[position - 1];
    }
    if (position == static_cast<int>(tails.size())) {
      tails.push_back(value);
      tail_index.push_back(i);
    } else {
      tails[position] = value;
      tail_index[position] = i;
    }
  }
  return restore_indices(previous, tail_index.back());
}

void print_indices(const std::vector<int>& indices) {
  std::cout << indices.size() << '\n';
  for (int index : indices) {
    std::cout << index << ' ';
  }
  std::cout << '\n';
}

int main() {
  optimize_input();

  const auto sequence = read_sequence();
  print_indices(longest_nonincreasing_subsequence(sequence));
}
