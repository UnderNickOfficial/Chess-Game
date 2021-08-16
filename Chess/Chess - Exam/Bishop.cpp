#include "Bishop.h"

Bishop::Bishop(Vector2i boardPosition, bool isWhite, Vector2f& startPosition, Vector2f& cellSize, vector<Move*>& moves, Figure* board[8][8], vector<Figure*>& figures, bool dangerousCells[8][8]) : Figure(3, boardPosition, isWhite, startPosition, cellSize, moves, board, figures, dangerousCells)
{
}

char Bishop::getFigure()
{
	return 'B';
}

void Bishop::addMoves(vector<Move*>* _moves)
{
	_begin = _moves->size();
	//Right-Up
	for (int i = 1; i < 8; i++)
		if (checkMove(_boardPosition.x + i, _boardPosition.y + i, _moves))
			break;
	//Left - Up
	for (int i = 1; i < 8; i++)
		if (checkMove(_boardPosition.x - i, _boardPosition.y + i, _moves))
			break;
	//Left - Down
	for (int i = 1; i < 8; i++)
		if (checkMove(_boardPosition.x - i, _boardPosition.y - i, _moves))
			break;
	//Right-Down
	for (int i = 1; i < 8; i++)
		if (checkMove(_boardPosition.x + i, _boardPosition.y - i, _moves))
			break;
	_end = _moves->size();
}

void Bishop::checkCells()
{
	//Right-Up
	for (int i = 1; i < 8; i++)
		if (checkCell(_boardPosition.x + i, _boardPosition.y + i))
			break;
	//Left - Up
	for (int i = 1; i < 8; i++)
		if (checkCell(_boardPosition.x - i, _boardPosition.y + i))
			break;
	//Left - Down
	for (int i = 1; i < 8; i++)
		if (checkCell(_boardPosition.x - i, _boardPosition.y - i))
			break;
	//Right-Down
	for (int i = 1; i < 8; i++)
		if (checkCell(_boardPosition.x + i, _boardPosition.y - i))
			break;
}

bool Bishop::checkMove(int x, int y, vector<Move*>* _moves)
{
	if (x < 0 || x > 7 || y < 0 || y > 7)
		return true;
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

bool Bishop::checkCell(int x, int y)
{
	if (x < 0 || x > 7 || y < 0 || y > 7)
		return true;
	_dangerousCells[x][y] = false;
	if (_board[x][y])
	{
		if (_board[x][y]->getFigure() == 'K')
			return false;
		return true;
	}
	return false;
}
