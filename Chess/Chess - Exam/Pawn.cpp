#include "Pawn.h"

Pawn::Pawn(Vector2i boardPosition, bool isWhite,const Vector2f& startPosition, const Vector2f& cellSize, vector<Move*>& moves, Figure* board[8][8], vector<Figure*>& figures, bool dangerousCells[8][8]) : Figure(0, boardPosition, isWhite, startPosition, cellSize, moves, board, figures, dangerousCells)
{
}

char Pawn::getFigure()
{
	return 'P';
}

void Pawn::addMoves(vector<Move*>* _moves)
{
	_begin = _moves->size();
	int dy = 0;
	if (isWhite())
		dy = -1;
	else
		dy = 1;

	if (_movesCount == 0 && _board[_boardPosition.x][_boardPosition.y + dy * 2] == nullptr && _board[_boardPosition.x][_boardPosition.y + dy] == nullptr)
		_moves->push_back(new SimpleMove(this, Vector2i(_boardPosition.x, _boardPosition.y + dy * 2)));

	if (_board[_boardPosition.x][_boardPosition.y + dy] == nullptr)
	{
		if ((_boardPosition.y == 6 && dy == 1) || (_boardPosition.y == 1 && dy == -1))
			_moves->push_back(new NewFigure(this, Vector2i(_boardPosition.x, _boardPosition.y + dy), _moves, _board, _figures, _dangerousCells));
		else
			_moves->push_back(new SimpleMove(this, Vector2i(_boardPosition.x, _boardPosition.y + dy)));
	}

	if (_boardPosition.x < 7 && _board[_boardPosition.x + 1][_boardPosition.y] && _board[_boardPosition.x + 1][_boardPosition.y]->isWhite() != isWhite() && _board[_boardPosition.x + 1][_boardPosition.y]->getFigure() == 'P' && _board[_boardPosition.x + 1][_boardPosition.y]->getMovesCount() == 1)
		_moves->push_back(new DeleteFigure(this, Vector2i(_boardPosition.x + 1, _boardPosition.y + dy), _board[_boardPosition.x + 1][_boardPosition.y]));

	if (_boardPosition.x > 0 && _board[_boardPosition.x - 1][_boardPosition.y] && _board[_boardPosition.x - 1][_boardPosition.y]->isWhite() != isWhite() && _board[_boardPosition.x - 1][_boardPosition.y]->getFigure() == 'P' && _board[_boardPosition.x - 1][_boardPosition.y]->getMovesCount() == 1)
		_moves->push_back(new DeleteFigure(this, Vector2i(_boardPosition.x - 1, _boardPosition.y + dy), _board[_boardPosition.x - 1][_boardPosition.y]));

	if (_boardPosition.x > 0 && _board[_boardPosition.x - 1][_boardPosition.y + dy] && _board[_boardPosition.x - 1][_boardPosition.y + dy]->isWhite() != _isWhite)
	{
		if ((_boardPosition.y == 6 && dy == 1) || (_boardPosition.y == 1 && dy == -1))
			_moves->push_back(new NewDeleteFigure(this, Vector2i(_boardPosition.x - 1, _boardPosition.y + dy), _moves, _board, _figures, _dangerousCells));
		else
			_moves->push_back(new DeleteFigure(this, Vector2i(_boardPosition.x - 1, _boardPosition.y + dy), _board[_boardPosition.x - 1][_boardPosition.y + dy]));
	}

	if (_boardPosition.x < 7 && _board[_boardPosition.x + 1][_boardPosition.y + dy] && _board[_boardPosition.x + 1][_boardPosition.y + dy]->isWhite() != _isWhite)
	{
		if ((_boardPosition.y == 6 && dy == 1) || (_boardPosition.y == 1 && dy == -1))
			_moves->push_back(new NewDeleteFigure(this, Vector2i(_boardPosition.x + 1, _boardPosition.y + dy), _moves, _board, _figures, _dangerousCells));
		else
			_moves->push_back(new DeleteFigure(this, Vector2i(_boardPosition.x + 1, _boardPosition.y + dy), _board[_boardPosition.x + 1][_boardPosition.y + dy]));
	}
	_end = _moves->size();
}

void Pawn::checkCells()
{
	int dy = 0;
	if (isWhite())
		dy = -1;
	else
		dy = 1;
	if (_boardPosition.x > 0)
	{
		_dangerousCells[_boardPosition.x - 1][_boardPosition.y + dy] = false;
	}

	if (_boardPosition.x < 7)
	{
		_dangerousCells[_boardPosition.x + 1][_boardPosition.y + dy] = false;
	}
}
