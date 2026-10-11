#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

constexpr std::uint32_t kInvalid = std::uint32_t{1} << 31;
using Masks                      = std::vector<std::uint32_t>;
using Graph                      = std::vector<std::uint64_t>;

Graph readGraph(int vertex_count) {
    Graph neighbors(vertex_count, 0);
    for (int vertex = 0; vertex < vertex_count; ++vertex) {
        std::string row{};
        std::cin >> row;
        for (int other = 0; other < vertex_count; ++other) {
            if (row[other] == '1') {
                neighbors[vertex] |= std::uint64_t{1} << other;
            }
        }
    }
    return neighbors;
}

Masks countRightCliques(const Graph& neighbors, int left_size) {
    const int right_size = static_cast<int>(neighbors.size()) - left_size;
    const std::uint32_t mask_count = std::uint32_t{1} << right_size;
    Masks counts(mask_count, 0);
    counts[0] = 1;
    for (std::uint32_t mask = 1; mask < mask_count; ++mask) {
        const int vertex              = __builtin_ctz(mask);
        const std::uint32_t remaining = mask & (mask - 1);
        const auto adjacent           = static_cast<std::uint32_t>(
            neighbors[left_size + vertex] >> left_size);
        counts[mask] = counts[remaining] + counts[remaining & adjacent];
    }
    return counts;
}

std::uint64_t countCliques(const Graph& neighbors) {
    const int left_size            = static_cast<int>(neighbors.size()) / 2;
    const auto right_counts        = countRightCliques(neighbors, left_size);
    const std::uint32_t mask_count = std::uint32_t{1} << left_size;
    Masks allowed(mask_count, kInvalid);
    allowed[0]           = static_cast<std::uint32_t>(right_counts.size()) - 1;
    std::uint64_t answer = right_counts.back();
    for (std::uint32_t mask = 1; mask < mask_count; ++mask) {
        const int vertex              = __builtin_ctz(mask);
        const std::uint32_t remaining = mask & (mask - 1);
        const auto adjacent = static_cast<std::uint32_t>(neighbors[vertex]);
        if (allowed[remaining] == kInvalid
            || (remaining & adjacent) != remaining) {
            continue;
        }
        allowed[mask] =
            allowed[remaining]
            & static_cast<std::uint32_t>(neighbors[vertex] >> left_size);
        answer += right_counts[allowed[mask]];
    }
    return answer;
}

void optimizeInput() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
}

int main() {
    optimizeInput();

    int vertex_count = 0;
    std::cin >> vertex_count;
    std::cout << countCliques(readGraph(vertex_count)) << '\n';
}
