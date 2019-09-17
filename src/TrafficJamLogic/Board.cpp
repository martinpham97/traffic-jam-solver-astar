/**
 * Copyright 2019 Martin Pham
 */

#include "Board.h"

#include <cmath>

Board::Board(const std::unordered_map<int, Car> &cars, const int &board_size,
             const int &main_id)
    : cars_{cars}, board_size_{board_size}, main_id_{main_id} {
  this->updateGameBoard();
};

Board::Board(const std::vector<int> &game_board, const int &main_id)
    : game_board_{game_board},
      board_size_{static_cast<int>(std::sqrt(game_board.size()))},
      main_id_{main_id} {
  this->updateCars();
};

void Board::updateCars() {
  this->cars_ = std::unordered_map<int, Car>{};
  // Get horizontal cars
  for (auto i = 0; i < this->board_size_; ++i) {
    for (auto j = 0; j < this->board_size_; ++j) {
      auto current_id = this->getGameBoardAt(i, j);
      auto length = 0;
      if (current_id != 0) {
        for (auto k = j; k < this->board_size_; ++k) {
          if (this->getGameBoardAt(i, k) == current_id) {
            ++length;
          }
        }
        if (length > 1) {
          this->cars_.emplace(current_id,
                              Car{current_id, i, j, length, Car::Horizontal});
        }
        j += length;
      }
    }
  }
  // Get vertical cars
  for (auto i = 0; i < this->board_size_; ++i) {
    for (auto j = 0; j < this->board_size_; ++j) {
      auto current_id = this->getGameBoardAt(this->board_size_ - j - 1, i);
      auto length = 0;
      if (current_id != 0) {
        for (auto k = j; k < this->board_size_; ++k) {
          if (this->getGameBoardAt(this->board_size_ - k - 1, i) ==
              current_id) {
            ++length;
          }
        }
        if (length > 1) {
          this->cars_.emplace(
              current_id, Car{current_id, this->board_size_ - j - 1, i, length,
                              Car::Vertical});
        }
        j += length - 1;
      }
    }
  }
}

void Board::printCars() const noexcept {
  for (const auto &c : this->cars_) {
    std::cout << c.second << '\n';
  }
  std::cout << '\n';
}

bool Board::solved() const {
  auto main_car = this->cars_.at(this->main_id_);
  return main_car.getPosCol() + main_car.getLength() == this->board_size_;
}

void Board::updateGameBoard() {
  // static casting to avoid integer overflow
  this->game_board_ =
      std::vector<int>(static_cast<uint64_t>(this->board_size_) *
                       static_cast<uint64_t>(this->board_size_));

  if (this->cars_.size() > 0) {
    for (const auto &c : this->cars_) {
      const Car &current_car = c.second;
      if (current_car.getDirection() == Car::Direction::Horizontal) {
        for (auto i = 0; i < current_car.getLength(); ++i) {
          this->setGameBoardAt(current_car.getPosRow(),
                               current_car.getPosCol() + i,
                               current_car.getId());
        }
      } else {
        for (auto i = 0; i < current_car.getLength(); ++i) {
          this->setGameBoardAt(
              current_car.getPosRow() + 1 - current_car.getLength() + i,
              current_car.getPosCol(), current_car.getId());
        }
      }
    }
  }
}

std::vector<Board> Board::getPossibleStates() const {
  std::vector<Board> states{};
  std::unordered_map<int, Car> cars_copy;

  // For each car in the board
  for (const auto &c : this->cars_) {
    Car current_car = c.second;
    auto cur_id = current_car.getId();
    auto cur_row = current_car.getPosRow();
    auto cur_col = current_car.getPosCol();
    auto cur_length = current_car.getLength();
    auto cur_direction = current_car.getDirection();

    if (cur_direction == Car::Direction::Horizontal) {
      // Move left
      if ((cur_col >= 1) && this->getGameBoardAt(cur_row, cur_col - 1) == 0) {
        Car new_car{cur_id, cur_row, cur_col - 1, cur_length, cur_direction};
        cars_copy = std::unordered_map<int, Car>(this->cars_);
        cars_copy[cur_id] = new_car;
        states.emplace_back(cars_copy);
      }

      // Move right
      if ((cur_col + cur_length <= this->board_size_ - 1) &&
          this->getGameBoardAt(cur_row, cur_col + cur_length) == 0) {
        Car new_car{cur_id, cur_row, cur_col + 1, cur_length, cur_direction};
        cars_copy = std::unordered_map<int, Car>(this->cars_);
        cars_copy[cur_id] = new_car;
        states.emplace_back(cars_copy);
      }
    } else {
      // Move up
      if ((cur_row + 1 - cur_length >= 1) &&
          this->getGameBoardAt(cur_row + 1 - cur_length - 1, cur_col) == 0) {
        Car new_car{cur_id, cur_row - 1, cur_col, cur_length, cur_direction};
        cars_copy = std::unordered_map<int, Car>(this->cars_);
        cars_copy[cur_id] = new_car;
        states.emplace_back(cars_copy);
      }

      // Move down
      if ((cur_row + 1 <= this->board_size_ - 1) &&
          this->getGameBoardAt(cur_row + 1, cur_col) == 0) {
        Car new_car{cur_id, cur_row + 1, cur_col, cur_length, cur_direction};
        cars_copy = std::unordered_map<int, Car>(this->cars_);
        cars_copy[cur_id] = new_car;
        states.emplace_back(cars_copy);
      }
    }
  }

  return states;
}

Car Board::getCar(const int &id) const { return this->cars_.at(id); }

std::vector<int> Board::getGameBoard() const noexcept {
  return this->game_board_;
}

int Board::getGameBoardAt(const int &row, const int &col) const {
  // static casting to avoid integer overflow
  return this->game_board_[static_cast<uint64_t>(
                               static_cast<uint64_t>(row) *
                               static_cast<uint64_t>(this->board_size_)) +
                           col];
}

void Board::setGameBoardAt(const int &row, const int &col, const int &value) {
  // static casting to avoid integer overflow
  this->game_board_[static_cast<uint64_t>(
                        static_cast<uint64_t>(row) *
                        static_cast<uint64_t>(this->board_size_)) +
                    col] = value;
}

std::unordered_map<int, Car> Board::getCars() const noexcept {
  return this->cars_;
}

int Board::getBoardSize() const noexcept { return this->board_size_; }

int Board::getMainId() const noexcept { return this->main_id_; }

Car Board::getMainCar() const noexcept {
  return this->cars_.at(this->main_id_);
}