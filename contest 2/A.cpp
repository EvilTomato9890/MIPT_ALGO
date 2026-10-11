#include <algorithm>
#include <iostream>
#include <vector>

struct Algorithm {
    int examples = 0;
    int correct  = 0;
};

using Groups = std::vector<std::vector<Algorithm>>;

Groups readGroups(int algorithm_count, int group_count) {
    Groups groups(group_count);
    for (int index = 0; index < algorithm_count; ++index) {
        Algorithm algorithm{};
        int group = 0;
        std::cin >> algorithm.examples >> algorithm.correct >> group;
        groups[group - 1].push_back(algorithm);
    }
    return groups;
}

int maxCorrect(const Groups& groups, int capacity) {
    std::vector<int> best(capacity + 1, 0);
    for (const auto& group : groups) {
        auto next = best;
        for (const auto& algorithm : group) {
            for (int limit = algorithm.examples; limit <= capacity; ++limit) {
                next[limit] =
                    std::max(next[limit], best[limit - algorithm.examples]
                                              + algorithm.correct);
            }
        }
        best.swap(next);
    }
    return best[capacity];
}

void optimizeInput() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
}

int main() {
    optimizeInput();

    int algorithm_count = 0;
    int group_count     = 0;
    int capacity        = 0;
    std::cin >> algorithm_count >> group_count >> capacity;
    const auto groups = readGroups(algorithm_count, group_count);
    std::cout << maxCorrect(groups, capacity) << '\n';
}
