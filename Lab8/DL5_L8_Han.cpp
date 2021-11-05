/*
  Programmer:           Jonathan Han
  Assignment:           Lab 8
  Topic:                Implement connect-4 game
  File Name:            DL5_L8_Han.cpp
  Course/Section:       COSC 1337; Section 5
  Instructor:           Thayer
*/

#include <iostream>
#include <iomanip>
using namespace std;

//GLOBAL CONSTANTS
const int WIDTH = 7;
const int HEIGHT = 6;
const int WINCONDITION = 4;

class Board {
    private:
        int spaces[WIDTH][HEIGHT];
        int emptySpacesRemaining;
        int lastPiece[3];
        void setPiece(int column, int row, int player);
        int getPiece(int column, int row);
    public:
        Board();
        int gameOver();
        void displayBoard();
        bool updateBoard(int column, int player);
};

/**
 * Constructs a new board.
 * Set remaining spaces counter to 42 spaces and set all spaces to 0.
 */
Board::Board() {
    emptySpacesRemaining = 42;
    for (int column = 0; column < WIDTH; column++) {
        for (int row = 0; row < HEIGHT; row++) {
            spaces[column][row] = 0;
        }
    }
}

/**
 * Finds the bottom-most empty space and sets a piece in that space. If column is full, then doesn't set a piece and
 * just returns false.
 *
 * @param column An integer representing the column selected by the player (1-7).
 * @param player Which player is playing (1 or 2).
 * @return false if provided column has no empty spaces, otherwise true
 */

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

/**
 * Sets the 2D spaces array with a player's piece.
 * Updates the lastPiece array with information about the piece that is being placed.
 * Decrements emptySpaceRemaining, a counter which represents the number of open spaces left in the board.
 *
 * @param column Integer representing column decided by player (0-6).
 * @param row Integer representing row of bottom-most empty space (0-5).
 * @param player Which player is playing (1 or 2).
 */
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

/**
 * Gets the piece in the board if the provided column and row are valid.
 *
 * @param column Integer representing column of board (0-6).
 * @param row Integer representing row of board (0-5).
 * @return 0 if empty, 1 if occupied by player 1's piece, 2 if occupied by player 2's piece, -63 if out of bounds.
 */
int Board::getPiece(int column, int row) {
    if (column >= WIDTH || column < 0 || row >= HEIGHT || row < 0) {
        return -63;
    }
    return spaces[column][row];
}

/**
 * Prints the current board out to the console.
 */
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

/**
 * Checks if a player has connected 4 pieces in a row on their current turn.
 *
 * Checks if a piece in a line is the same as the last placed pieced and is the same as the adjacent piece.
 * lastPiece[0] is the column value of the last set piece (0-6).
 * lastPiece[1] is the row value of the last set piece (0-5).
 * lastPiece[2] is the last player who set a piece (1 or 2).
 * Possible optimization here and make code less ugly.
 *
 * @return 1 if player 1 has connected four, 2 if player 2 has connected four, 3 if no empty spaces remain, otherwise 0.
 */
