#ifndef COMPUTERPLAYER_H
#define COMPUTERPLAYER_H

#include "player.hpp"

/**
 * @brief Player controlled by the computer. Has a random and a minimax mode.
 */
class ComputerPlayer : public Player  {
public:
	enum Mode { RANDOM, MINIMAX };
	ComputerPlayer(const GameBoard::Player player, const Mode mode);
	void play(GameBoard& board, int& row, int& column) override;
private:
	void randomPlay(GameBoard& board, int& row, int& column);
	void minimaxPlay(GameBoard& board, int& row, int& column);
	Mode mode;
};

#endif // COMPUTERPLAYER_H