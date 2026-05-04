#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/benchmark/catch_constructor.hpp>
#include <catch2/generators/catch_generators_range.hpp>

#include "../src/tictactoe.hpp"


TEST_CASE("hasTrap returns false on normal reset", "[trap]") {
    Board b;
    b.reset();
    REQUIRE(b.hasTrap() == false);
}

TEST_CASE("hasTrap returns true after resetWithTrap", "[trap]") {
    Board b;

    std::srand(42);
    b.resetWithTrap();
    REQUIRE(b.hasTrap() == true);
}

TEST_CASE("isTrapCell identifies correct cell with fixed seed", "[trap]") {
    Board b;
    std::srand(42);
    b.resetWithTrap();
    std::srand(42);
    int expectedTrap = (rand() % 9) + 1;
    REQUIRE(b.isTrapCell(expectedTrap) == true);
}

TEST_CASE("isTrapCell returns false for non-trap cells", "[trap]") {
    Board b;
    std::srand(42);
    b.resetWithTrap();
    std::srand(42);
    int trapCell = (rand() % 9) + 1;
    for (int cell = 1; cell <= 9; cell++) {
        if (cell != trapCell)
            REQUIRE(b.isTrapCell(cell) == false);
    }
}

TEST_CASE("Trap cell is not marked when triggered", "[trap]") {
    Board b;
    std::srand(42);
    b.resetWithTrap();
    std::srand(42);
    int trapCell = (rand() % 9) + 1;


    REQUIRE(b.isCellTaken(trapCell) == false);
}

TEST_CASE("isFull ignores trap cell", "[trap]") {
    Board b;
    std::srand(42);
    b.resetWithTrap();
    std::srand(42);
    int trapCell = (rand() % 9) + 1;


    for (int cell = 1; cell <= 9; cell++) {
        if (cell == trapCell) continue;
        b.makeMove(cell, cell % 2 == 0 ? 'O' : 'X');
    }
    REQUIRE(b.isFull() == true);
}