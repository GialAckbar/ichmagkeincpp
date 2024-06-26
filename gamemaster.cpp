#include <iostream>
#include <climits>
#include "gamemaster.hpp"
#include "humanplayer.hpp"
#include "computerplayer.hpp"

/**
 * @brief Starts a game of Tic Tac Toe.
 * @return True if the game should be exited, false otherwise.
 */
bool GameMaster::start() {
	std::cout << "Choose your game mode." << std::endl;
	std::cout << "(1) Human vs. Human" << std::endl;
	std::cout << "(2) Human vs. Computer (Minimax)" << std::endl;
	std::cout << "(3) Human vs. Computer (Random)" << std::endl;
	std::cout << "(4) Computer (Minimax) vs. Computer (Minimax)" << std::endl;
	std::cout << "(5) Exit Program" << std::endl;

	int mode;
	std::cin >> mode;

	if (std::cin.fail()) {
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
		return false;
	}

	switch (mode) {
	case 1:
		player1 = new HumanPlayer(GameBoard::Player::PLAYER1);
		player2 = new HumanPlayer(GameBoard::Player::PLAYER2);
		break;
	case 2:
		player1 = new HumanPlayer(GameBoard::Player::PLAYER1);
		player2 = new ComputerPlayer(GameBoard::Player::PLAYER2, ComputerPlayer::Mode::MINIMAX);
		break;
	case 3:
		player1 = new HumanPlayer(GameBoard::Player::PLAYER1);
		player2 = new ComputerPlayer(GameBoard::Player::PLAYER2, ComputerPlayer::Mode::RANDOM);
		break;
	case 4:
		player1 = new ComputerPlayer(GameBoard::Player::PLAYER1, ComputerPlayer::Mode::MINIMAX);
		player2 = new ComputerPlayer(GameBoard::Player::PLAYER2, ComputerPlayer::Mode::MINIMAX);
		break;
	case 5:
		return true;
	default:
		return false;
	}

	board = GameBoard();
	GameBoard::Status status = board.getStatus();
	int curPlayer = 1;

	std::cout << board << "Player 1: X" << std::endl << "Player 2: O" << std::endl;

	// Main game loop. Continue until either a player wins or the field is full (=draw)
	while (status == GameBoard::Status::RUNNING) {
		int row, column;

		std::cout << "Player " << curPlayer << "'s turn" << std::endl;

		// We give the player the row and column by reference so we can see the move the player made.
		if (curPlayer == 1) {
			player1->play(board, row, column);
		} else {
			player2->play(board, row, column);
		}

		std::cout << "Player " << curPlayer << ": " << row << "|" << column << std::endl << board;

		// Simple way to switch between player 1 and 2 each turn.
		curPlayer = 3 - curPlayer;
		status = board.getStatus();
	}

	switch (status) {
	case GameBoard::Status::DRAW :
		std::cout << "A draw!" << std::endl;
		return false;
	case GameBoard::Status::PLAYER1_WON :
		std::cout << "Winner is: Player 1 (X)" << std::endl;
		return false;
	case GameBoard::Status::PLAYER2_WON :
		std::cout << "Winner is: Player 2 (O)" << std::endl;
		return false;
	default :
		return false;
	}
}

/**
 * @brief Destructor for the GameMaster.
 */
GameMaster::~GameMaster() {
	delete player1;
	player1 = nullptr;

	delete player2;
	player2 = nullptr;
}