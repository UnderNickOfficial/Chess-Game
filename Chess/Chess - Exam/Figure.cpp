#include "Figure.h"
#include"Queen.h"
Figure::Figure(int textureIndex, Vector2i boardPosition, bool isWhite, const Vector2f& startPosition, const Vector2f& cellSize, vector<Move*>& moves, Figure* board[8][8], vector<Figure*>& figures, bool dangerousCells[8][8]) : ChessSystemPtr()
{
	_vectorPos = _chessSystem->_allFigures->size();
	_chessSystem->_allFigures->push_back(this);
	_figures = &figures;
	_figures->push_back(this);
	_moves = &moves;
	_board = board;
	_dangerousCells = dangerousCells;
	_boardPosition = boardPosition;
	_isWhite = isWhite;
	_figure.setTexture(_chessSystem->_textures[textureIndex]);	
	UpdateColor();
	updateScale(cellSize);
	updatePosition(startPosition, cellSize);
}

bool Figure::isWhite()
{
	return _isWhite;
}

void Figure::draw()
{
	_chessSystem->_renderWindow->draw(_figure);
}

int Figure::getPosX()
{
	return _boardPosition.x;
}

int Figure::getPosY()
{
	return _boardPosition.y;
}

int Figure::getBegin()
{
	return _begin;
}

int Figure::getEnd()
{
	return _end;
}

int Figure::getVectorPos()
{
	return _vectorPos;
}

bool Figure::isOnBoard()
{
	return _isOnBoard;
}

void Figure::Insert()
{
	_figures->push_back(this);
	_isOnBoard = true;
}

void Figure::Erase()
{
	int i = 0;
	_isOnBoard = false;
	for (Figure* figure : *_figures)
	{
		if (figure == this)
		{
			_figures->erase(_figures->begin() + i);
			break;
		}
		i++;
	}
}

void Figure::UpdateColor()
{
	if (!_isWhite)
	{
		if (_chessSystem->_darkMode)
			_figure.setColor(Color(23, 32, 42));//black; dark mode
		else
			_figure.setColor(Color(23, 32, 42));//black; light mode
	}
	else
	{
		if (_chessSystem->_darkMode)
			_figure.setColor(Color(240, 243, 244));//white; dark mode
		else
			_figure.setColor(Color(244, 246, 241));//white; light mode
	}

}

unsigned long long Figure::getMovesCount()
{
	return _movesCount;
}

void Figure::setMovesCount(unsigned long long movesCount)
{
	_movesCount = movesCount;
}

vector<Move*>* Figure::getMoves()
{
	return _moves;
}

void Figure::incMovesCount()
{
	_movesCount++;
}

void Figure::decMovesCount()
{
	_movesCount--;
}

void Figure::nextMove(Vector2i boardPosition, const Vector2f & startPosition, const Vector2f & cellSize)
{
	setPosition(boardPosition, startPosition, cellSize);
	_movesCount++;
}

void Figure::prevMove(Vector2i boardPosition, const Vector2f & startPosition, const Vector2f & cellSize)
{
	setPosition(boardPosition, startPosition, cellSize);
	_movesCount--;
}

void Figure::setPosition(Vector2i boardPosition, const Vector2f & startPosition, const Vector2f & cellSize)
{
	_boardPosition.x = boardPosition.x;
	_boardPosition.y = boardPosition.y;
	updatePosition(startPosition, cellSize);
}

const Vector2i& Figure::getPosition()
{
	return _boardPosition;
}

void Figure::updatePosition(const Vector2f& startPosition, const Vector2f& cellSize)
{
	_figure.setPosition(Vector2f(cellSize.x * _boardPosition.x + startPosition.x + 4, cellSize.y * _boardPosition.y + startPosition.y + 4));
}

void Figure::updateScale(const Vector2f& cellSize)
{
	_figure.setScale(Vector2f((cellSize.x - 8) / _figure.getTexture()->getSize().x, (cellSize.y - 8) / _figure.getTexture()->getSize().y));
}

Figure & Figure::operator=(const Figure & figure)
{
	if (this == &figure)
		return *this;
	_figure = figure._figure;
	_boardPosition = figure._boardPosition;
	_isWhite = figure._isWhite;
	return *this;
}

