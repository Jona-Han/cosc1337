#include <iostream>
using namespace std;
/*
 * 1. Make a new board.
 * 2. Prompt player 1 to drop piece in a column.
 * 3. Get player 1 input.
 * 4. Check if column is empty.
 *      - if so: place piece on the bottom position
 *      - if not: Find topmost empty space.
 * 5. Place piece in topmost empty space.
 * 6. Check for win condition and game over.
 * 7. If game is over, then end game with prompt and tally score.
 * 8. If not, repeat 2-6 for next player.
 */

const int XDIMENSION = 7;
const int YDIMENSION = 6;
const int WINCONDITION = 4;

class Board {
    private:
        char spaces[XDIMENSION][YDIMENSION];
        void setPiece(int column, int row, int player);
        char getPiece(int column, int row);
public:
        Board();
        bool gameOver();
        void displayBoard();
        bool updateBoard(int column, int player);
};

Board::Board() {
    for (int column = 0; column < XDIMENSION; column++) {
        for (int row = 0; row < YDIMENSION; row++) {
            spaces[column][row] = '*';
        }
    }
}

bool Board::updateBoard(int column, int player) {
    int row = 0;
    while (getPiece(column, row) != '*') {
        if (row == YDIMENSION) {
            return false;
        }
        row++;
    }
    setPiece(column, row, player);
    return true;
}

void Board::setPiece(int column, int row, int player) {
    if (player == 0) {
        spaces[column][row] = 'X';
    } else {
        spaces[column][row] = 'O';
    }
}

char Board::getPiece(int column, int row) {
    return spaces[column][row];
}

void Board::displayBoard() {
    cout << "    1234567\n    -------";
    for (int row = YDIMENSION - 1; row >= 0; row--) {
        cout << "    ";
        for (int column = XDIMENSION - 1; column >= 0; column--) {
            cout << spaces[column][row];
        }
        cout << endl;
    }
}

bool Board::gameOver() {
    int piecesInARow;
    int columnIndex = 0;
    int rowIndex = 0;
    
}

class Game {
    private:
        bool gameOver;
        int whichPlayerIsPlaying;
        Board board;

        void checkGameOver();
        void promptUser();
        void updateGame(int column);
        int getUserInput();
public:
        Game();
        void playGame();
};

Game::Game() {
    board = Board();
    gameOver = false;
    whichPlayerIsPlaying = 0;
}

void Game::playGame() {
    board.displayBoard();
    while (!gameOver) {
        promptUser();
        int userInput = getUserInput();
        updateGame(userInput);
        checkGameOver();
        whichPlayerIsPlaying = (whichPlayerIsPlaying + 1) % 2;
    }
}

void Game::promptUser() {
    if (whichPlayerIsPlaying == 0) {
        cout << "Player 1 (" << "X) " << "enter your column to drop into (1-7, zero to quit): ";
    } else {
        cout << "Player 2 (" << "O) " << "enter your column to drop into (1-7, zero to quit): ";
    }
}

int Game::getUserInput() {
    int userInput;
    while (!(cin >> userInput && userInput >= 0 && userInput <= XDIMENSION)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Please enter a column (1-7).\n";
    }
    return userInput;
}

void Game::updateGame(int column) {
    if (column == 0) {
        gameOver = true;
        return;
    } else {
        while(!board.updateBoard(column, whichPlayerIsPlaying)) {
            cout << "Column is full! Please enter a column (1-7): ";
            column = getUserInput();
        }
        board.displayBoard();
    }
}

void Game::checkGameOver() {
    if (board.gameOver()) {
        gameOver = true;
    }
}

int main() {
    Game game = Game();
    game.playGame();
    cout << "Good-bye!";
    return 0;
}
