#include <cstdint>
#include <iostream>
#include <utility>

constexpr std::int64_t kMod = 1000003;

void optimizeInput() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
}

std::pair<std::int64_t, std::int64_t> fibonacci(std::uint64_t index) {
    if (index == 0) {
        return {0, 1};
    }
    const auto [current, next] = fibonacci(index / 2);
    const auto doubled =
        current * (((2 * next) - current + kMod) % kMod) % kMod;
    const auto doubled_next = ((current * current) + (next * next)) % kMod;
    if (index % 2 == 0) {
        return {doubled, doubled_next};
    }
    return {doubled_next, (doubled + doubled_next) % kMod};
}

int main() {
    optimizeInput();

    std::uint64_t index = 0;
    std::cin >> index;
    std::cout << fibonacci(index - 1).first << '\n';
}