void Figure::clearFromAllFigures()
{
	_chessSystem->_allFigures->erase(_chessSystem->_allFigures->begin() + _vectorPos);
}

Figure::~Figure()
{
	//_chessSystem->_allFigures->erase(_chessSystem->_allFigures->begin() + _vectorPos);
}

Move::Move(Figure* figure, const Vector2i& position)
{
	_figure = figure;
	_position = position;
}

Figure * Move::getFigure()
{
	return _figure;
}

Vector2i Move::getPosition()
{
	return _position;
}

int Move::getNewPosX()
{
	return _position.x;
}

int Move::getNewPosY()
{
	return _position.y;
}

int Move::getOldPosX()
{
	return _position2.x;
}

int Move::getOldPosY()
{
	return _position2.y;
}

void Move::simpleMove(Figure * board[8][8], Vector2f startPosition, Vector2f cellSize)
{
	_position2 = _figure->getPosition();
	swap(board[_position2.x][_position2.y], board[_position.x][_position.y]);
	_figure->nextMove(_position, startPosition, cellSize);
}

void Move::simpleUndo(Figure * board[8][8], Vector2f startPosition, Vector2f cellSize)
{
	_position = _figure->getPosition();
	swap(board[_position2.x][_position2.y], board[_position.x][_position.y]);
	_figure->prevMove(_position2, startPosition, cellSize);
}

void Move::clear()
{
}

SimpleMove::SimpleMove(Figure * figure, const Vector2i & position) : Move(figure, position)
{
}

SimpleMove::SimpleMove(Figure * figure, const Vector2i & position, const Vector2i & oldPosition) : Move(figure, position)
{
	_position2 = oldPosition;
}

void SimpleMove::move(Figure * board[8][8], Vector2f startPosition, Vector2f cellSize)
{
	simpleMove(board, startPosition, cellSize);
}

void SimpleMove::undo(Figure * board[8][8], Vector2f startPosition, Vector2f cellSize)
{
	simpleUndo(board, startPosition, cellSize);
}

DeleteFigure::DeleteFigure(Figure * figure, const Vector2i & position, Figure * deletedFigure) : Move(figure, position)
{
	_deletedFigure = deletedFigure;
}

DeleteFigure::DeleteFigure(Figure * figure, const Vector2i & position, Figure * deletedFigure, const Vector2i & oldPosition) : Move(figure, position)
{
	_position2 = oldPosition;
	_deletedFigure = deletedFigure;
}

Figure * DeleteFigure::getDeletedFigure()
{
	return _deletedFigure;
}

void DeleteFigure::move(Figure * board[8][8], Vector2f startPosition, Vector2f cellSize)
{
	board[_deletedFigure->getPosX()][_deletedFigure->getPosY()] = nullptr;
	_deletedFigure->Erase();
	simpleMove(board, startPosition, cellSize);
}

void DeleteFigure::undo(Figure * board[8][8], Vector2f startPosition, Vector2f cellSize)
{
	
	simpleUndo(board, startPosition, cellSize);
	//cout << _position2.x << " " << _position2.y << " " << _position.x << " " << _position.y << endl;
	board[_deletedFigure->getPosX()][_deletedFigure->getPosY()] = _deletedFigure;
	_deletedFigure->Insert();
}

void DeleteFigure::clear()
{
	delete _deletedFigure;
}

NewFigure::NewFigure(Figure * figure, const Vector2i & position, vector<Move*>* moves, Figure* board[8][8], vector<Figure*>* figures, bool dangerousCells[8][8]) : Move(figure, position)
{
	_dangerousCells = dangerousCells;
	_figures = figures;
	_moves = moves;
	_board = board;
}

NewFigure::NewFigure(Figure * figure, const Vector2i & position, Figure * newFigure, const Vector2i& oldPosition) : Move(figure, position)
{
	_newFigure = newFigure;
	_position2 = oldPosition;
}

Figure * NewFigure::getNewFigure()
{
	return _newFigure;
}

void NewFigure::move(Figure * board[8][8], Vector2f startPosition, Vector2f cellSize)
{
	_position2 = _figure->getPosition();
	_newFigure = new Queen(_position, _figure->isWhite(), startPosition, cellSize, *_moves, _board, *_figures, _dangerousCells);
	board[_position2.x][_position2.y] = nullptr;
	board[_position.x][_position.y] = _newFigure;
	_figure->Erase();
}

