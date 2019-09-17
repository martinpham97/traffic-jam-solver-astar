/**
 * Copyright 2019 Martin Pham
 */

#include "Car.h"

Car::Car(int id, int pos_row, int pos_col,
         int length, Direction direction)
    : id_{id},
      pos_row_{pos_row},
      pos_col_{pos_col},
      length_{length},
      direction_{direction} {};

int Car::getId() const noexcept { return this->id_; }

int Car::getPosRow() const noexcept { return this->pos_row_; }

int Car::getPosCol() const noexcept { return this->pos_col_; }

int Car::getLength() const noexcept { return this->length_; }

Car::Direction Car::getDirection() const noexcept { return this->direction_; }