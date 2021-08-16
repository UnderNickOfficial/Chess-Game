#include "Queen.h"

Queen::Queen(Vector2i boardPosition, bool isWhite, const Vector2f& startPosition, const Vector2f& cellSize, vector<Move*>& moves, Figure* board[8][8], vector<Figure*>& figures, bool dangerousCells[8][8]) : Figure(4, boardPosition, isWhite, startPosition, cellSize, moves, board, figures, dangerousCells)
{
}

char Queen::getFigure()
{
	return 'Q';
}

void Queen::addMoves(vector<Move*>* _moves)
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

	//Right
	for (int i = _boardPosition.x + 1; i < 8; i++)
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

void Queen::checkCells()
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

bool Queen::checkMove(int x, int y, vector<Move*>* _moves)
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

bool Queen::checkCell(int x, int y)
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
