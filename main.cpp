#include <iostream>
#include <sstream>
#include "src/tictactoe.hpp"
#include <string>

int getHumanMove(Board& board, int currentPlayer, char symbol) {
    std::string input;
    while (true) {
        std::cout << "Player " << currentPlayer << " (" << symbol << "), enter a cell (1-9): ";
        std::getline(std::cin, input);

        if (input.empty()) {
            std::cout << "Invalid input! Please enter a whole number between 1 and 9.\n";
            continue;
        }

        bool allSpace = true;
        for (char c : input) {
            if (!std::isspace(c)) { allSpace = false; break; }
        }
        if (allSpace) {
            std::cout << "Invalid input! Please enter a whole number between 1 and 9.\n";
            continue;
        }

        if (input.find('.') != std::string::npos) {
            std::cout << "Invalid input! Please enter a whole number, not a decimal.\n";
            continue;
        }

        std::istringstream iss(input);
        int cell;
        iss >> cell;
        if (iss.fail() || !iss.eof()) {
            std::cout << "Invalid input! Please enter a whole number between 1 and 9.\n";
            continue;
        }

        if (!board.isCellValid(cell)) {
            std::cout << "Invalid input! Cell must be between 1 and 9.\n";
            continue;
        }

        if (board.isCellTaken(cell)) {
            std::cout << "That cell is already taken! Try again.\n";
            continue;
        }

        return cell;
    }
}

int selectMode() {
    std::string input;
    while (true) {
        std::cout << "\nWhat kind of game would you like to play?\n";
        std::cout << "  1. Human vs. Human\n";
        std::cout << "  2. Human vs. Computer\n";
        std::cout << "  3. Computer vs. Human\n";
        std::cout << "What is your selection? ";
        std::getline(std::cin, input);

        if (input == "1") return 1;
        if (input == "2") return 2;
        if (input == "3") return 3;

        std::cout << "That is not a valid selection! Try again.\n";
    }
}

bool askPlayAgain() {
    std::string input;
    while (true) {
        std::cout << "Would you like to play again? (yes/no): ";
        std::getline(std::cin, input);

        if (input.empty()) {
            std::cout << "Invalid input. Please enter 'yes' or 'no'.\n";
            continue;
        }

        for (char& c : input) c = std::tolower(c);

        if (input == "yes" || input == "y") return true;
        if (input == "no"  || input == "n") return false;

        std::cout << "Invalid input. Please enter 'yes' or 'no'.\n";
    }
}

int main() {
    std::cout << "================================\n";
    std::cout << "   Welcome to Tic-Tac-Toe!\n";
    std::cout << "================================\n";

    Board board;
    bool keepPlaying = true;

    while (keepPlaying) {
        int mode = selectMode();
        bool computerFirst = (mode == 3);

        if (mode == 2)
            std::cout << "Great! You will go first.\n";
        else if (mode == 3)
            std::cout << "Great! The computer will go first.\n";
        else
            std::cout << "Player 1 = X   |   Player 2 = O\n";

        board.reset();
        board.display();

        int turn = 0;
        bool gameOver = false;

        while (!gameOver) {
            char symbol = (turn % 2 == 0) ? 'X' : 'O';

            bool isComputerTurn = (mode != 1) &&
                ((computerFirst  && turn % 2 == 0) ||
                 (!computerFirst && turn % 2 == 1));

            int move;
            if (isComputerTurn) {
                move = getComputerMove(board);
                std::cout << "Computer (" << symbol << ") plays cell " << move << ".\n";
            } else {
                int humanNum = (mode == 1) ? (turn % 2 + 1) : 1;
                move = getHumanMove(board, humanNum, symbol);
            }

            board.makeMove(move, symbol);
            board.display();

            if (board.checkWin(symbol)) {
                if (isComputerTurn)
                    std::cout << "Computer (" << symbol << ") wins!\n\n";
                else if (mode == 1)
                    std::cout << "Player " << (turn % 2 + 1) << " (" << symbol << ") wins!\n\n";
                else
                    std::cout << "Player (" << symbol << ") wins!\n\n";
                gameOver = true;
            } else if (board.isFull()) {
                std::cout << "It's a draw!\n\n";
                gameOver = true;
            }

            turn++;
        }

        keepPlaying = askPlayAgain();
    }

    std::cout << "\nThanks for playing! Goodbye.\n";
    return 0;
}