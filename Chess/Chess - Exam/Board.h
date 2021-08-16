#pragma once
#include"Pawn.h"
#include"Rook.h"
#include"Knight.h"
#include"Bishop.h"
#include"Queen.h"
#include"King.h"
#include"ColoredText.h"
class Board : public ICommand
{
	const int _maxFindDepth = 4;
	int _findDepth = 4;
	float pawnEvalWhite[8][8] =
	{
		{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
		{5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0},
		{1.0, 1.0, 2.0, 3.0, 3.0, 2.0, 1.0, 1.0},
		{0.5, 0.5, 1.0, 2.5, 2.5, 1.0, 0.5, 0.5},
		{0.0, 0.0, 0.0, 2.0, 2.0, 0.0, 0.0, 0.0},
		{0.5, -0.5, -1.0, 0.0, 0.0, -1.0, -0.5, 0.5},
		{0.5, 1.0, 1.0, -2.0, -2.0, 1.0, 1.0, 0.5},
		{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}
	};

	float pawnEvalBlack[8][8]{};

	float knightEval[8][8] =
	{
		{-5.0, -4.0, -3.0, -3.0, -3.0, -3.0, -4.0, -5.0},
		{-4.0, -2.0, 0.0, 0.0, 0.0, 0.0, -2.0, -4.0},
		{-3.0, 0.0, 1.0, 1.5, 1.5, 1.0, 0.0, -3.0},
		{-3.0, 0.5, 1.5, 2.0, 2.0, 1.5, 0.5, -3.0},
		{-3.0, 0.0, 1.5, 2.0, 2.0, 1.5, 0.0, -3.0},
		{-3.0, 0.5, 1.0, 1.5, 1.5, 1.0, 0.5, -3.0},
		{-4.0, -2.0, 0.0, 0.5, 0.5, 0.0, -2.0, -4.0},
		{-5.0, -4.0, -3.0, -3.0, -3.0, -3.0, -4.0, -5.0}
	};

	float bishopEvalWhite[8][8] =
	{
		{-2.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -2.0},
		{-1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0},
		{-1.0, 0.0, 0.5, 1.0, 1.0, 0.5, 0.0, -1.0},
		{-1.0, 0.5, 0.5, 1.0, 1.0, 0.5, 0.5, -1.0},
		{-1.0, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0, -1.0},
		{-1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, -1.0},
		{-1.0, 0.5, 0.0, 0.0, 0.0, 0.0, 0.5, -1.0},
		{-2.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -2.0}
	};

	float bishopEvalBlack[8][8]{};
	float rookEvalWhite[8][8] = 
	{
		{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
		{0.5, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.5},
		{-0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.5},
		{-0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.5},
		{-0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.5},
		{-0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.5},
		{-0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.5},
		{0.0, 0.0, 0.0, 0.5, 0.5, 0.0, 0.0, 0.0}
	};

	float rookEvalBlack[8][8]{};
	float evalQueen[8][8] = 
	{
		{-2.0, -1.0, -1.0, -0.5, -0.5, -1.0, -1.0, -2.0},
		{-1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0},
		{-1.0, 0.0, 0.5, 0.5, 0.5, 0.5, 0.0, -1.0},
		{-0.5, 0.0, 0.5, 0.5, 0.5, 0.5, 0.0, -0.5},
		{0.0, 0.0, 0.5, 0.5, 0.5, 0.5, 0.0, -0.5},
		{-1.0, 0.5, 0.5, 0.5, 0.5, 0.5, 0.0, -1.0},
		{-1.0, 0.0, 0.5, 0.0, 0.0, 0.0, 0.0, -1.0},
		{-2.0, -1.0, -1.0, -0.5, -0.5, -1.0, -1.0, -2.0}
	};

	float kingEvalWhite[8][8] = 
	{
		{-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0},
		{-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0},
		{-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0},
		{-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0},
		{-2.0, -3.0, -3.0, -4.0, -4.0, -3.0, -3.0, -2.0},
		{-1.0, -2.0, -2.0, -2.0, -2.0, -2.0, -2.0, -1.0},
		{2.0, 2.0, 0.0, 0.0, 0.0, 0.0, 2.0, 2.0},
		{2.0, 3.0, 1.0, 0.0, 0.0, 1.0, 3.0, 2.0}
	};
	float kingEvalBlack[8][8]{};

	Vector2f _startPosition;
	Vector2f _cellSize;
	Figure* _board[8][8]{};
	Figure* _figure = nullptr;
	King* _whiteKing;
	King* _blackKing;
	vector<Move*> _figureMoves;
	list<Move*> _history;
	vector<Figure*> _figures;
	vector<Figure*> _allFigures;
	CentredText* _moveText;
	CentredText* _stateText;
	bool _dangerousCells[8][8]{};
	bool _isWhite;
	bool _ifCanMove = true;
	RectangleShape _rects[8][8];
	RectangleShape _greySquare;
	RectangleShape _redSquare;
	int _begin = 0;
	int _end = 0;
	int _stateWhite = 0;
	int _stateBlack = 0;
	bool _isWithBot = false;
	string _fileName;
public:
	Board(Vector2f startPosition, Vector2f cellSize, string fileName);
	void NewGame();
	void undo();
	void setMoveText(CentredText* moveText);
	void setStateText(CentredText* stateText);
	void UpdateText();
	void move(Move* move);
	void UpdateBoard();
	void draw()override;
	void UpdateColor()override;
	bool CheckCoord(Vector2i position)override;
	int Edit(Vector2i position)override;
	int getWidth();
	void setWithBot(bool state);
	bool isWithBot();
	bool isWhite();
	int getFindDepth();
	void incFindDepth();
	void Save(fstream &fs);
	void Load(ifstream &fs);
	~Board();
private:
	void ReCalcDangerousCells(bool isWhite);
	void Clear();
	Move* BotMove(int depth);
	float botFindBestMove(int depth, float alpha, float beta, bool isMaximisingPlayer);
	float evaluateBoard();
	float getPieceValue(int x, int y);
	void reverseArray(float arr1[8][8], float arr2[8][8]);
	void clearMoves(vector<Move*>& moves);
};

