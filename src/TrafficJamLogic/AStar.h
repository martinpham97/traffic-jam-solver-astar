/**
 * Copyright 2019 Martin Pham
 */

#pragma once

#include "Board.h"

#include <algorithm>
#include <memory>
#include <queue>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace AStar {
struct Node {
  /// <summary>
  /// A constructor for Node object.
  /// </summary>
  /// <param name="board">A Board object container positions of all
  /// cars.</param>
  explicit Node(const Board &board)
      : board{std::make_shared<Board>(board)},
        parent{nullptr},
        g_value{0},
        h_value{0},
        f_value{0} {};

  /// <summary>
  /// Default constructor.
  /// </summary>
  Node() = default;

  /// <summary>
  /// Default destructor.
  /// </summary>
  ~Node() = default;

  /// <summary>
  /// Get all neighbouring nodes.
  /// </summary>
  /// <returns>An array/vector of Node objects that are permutations of the
  /// current node.</returns>
  std::vector<std::shared_ptr<Node>> getNeighbours() const {
    std::vector<std::shared_ptr<Node>> neighbours{};

    auto states = board->getPossibleStates();

    for (const Board &b : states) {
      Node child(b);
      child.parent = std::make_shared<Node>(*this);
      neighbours.emplace_back(std::make_shared<Node>(child));
    }

    return neighbours;
  }

  std::shared_ptr<Board> board;
  std::shared_ptr<Node> parent;
  int g_value;
  int h_value;
  int f_value;
};

/// <summary>
/// A function to return an array of Board objects representing the solution to
/// the puzzle.
/// The function will iterate over the parent of the current node to reconstruct
/// the shortest possible solution.
/// </summary>
std::vector<std::shared_ptr<Board>> reconstructPath(
    const std::unordered_map<std::shared_ptr<Node>, std::shared_ptr<Node>>
        &came_from,
    const std::shared_ptr<Node> &current);

/// <summary>
/// A function to return the heuristic value for the current board position.
/// </summary>
int calculateHValue(const Node &current);

/// <summary>
/// The A* search function to find the shortest solution to the board puzzle.
/// </summary>
std::vector<std::shared_ptr<Board>> search(const Board &board);
}  // namespace AStar
