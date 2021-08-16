#include "Knight.h"

Knight::Knight(Vector2i boardPosition, bool isWhite, Vector2f& startPosition, Vector2f& cellSize, vector<Move*>& moves, Figure* board[8][8], vector<Figure*>& figures, bool dangerousCells[8][8]) : Figure(2, boardPosition, isWhite, startPosition, cellSize, moves, board, figures, dangerousCells)
{
}

char Knight::getFigure()
{
	return 'N';
}

void Knight::addMoves(vector<Move*>* _moves)
{
	_begin = _moves->size();
	checkMove(_boardPosition.x + 1, _boardPosition.y + 2, _moves);
	checkMove(_boardPosition.x + 2, _boardPosition.y + 1, _moves);
	checkMove(_boardPosition.x + 2, _boardPosition.y - 1, _moves);
	checkMove(_boardPosition.x + 1, _boardPosition.y - 2, _moves);
	checkMove(_boardPosition.x - 1, _boardPosition.y - 2, _moves);
	checkMove(_boardPosition.x - 2, _boardPosition.y - 1, _moves);
	checkMove(_boardPosition.x - 2, _boardPosition.y + 1, _moves);
	checkMove(_boardPosition.x - 1, _boardPosition.y + 2, _moves);
	_end = _moves->size();
}

void Knight::checkCells()
{
	checkCell(_boardPosition.x + 1, _boardPosition.y + 2);
	checkCell(_boardPosition.x + 2, _boardPosition.y + 1);
	checkCell(_boardPosition.x + 2, _boardPosition.y - 1);
	checkCell(_boardPosition.x + 1, _boardPosition.y - 2);
	checkCell(_boardPosition.x - 1, _boardPosition.y - 2);
	checkCell(_boardPosition.x - 2, _boardPosition.y - 1);
	checkCell(_boardPosition.x - 2, _boardPosition.y + 1);
	checkCell(_boardPosition.x - 1, _boardPosition.y + 2);
}

void Knight::checkMove(int x, int y, vector<Move*>* _moves)
{
	if (x < 0 || x > 7 || y < 0 || y > 7)
		return;
	if (_board[x][y] == nullptr)
		_moves->push_back(new SimpleMove(this, Vector2i(x, y)));
	else if (_board[x][y]->isWhite() != isWhite())
		_moves->push_back(new DeleteFigure(this, Vector2i(x, y), _board[x][y]));
}

bool Knight::checkCell(int x, int y)
{
	if (x < 0 || x > 7 || y < 0 || y > 7)
		return true;
	_dangerousCells[x][y] = false;
}
