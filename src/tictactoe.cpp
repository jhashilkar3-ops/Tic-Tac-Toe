#include "tictactoe.hpp"
#include <iostream>

Board::Board() {
    reset();
}

void Board::reset() {
    for (int i = 0; i < 9; i++) {
        cells[i] = '1' + i;
    }
}

void Board::display() const {
    std::cout << "\n";
    for (int i = 0; i < 9; i++) {
        std::cout << " " << cells[i] << " ";
        if (i % 3 != 2) {
            std::cout << "|";
        } else if (i != 8) {
            std::cout << "\n---+---+---\n";
        }
    }
    std::cout << "\n\n";
}

bool Board::isCellValid(int cell) const {
    return cell >= 1 && cell <= 9;
}

bool Board::isCellTaken(int cell) const {
    char c = cells[cell - 1];
    return c == 'X' || c == 'O';
}

bool Board::makeMove(int cell, char player) {
    if (!isCellValid(cell) || isCellTaken(cell)) {
        return false;
    }
    cells[cell - 1] = player;
    return true;
}

bool Board::checkWin(char player) const {

    for (int r = 0; r < 3; r++) {
        if (cells[r*3] == player && cells[r*3+1] == player && cells[r*3+2] == player)
            return true;
    }

    for (int c = 0; c < 3; c++) {
        if (cells[c] == player && cells[c+3] == player && cells[c+6] == player)
            return true;
    }

    if (cells[0] == player && cells[4] == player && cells[8] == player) return true;
    if (cells[2] == player && cells[4] == player && cells[6] == player) return true;

    return false;
}

bool Board::isFull() const {
    for (int i = 0; i < 9; i++) {
        if (cells[i] != 'X' && cells[i] != 'O') return false;
    }
    return true;
}

char Board::getCell(int index) const {
    return cells[index];
}