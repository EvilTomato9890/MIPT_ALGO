#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

constexpr std::int64_t kModulo = 1000000007;
using Matrix                   = std::vector<std::vector<std::int64_t>>;
using Counts                   = std::vector<std::int64_t>;

Matrix buildTransition(int height) {
    Matrix matrix(height + 1, Counts(height + 1, 0));
    for (int from = 0; from <= height; ++from) {
        for (int to = std::max(0, from - 1); to <= std::min(height, from + 1);
             ++to) {
            matrix[from][to] = 1;
        }
    }
    return matrix;
}

Matrix multiply(const Matrix& first, const Matrix& second) {
    const int size = static_cast<int>(first.size());
    Matrix result(size, Counts(size, 0));
    for (int row = 0; row < size; ++row) {
        for (int middle = 0; middle < size; ++middle) {
            for (int column = 0; column < size; ++column) {
                result[row][column] =
                    (result[row][column]
                     + (first[row][middle] * second[middle][column]))
                    % kModulo;
            }
        }
    }
    return result;
}

Counts applyTransition(const Counts& counts, const Matrix& matrix) {
    Counts result(counts.size(), 0);
    for (int from = 0; from < static_cast<int>(counts.size()); ++from) {
        for (int to = 0; to < static_cast<int>(counts.size()); ++to) {
            result[to] =
                (result[to] + (counts[from] * matrix[from][to])) % kModulo;
        }
    }
    return result;
}

Counts walkSegment(Counts counts, int height, std::uint64_t length) {
    counts.resize(height + 1, 0);
    auto transition = buildTransition(height);
    while (length != 0) {
        if ((length & 1U) != 0) {
            counts = applyTransition(counts, transition);
        }
        length >>= 1;
        if (length != 0) {
            transition = multiply(transition, transition);
        }
    }
    return counts;
}

void optimizeInput() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
}

int main() {
    optimizeInput();

    int segment_count         = 0;
    std::uint64_t destination = 0;
    std::cin >> segment_count >> destination;
    Counts counts(1, 1);
    for (int segment = 0; segment < segment_count; ++segment) {
        std::uint64_t left  = 0;
        std::uint64_t right = 0;
        int height          = 0;
        std::cin >> left >> right >> height;
        counts =
            walkSegment(counts, height, std::min(right, destination) - left);
    }
    std::cout << counts.front() << '\n';
}
