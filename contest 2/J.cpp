#include <cstdint>
#include <deque>
#include <iostream>

struct Line {
    std::int64_t slope     = 0;
    std::int64_t intercept = 0;
};

std::int64_t evaluate(const Line& line, std::int64_t height) {
    return (line.slope * height) + line.intercept;
}

bool isRedundant(const Line& first, const Line& middle, const Line& last) {
    return (middle.intercept - first.intercept) * (middle.slope - last.slope)
           >= (last.intercept - middle.intercept)
                  * (first.slope - middle.slope);
}

void addLine(std::deque<Line>& hull, const Line& line) {
    while (hull.size() >= 2
           && isRedundant(hull[hull.size() - 2], hull.back(), line)) {
        hull.pop_back();
    }
    hull.push_back(line);
}

std::int64_t minimumCost(int stone_count, std::int64_t jump_cost) {
    std::int64_t height = 0;
    std::cin >> height;
    std::deque<Line> hull{{-2 * height, height * height}};
    std::int64_t cost = 0;
    for (int stone = 1; stone < stone_count; ++stone) {
        std::cin >> height;
        while (hull.size() >= 2
               && evaluate(hull[0], height) >= evaluate(hull[1], height)) {
            hull.pop_front();
        }
        cost = (height * height) + jump_cost + evaluate(hull.front(), height);
        addLine(hull, {-2 * height, cost + (height * height)});
    }
    return cost;
}

void optimizeInput() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
}

int main() {
    optimizeInput();

    int stone_count        = 0;
    std::int64_t jump_cost = 0;
    std::cin >> stone_count >> jump_cost;
    std::cout << minimumCost(stone_count, jump_cost) << '\n';
}
