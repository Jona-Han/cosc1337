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

const int WIDTH = 7;
const int HEIGHT = 6;
const int WINCONDITION = 4;

class Board {
    private:
        int spaces[WIDTH][HEIGHT];
        int lastPiece[3];
        void setPiece(int column, int row, int player);
        char getPiece(int column, int row);
    public:
        Board();
        bool gameOver();
        void displayBoard();
        bool updateBoard(int column, int player);
};

Board::Board() {
    for (int column = 0; column < WIDTH; column++) {
        for (int row = 0; row < HEIGHT; row++) {
            spaces[column][row] = 0;
        }
    }
}

bool Board::updateBoard(int column, int player) {
    int row = 0;
    while (getPiece(column, row) != 0) {
        if (row >= HEIGHT - 1) {
            return false;
        }
        row++;
    }
    setPiece(column, row, player);
    return true;
}

void Board::setPiece(int column, int row, int player) {
    if (player == 1) {
        spaces[column][row] = 1;
    } else {
        spaces[column][row] = 2;
    }
    lastPiece[0] = column;
    lastPiece[1] = row;
    lastPiece[2] = player;
}

char Board::getPiece(int column, int row) {
    if (column >= WIDTH || column < 0 || row >= HEIGHT || row < 0) {
        return 0;
    }
    return spaces[column][row];
}

void Board::displayBoard() {
    cout << "\n    1234567\n    -------\n";
    for (int row = HEIGHT - 1; row >= 0; row--) {
        cout << "    ";
        for (int column = 0; column < WIDTH; column++) {
            int piece = getPiece(column, row);
            if (piece == 0) {
                cout << '*';
            } else if (piece == 1) {
                cout << 'X';
            } else {
                cout << 'O';
            }
        }
        cout << endl;
    }
}

bool Board::gameOver() {
    int piecesConnected = 1;

    //Check horizontal
    for (int columnCounter = 0; columnCounter < WIDTH - 1; columnCounter++) {
        if ((getPiece(columnCounter, lastPiece[1]) == lastPiece[2])
            && (getPiece(columnCounter, lastPiece[1]) == getPiece(columnCounter + 1, lastPiece[1]))) {
            piecesConnected++;
            if (piecesConnected >= 4) { return true; }
        } else { piecesConnected = 1; }
    }

    //Check vertical
    for (int rowCounter = 0; rowCounter < HEIGHT - 1; rowCounter++) {
        if ((getPiece(lastPiece[0], rowCounter) == lastPiece[2])
            && (getPiece(lastPiece[0], rowCounter) == getPiece(lastPiece[0], rowCounter + 1))) {
            piecesConnected++;
            if (piecesConnected >= 4) {return true;}
        } else { piecesConnected = 1;}
    }
    return false;
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
    whichPlayerIsPlaying = 1;
}

void Game::playGame() {
    board.displayBoard();
    while (!gameOver) {
        promptUser();
        int userInput = getUserInput();
        updateGame(userInput);
        checkGameOver();
        if (whichPlayerIsPlaying == 1) {
            whichPlayerIsPlaying = 2;
        } else {
            whichPlayerIsPlaying = 1;
        }
    }
}

void Game::promptUser() {
    if (whichPlayerIsPlaying == 1) {
        cout << "Player 1 (" << "X) " << "enter your column to drop into (1-7, 0 to quit): ";
    } else {
        cout << "Player 2 (" << "O) " << "enter your column to drop into (1-7, 0 to quit): ";
    }
}

int Game::getUserInput() {
    int userInput;
    while (!(cin >> userInput && userInput >= 0 && userInput <= WIDTH)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Out of Bounds. Please enter a column (1-7, 0 to quit): ";
    }
    return userInput;
}

void Game::updateGame(int column) {
    if (column == 0) {
        gameOver = true;
        return;
    } else {
        while(!board.updateBoard(column - 1, whichPlayerIsPlaying)) {
            cout << "Column is full! Please enter a column (1-7, 0 to quit): ";
            column = getUserInput();

            if (column == 0) {
                gameOver = true;
                return;
            }
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
    cout << "Welcome to connect 4.\n";
    Game game = Game();
    game.playGame();
    cout << "Good-bye!";
    return 0;
}