void NewFigure::undo(Figure * board[8][8], Vector2f startPosition, Vector2f cellSize)
{
	board[_position.x][_position.y] = nullptr;
	board[_position2.x][_position2.y] = _figure;
	_newFigure->Erase();
	_figure->Insert();
	_newFigure->clearFromAllFigures();
	delete _newFigure;
}

void NewFigure::clear()
{
	delete _figure;
}

NewDeleteFigure::NewDeleteFigure(Figure * figure, const Vector2i & position, vector<Move*>* moves, Figure * board[8][8], vector<Figure*>* figures, bool dangerousCells[8][8]) : Move(figure, position)
{
	_deletedFigure = board[_position.x][_position.y];
	_dangerousCells = dangerousCells;
	_figures = figures;
	_moves = moves;
	_board = board;
}

NewDeleteFigure::NewDeleteFigure(Figure * figure, const Vector2i & position, Figure * newFigure, Figure * deletedFigure, const Vector2i& oldPosition) : Move(figure, position)
{
	_newFigure = newFigure;
	_deletedFigure = _deletedFigure;
	_position2 = oldPosition;
}

Figure * NewDeleteFigure::getNewFigure()
{
	return _newFigure;
}

Figure * NewDeleteFigure::getDeletedFigure()
{
	return _deletedFigure;
}

void NewDeleteFigure::move(Figure * board[8][8], Vector2f startPosition, Vector2f cellSize)
{
	_position2 = _figure->getPosition();
	_newFigure = new Queen(_position, _figure->isWhite(), startPosition, cellSize, *_moves, _board, *_figures, _dangerousCells);
	board[_position2.x][_position2.y] = nullptr;
	board[_position.x][_position.y] = _newFigure;
	_figure->Erase();
	_deletedFigure->Erase();
}

void NewDeleteFigure::undo(Figure * board[8][8], Vector2f startPosition, Vector2f cellSize)
{
	board[_position.x][_position.y] = _deletedFigure;
	board[_position2.x][_position2.y] = _figure;
	_figure->Insert();
	_deletedFigure->Insert();
	_newFigure->Erase();
	_newFigure->clearFromAllFigures();
	delete _newFigure;
}

void NewDeleteFigure::clear()
{
	delete _deletedFigure;
	delete _figure;
}

Castling::Castling(Figure * figure, const Vector2i & position, Figure * secondFigure, Vector2i secondPosition) : Move(figure, position)
{
	_secondPosition = secondPosition;
	_secondFigure = secondFigure;
}

Castling::Castling(Figure * figure, const Vector2i & position, Figure * secondFigure, Vector2i secondPosition, Vector2i oldPosition, Vector2i secondOldPosition) : Move(figure, position)
{
	_secondPosition = secondPosition;
	_secondFigure = secondFigure;
	_position2 = oldPosition;
	_secondPosition2 = secondOldPosition;
}

Figure * Castling::getSecondFigure()
{
	return _secondFigure;
}

int Castling::getSecondNewPosX()
{
	return _secondPosition.x;
}

int Castling::getSecondNewPosY()
{
	return _secondPosition.y;
}

int Castling::getSecondOldPosX()
{
	return _secondPosition2.x;
}

int Castling::getSecondOldPosY()
{
	return _secondPosition2.y;
}

void Castling::move(Figure * board[8][8], Vector2f startPosition, Vector2f cellSize)
{
	simpleMove(board, startPosition, cellSize);
	_secondPosition2 = _secondFigure->getPosition();
	swap(board[_secondPosition2.x][_secondPosition2.y], board[_secondPosition.x][_secondPosition.y]);
	_secondFigure->nextMove(_secondPosition, startPosition, cellSize);
}

void Castling::undo(Figure * board[8][8], Vector2f startPosition, Vector2f cellSize)
{
	simpleUndo(board, startPosition, cellSize);
	swap(board[_secondPosition2.x][_secondPosition2.y], board[_secondPosition.x][_secondPosition.y]);
	_secondFigure->prevMove(_secondPosition2, startPosition, cellSize);
}
