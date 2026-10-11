#include <algorithm>
#include <iostream>
#include <vector>

void optimizeInput() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
}

int usefulPlaneCount(int level_count) {
    int planes = 0;
    for (int possibilities  = 1; possibilities < level_count;
         possibilities     *= 2) {
        ++planes;
    }
    return planes;
}

int minimumExperiments(int level_count, int plane_count) {
    if (level_count == 1) {
        return 0;
    }
    if (plane_count == 0) {
        return -1;
    }
    plane_count = std::min(plane_count, usefulPlaneCount(level_count));
    std::vector<int> covered(plane_count + 1, 0);
    int experiments = 0;
    while (covered[plane_count] < level_count - 1) {
        ++experiments;
        for (int planes = plane_count; planes >= 1; --planes) {
            covered[planes] = std::min(
                level_count - 1, covered[planes] + covered[planes - 1] + 1);
        }
    }
    return experiments;
}

int main() {
    optimizeInput();

    int level_count = 0;
    int plane_count = 0;
    std::cin >> level_count >> plane_count;
    std::cout << minimumExperiments(level_count, plane_count) << '\n';
}
