#include <algorithm>
#include <iostream>
#include <vector>

void optimizeInput() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
}

std::vector<int> readSequence(int size) {
    std::vector<int> sequence(size, 0);
    for (int& value : sequence) {
        std::cin >> value;
    }
    return sequence;
}

int commonIncreasingLength(const std::vector<int>& first,
                           const std::vector<int>& second) {
    const int second_size = static_cast<int>(second.size());
    std::vector<int> best(second_size, 0);
    for (int value : first) {
        int current_best = 0;
        for (int j = 0; j < second_size; ++j) {
            if (second[j] < value) {
                current_best = std::max(current_best, best[j]);
            } else if (second[j] == value) {
                best[j] = std::max(best[j], current_best + 1);
            }
        }
    }
    return *std::max_element(best.begin(), best.end());
}

int main() {
    optimizeInput();

    int first_size  = 0;
    int second_size = 0;
    std::cin >> first_size >> second_size;
    const auto first  = readSequence(first_size);
    const auto second = readSequence(second_size);
    std::cout << commonIncreasingLength(first, second) << '\n';
}
