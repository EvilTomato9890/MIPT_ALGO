#include <algorithm>
#include <cstdint>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

constexpr int kTaxiCapacity    = 4;
constexpr int kMaxGirlsPerTaxi = kTaxiCapacity - 1;

struct Person {
    std::string name;
    int distance = 0;
};

struct TaxiPlan {
    int total_cost = 0;
    std::vector<std::vector<std::uint8_t>> choice;
};

using Taxis = std::vector<std::vector<std::string>>;

struct TaxiState {
    std::vector<std::vector<int>> best;
    std::vector<std::vector<std::uint8_t>> choice;
};

struct PassengerCounts {
    int boys  = 0;
    int girls = 0;
};

void optimizeInput() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
}

std::vector<Person> readPeople() {
    int count = 0;
    std::cin >> count;
    std::vector<Person> people(count, Person{});
    for (auto& person : people) {
        std::cin >> person.name >> person.distance;
    }
    std::sort(people.begin(), people.end(),
              [](const Person& first, const Person& second) {
                  return first.distance < second.distance;
              });
    return people;
}

void addTaxi(TaxiState& state, const std::vector<Person>& boys,
             const std::vector<Person>& girls, PassengerCounts used) {
    for (int boys_taken = 1; boys_taken <= std::min(used.boys, kTaxiCapacity);
         ++boys_taken) {
        for (int girls_taken = 0;
             girls_taken <= std::min(used.girls, kTaxiCapacity - boys_taken);
             ++girls_taken) {
            const int cost = girls_taken == 0 ?
                                 boys[used.boys - 1].distance :
                                 std::max(boys[used.boys - 1].distance,
                                          girls[used.girls - 1].distance);
            const int candidate =
                state.best[used.boys - boys_taken][used.girls - girls_taken]
                + cost;
            if (candidate < state.best[used.boys][used.girls]) {
                state.best[used.boys][used.girls]   = candidate;
                state.choice[used.boys][used.girls] = static_cast<std::uint8_t>(
                    (kTaxiCapacity * boys_taken) + girls_taken);
            }
        }
    }
}

TaxiPlan buildTaxiPlan(const std::vector<Person>& boys,
                       const std::vector<Person>& girls) {
    constexpr int inf    = 1000000000;
    const int boy_count  = static_cast<int>(boys.size());
    const int girl_count = static_cast<int>(girls.size());
    TaxiState state{
        std::vector<std::vector<int>>(boy_count + 1,
                                      std::vector<int>(girl_count + 1, inf)),
        std::vector<std::vector<std::uint8_t>>(
            boy_count + 1, std::vector<std::uint8_t>(girl_count + 1, 0))};
    state.best[0][0] = 0;
    for (int boys_used = 1; boys_used <= boy_count; ++boys_used) {
        for (int girls_used = 0;
             girls_used <= std::min(girl_count, kMaxGirlsPerTaxi * boys_used);
             ++girls_used) {
            addTaxi(state, boys, girls, {boys_used, girls_used});
        }
    }
    return {state.best[boy_count][girl_count], std::move(state.choice)};
}

Taxis restoreTaxis(const std::vector<Person>& boys,
                   const std::vector<Person>& girls, const TaxiPlan& plan) {
    Taxis taxis{};
    int boys_used  = static_cast<int>(boys.size());
    int girls_used = static_cast<int>(girls.size());
    while (boys_used > 0) {
        const int boys_taken =
            plan.choice[boys_used][girls_used] / kTaxiCapacity;
        const int girls_taken =
            plan.choice[boys_used][girls_used] % kTaxiCapacity;
        std::vector<std::string> passengers{};
        for (int passenger_index = boys_used - boys_taken;
             passenger_index < boys_used; ++passenger_index) {
            passengers.push_back(boys[passenger_index].name);
        }
        for (int passenger_index = girls_used - girls_taken;
             passenger_index < girls_used; ++passenger_index) {
            passengers.push_back(girls[passenger_index].name);
        }
        taxis.push_back(std::move(passengers));
        boys_used  -= boys_taken;
        girls_used -= girls_taken;
    }
    return taxis;
}

void printTaxi(const std::vector<std::string>& passengers, std::size_t number) {
    std::cout << "Taxi " << number << ": ";
    for (std::size_t index = 0; index < passengers.size(); ++index) {
        if (index > 0) {
            std::cout << (index + 1 == passengers.size() ? " and " : ", ");
        }
        std::cout << passengers[index];
    }
    std::cout << ".\n";
}

void printSolution(int cost, const Taxis& taxis) {
    std::cout << cost << '\n' << taxis.size() << '\n';
    for (std::size_t boys_used = 0; boys_used < taxis.size(); ++boys_used) {
        printTaxi(taxis[boys_used], boys_used + 1);
    }
}

int main() {
    optimizeInput();

    const auto boys  = readPeople();
    const auto girls = readPeople();
    const auto plan  = buildTaxiPlan(boys, girls);
    const auto taxis = restoreTaxis(boys, girls, plan);
    printSolution(plan.total_cost, taxis);
}
