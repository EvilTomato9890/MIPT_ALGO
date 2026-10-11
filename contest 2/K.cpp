#include <cstdint>
#include <iostream>

std::int64_t minimumSum(std::int64_t point_count, std::int64_t segment_count) {
    if (segment_count == 0) {
        return 0;
    }
    const std::int64_t points_per_segment = point_count / segment_count;
    const std::int64_t longer_count       = point_count % segment_count;
    const std::int64_t shorter_length     = points_per_segment - 1;
    return ((segment_count - longer_count) * shorter_length * shorter_length)
           + (longer_count * points_per_segment * points_per_segment);
}

void optimizeInput() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
}

int main() {
    optimizeInput();

    std::int64_t point_count   = 0;
    std::int64_t segment_count = 0;
    std::cin >> point_count >> segment_count;
    std::cout << minimumSum(point_count, segment_count) << '\n';
}
