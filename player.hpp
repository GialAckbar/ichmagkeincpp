#ifndef PLAYER_H
#define PLAYER_H

#include "gameboard.hpp"

/**
 * @brief Interface for player classes.
 */
class Player {
public:
	virtual void play(GameBoard& board, int& row, int& column) = 0;
protected:
	GameBoard::Player player;
};

#endif // PLAYER_H