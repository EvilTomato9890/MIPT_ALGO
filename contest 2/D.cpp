#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

constexpr int kModulo = 1000000007;

struct Column {
    int protected_mask = 0;
    int captured_mask  = 0;
};

std::vector<Column> readColumns(int height, int width) {
    std::vector<Column> columns(width);
    for (int row = 0; row < height; ++row) {
        std::string cells{};
        std::cin >> cells;
        for (int column = 0; column < width; ++column) {
            if (cells[column] == '+') {
                columns[column].protected_mask |= 1 << row;
            } else if (cells[column] == '-') {
                columns[column].captured_mask |= 1 << row;
            }
        }
    }
    return columns;
}

bool fitsColumn(int mask, const Column& column) {
    return (mask & column.protected_mask) == column.protected_mask
           && (mask & column.captured_mask) == 0;
}

int countCities(const std::vector<Column>& columns, int height) {
    const int mask_count    = 1 << height;
    const int full_mask     = mask_count - 1;
    const int neighbor_mask = (1 << (height - 1)) - 1;
    std::vector<int> previous(mask_count, 0);
    std::vector<int> current(mask_count, 0);
    for (int mask = 0; mask < mask_count; ++mask) {
        previous[mask] = static_cast<int>(fitsColumn(mask, columns.front()));
    }
    for (int column = 1; column < static_cast<int>(columns.size()); ++column) {
        for (int mask = 0; mask < mask_count; ++mask) {
            current[mask] = 0;
            if (!fitsColumn(mask, columns[column])) {
                continue;
            }
            current[mask] = previous[full_mask ^ mask];
            if (((mask ^ (mask >> 1)) & neighbor_mask) == neighbor_mask) {
                current[mask] = (current[mask] + previous[mask]) % kModulo;
            }
        }
        previous.swap(current);
    }
    std::int64_t answer = 0;
    for (int count : previous) {
        answer += count;
    }
    return static_cast<int>(answer % kModulo);
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
    const auto columns = readColumns(height, width);
    std::cout << countCities(columns, height) << '\n';
}
