#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

using Transitions = std::vector<std::vector<int>>;

bool areCompatible(int first, int second, int full_mask) {
    const int owned   = first & second;
    const int unowned = full_mask ^ (first | second);
    return (owned & (owned >> 1)) == 0 && (unowned & (unowned >> 1)) == 0;
}

Transitions buildTransitions(int width) {
    const int mask_count = 1 << width;
    Transitions transitions(mask_count);
    for (int first = 0; first < mask_count; ++first) {
        for (int second = 0; second < mask_count; ++second) {
            if (areCompatible(first, second, mask_count - 1)) {
                transitions[first].push_back(second);
            }
        }
    }
    return transitions;
}

std::int64_t countDistributions(int height, int width) {
    const auto transitions = buildTransitions(width);
    std::vector<std::int64_t> previous(transitions.size(), 1);
    std::vector<std::int64_t> current(transitions.size(), 0);
    for (int row = 1; row < height; ++row) {
        std::fill(current.begin(), current.end(), 0);
        for (int first = 0; first < static_cast<int>(transitions.size());
             ++first) {
            for (int second : transitions[first]) {
                current[second] += previous[first];
            }
        }
        previous.swap(current);
    }
    std::int64_t answer = 0;
    for (std::int64_t count : previous) {
        answer += count;
    }
    return answer;
}

void optimizeInput() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
}

int main() {
    optimizeInput();

    int height = 0;
    int width  = 0;
    std::cin >> height >> width;
    std::cout << countDistributions(std::max(height, width),
                                    std::min(height, width))
              << '\n';
}
