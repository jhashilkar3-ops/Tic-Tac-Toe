#ifndef tictactoe_hpp
#define tictactoe_hpp

class Board {
public:
    Board();
    void reset();
    void display() const;
    bool makeMove(int cell, char player);
    bool isCellValid(int cell) const;
    bool isCellTaken(int cell) const;
    bool checkWin(char player) const;
    bool isFull() const;
    char getCell(int index) const;

private:
    char cells[9];
};

#endif

