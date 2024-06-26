#include <climits>
#include "humanplayer.hpp"

/**
 * @brief Constructor for the HumanPlayer class.
 * @param player The player this object represents.
 */
HumanPlayer::HumanPlayer(const GameBoard::Player player) {
	this->player = player;
}

/**
 * @brief Lets the human player play a move on the board.
 * @param board The game board to play on.
 * @param row The row to place the move.
 * @param column The column to place the move.
 */
void HumanPlayer::play(GameBoard& board, int& row, int& column) {
	bool validInput = false;

	// Let the player select a row until a valid input is given.
	while (!validInput) {
		std::cout << "Select a row:";
		std::cin >> row;

		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
			std::cout << "Invalid field selection" << std::endl;
		} else {
			validInput = true;
		}
	}

	std::cout << std::endl;
	validInput = false;

	// Let the player select a column until a valid input is given.
	while (!validInput) {
		std::cout << "Select a column:";
		std::cin >> column;

		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
			std::cout << "Invalid field selection" << std::endl;
		} else {
			validInput = true;
		}
	}

	// If a player enters for example a 1, it needs to be converted to a 0 since we work with arrays.
	bool success = board.place(player, row - 1, column - 1);

	// If the field is already occupied, let the player play again.
	if (!success) {
		std::cout << "Invalid field selection" << std::endl;
		play(board, row, column);
	}
}