#include <algorithm>
#include <iostream>
#include <vector>

using Table = std::vector<std::vector<int>>;

struct Missions {
    std::vector<int> weight;
    std::vector<int> reward;
};

void optimizeInput() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
}

Missions readMissions(int mission_count) {
    Missions missions{std::vector<int>(mission_count + 1, 0),
                      std::vector<int>(mission_count + 1, 0)};
    for (int i = 1; i <= mission_count; ++i) {
        std::cin >> missions.weight[i];
    }
    for (int i = 1; i <= mission_count; ++i) {
        std::cin >> missions.reward[i];
    }
    return missions;
}

Table buildKnapsackTable(const Missions& missions, int capacity) {
    const int mission_count = static_cast<int>(missions.weight.size()) - 1;
    Table best(mission_count + 1, std::vector<int>(capacity + 1, 0));
    for (int i = 1; i <= mission_count; ++i) {
        for (int remaining = 0; remaining <= capacity; ++remaining) {
            best[i][remaining] = best[i - 1][remaining];
            if (missions.weight[i] <= remaining) {
                best[i][remaining] =
                    std::max(best[i][remaining],
                             best[i - 1][remaining - missions.weight[i]]
                                 + missions.reward[i]);
            }
        }
    }
    return best;
}

std::vector<int> restoreMissions(const Missions& missions, const Table& best,
                                 int capacity) {
    const int mission_count = static_cast<int>(missions.weight.size()) - 1;
    std::vector<int> answer{};
    int remaining = capacity;
    for (int i = mission_count; i > 0; --i) {
        if (best[i][remaining] != best[i - 1][remaining]) {
            answer.push_back(i);
            remaining -= missions.weight[i];
        }
    }
    std::reverse(answer.begin(), answer.end());
    return answer;
}

void printMissions(const std::vector<int>& missions) {
    for (int mission : missions) {
        std::cout << mission << '\n';
    }
}

int main() {
    optimizeInput();

    int mission_count = 0;
    int capacity      = 0;
    std::cin >> mission_count >> capacity;
    const auto missions = readMissions(mission_count);
    const auto best     = buildKnapsackTable(missions, capacity);
    printMissions(restoreMissions(missions, best, capacity));
}
