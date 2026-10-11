#include <cstdint>
#include <iostream>
#include <vector>

void optimizeInput() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
}

std::uint64_t countPeacefulSets(int sum_limit) {
    const int width = sum_limit + 1;
    std::vector<std::uint64_t> counts(width * width, 0);
    for (int limit = 0; limit <= sum_limit; ++limit) {
        counts[limit] = 1;
    }
    for (int sum = 1; sum <= sum_limit; ++sum) {
        for (int limit = 1; limit <= sum_limit; ++limit) {
            counts[(sum * width) + limit] = counts[(sum * width) + limit - 1];
            if (sum >= limit) {
                counts[(sum * width) + limit] +=
                    counts[((sum - limit) * width) + (limit / 2)];
            }
        }
    }
    return counts[(sum_limit * width) + sum_limit];
}

int main() {
    optimizeInput();

    int sum_limit = 0;
    std::cin >> sum_limit;
    std::cout << countPeacefulSets(sum_limit) << '\n';
}
