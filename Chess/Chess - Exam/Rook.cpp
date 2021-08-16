#include "Rook.h"

Rook::Rook(Vector2i boardPosition, bool isWhite, Vector2f& startPosition, Vector2f& cellSize, vector<Move*>& moves, Figure* board[8][8], vector<Figure*>& figures, bool dangerousCells[8][8]) : Figure(1, boardPosition, isWhite, startPosition, cellSize, moves, board, figures, dangerousCells)
{
}

char Rook::getFigure()
{
	return 'R';
}

void Rook::addMoves(vector<Move*>* _moves)
{
	_begin = _moves->size();
	//Right
	for (int i = _boardPosition.x + 1; i<8; i++)
		if (checkMove(i, _boardPosition.y, _moves))
			break;
	//Left
	for (int i = _boardPosition.x - 1; i >= 0; i--)
		if (checkMove(i, _boardPosition.y, _moves))
			break;
	//Up
	for (int i = _boardPosition.y + 1; i < 8; i++)
		if (checkMove(_boardPosition.x, i, _moves))
			break;
	//Down
	for (int i = _boardPosition.y - 1; i >= 0; i--)
		if (checkMove(_boardPosition.x, i, _moves))
			break;
	_end = _moves->size();
}

void Rook::checkCells()
{
	//Right
	for (int i = _boardPosition.x + 1; i < 8; i++)
		if (checkCell(i, _boardPosition.y))
			break;
	//Left
	for (int i = _boardPosition.x - 1; i >= 0; i--)
		if (checkCell(i, _boardPosition.y))
			break;
	//Up
	for (int i = _boardPosition.y + 1; i < 8; i++)
		if (checkCell(_boardPosition.x, i))
			break;
	//Down
	for (int i = _boardPosition.y - 1; i >= 0; i--)
		if (checkCell(_boardPosition.x, i))
			break;
}

bool Rook::checkMove(int x, int y, vector<Move*>* _moves)
{
	if (_board[x][y])
	{
		if (_board[x][y]->isWhite() != isWhite())
			_moves->push_back(new DeleteFigure(this, Vector2i(x, y), _board[x][y]));
		return true;
	}
	else
		_moves->push_back(new SimpleMove(this, Vector2i(x, y)));
	return false;
}

bool Rook::checkCell(int x, int y)
{
	_dangerousCells[x][y] = false;
	if (_board[x][y])
	{
		if (_board[x][y]->getFigure() == 'K')
			return false;
		return true;
	}
	return false;
}
