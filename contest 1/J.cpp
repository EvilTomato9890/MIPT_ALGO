#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using Table = std::vector<std::vector<int>>;

struct CommonDance {
    std::vector<int> first;
    std::vector<int> second;
};

void optimizeInput() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
}

Table buildLcsTable(const std::string& first_text,
                    const std::string& second_text) {
    const int first_length  = static_cast<int>(first_text.size());
    const int second_length = static_cast<int>(second_text.size());
    Table best(first_length + 1, std::vector<int>(second_length + 1, 0));
    for (int first_index = 1; first_index <= first_length; ++first_index) {
        for (int second_index = 1; second_index <= second_length;
             ++second_index) {
            if (first_text[first_index - 1] == second_text[second_index - 1]) {
                best[first_index][second_index] =
                    best[first_index - 1][second_index - 1] + 1;
            } else {
                best[first_index][second_index] =
                    std::max(best[first_index - 1][second_index],
                             best[first_index][second_index - 1]);
            }
        }
    }
    return best;
}

CommonDance restoreDance(const std::string& first_text,
                         const std::string& second_text, const Table& best) {
    CommonDance dance{};
    int first_index  = static_cast<int>(first_text.size());
    int second_index = static_cast<int>(second_text.size());
    while (first_index > 0 && second_index > 0) {
        if (first_text[first_index - 1] == second_text[second_index - 1]) {
            dance.first.push_back(first_index);
            dance.second.push_back(second_index);
            --first_index;
            --second_index;
        } else if (best[first_index - 1][second_index]
                   >= best[first_index][second_index - 1]) {
            --first_index;
        } else {
            --second_index;
        }
    }
    std::reverse(dance.first.begin(), dance.first.end());
    std::reverse(dance.second.begin(), dance.second.end());
    return dance;
}

void printIndices(const std::vector<int>& indices) {
    for (int index : indices) {
        std::cout << index << ' ';
    }
    std::cout << '\n';
}

void printDance(const CommonDance& dance) {
    std::cout << dance.first.size() << '\n';
    printIndices(dance.first);
    printIndices(dance.second);
}

int main() {
    optimizeInput();

    std::string first_text{};
    std::string second_text{};
    std::cin >> first_text >> second_text;
    const auto best = buildLcsTable(first_text, second_text);
    printDance(restoreDance(first_text, second_text, best));
}
