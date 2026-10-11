#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

constexpr int kInfinity = std::numeric_limits<int>::max() / 2;
using Row               = std::vector<std::vector<int>>;

struct Words {
    const std::string& source;
    const std::string& target;
};

void updateCell(Row& current, const Row& previous, const Words& words,
                int source_size, int target_size) {
    const int budget = static_cast<int>(current[target_size].size()) - 1;
    for (int edits = 0; edits <= budget; ++edits) {
        auto& best = current[target_size][edits];
        if (target_size > 0) {
            const int mismatch = static_cast<int>(
                words.source[source_size - 1] != words.target[target_size - 1]);
            best = previous[target_size - 1][edits] + mismatch;
        }
        if (edits == 0) {
            continue;
        }
        best = std::min(best, previous[target_size][edits - 1]);
        if (target_size > 0) {
            best = std::min({best, previous[target_size - 1][edits - 1],
                             current[target_size - 1][edits - 1]});
        }
    }
}

int minMismatches(const std::string& source, const std::string& target,
                  int budget) {
    const int source_length = static_cast<int>(source.size());
    const int target_length = static_cast<int>(target.size());
    if (std::abs(source_length - target_length) > budget) {
        return -1;
    }
    Row previous(target_length + 1, std::vector<int>(budget + 1, kInfinity));
    Row current = previous;
    const Words words{source, target};
    for (int length = 0; length <= std::min(budget, target_length); ++length) {
        previous[length][length] = 0;
    }
    for (int length = 1; length <= source_length; ++length) {
        for (auto& cell : current) {
            std::fill(cell.begin(), cell.end(), kInfinity);
        }
        for (int matched = std::max(0, length - budget);
             matched <= std::min(target_length, length + budget); ++matched) {
            updateCell(current, previous, words, length, matched);
        }
        previous.swap(current);
    }
    return *std::min_element(previous.back().begin(), previous.back().end());
}

void optimizeInput() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
}

int main() {
    optimizeInput();

    std::string source{};
    std::string target{};
    int budget = 0;
    std::cin >> source >> target >> budget;
    std::cout << minMismatches(source, target, budget) << '\n';
}
