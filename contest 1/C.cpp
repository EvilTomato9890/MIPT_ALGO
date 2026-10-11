#include <algorithm>
#include <cstdint>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

struct Person {
  std::string name{};
  int distance = 0;
};

struct TaxiPlan {
  int total_cost = 0;
  std::vector<std::vector<std::uint8_t>> choice{};
};

using Taxis = std::vector<std::vector<std::string>>;

void optimize_input() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
}

std::vector<Person> read_people() {
  int count = 0;
  std::cin >> count;
  std::vector<Person> people(count, Person{});
  for (auto& person : people) {
    std::cin >> person.name >> person.distance;
  }
  std::sort(people.begin(), people.end(), [](const Person& a, const Person& b) {
    return a.distance < b.distance;
  });
  return people;
}

TaxiPlan build_taxi_plan(const std::vector<Person>& boys,
                         const std::vector<Person>& girls) {
  constexpr int INF = 1000000000;
  const int n = static_cast<int>(boys.size());
  const int m = static_cast<int>(girls.size());
  std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1, INF));
  std::vector<std::vector<std::uint8_t>> choice(
      n + 1, std::vector<std::uint8_t>(m + 1, 0));
  dp[0][0] = 0;
  for (int i = 1; i <= n; ++i) {
    for (int j = 0; j <= std::min(m, 3 * i); ++j) {
      for (int b = 1; b <= std::min(i, 4); ++b) {
        for (int g = 0; g <= std::min(j, 4 - b); ++g) {
          const int cost =
              g == 0 ? boys[i - 1].distance :
                       std::max(boys[i - 1].distance, girls[j - 1].distance);
          const int candidate = dp[i - b][j - g] + cost;
          if (candidate < dp[i][j]) {
            dp[i][j] = candidate;
            choice[i][j] = static_cast<std::uint8_t>(4 * b + g);
          }
        }
      }
    }
  }
  return {dp[n][m], std::move(choice)};
}

Taxis restore_taxis(const std::vector<Person>& boys,
                    const std::vector<Person>& girls, const TaxiPlan& plan) {
  Taxis taxis{};
  int i = static_cast<int>(boys.size());
  int j = static_cast<int>(girls.size());
  while (i > 0) {
    const int b = plan.choice[i][j] / 4;
    const int g = plan.choice[i][j] % 4;
    std::vector<std::string> passengers{};
    for (int p = i - b; p < i; ++p) {
      passengers.push_back(boys[p].name);
    }
    for (int p = j - g; p < j; ++p) {
      passengers.push_back(girls[p].name);
    }
    taxis.push_back(std::move(passengers));
    i -= b;
    j -= g;
  }
  return taxis;
}

void print_taxi(const std::vector<std::string>& passengers,
                std::size_t number) {
  std::cout << "Taxi " << number << ": ";
  for (std::size_t i = 0; i < passengers.size(); ++i) {
    if (i > 0) {
      std::cout << (i + 1 == passengers.size() ? " and " : ", ");
    }
    std::cout << passengers[i];
  }
  std::cout << ".\n";
}

void print_solution(int cost, const Taxis& taxis) {
  std::cout << cost << '\n' << taxis.size() << '\n';
  for (std::size_t i = 0; i < taxis.size(); ++i) {
    print_taxi(taxis[i], i + 1);
  }
}

int main() {
  optimize_input();

  const auto boys = read_people();
  const auto girls = read_people();
  const auto plan = build_taxi_plan(boys, girls);
  const auto taxis = restore_taxis(boys, girls, plan);
  print_solution(plan.total_cost, taxis);
}
