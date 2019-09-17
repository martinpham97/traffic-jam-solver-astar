#include "../TrafficJamLogic/Board.cpp"
#include "pch.h"

class BoardTest : public ::testing::Test {
 protected:
  void SetUp() override {
    car_1 = Car(1, 2, 0, 2, Car::Direction::Horizontal);
    car_2 = Car(2, 4, 1, 3, Car::Direction::Horizontal);
    car_3 = Car(3, 0, 3, 3, Car::Direction::Horizontal);
    car_4 = Car(4, 3, 2, 3, Car::Direction::Vertical);
    car_5 = Car(5, 3, 0, 2, Car::Direction::Horizontal);
    car_6 = Car(6, 2, 4, 2, Car::Direction::Vertical);
    car_7 = Car(7, 5, 5, 3, Car::Direction::Vertical);

    all_cars.insert({1, car_1});
    all_cars.insert({2, car_2});
    all_cars.insert({3, car_3});
    all_cars.insert({4, car_4});
    all_cars.insert({5, car_5});
    all_cars.insert({6, car_6});
    all_cars.insert({7, car_7});

    game_board =
        std::vector<int>{0, 0, 0, 3, 3, 3, 0, 0, 4, 0, 6, 0, 1, 1, 4, 0, 6, 0,
                         5, 5, 4, 0, 0, 7, 0, 2, 2, 2, 0, 7, 0, 0, 0, 0, 0, 7};
  }

  // void TearDown() override {}

  Car car_1;
  Car car_2;
  Car car_3;
  Car car_4;
  Car car_5;
  Car car_6;
  Car car_7;
  std::unordered_map<int, Car> all_cars{};
  std::vector<int> game_board{};
};

TEST_F(BoardTest, ConstructorMap) {
  const Board board{all_cars};

  ASSERT_EQ(board.getGameBoard(), game_board);
  ASSERT_EQ(board.getCars(), all_cars);
  ASSERT_EQ(board.getBoardSize(), 6);
  ASSERT_EQ(board.getMainId(), 1);
}

TEST_F(BoardTest, ConstructorVector) {
  const Board board{game_board};

  ASSERT_EQ(board.getGameBoard(), game_board);
  ASSERT_EQ(board.getCars(), all_cars);
  ASSERT_EQ(board.getBoardSize(), 6);
  ASSERT_EQ(board.getMainId(), 1);
}

TEST_F(BoardTest, EqualToOperator) {
  Board board_1{game_board};
  const Board board_2{all_cars};
  Board board_3{{0, 0, 0, 0, 3, 3, 0, 0, 4, 0, 6, 0, 1, 1, 4, 0, 6, 0,
                 5, 5, 4, 0, 0, 7, 0, 2, 2, 2, 0, 7, 0, 0, 0, 0, 0, 7}};

  ASSERT_TRUE(board_1 == board_2);
  ASSERT_TRUE(board_2 == board_1);
  ASSERT_FALSE(board_1 == board_3);
  ASSERT_FALSE(board_3 == board_2);
}

TEST_F(BoardTest, TestSolvedMethod) {
  // Normal board unsolved state
  const Board board_1{game_board};

  ASSERT_EQ(board_1.getMainId(), 1);
  ASSERT_FALSE(board_1.solved());

  // 1 car solved state
  const Board board_2{{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1,
                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

  ASSERT_EQ(board_2.getMainId(), 1);
  ASSERT_TRUE(board_2.solved());

  // 1 car with id 2 solved state
  const Board board_3{{0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2,
                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                      2};

  ASSERT_EQ(board_3.getMainId(), 2);
  ASSERT_TRUE(board_3.solved());
}

TEST_F(BoardTest, TestGetGameBoardAtMethod) {
  const Board board{game_board};

  ASSERT_EQ(board.getGameBoardAt(0, 0), 0);
  ASSERT_EQ(board.getGameBoardAt(3, 2), 4);
  ASSERT_EQ(board.getGameBoardAt(5, 5), 7);
  ASSERT_EQ(board.getGameBoardAt(4, 1), 2);
  ASSERT_NE(board.getGameBoardAt(5, 1), 3);
  ASSERT_NE(board.getGameBoardAt(1, 1), 6);
  ASSERT_NE(board.getGameBoardAt(2, 1), 3);
}

TEST_F(BoardTest, TestSetGameBoardAtMethod) {
  Board board{game_board};

  ASSERT_EQ(board.getGameBoardAt(0, 0), 0);
  board.setGameBoardAt(0, 0, 4);
  ASSERT_EQ(board.getGameBoardAt(0, 0), 4);
}

TEST_F(BoardTest, TestGetMainCarMethod) {
  Board board{game_board};

  ASSERT_EQ(board.getMainId(), 1);
  ASSERT_EQ(board.getMainCar().getId(), 1);
  ASSERT_EQ(board.getMainCar(), Car(1, 2, 0, 2, Car::Direction::Horizontal));
}

TEST_F(BoardTest, TestGetPossibleStatesMethod) {
  Board board{game_board};

  auto states = board.getPossibleStates();
  std::ostringstream oss{};

  for (const auto &state : states) {
    oss << state << '\n';
  }

  auto output = oss.str();
  auto expected =
      "003330\n004060\n114060\n554007\n022207\n000007\n\n000333\n004060\n114060"
      "\n5540"
      "07\n222007\n000007\n\n000333\n004060\n114060\n554007\n002227\n000007\n\n"
      "004333"
      "\n004060\n114060\n550007\n022207\n000007\n\n000333\n004000\n114060\n5540"
      "67\n02"
      "2207\n000007\n\n000333\n004060\n114067\n554007\n022207\n000000\n\n";
  ASSERT_EQ(output, expected);
}
