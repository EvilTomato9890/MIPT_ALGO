#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

constexpr int kInfinity = std::numeric_limits<int>::max() / 2;
using Table             = std::vector<std::vector<int>>;

Table readDistances(int city_count) {
    Table distances(city_count, std::vector<int>(city_count, 0));
    for (auto& row : distances) {
        for (auto& distance : row) {
            std::cin >> distance;
        }
    }
    return distances;
}

Table findPaths(const Table& distances) {
    const int city_count = static_cast<int>(distances.size());
    const int mask_count = 1 << city_count;
    Table best(mask_count, std::vector<int>(city_count, kInfinity));
    for (int city = 0; city < city_count; ++city) {
        best[1 << city][city] = 0;
    }
    for (int mask = 1; mask < mask_count; ++mask) {
        for (int city = 0; city < city_count; ++city) {
            if ((mask & (1 << city)) == 0) {
                continue;
            }
            const int previous = mask ^ (1 << city);
            for (int last = 0; last < city_count; ++last) {
                if ((previous & (1 << last)) != 0) {
                    best[mask][city] =
                        std::min(best[mask][city],
                                 best[previous][last] + distances[last][city]);
                }
            }
        }
    }
    return best;
}

std::vector<int> restorePath(const Table& best, const Table& distances,
                             int last) {
    int mask = static_cast<int>(best.size()) - 1;
    std::vector<int> path{};
    while (mask != 0) {
        path.push_back(last + 1);
        const int previous = mask ^ (1 << last);
        for (int city = 0; city < static_cast<int>(distances.size()); ++city) {
            if ((previous & (1 << city)) != 0
                && best[mask][last]
                       == best[previous][city] + distances[city][last]) {
                last = city;
                break;
            }
        }
        mask = previous;
    }
    std::reverse(path.begin(), path.end());
    return path;
}

void optimizeInput() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
}

int main() {
    optimizeInput();

    int city_count = 0;
    std::cin >> city_count;
    const auto distances = readDistances(city_count);
    const auto best      = findPaths(distances);
    const auto minimum =
        std::min_element(best.back().begin(), best.back().end());
    const int last = static_cast<int>(minimum - best.back().begin());
    std::cout << *minimum << '\n';
    for (int city : restorePath(best, distances, last)) {
        std::cout << city << ' ';
    }
    std::cout << '\n';
}
