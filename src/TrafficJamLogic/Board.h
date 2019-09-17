/**
 * Copyright 2019 Martin Pham
 */

#pragma once
#include <unordered_map>
#include <vector>
#include "Car.h"

class Board {
 public:
  /// <summary>
  /// A constructor for creating a Board object.
  /// </summary>
  /// <param name="cars">A map of Car objects with IDs as values.</param>
  /// <param name="board_size">A number for the size of the board. The board
  /// will be an NxN grid where N is the board size. Default board is a 6x6
  /// grid.</param>
  /// <param name="main_id">A number representing the main car's
  /// ID. Default main car's ID is 1.</param>
  explicit Board(const std::unordered_map<int, Car> &cars,
                 const int &board_size = 6, const int &main_id = 1);

  /// <summary>
  /// A constructor for creating a Board object.
  /// </summary>
  /// <param name="game_board">An array/vector representation of the game
  /// board.</param>
  /// <param name="main_id">A number representing the main car's
  /// ID. Default main car's ID is 1.</param>
  explicit Board(const std::vector<int> &game_board, const int &main_id = 1);

  /// <summary>
  /// Default constructor.
  /// </summary>
  Board() = default;

  /// <summary>
  /// Default destructor.
  /// </summary>
  ~Board() = default;

  /// <summary>
  /// Overloaded equality operator.
  /// Comparing only the array representation of
  /// the board for better performance.
  /// </summary>
  friend bool operator==(const Board &lhs, const Board &rhs) {
    return lhs.game_board_ == rhs.game_board_;
  }

  /// <summary>
  /// Overloaded less operator.
  /// Comparing only the array representation of
  /// the board for better performance.
  /// </summary>
  friend bool operator<(const Board &lhs, const Board &rhs) {
    return lhs.game_board_ < rhs.game_board_;
  }

  /// <summary>
  /// Overloaded << operator to print out the array representation of the board.
  /// </summary>
  friend std::ostream &operator<<(std::ostream &os,
                                  const Board &board) noexcept {
    for (auto i = 0; i < board.board_size_; ++i) {
      for (auto j = 0; j < board.board_size_; ++j) {
        os << board.getGameBoardAt(i, j);
      }
      os << '\n';
    }
    return os;
  }

  /// <summary>
  /// Print each car of the board.
  /// </summary>
  void printCars() const noexcept;

  /// <summary>
  /// Check if the board is solved for the main car
  /// </summary>
  /// <returns>True if the main car reaches the board's edge, False if
  /// otherwise.</returns>
  bool solved() const;

  /// <summary>
  /// Update the board array according to the map of Car objects.
  /// </summary>
  void updateGameBoard();

  /// <summary>
  /// Load an create a map of Car objects from an array/vector representation of
  /// cars.
  /// </summary>
  void updateCars();

  /// <summary>
  /// Get all possible car positions.
  /// </summary>
  /// <returns>An array/vector of all permutations of Board objects from the
  /// current board.</returns>
  std::vector<Board> getPossibleStates() const;

  /// <summary>
  /// Default getter for a car with a specific ID in the board.
  /// </summary>
  /// <param name="id">A number representing the car's ID.</param>
  /// <returns>A Car object with the specified ID.</returns>
  Car getCar(const int &id) const;

  /// <summary>
  /// Default getter for the game board array.
  /// </summary>
  /// <returns>An array/vector representing the game board.</returns>
  std::vector<int> getGameBoard() const noexcept;

  /// <summary>
  /// Default getter for the cell at (row, col) position.
  /// </summary>
  /// <param name="row">A number representing the row position.</param>
  /// <param name="col">A number representing the column position.</param>
  /// <returns>A number representing the cell at (row, col) position.</returns>
  int getGameBoardAt(const int &row, const int &col) const;

  /// <summary>
  /// Default setter for the cell at (row, col) position.
  /// </summary>
  /// <param name="row">A number representing the row position.</param>
  /// <param name="col">A number representing the column position.</param>
  void setGameBoardAt(const int &row, const int &col, const int &value);

  /// <summary>
  /// Default getter for the map of Car objects.
  /// </summary>
  /// <returns>A map of Car objects.</returns>
  std::unordered_map<int, Car> getCars() const noexcept;

  /// <summary>
  /// Default getter for board size.
  /// </summary>
  /// <returns>A number representing the board size in width.</returns>
  int getBoardSize() const noexcept;

  /// <summary>
  /// Default getter for main car's ID.
  /// </summary>
  /// <returns>A number representing the main car's ID.</returns>
  int getMainId() const noexcept;

  /// <summary>
  /// Default getter for main car.
  /// </summary>
  /// <returns>A Car object with the main ID.</returns>
  Car getMainCar() const noexcept;

 private:
  std::unordered_map<int, Car> cars_;
  // Using 1D vector/array instead of 2D for 50% faster operations
  std::vector<int> game_board_;
  int board_size_;
  int main_id_;
};
