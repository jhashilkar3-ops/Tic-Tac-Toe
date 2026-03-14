#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/benchmark/catch_constructor.hpp>
#include <catch2/generators/catch_generators_range.hpp>

#include "../src/tictactoe.hpp"

TEST_CASE("Board initializes with cells 1-9", "[board]") {
    Board b;
    for (int i = 0; i < 9; i++) {
        REQUIRE(b.getCell(i) == ('1' + i));
    }
}

TEST_CASE("Board resets correctly", "[board]") {
    Board b;
    b.makeMove(1, 'X');
    b.makeMove(2, 'O');
    b.reset();
    for (int i = 0; i < 9; i++) {
        REQUIRE(b.getCell(i) == ('1' + i));
    }
}

TEST_CASE("isCellValid returns correct results", "[board]") {
    Board b;
    REQUIRE(b.isCellValid(1)  == true);
    REQUIRE(b.isCellValid(9)  == true);
    REQUIRE(b.isCellValid(0)  == false);
    REQUIRE(b.isCellValid(10) == false);
    REQUIRE(b.isCellValid(-1) == false);
}

TEST_CASE("isCellTaken detects taken cells", "[board]") {
    Board b;
    REQUIRE(b.isCellTaken(1) == false);
    b.makeMove(1, 'X');
    REQUIRE(b.isCellTaken(1) == true);
}

TEST_CASE("makeMove places marker correctly", "[board]") {
    Board b;
    REQUIRE(b.makeMove(5, 'X') == true);
    REQUIRE(b.getCell(4) == 'X');
}

TEST_CASE("makeMove fails on taken cell", "[board]") {
    Board b;
    b.makeMove(1, 'X');
    REQUIRE(b.makeMove(1, 'O') == false);
    REQUIRE(b.getCell(0) == 'X');
}

TEST_CASE("checkWin detects row wins", "[board]") {
    Board b;
    b.makeMove(1, 'X'); b.makeMove(2, 'X'); b.makeMove(3, 'X');
    REQUIRE(b.checkWin('X') == true);
    REQUIRE(b.checkWin('O') == false);
}

TEST_CASE("checkWin detects column wins", "[board]") {
    Board b;
    b.makeMove(1, 'O'); b.makeMove(4, 'O'); b.makeMove(7, 'O');
    REQUIRE(b.checkWin('O') == true);
}

TEST_CASE("checkWin detects diagonal wins", "[board]") {
    Board b;
    b.makeMove(1, 'X'); b.makeMove(5, 'X'); b.makeMove(9, 'X');
    REQUIRE(b.checkWin('X') == true);

    Board b2;
    b2.makeMove(3, 'O'); b2.makeMove(5, 'O'); b2.makeMove(7, 'O');
    REQUIRE(b2.checkWin('O') == true);
}

TEST_CASE("checkWin returns false when no winner", "[board]") {
    Board b;
    b.makeMove(1, 'X'); b.makeMove(2, 'O'); b.makeMove(3, 'X');
    REQUIRE(b.checkWin('X') == false);
    REQUIRE(b.checkWin('O') == false);
}

TEST_CASE("isFull detects full board", "[board]") {
    Board b;
    REQUIRE(b.isFull() == false);
    b.makeMove(1, 'X'); b.makeMove(2, 'O'); b.makeMove(3, 'X');
    b.makeMove(4, 'O'); b.makeMove(5, 'X'); b.makeMove(6, 'O');
    b.makeMove(7, 'O'); b.makeMove(8, 'X'); b.makeMove(9, 'O');
    REQUIRE(b.isFull() == true);
}

TEST_CASE("isFull returns false on partial board", "[board]") {
    Board b;
    b.makeMove(1, 'X');
    REQUIRE(b.isFull() == false);
}
