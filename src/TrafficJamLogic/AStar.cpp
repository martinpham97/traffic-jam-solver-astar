/**
 * Copyright 2019 Martin Pham
 */

#include "AStar.h"

std::vector<std::shared_ptr<Board>> AStar::reconstructPath(
    const std::unordered_map<std::shared_ptr<Node>, std::shared_ptr<Node>>
        &came_from,
    const std::shared_ptr<Node> &current) {
  // Using vector of shared_ptr is 20% faster
  std::vector<std::shared_ptr<Board>> path{current->board};

  auto curr = current;

  while (curr->parent != nullptr) {
    auto parent = curr->parent;
    path.emplace(path.begin(), parent->board);
    curr = parent;
  }

  return path;
}

int AStar::calculateHValue(const Node &current) {
  // Heuristic value is the number of cars in front of the main car
  int h = 0;

  if (!current.board->solved()) {
    auto main_car = current.board->getMainCar();
    int main_id = main_car.getId();
    int main_row = main_car.getPosRow();
    int main_col = main_car.getPosCol();
    int main_length = main_car.getLength();

    for (auto i = main_col + main_length; i < current.board->getBoardSize();
         ++i) {
      if (current.board->getGameBoardAt(main_row, i) != main_id &&
          current.board->getGameBoardAt(main_row, i) != 0) {
        ++h;
      }
    }

    return 1 + h;
  }

  return h;
}

std::vector<std::shared_ptr<Board>> AStar::search(const Board &board) {
  // Using shared_ptr for Node objects is 50% faster
  std::unordered_map<std::shared_ptr<Node>, std::shared_ptr<Node>> came_from{};
  std::unordered_set<std::shared_ptr<Node>> closed_list{};

  // Comparing only the f_value of each Node for the priority queue
  auto node_priority_cmp = [](const std::shared_ptr<Node> &lhs,
                              const std::shared_ptr<Node> &rhs) {
    return lhs->f_value < rhs->f_value;
  };
  std::multiset<std::shared_ptr<Node>, decltype(node_priority_cmp)> open_list{
      node_priority_cmp};

  // Comparing only the board of each Node to check if the node is visited
  auto node_cmp = [](const std::shared_ptr<Node> &lhs,
                     const std::shared_ptr<Node> &rhs) {
    return *lhs->board < *rhs->board;
  };
  std::set<std::shared_ptr<Node>, decltype(node_cmp)> visited_list{node_cmp};

  Node start{board};
  start.g_value = 0;
  start.f_value = calculateHValue(start) + start.g_value;

  open_list.emplace(std::make_shared<Node>(start));

  while (!open_list.empty()) {
    auto current_it = open_list.begin();
    auto current = *current_it;

    if (current->board->solved()) {
      return reconstructPath(came_from, current);
    }

    open_list.erase(current_it);
    closed_list.emplace(current);

    for (auto &n : current->getNeighbours()) {
      if (closed_list.count(n)) {
        continue;
      }

      // Each move counts as 1
      int g_score = current->g_value + 1;

      bool visited = visited_list.count(n);

      if (!visited || g_score < n->g_value) {
        came_from.emplace(n, current);
        n->parent = std::make_shared<Node>(*current);
        n->g_value = g_score;
        n->f_value = calculateHValue(*n);

        if (!visited) {
          open_list.emplace(n);
          visited_list.emplace(n);
        }
      }
    }
  }

  return {};
}