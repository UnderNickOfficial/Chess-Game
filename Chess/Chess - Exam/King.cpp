#include "King.h"

King::King(Vector2i boardPosition, bool isWhite, const Vector2f& startPosition, const Vector2f& cellSize, vector<Move*>& moves, Figure* board[8][8], vector<Figure*>& figures, bool dangerousCells[8][8], int& state) : Figure(5, boardPosition, isWhite, startPosition, cellSize, moves, board, figures, dangerousCells)
{
	_state = &state;
}

char King::getFigure()
{
	return 'K';
}

void King::addMoves(vector<Move*>* _moves)
{
	_begin = _moves->size();
	checkMove(_boardPosition.x + 1, _boardPosition.y, _moves);
	checkMove(_boardPosition.x, _boardPosition.y + 1, _moves);
	checkMove(_boardPosition.x - 1, _boardPosition.y, _moves);
	checkMove(_boardPosition.x, _boardPosition.y - 1, _moves);

	checkMove(_boardPosition.x + 1, _boardPosition.y + 1, _moves);
	checkMove(_boardPosition.x - 1, _boardPosition.y + 1, _moves);
	checkMove(_boardPosition.x - 1, _boardPosition.y - 1, _moves);
	checkMove(_boardPosition.x + 1, _boardPosition.y - 1, _moves);
	if (getMovesCount() == 0)
	{
		int dx = 1;
		int t = 0;
		if (_isWhite)
		{
			dx = 0;
			t = 7;
		}

		if (_board[7][t] && _board[7][t]->isWhite() == _isWhite && _board[7][t]->getFigure() == 'R' && _board[7][t]->getMovesCount() == 0)
		{
			bool flag = true;
			for (int i = 5 - dx; i < 7; i++)
				if (_board[i][t] != nullptr || !_dangerousCells[i][t])
					flag = false;
			if (flag)
				_moves->push_back(new Castling(this, Vector2i(6, t), _board[7][t], Vector2i(5, t)));
		}
		if (_board[0][t] && _board[0][t]->isWhite() == _isWhite && _board[0][t]->getFigure() == 'R' && _board[0][t]->getMovesCount() == 0)
		{
			bool flag = true;
			for (int i = 3 - dx; i > 0; i--)
				if (_board[i][t] != nullptr || !_dangerousCells[i][t])
					flag = false;
			if (flag)
				_moves->push_back(new Castling(this, Vector2i(1, t), _board[0][t], Vector2i(2, t)));
		}
	}
	_end = _moves->size();
	if (!_dangerousCells[_boardPosition.x][_boardPosition.y])
	{
		if (_begin == _end)
			*_state = 2;
		else
			*_state = 1;
	}
	else
		*_state = 0;
}

void King::UpdateState()
{
	vector<Move*> tmp;
	addMoves(&tmp);
	for (Move* move : tmp)
		delete move;
}

void King::checkCells()
{
	checkCell(_boardPosition.x + 1, _boardPosition.y);
	checkCell(_boardPosition.x, _boardPosition.y + 1);
	checkCell(_boardPosition.x - 1, _boardPosition.y);
	checkCell(_boardPosition.x, _boardPosition.y - 1);

	checkCell(_boardPosition.x + 1, _boardPosition.y + 1);
	checkCell(_boardPosition.x - 1, _boardPosition.y + 1);
	checkCell(_boardPosition.x - 1, _boardPosition.y - 1);
	checkCell(_boardPosition.x + 1, _boardPosition.y - 1);
}

bool King::checkMove(int x, int y, vector<Move*>* _moves)
{
	if (x < 0 || x > 7 || y < 0 || y > 7 || !_dangerousCells[x][y])
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

void King::checkCell(int x, int y)
{
	if (x < 0 || x > 7 || y < 0 || y > 7)
		return;

	_dangerousCells[x][y] = false;
}
