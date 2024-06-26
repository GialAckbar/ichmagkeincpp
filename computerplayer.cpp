#include <random>
#include <climits>
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
 * @brief Recursive function to calculate the best move using the minimax algorithm.
 * @param board The game board to play on.
 * @param myself True if the current player is the computer player, false otherwise.
 * @return The score of the best move.
 */
int ComputerPlayer::minimax(GameBoard& board, const bool myself) {
	GameBoard::Status status = board.getStatus();

	switch (status) {
	case GameBoard::Status::PLAYER1_WON :
		return (player == GameBoard::Player::PLAYER1) ? 10 : -10;
	case GameBoard::Status::PLAYER2_WON :
		return (player == GameBoard::Player::PLAYER2) ? 10 : -10;
	case GameBoard::Status::DRAW :
		return 0;
	default:
		break;
	}

	GameBoard::Player opponent = (player == GameBoard::Player::PLAYER1) ? GameBoard::Player::PLAYER2 : GameBoard::Player::PLAYER1;
	int bestScore = myself ? INT_MIN : INT_MAX;

	for (int curRow = 0; curRow < board.getDimension(); curRow++) {
		for (int curColumn = 0; curColumn < board.getDimension(); curColumn++) {
			if (!board.place(myself ? player : opponent, curRow, curColumn)) continue;

			bestScore = myself ? std::max(bestScore, minimax(board, !myself)) : std::min(bestScore, minimax(board, !myself));
			board.remove(curRow, curColumn);
		}
	}

	return bestScore;
}

/**
 * @brief Plays a move on the board using the minimax algorithm.
 * @param board The game board to play on.
 * @param row The row to place the move.
 * @param column The column to place the move.
 */
void ComputerPlayer::minimaxPlay(GameBoard& board, int& row, int& column) {
	int bestScore = INT_MIN;
	int bestRow = -1;
	int bestColumn = -1;

	// Loop through all fields on the board.
	for (int curRow = 0; curRow < board.getDimension(); curRow++) {
		for (int curColumn = 0; curColumn < board.getDimension(); curColumn++) {
			// If the field is already occupied, skip this field.
			if (!board.place(player, curRow, curColumn)) continue;

			int score = minimax(board, false);
			board.remove(curRow, curColumn);

			// If the score is better than the current best score, update the best score and move.
			if (score > bestScore) {
				bestScore = score;
				bestRow = curRow;
				bestColumn = curColumn;
			}
		}
	}

	// Place the move with the best score.
	board.place(player, bestRow, bestColumn);

	row = bestRow + 1;
	column = bestColumn + 1;
}