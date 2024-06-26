#include <random>
#include "computerplayer.hpp"

/**
 * @brief Constructor for the computer player.
 * @param player The player this object represents (Either PLAYER1 or PLAYER2)
 * @param mode The mode of the computer player (Either RANDOM or MINIMAX)
 */
ComputerPlayer::ComputerPlayer(const GameBoard::Player player, const Mode mode) {
	this->player = player;
	this->mode = mode;
}

/**
 * @brief Plays a move on the board depending on the mode of the computer player.
 * @param board The game board to play on.
 * @param row The row to place the move.
 * @param column The column to place the move.
 */
void ComputerPlayer::play(GameBoard& board, int& row, int& column) {
	switch (mode) {
		case Mode::RANDOM : randomPlay(board, row, column); break;
		case Mode::MINIMAX : minimaxPlay(board, row, column); break;
		default: break;
	}
}

/**
 * @brief Plays a random move on the board.
 * @param board The game board to play on.
 * @param row The row to place the move.
 * @param column The column to place the move.
 */
void ComputerPlayer::randomPlay(GameBoard& board, int& row, int& column) {
	std::random_device rd;
	std::mt19937 gen(rd());

	// Generate random numbers between 1 and the dimension of the board.
	std::uniform_int_distribution<> dis(1, board.getDimension());

	bool success = false;

	// Repeat generating random numbers until a valid move is found.
	while (!success) {
		row = dis(gen);
		column = dis(gen);
		success = board.place(player, row - 1, column - 1);
	}
}

/**
 * @brief Plays a move on the board using the minimax algorithm.
 * @param board The game board to play on.
 * @param row The row to place the move.
 * @param column The column to place the move.
 */
void ComputerPlayer::minimaxPlay(GameBoard& board, int& row, int& column) {
	// Task02
}