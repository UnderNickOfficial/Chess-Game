#pragma once
#include"Figure.h"
class Pawn : public Figure
{

public:
	Pawn(Vector2i boardPosition, bool isWhite, const Vector2f& startPosition, const Vector2f& cellSize, vector<Move*>& moves, Figure* board[8][8], vector<Figure*>& figures, bool dangerousCells[8][8]);
	char getFigure()override;
	void addMoves(vector<Move*>* _moves)override;
	void checkCells()override;
};
