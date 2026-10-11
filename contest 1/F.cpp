#include <algorithm>
#include <iostream>
#include <vector>

void optimize_input() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
}

int useful_plane_count(int n) {
  int planes = 0;
  for (int possibilities = 1; possibilities < n; possibilities *= 2) {
    ++planes;
  }
  return planes;
}

int minimum_experiments(int n, int k) {
  if (n == 1) {
    return 0;
  }
  if (k == 0) {
    return -1;
  }
  k = std::min(k, useful_plane_count(n));
  std::vector<int> covered(k + 1, 0);
  int experiments = 0;
  while (covered[k] < n - 1) {
    ++experiments;
    for (int planes = k; planes >= 1; --planes) {
      covered[planes] =
          std::min(n - 1, covered[planes] + covered[planes - 1] + 1);
    }
  }
  return experiments;
}

int main() {
  optimize_input();

  int n = 0;
  int k = 0;
  std::cin >> n >> k;
  std::cout << minimum_experiments(n, k) << '\n';
}
