#include <algorithm>
#include <array>
#include <cstdint>
#include <iostream>
#include <vector>

constexpr int kMaxLength = 60;
using ChainRow           = std::array<int, kMaxLength + 1>;

struct ChainState {
    std::vector<ChainRow> start;
    std::vector<ChainRow> previous;
    std::vector<int> length;
};

ChainState createChainState(int mission_count) {
    ChainRow empty_row{};
    empty_row.fill(-1);
    return {std::vector<ChainRow>(2 * mission_count, empty_row),
            std::vector<ChainRow>(2 * mission_count, empty_row),
            std::vector<int>(2 * mission_count, 1)};
}

void optimizeInput() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
}

std::vector<std::uint64_t> readMissions() {
    int mission_count = 0;
    std::cin >> mission_count;
    std::vector<std::uint64_t> missions(mission_count, 0);
    for (auto& difficulty : missions) {
        std::cin >> difficulty;
    }
    return missions;
}

std::vector<std::uint64_t> repeatCircle(
    const std::vector<std::uint64_t>& missions) {
    auto repeated = missions;
    repeated.insert(repeated.end(), missions.begin(), missions.end());
    return repeated;
}

std::vector<int> restoreChain(const std::vector<ChainRow>& previous, int last,
                              int length, int mission_count) {
    std::vector<int> answer{};
    int index = last;
    for (int chain_length = length; chain_length > 0; --chain_length) {
        answer.push_back((index % mission_count) + 1);
        index = previous[index][chain_length];
    }
    std::reverse(answer.begin(), answer.end());
    return answer;
}

void extendChains(ChainState& state,
                  const std::vector<std::uint64_t>& difficulties, int end,
                  int mission_count) {
    for (int last = std::max(0, end - mission_count + 1); last < end; ++last) {
        if (difficulties[end] <= difficulties[last]
            || difficulties[end] % difficulties[last] != 0) {
            continue;
        }
        for (int length = 1;
             length <= state.length[last] && length < kMaxLength; ++length) {
            if (state.start[last][length] <= end - mission_count) {
                continue;
            }
            if (state.start[last][length] > state.start[end][length + 1]) {
                state.start[end][length + 1]    = state.start[last][length];
                state.previous[end][length + 1] = last;
                state.length[end] = std::max(state.length[end], length + 1);
            }
        }
    }
}

std::vector<int> longestMissionChain(
    const std::vector<std::uint64_t>& missions) {
    const int mission_count = static_cast<int>(missions.size());
    const auto difficulties = repeatCircle(missions);
    auto state              = createChainState(mission_count);
    int best_length         = 1;
    int best_end            = 0;
    for (int index = 0; index < 2 * mission_count; ++index) {
        state.start[index][1] = index;
        extendChains(state, difficulties, index, mission_count);
        if (state.length[index] > best_length) {
            best_length = state.length[index];
            best_end    = index;
        }
    }
    return restoreChain(state.previous, best_end, best_length, mission_count);
}

void printMissions(const std::vector<int>& missions) {
    std::cout << missions.size() << '\n';
    for (int mission : missions) {
        std::cout << mission << ' ';
    }
    std::cout << '\n';
}

int main() {
    optimizeInput();

    const auto missions = readMissions();
    printMissions(longestMissionChain(missions));
}
