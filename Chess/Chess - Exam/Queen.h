#pragma once
#include"Figure.h"
class Queen : public Figure
{

public:
	Queen(Vector2i boardPosition, bool isWhite, const Vector2f& startPosition, const Vector2f& cellSize, vector<Move*>& moves, Figure* board[8][8], vector<Figure*>& figures, bool dangerousCells[8][8]);
	char getFigure()override;
	void addMoves(vector<Move*>* _moves)override;
	void checkCells()override;
private:
	bool checkMove(int x, int y, vector<Move*>* _moves);
	bool checkCell(int x, int y);
};
