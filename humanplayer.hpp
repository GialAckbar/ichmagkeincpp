#ifndef HUAMPLAYER_H
#define HUAMPLAYER_H

#include "player.hpp"

/**
 * @brief Player controlled by a human.
 */
class HumanPlayer : public Player  {
public:
	HumanPlayer(const GameBoard::Player player);
	void play(GameBoard& board, int& row, int& column) override;
};

#endif // HUAMPLAYER_H