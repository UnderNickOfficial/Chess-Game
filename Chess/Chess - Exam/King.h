#pragma once
#include"Figure.h"
class King : public Figure
{
	int* _state = nullptr;
public:
	King(Vector2i boardPosition, bool isWhite, const Vector2f& startPosition, const Vector2f& cellSize, vector<Move*>& moves, Figure* board[8][8], vector<Figure*>& figures, bool dangerousCells[8][8], int& state);
	char getFigure()override;
	void addMoves(vector<Move*>* _moves)override;
	void UpdateState();
	void checkCells()override;
private:
	bool checkMove(int x, int y, vector<Move*>* _moves);
	void checkCell(int x, int y);
};
