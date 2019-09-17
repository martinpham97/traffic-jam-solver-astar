/**
 * Copyright 2019 Martin Pham
 */

#pragma once

#include <iostream>
#include <tuple>

class Car {
 public:
  enum Direction { Horizontal, Vertical };

  /// <summary>
  /// A parameterized constructor for creating a Car object.
  /// </summary>
  /// <param name="id">The car's ID.</param>
  /// <param name="pos_row">The car's row position (y-coordinate).</param>
  /// <param name="pos_col">The car's column position (x-coordinate).</param>
  /// <param name="length">The car's length.</param>
  /// <param name="direction">The car's direction/orientation
  /// (horizontal/vertical).</param>
  Car(int id, int pos_row, int pos_col, int length, Direction direction);

  /// <summary>
  /// Default constructor.
  /// </summary>
  Car() = default;

  /// <summary>
  /// Default destructor.
  /// </summary>
  ~Car() = default;

  /// <summary>
  /// Overloaded << operator to print out the car's properties.
  /// </summary>
  friend std::ostream &operator<<(std::ostream &os, const Car &car) noexcept {
    os << car.getId() << ' ' << car.getPosRow() << ' ' << car.getPosCol() << ' '
       << car.getLength() << ' ' << car.getDirection();
    return os;
  }

  friend bool operator==(const Car &lhs, const Car &rhs) noexcept {
    return std::tie(lhs.id_, lhs.pos_row_, lhs.pos_col_, lhs.length_,
                    lhs.direction_) == std::tie(rhs.id_, rhs.pos_row_,
                                                rhs.pos_col_, rhs.length_,
                                                rhs.direction_);
  }

  /// <summary>
  /// Default getter for ID.
  /// </summary>
  /// <returns>A number denoting the car's ID.</returns>
  int getId() const noexcept;

  /// <summary>
  /// Default getter for row position.
  /// </summary>
  /// <returns>A number denoting the car's row position
  /// (y-coordinate).</returns>
  int getPosRow() const noexcept;

  /// <summary>
  /// Default getter for column position.
  /// </summary>
  /// <returns>A number denoting the car's column position
  /// (x-coordinate).</returns>
  int getPosCol() const noexcept;

  /// <summary>
  /// Default getter for length.
  /// </summary>
  /// <returns>A number denoting the car's length.</returns>
  int getLength() const noexcept;

  /// <summary>
  /// Default getter for direction.
  /// </summary>
  /// <returns>A Car::Direction object denoting the car's direciton
  /// (orientation).</returns>
  Direction getDirection() const noexcept;

 private:
  int id_;
  int pos_row_;
  int pos_col_;
  int length_;
  Direction direction_;
};
