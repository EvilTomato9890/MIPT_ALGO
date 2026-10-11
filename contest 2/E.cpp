#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

std::vector<int> readNetwork(int computer_count) {
    std::vector<int> neighbors(computer_count, 0);
    for (int computer = 0; computer < computer_count; ++computer) {
        std::string row{};
        std::cin >> row;
        for (int other = 0; other < computer_count; ++other) {
            if (row[other] == 'Y') {
                neighbors[computer] |= 1 << other;
            }
        }
    }
    return neighbors;
}

int maxParticipants(const std::vector<int>& neighbors) {
    const int mask_count = 1 << neighbors.size();
    std::vector<int> best(mask_count, 0);
    for (int mask = 1; mask < mask_count; ++mask) {
        const int computer  = __builtin_ctz(static_cast<unsigned int>(mask));
        const int remaining = mask ^ (1 << computer);
        best[mask]          = best[remaining];
        int partners        = remaining & neighbors[computer];
        while (partners != 0) {
            const int other =
                __builtin_ctz(static_cast<unsigned int>(partners));
            best[mask] =
                std::max(best[mask], best[remaining ^ (1 << other)] + 2);
            partners &= partners - 1;
        }
    }
    return best.back();
}

void optimizeInput() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
}

int main() {
    optimizeInput();

    int computer_count = 0;
    std::cin >> computer_count;
    std::cout << maxParticipants(readNetwork(computer_count)) << '\n';
}
