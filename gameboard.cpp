#include <string>
#include "gameboard.hpp"

/**
 * @brief Constructor for the game board.
 */
GameBoard::GameBoard() {
	// Initialize the board with empty fields.
	for (int row = 0; row < rows; row++) {
		for (int column = 0; column < columns; column++) {
			board[row][column] = Player::NONE;
		}
	}
}

/**
 * @brief Checks the status of the game.
 * @return Status of the game.
 */
GameBoard::Status GameBoard::getStatus() const {
	// Check for a horizontal line
	Player winner = checkLines(true);
	if (winner == Player::PLAYER1) return Status::PLAYER1_WON;
	if (winner == Player::PLAYER2) return Status::PLAYER2_WON;

	// Check for a vertical line
	winner = checkLines(false);
	if (winner == Player::PLAYER1) return Status::PLAYER1_WON;
	if (winner == Player::PLAYER2) return Status::PLAYER2_WON;

	// Check for descending diagonal line
	winner = checkDiagonal(true);
	if (winner == Player::PLAYER1) return Status::PLAYER1_WON;
	if (winner == Player::PLAYER2) return Status::PLAYER2_WON;

	// Check for ascending diagonal line
	winner = checkDiagonal(false);
	if (winner == Player::PLAYER1) return Status::PLAYER1_WON;
	if (winner == Player::PLAYER2) return Status::PLAYER2_WON;

	// Declare a draw when no empty fields are left
	return fieldsAvailable() ? Status::RUNNING : Status::DRAW;
}

/**
 * @brief Places a player on the board.
 * @param player The player to place on the board.
 * @param row The row to place the player.
 * @param column The column to place the player.
 * @return True if the player was placed successfully, false otherwise.
 */
bool GameBoard::place(const Player player, const int row, const int column) {
	// Only place something when given field is valid
	if (!isFree(row, column)) return false;

	board[row][column] = player;
	return true;
}

/**
 * @brief Removes a player from the board.
 * @param row The row to remove the player from.
 * @param column The column to remove the player from.
 * @return True if the player was removed successfully, false otherwise.
 */
bool GameBoard::remove(const int row, const int column) {
	// check if row and column are in bounds
	if (!inBounds(row, column)) return false;

	board[row][column] = Player::NONE;
	return true;
}

/**
 * @brief Checks if a field is free.
 * @param row The row to check.
 * @param column The column to check.
 * @return True if the field is free, false otherwise.
 */
bool GameBoard::isFree(const int row, const int column) const {
	// check if row and column are in bounds
	if (!inBounds(row, column)) return false;

	// check if selected field is not occupied
	if (board[row][column] != Player::NONE) return false;

	return true;
}

/**
 * @brief Checks if a field is in bounds.
 * @param row The row to check.
 * @param column The column to check.
 * @return True if the field is in bounds, false otherwise.
 */
bool GameBoard::inBounds(const int row, const int column) const {
	return !(row >= rows || row < 0 || column >= columns || column < 0);
}

/**
 * @brief Checks if a player has occupied a full line.
 * @param horizontal If true, checks for a horizontal line, otherwise for a vertical line.
 * @return The player that has occupied a full line, or NONE if no player has occupied a full line.
 */
GameBoard::Player GameBoard::checkLines(const bool horizontal) const {
	for (int i = 0; i < dimension; i++) {
		// Counts how many fields a player has occupied in a specific row/column
		int player1_points = 0;
		int player2_points = 0;

		for (int j = 0; j < dimension; j++) {
			// First dimension is row, second dimension is column.
			// Means that if we want to check horizontally, we check in order board[0][0] -> board[0][1] ...
			// Vertically we check board[0][0] -> board[1][0] -> board[2][0] ...
			switch (horizontal ? board[i][j] : board[j][i]) {
			case Player::PLAYER1 :
				player1_points++;
				break;
			case Player::PLAYER2 :
				player2_points++;
				break;
			default:
				break;
			}
		}

		// If our dimension is 3 and a player has occupied 3 fields in a line
		// then he has a full line making him the winner of the game
		if (player1_points == dimension) {
			return Player::PLAYER1;
		} 
		
		if (player2_points == dimension) {
			return Player::PLAYER2;
		}
	}

	return Player::NONE;
}

/**
 * @brief Checks if a player has occupied a full diagonal.
 * @param descending If true, checks for a descending diagonal, otherwise for an ascending diagonal.
 * @return The player that has occupied a full diagonal, or NONE if no player has occupied a full diagonal.
 */
GameBoard::Player GameBoard::checkDiagonal(const bool descending) const {
	int player1_points = 0;
	int player2_points = 0;

	// Used for ascending check. Starts at bottom left and goes up to top right
	int row = rows - 1;
	int column = 0;

	for (int i = 0; i < dimension; i++) {
		// When checking descending, we check in order board[0][0] -> board[1][1] -> board[2][2]
		// When checking ascending, we check in order board[2][0] -> board[1][1] -> board[0][2]
		Player player = descending ? board[i][i] : board[row][column];
	
		if (player == Player::PLAYER1) {
			player1_points++;
		} else if (player == Player::PLAYER2) {
			player2_points++;
		}

		row--;
		column++;
	}

	if (player1_points == dimension) {
		return Player::PLAYER1;
	}

	if (player2_points == dimension) {
		return Player::PLAYER2;
	}

	return Player::NONE;
}

/**
 * @brief Checks if there are any fields available.
 * @return True if there are fields available, false otherwise.
 */
bool GameBoard::fieldsAvailable() const {
	for (int row = 0; row < rows; row++) {
		for (int column = 0; column < columns; column++) {
			if (board[row][column] == Player::NONE) return true;
		}
	}

	return false;
}

/**
 * @brief Getter for the dimension of the game board.
 * @return The dimension of the game board.
 */
int GameBoard::getDimension() const {
	return dimension;
}

/**
 * @brief Overloaded operator to print the game board.
 * @param out The output stream to print to.
 * @param board The game board to print.
 * @return The output stream.
 */
std::ostream& operator<<(std::ostream& out, GameBoard& board) {
	std::string line = "   ";
	out << "    ";

	for (int i = 1; i <= GameBoard::dimension; i++) {
		out << " " << i << "  ";
		line += "----";
	}

	line += "-";
	out << std::endl << line << std::endl;

	for (int i = 0; i < GameBoard::dimension; i++) {
		out << " " << i + 1 << " |";
		for (int j = 0; j < GameBoard::dimension; j++) {
			char playerIcon = ' ';
			switch (board.board[i][j]) {
			case GameBoard::Player::PLAYER1 :
				playerIcon = 'X';
				break;
			case GameBoard::Player::PLAYER2 :
				playerIcon = 'O';
				break;
			default:
				break;
			}
			out << " " << playerIcon << " |";
		}
		out << std::endl << line << std::endl;
	}

	return out;
}