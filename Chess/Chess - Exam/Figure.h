#pragma once
#include"ChessSystem.h"
class Move;
class Queen;
class Figure : public ChessSystemPtr
{
protected:
	Sprite _figure;
	Vector2i _boardPosition;
	bool _isWhite;
	unsigned long long _movesCount = 0;
	vector<Move*>* _moves;
	vector<Figure*>* _figures;
	vector<Figure*> _allFigures;
	Figure* (*_board)[8];
	bool (*_dangerousCells)[8];
	int _begin;
	int _end;
	int _vectorPos = 0;
	bool _isOnBoard = true;
public:
	Figure(int textureIndex, Vector2i boardPosition, bool isWhite, const Vector2f& startPosition, const Vector2f& cellSize, vector<Move*>& moves, Figure* board[8][8], vector<Figure*>& figures, bool _dangerousCells[8][8]);
	virtual char getFigure() = 0;
	virtual void addMoves(vector<Move*>* _moves) = 0;
	virtual void checkCells() = 0;
	bool isWhite();
	void draw();
	int getPosX();
	int getPosY();
	int getBegin();
	int getEnd();
	int getVectorPos();
	bool isOnBoard();
	void Insert();
	void Erase();
	void UpdateColor();
	unsigned long long getMovesCount();
	void setMovesCount(unsigned long long movesCount);
	vector<Move*>* getMoves();
	void incMovesCount();
	void decMovesCount();
	void nextMove(Vector2i boardPosition, const Vector2f& startPosition, const Vector2f& cellSize);
	void prevMove(Vector2i boardPosition, const Vector2f& startPosition, const Vector2f& cellSize);
	void setPosition(Vector2i boardPosition, const Vector2f& startPosition, const Vector2f& cellSize);
	const Vector2i& getPosition();
	void updatePosition(const Vector2f& startPosition, const Vector2f& cellSize);
	void updateScale(const Vector2f& cellSize);
	Figure&operator=(const Figure& figure); 
	void clearFromAllFigures();
	~Figure();
};

class Move
{
protected:
	Figure* _figure = nullptr;
	Vector2i _position;
	Vector2i _position2;
public:
	Move(Figure* figure, const Vector2i& position);
	Figure* getFigure();
	Vector2i getPosition();
	int getNewPosX();
	int getNewPosY();
	int getOldPosX();
	int getOldPosY();
	void simpleMove(Figure* board[8][8], Vector2f startPosition, Vector2f cellSize);
	void simpleUndo(Figure* board[8][8], Vector2f startPosition, Vector2f cellSize);
	virtual void move(Figure* board[8][8], Vector2f startPosition, Vector2f cellSize) = 0;
	virtual void undo(Figure* board[8][8], Vector2f startPosition, Vector2f cellSize) = 0;
	virtual void clear();
};

class Castling : public Move
{
	Figure* _secondFigure;
	Vector2i _secondPosition;
	Vector2i _secondPosition2;
public:
	Castling(Figure* figure, const Vector2i& position, Figure* secondFigure, Vector2i secondPosition);
	Castling(Figure* figure, const Vector2i& position, Figure* secondFigure, Vector2i secondPosition, Vector2i oldPosition, Vector2i secondOldPosition);
	Figure* getSecondFigure();
	int getSecondNewPosX();
	int getSecondNewPosY();
	int getSecondOldPosX();
	int getSecondOldPosY();
	void move(Figure* board[8][8], Vector2f startPosition, Vector2f cellSize)override;
	void undo(Figure* board[8][8], Vector2f startPosition, Vector2f cellSize)override;
};

class SimpleMove : public Move
{
public:
	SimpleMove(Figure* figure, const Vector2i& position);
	SimpleMove(Figure* figure, const Vector2i& position, const Vector2i& oldPosition);
	void move(Figure* board[8][8], Vector2f startPosition, Vector2f cellSize)override;
	void undo(Figure* board[8][8], Vector2f startPosition, Vector2f cellSize)override;
};

class DeleteFigure : public Move
{
	Figure* _deletedFigure;
public:
	DeleteFigure(Figure* figure, const Vector2i& position, Figure* deletedFigure);
	DeleteFigure(Figure* figure, const Vector2i& position, Figure* deletedFigure, const Vector2i& oldPosition);
	Figure* getDeletedFigure();
	void move(Figure* board[8][8], Vector2f startPosition, Vector2f cellSize)override;
	void undo(Figure* board[8][8], Vector2f startPosition, Vector2f cellSize)override;
	void clear()override;
};

class NewFigure : public Move
{
	Figure* _newFigure;
	vector<Move*>* _moves;
	Figure* (*_board)[8];
	vector<Figure*>* _figures;
	bool (*_dangerousCells)[8];
public:
	NewFigure(Figure* figure, const Vector2i& position, vector<Move*>* moves, Figure* board[8][8], vector<Figure*>* figures, bool dangerousCells[8][8]);
	NewFigure(Figure* figure, const Vector2i& position, Figure* newFigure, const Vector2i& oldPosition);
	Figure* getNewFigure();
	void move(Figure* board[8][8], Vector2f startPosition, Vector2f cellSize)override;
	void undo(Figure* board[8][8], Vector2f startPosition, Vector2f cellSize)override;
	void clear()override;
};

class NewDeleteFigure : public Move
{
	Figure* _newFigure;
	Figure* _deletedFigure;
	vector<Move*>* _moves;
	Figure* (*_board)[8];
	vector<Figure*>* _figures;
	bool(*_dangerousCells)[8];
public:
	NewDeleteFigure(Figure* figure, const Vector2i& position, vector<Move*>* moves, Figure* board[8][8], vector<Figure*>* figures, bool dangerousCells[8][8]);
	NewDeleteFigure(Figure* figure, const Vector2i& position, Figure* newFigure, Figure* deletedFigure, const Vector2i& oldPosition);
	Figure* getNewFigure();
	Figure* getDeletedFigure();
	void move(Figure* board[8][8], Vector2f startPosition, Vector2f cellSize)override;
	void undo(Figure* board[8][8], Vector2f startPosition, Vector2f cellSize)override;
	void clear()override;
};
