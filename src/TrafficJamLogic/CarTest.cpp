#define CATCH_CONFIG_RUNNER
#include "Car.h"
#include "catch.hpp"

SCENARIO("Testing Car object creation and methods", "[car]") {
  GIVEN(
      "id = 5, pos_row = 3, pos_col = 2, length = 3, diretion = "
      "Car::Horizontal") {
    WHEN("Constructing a Car object using the specified parameters") {
      Car car{5, 3, 2, 3, Car::Horizontal};
      THEN("The car will have the correct specified properties") {
        REQUIRE(car.getId() == 5);
        REQUIRE(car.getPosRow() == 3);
        REQUIRE(car.getPosCol() == 2);
        REQUIRE(car.getLength() == 3);
        REQUIRE(car.getDirection() == Car::Horizontal);
      }
    }
  }
}