int Board::gameOver() {
    //Check for tie and return 3 if no empty spaces remain on the board.
    if (emptySpacesRemaining == 0) { return 3; }

    //Check horizontal connections
    int piecesConnected = 1;
    for (int columnCounter = 0; columnCounter < WIDTH - 1; columnCounter++) {
        if ((getPiece(columnCounter, lastPiece[1]) == lastPiece[2])
            && (getPiece(columnCounter, lastPiece[1]) == getPiece(columnCounter + 1, lastPiece[1]))) {
            piecesConnected++;

            if (piecesConnected >= 4) {
                return lastPiece[2];
            }
        } else {
            piecesConnected = 1;
        }
    }

    //Check vertical connections
    piecesConnected = 1;
    for (int rowCounter = 0; rowCounter < HEIGHT - 1; rowCounter++) {
        if ((getPiece(lastPiece[0], rowCounter) == lastPiece[2])
            && (getPiece(lastPiece[0], rowCounter) == getPiece(lastPiece[0], rowCounter + 1))) {
            piecesConnected++;

            if (piecesConnected >= 4) {
                return lastPiece[2];
            }
        } else {
            piecesConnected = 1;
        }
    }

    //Check diagonal ascending connections
    piecesConnected = 1;
    for (int counter = -3; counter <= 3; counter++) {
        if ((getPiece(lastPiece[0] + counter, lastPiece[1] + counter) == lastPiece[2])
            && (getPiece(lastPiece[0] + counter, lastPiece[1] + counter)
                == getPiece(lastPiece[0] + counter + 1, lastPiece[1] + counter + 1))) {
            piecesConnected++;

            if (piecesConnected >= 4) {
                return lastPiece[2];
            }
        } else {
            piecesConnected = 1;
        }
    }

    //Check diagonal descending connections
    piecesConnected = 1;
    for (int counter = -3; counter <= 3; counter++) {
        if ((getPiece(lastPiece[0] + counter, lastPiece[1] - counter) == lastPiece[2])
            && (getPiece(lastPiece[0] + counter, lastPiece[1] - counter)
                == getPiece(lastPiece[0] + counter + 1, lastPiece[1] - counter - 1))) {
            piecesConnected++;

            if (piecesConnected >= 4) {
                return lastPiece[2];
            }
        } else {
            piecesConnected = 1;
        }
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

/**
 * Constructs a new game instance.
 * Creates a blank board, sets the gameOver variable to false, sets the first player to 1, and sets an arbitrary winner.
 */
Game::Game() {
    board = Board();
    gameOver = false;
    whichPlayerIsPlaying = 1;
    whoWon = 0;
}

/**
 * Starts a game of connect-4.
 * 1. Display initial board.
 * 2. Give current player a prompt.
 * 3. Get player's column selection (1-7).
 * 4. Update the board with the user's selection.
 * 5. Check for a winner.
 * 6. Switch to next player.
 * 7. Repeat steps 2-6.
 */
void Game::playGame() {
    board.displayBoard();
    while (!gameOver) {
        promptUser();
        int userInput = getUserInput();
        updateGame(userInput);
        checkGameOver();

        if (whichPlayerIsPlaying == 1) { //Switch to next player
            whichPlayerIsPlaying = 2;
        } else {
            whichPlayerIsPlaying = 1;
        }
    }
}

/**
 * Prints each player's prompt to the console.
 */
void Game::promptUser() {
    if (whichPlayerIsPlaying == 1) {
        cout << "\nPlayer 1 (" << "X) " << "enter your column to drop into (1-7, 0 to quit): ";
    } else {
        cout << "\nPlayer 2 (" << "O) " << "enter your column to drop into (1-7, 0 to quit): ";
    }
}

/**
 * Obtains a column or 0 from the user. Validates input.
 *
 * @return Integer (0-7 inclusive) representing the user's desired column or 0 to quit.
 */
int Game::getUserInput() {
    int userInput;
    while (!(cin >> userInput && userInput >= 0 && userInput <= WIDTH)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Out of Bounds. Please enter a column (1-7, 0 to quit): ";
    }
    return userInput;
}

/**
 * Updates the board with the user's desired column or asks for a new selection if the provided column is already full.
 * Then displays updated board.
 * If zero is provided, sets gameOver flag to true, doesn't update board, and just returns.
 *
 * @param column Integer representing user's column input or zero to quit(0-7).
 */
void Game::updateGame(int column) {
    if (column == 0) {  //Set gameOver to true and don't update board if user provides 0
        gameOver = true;
        return;
    } else {
        //Update board or if column is full, get a new column
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

/**
 * Checks if the game is over, and if so, sets the gameOver flag to true and adds to scores.
 * winner is 1 means player 1 has won.
 * winner is 2 means player 2 has won.
 * winner is 3 means no empty spaces remain and thus there is a tie.
 * winner is 0 means no player has won yet and game continues.
 */
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

/**
 * Returns the number of total wins player 1 has.
 */
inline int Game::getPlayerOneScore() { return playerOneWins; }

/**
 * Returns the number of total wins player 2 has.
 */
inline int Game::getPlayerTwoScore() { return playerTwoWins; }

/**
 * Returns who won a particular game instance.
 */
inline int Game::getWhoWon() { return whoWon; }

/**
 * Returns the number of total ties.
 */
inline int Game:: getTies() { return ties; }

int main() {
    cout << "Welcome to connect 4. Below is the initial game board.\nEach column is marked by a number 1-7.\n"
         << "The two player tokens are X and O. X begins.\n";

    //main loop
    while (true) {
        Game game = Game();     //Creates a new game instance
        game.playGame();        //Starts game
        int winner = game.getWhoWon();       //Get winner of the game

        //Print outcome of the game
        if (winner == 1 || winner == 2) {
            cout << "Player " << winner << " has won the game!!!\n";
        } else if (winner == 3){
            cout << "Game is a tie. No one won!\n";
        } else {
            break;
        }

        //Get total scores
        int playerOneWins = Game::getPlayerOneScore();
        int playerTwoWins = Game::getPlayerTwoScore();
        int ties = Game::getTies();
        double totalGamesPlayed = playerOneWins + playerTwoWins + ties;

        //Print total wins and percentage for player 1, player 2, and ties.
        cout << fixed << setprecision(0) << "Player one wins: " << playerOneWins << " ("
        << playerOneWins / totalGamesPlayed  * 100 << "%)    Player two wins: " << playerTwoWins << " ("
        << playerTwoWins / totalGamesPlayed  * 100 << "%)    Ties: " << ties << " ("
        << ties / totalGamesPlayed * 100 << "%)";

        //Ask to play again and get
        cout << "\nDo you want to play again? (y/n): ";
        char userInput;
        cin >> userInput;

        //If user provides a y, then a new game is started, else the program breaks out of the main game loop and ends
        if (tolower(userInput) == 'y') {
            continue;
        }
        break;
    }
    cout << "\nThis ends the Connect 4 game. Thanks for playing. Good-bye!";
    return 0;
}

/*
Test Output:

 */
