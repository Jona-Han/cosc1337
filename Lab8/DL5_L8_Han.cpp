#include <iostream>
#include <iomanip>
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
        int emptySpacesRemaining;
        int lastPiece[3];
        void setPiece(int column, int row, int player);
        char getPiece(int column, int row);
    public:
        Board();
        int gameOver();
        void displayBoard();
        bool updateBoard(int column, int player);
};

Board::Board() {
    emptySpacesRemaining = 42;
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
    emptySpacesRemaining--;
}

char Board::getPiece(int column, int row) {
    if (column >= WIDTH || column < 0 || row >= HEIGHT || row < 0) {
        return -63;
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

int Board::gameOver() {
    //Check for tie
    if (emptySpacesRemaining == 0) { return 3; }

    //Check horizontal
    int piecesConnected = 1;
    for (int columnCounter = 0; columnCounter < WIDTH - 1; columnCounter++) {
        if ((getPiece(columnCounter, lastPiece[1]) == lastPiece[2])
            && (getPiece(columnCounter, lastPiece[1]) == getPiece(columnCounter + 1, lastPiece[1]))) {
            piecesConnected++;
            if (piecesConnected >= 4) { return lastPiece[2]; }
        } else { piecesConnected = 1; }
    }

    //Check vertical
    piecesConnected = 1;
    for (int rowCounter = 0; rowCounter < HEIGHT - 1; rowCounter++) {
        if ((getPiece(lastPiece[0], rowCounter) == lastPiece[2])
            && (getPiece(lastPiece[0], rowCounter) == getPiece(lastPiece[0], rowCounter + 1))) {
            piecesConnected++;
            if (piecesConnected >= 4) { return lastPiece[2]; }
        } else { piecesConnected = 1; }
    }

    //Check diagonal ascending
    piecesConnected = 1;
    for (int counter = -3; counter <= 3; counter++) {
        if ((getPiece(lastPiece[0] + counter, lastPiece[1] + counter) == lastPiece[2])
            && (getPiece(lastPiece[0] + counter, lastPiece[1] + counter)
                == getPiece(lastPiece[0] + counter + 1, lastPiece[1] + counter + 1))) {
            piecesConnected++;
            if (piecesConnected >= 4) { return lastPiece[2]; }
        } else { piecesConnected = 1; }
    }

    //Check diagonal descending
    piecesConnected = 1;
    for (int counter = -3; counter <= 3; counter++) {
        if ((getPiece(lastPiece[0] + counter, lastPiece[1] - counter) == lastPiece[2])
            && (getPiece(lastPiece[0] + counter, lastPiece[1] - counter)
                == getPiece(lastPiece[0] + counter + 1, lastPiece[1] - counter - 1))) {
            piecesConnected++;
            if (piecesConnected >= 4) { return lastPiece[2]; }
        } else { piecesConnected = 1; }
    }
    return 0;
}

class Game {
    private:
        Board board;
        bool gameOver;
        int whichPlayerIsPlaying;
        int whoWon;
        static int playerOneWins;
        static int playerTwoWins;
        static int ties;

        void checkGameOver();
        void promptUser();
        void updateGame(int column);
        int getUserInput();
    public:
        Game();
        void playGame();
        int getWhoWon();
        static int getPlayerOneScore();
        static int getPlayerTwoScore();
        static int getTies();
};
int Game::playerOneWins = 0;
int Game::playerTwoWins = 0;
int Game::ties = 0;

Game::Game() {
    board = Board();
    gameOver = false;
    whichPlayerIsPlaying = 1;
    whoWon = 0;
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
        cout << "\nPlayer 1 (" << "X) " << "enter your column to drop into (1-7, 0 to quit): ";
    } else {
        cout << "\nPlayer 2 (" << "O) " << "enter your column to drop into (1-7, 0 to quit): ";
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
    int winner = board.gameOver();
    switch (winner) {
        case 1:
            gameOver = true;
            whoWon = 1;
            playerOneWins++;
            break;
        case 2:
            gameOver = true;
            whoWon = 2;
            playerTwoWins++;
            break;
        case 3:
            gameOver = true;
            whoWon = 3;
            ties++;
            break;
    }
}

inline int Game::getPlayerOneScore() { return playerOneWins; }

inline int Game::getPlayerTwoScore() { return playerTwoWins; }

inline int Game::getWhoWon() { return whoWon; }

inline int Game:: getTies() { return ties; }

int main() {
    cout << "Welcome to connect 4. Below is the initial game board.\nEach column is marked by a number 1-7.\n"
         << "The two player tokens are X and O. X begins.\n";
    while (true) {
        Game game = Game();
        game.playGame();
        int winner= game.getWhoWon();
        if (winner == 1 || winner == 2) {
            cout << "Player " << winner << " has won the game!!!\n";
        } else if (winner == 3){
            cout << "Game is a tie. No one won!\n";
        } else {
            break;
        }

        int playerOneWins = Game::getPlayerOneScore();
        int playerTwoWins = Game::getPlayerTwoScore();
        int ties = Game::getTies();
        double totalGamesPlayed = playerOneWins + playerTwoWins + ties;
        cout << fixed << setprecision(0) << "Player one wins: " << playerOneWins << " ("
        << playerOneWins / totalGamesPlayed  * 100 << "%)    Player two wins: " << playerTwoWins << " ("
        << playerTwoWins / totalGamesPlayed  * 100 << "%)    Ties: " << ties << " ("
        << ties / totalGamesPlayed * 100 << "%)";
        cout << "\nDo you want to play again? (y/n): ";
        char userInput;
        cin >> userInput;
        if (tolower(userInput) == 'y') {
            continue;
        }
        break;
    }
    cout << "\nThis ends the Connect 4 game. Thanks for playing. Good-bye!";
    return 0;
}
