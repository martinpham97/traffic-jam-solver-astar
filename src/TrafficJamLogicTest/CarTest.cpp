#include <sstream>
#include "../TrafficJamLogic/Car.cpp"
#include "pch.h"

class CarTest : public ::testing::Test {
 protected:
  void SetUp() override {
    car_1 = Car{4, 2, 0, 3, Car::Direction::Horizontal};
    car_2 = Car{4, 2, 0, 3, Car::Direction::Horizontal};
    car_3 = Car{1, 0, 0, 2, Car::Direction::Vertical};
  }

  // void TearDown() override {}

  Car car_1;
  Car car_2;
  Car car_3;
};

TEST_F(CarTest, ConstructorAndMethods) {
  ASSERT_EQ(car_1.getId(), 4);
  ASSERT_EQ(car_1.getPosRow(), 2);
  ASSERT_EQ(car_1.getPosCol(), 0);
  ASSERT_EQ(car_1.getLength(), 3);
  ASSERT_EQ(car_1.getDirection(), Car::Direction::Horizontal);
}

TEST_F(CarTest, OutputStreamOperator) {
  std::ostringstream oss{};
  oss << car_1;
  auto output = oss.str();
  auto expected = "4 2 0 3 0";
  ASSERT_EQ(output, expected);
}

TEST_F(CarTest, EqualToOperator) {
  ASSERT_TRUE(car_1 == car_2);
  ASSERT_FALSE(car_1 == car_3);
  ASSERT_FALSE(car_2 == car_3);
}