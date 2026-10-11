#include <algorithm>
#include <iostream>
#include <vector>

using Table = std::vector<std::vector<int>>;

struct Placement {
    int total_cost = 0;
    std::vector<int> points;
};

void optimizeInput() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
}

std::vector<int> readHouses(int house_count) {
    std::vector<int> houses(house_count + 1, 0);
    for (int i = 1; i <= house_count; ++i) {
        std::cin >> houses[i];
    }
    return houses;
}

Table buildGroupCosts(const std::vector<int>& houses) {
    const int house_count = static_cast<int>(houses.size()) - 1;
    std::vector<int> prefix(house_count + 1, 0);
    for (int i = 1; i <= house_count; ++i) {
        prefix[i] = prefix[i - 1] + houses[i];
    }
    Table cost(house_count + 1, std::vector<int>(house_count + 1, 0));
    for (int left = 1; left <= house_count; ++left) {
        for (int right = left; right <= house_count; ++right) {
            const int median  = (left + right) / 2;
            cost[left][right] = (houses[median] * (median - left + 1))
                                - (prefix[median] - prefix[left - 1])
                                + prefix[right] - prefix[median]
                                - (houses[median] * (right - median));
        }
    }
    return cost;
}

std::vector<int> restorePoints(const std::vector<int>& houses,
                               const Table& split, int point_count) {
    std::vector<int> points{};
    int right = static_cast<int>(houses.size()) - 1;
    for (int groups = point_count; groups > 0; --groups) {
        const int left = split[groups][right];
        points.push_back(houses[(left + 1 + right) / 2]);
        right = left;
    }
    std::reverse(points.begin(), points.end());
    return points;
}

Placement choosePoints(const std::vector<int>& houses, int point_count) {
    constexpr int inf     = 1000000000;
    const int house_count = static_cast<int>(houses.size()) - 1;
    const auto cost       = buildGroupCosts(houses);
    Table best(point_count + 1, std::vector<int>(house_count + 1, inf));
    Table split(point_count + 1, std::vector<int>(house_count + 1, 0));
    best[0][0] = 0;
    for (int groups = 1; groups <= point_count; ++groups) {
        for (int right = groups; right <= house_count; ++right) {
            for (int left = groups - 1; left < right; ++left) {
                const int candidate =
                    best[groups - 1][left] + cost[left + 1][right];
                if (candidate < best[groups][right]) {
                    best[groups][right]  = candidate;
                    split[groups][right] = left;
                }
            }
        }
    }
    return {best[point_count][house_count],
            restorePoints(houses, split, point_count)};
}

void printPlacement(const Placement& placement) {
    std::cout << placement.total_cost << '\n';
    for (int coordinate : placement.points) {
        std::cout << coordinate << ' ';
    }
    std::cout << '\n';
}

int main() {
    optimizeInput();

    int house_count = 0;
    int point_count = 0;
    std::cin >> house_count >> point_count;
    const auto houses = readHouses(house_count);
    printPlacement(choosePoints(houses, point_count));
}
