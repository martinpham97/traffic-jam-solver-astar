/**
 * Copyright 2019 Martin Pham
 */

#include "AStar.h"
#include "Board.h"
#include "Car.h"
#include "Config.h"

#include <chrono>
#include <iostream>
#include <unordered_map>

// Speed up IO
auto speedup = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return nullptr;
}();

int main() {
  // Create board with map
  /*
  std::unordered_map<int, Car> all_cars{};

  Car car1(1, 2, 0, 2, Car::Direction::Horizontal);
  Car car2(2, 4, 1, 3, Car::Direction::Horizontal);
  Car car3(3, 0, 3, 3, Car::Direction::Horizontal);
  Car car4(4, 3, 2, 3, Car::Direction::Vertical);
  Car car5(5, 3, 0, 2, Car::Direction::Horizontal);
  Car car6(6, 2, 4, 2, Car::Direction::Vertical);
  Car car7(7, 5, 5, 3, Car::Direction::Vertical);

  all_cars.insert({1, car1});
  all_cars.insert({2, car2});
  all_cars.insert({3, car3});
  all_cars.insert({4, car4});
  all_cars.insert({5, car5});
  all_cars.insert({6, car6});
  all_cars.insert({7, car7});

  Board board{all_cars};
  */

  // Create board with array
  std::vector<int> game_board{0, 0, 0, 3, 3, 3, 0, 0, 4, 0, 6, 0,
                              1, 1, 4, 0, 6, 0, 5, 5, 4, 0, 0, 7,
                              0, 2, 2, 2, 0, 7, 0, 0, 0, 0, 0, 7};

  Board board{game_board};

  // Measure AStar performance
  auto t1 = std::chrono::high_resolution_clock::now();
  auto path = AStar::search(board);
  auto t2 = std::chrono::high_resolution_clock::now();
  auto duration =
      std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();

  std::cout << "Solution found in: " << duration << " ms" << '\n';

  // Print solutions
  std::cout << "Moves: " << path.size() << '\n';
  std::cout << board << '\n';

  for (const auto &b : path) {
    std::cout << *b << '\n';
  }
}