#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

constexpr int kDecimalBase = 10;
using Matrix               = std::vector<std::vector<int>>;
using Counts               = std::vector<int>;

bool areCompatible(int first, int second, int full_mask) {
    const int owned   = first & second;
    const int unowned = full_mask ^ (first | second);
    return (owned & (owned >> 1)) == 0 && (unowned & (unowned >> 1)) == 0;
}

Matrix buildTransition(int width, int modulo) {
    const int state_count = 1 << (width - 1);
    const int full_mask   = (1 << width) - 1;
    Matrix matrix(state_count, Counts(state_count, 0));
    for (int first = 0; first < state_count; ++first) {
        for (int second = 0; second < state_count; ++second) {
            matrix[first][second] =
                (static_cast<int>(areCompatible(first, second, full_mask))
                 + static_cast<int>(
                     areCompatible(first, full_mask ^ second, full_mask)))
                % modulo;
        }
    }
    return matrix;
}

Matrix multiply(const Matrix& first, const Matrix& second, int modulo) {
    const int size = static_cast<int>(first.size());
    Matrix result(size, Counts(size, 0));
    for (int row = 0; row < size; ++row) {
        for (int column = 0; column < size; ++column) {
            std::int64_t sum = 0;
            for (int middle = 0; middle < size; ++middle) {
                sum += static_cast<std::int64_t>(first[row][middle])
                       * second[middle][column];
            }
            result[row][column] = static_cast<int>(sum % modulo);
        }
    }
    return result;
}

Counts applyTransition(const Counts& counts, const Matrix& matrix, int modulo) {
    Counts result(counts.size(), 0);
    for (int to = 0; to < static_cast<int>(counts.size()); ++to) {
        std::int64_t sum = 0;
        for (int from = 0; from < static_cast<int>(counts.size()); ++from) {
            sum += static_cast<std::int64_t>(counts[from]) * matrix[from][to];
        }
        result[to] = static_cast<int>(sum % modulo);
    }
    return result;
}

void decrement(std::string& number) {
    for (int index = static_cast<int>(number.size()) - 1; index >= 0; --index) {
        if (number[index] != '0') {
            --number[index];
            break;
        }
        number[index] = '9';
    }
}

bool halve(std::string& number) {
    int remainder = 0;
    for (char& digit : number) {
        const int value = (remainder * kDecimalBase) + digit - '0';
        digit           = static_cast<char>('0' + (value / 2));
        remainder       = value % 2;
    }
    return remainder != 0;
}

int countDistributions(std::string height, int width, int modulo) {
    decrement(height);
    auto transition = buildTransition(width, modulo);
    Counts counts(transition.size(), 1 % modulo);
    while (height.find_first_not_of('0') != std::string::npos) {
        if (halve(height)) {
            counts = applyTransition(counts, transition, modulo);
        }
        if (height.find_first_not_of('0') != std::string::npos) {
            transition = multiply(transition, transition, modulo);
        }
    }
    int answer = 0;
    for (int count : counts) {
        answer = (answer + (2 * count)) % modulo;
    }
    return answer;
}

void optimizeInput() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
}

int main() {
    optimizeInput();

    std::string height{};
    int width  = 0;
    int modulo = 0;
    std::cin >> height >> width >> modulo;
    std::cout << countDistributions(height, width, modulo) << '\n';
}
