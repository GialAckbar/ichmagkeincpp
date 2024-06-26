#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <iostream>

/**
 * @brief Class representing the tic tac toe field.
 */
class GameBoard {
public:
	enum Status { PLAYER1_WON, PLAYER2_WON, DRAW, RUNNING };
	enum Player { NONE, PLAYER1, PLAYER2 };
	GameBoard();
	Status getStatus() const;
	int getDimension() const;
	bool place(const Player player, const int row, const int column);
	bool remove(const int row, const int column);
	friend std::ostream& operator<<(std::ostream& out, GameBoard& board);
private:
	bool inBounds(const int row, const int column) const;
	bool isFree(const int row, const int column) const;
	Player checkLines(const bool horizontal) const;
	Player checkDiagonal(const bool descending) const;
	bool fieldsAvailable() const;
	static const int dimension = 3;
	static const int rows = dimension;
	static const int columns = dimension;
	Player board[rows][columns];
};

#endif // GAMEBOARD_H