#include "gamemaster.hpp"

/**
 * @brief Main function starting the game.
 * @return 0 (success)
 */
int main() {
	GameMaster gm = GameMaster();
	while (true) {
		if (gm.start()) return 0;
	}
}