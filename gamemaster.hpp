#ifndef GAMEMASTER_H
#define GAMEMASTER_H

#include "gameboard.hpp"
#include "player.hpp"

/**
 * @brief Class controlling the game.
 */
class GameMaster {
public:
	bool start();
	~GameMaster();
private:
	Player* player1;
	Player* player2;
	GameBoard board;
};

#endif // GAMEMASTER_H