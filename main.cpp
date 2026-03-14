#include <iostream>
#include <sstream>
#include "src/tictactoe.hpp"
#include <string>

int getMove(Board& board, int currentPlayer, char symbol) {
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

        // Reject decimals
        if (input.find('.') != std::string::npos) {
            std::cout << "Invalid input! Please enter a whole number, not a decimal.\n";
            continue;
        }

        // Try to parse as integer
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
        return cell;
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
    std::cout << "Player 1 = X   |   Player 2 = O\n";

    Board board;
    bool keepPlaying = true;

    while (keepPlaying) {
        board.reset();
        int currentPlayer = 1;
        board.display();

        bool gameOver = false;
        while (!gameOver) {
            char symbol = (currentPlayer == 1) ? 'X' : 'O';
            int move = getMove(board, currentPlayer, symbol);
            board.makeMove(move, symbol);
            board.display();

            if (board.checkWin(symbol)) {
                std::cout << "Player " << currentPlayer << " (" << symbol << ") wins!\n\n";
                gameOver = true;
            } else {
                currentPlayer = (currentPlayer == 1) ? 2 : 1;
            }
        }

        keepPlaying = askPlayAgain();
    }

    std::cout << "\nThanks for playing! Goodbye.\n";
    return 0;
}
