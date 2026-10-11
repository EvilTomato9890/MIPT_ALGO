#include <iostream>
#include <vector>

void optimizeInput() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
}

std::vector<int> readSequence() {
    int size = 0;
    std::cin >> size;
    std::vector<int> sequence(size, 0);
    for (int& value : sequence) {
        std::cin >> value;
    }
    return sequence;
}

std::vector<int> longestAlternatingSubsequence(
    const std::vector<int>& sequence) {
    std::vector<int> answer{};
    for (int value : sequence) {
        if (answer.empty()) {
            answer.push_back(value);
        } else if (value != answer.back()) {
            if (answer.size() == 1) {
                answer.push_back(value);
            } else {
                const bool was_increasing =
                    answer.back() > answer[answer.size() - 2];
                const bool is_increasing = value > answer.back();
                if (was_increasing == is_increasing) {
                    answer.back() = value;
                } else {
                    answer.push_back(value);
                }
            }
        }
    }
    return answer;
}

void printSequence(const std::vector<int>& sequence) {
    std::cout << sequence.size() << '\n';
    for (int value : sequence) {
        std::cout << value << ' ';
    }
    std::cout << '\n';
}

int main() {
    optimizeInput();

    const auto sequence = readSequence();
    printSequence(longestAlternatingSubsequence(sequence));
}
