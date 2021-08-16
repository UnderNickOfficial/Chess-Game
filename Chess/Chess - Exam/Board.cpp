#include "Board.h"


Board::Board(Vector2f startPosition, Vector2f cellSize, string fileName) : ICommand()
{
	_chessSystem->_allFigures = &_allFigures;
	_fileName = fileName;
	_startPosition = startPosition;
	_cellSize = cellSize;
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			_rects[i][j].setPosition(_startPosition.x + i * _cellSize.x, _startPosition.y + j * _cellSize.y);
			_rects[i][j].setSize(_cellSize);
		}
	_greySquare.setSize(Vector2f(_cellSize.x - 4, _cellSize.y - 4));
	_redSquare.setSize(Vector2f(_cellSize.x - 4, _cellSize.y - 4));
	reverseArray(kingEvalBlack, kingEvalWhite);
	reverseArray(rookEvalBlack, rookEvalWhite);
	reverseArray(bishopEvalBlack, bishopEvalWhite);
	reverseArray(pawnEvalBlack, pawnEvalWhite);
	UpdateColor();
}

void Board::NewGame()
{
	Clear();
	_figure = nullptr;
	_isWhite = true;
	//Black Figures
	_board[0][1] = new Pawn(Vector2i(0,1), false, _startPosition, _cellSize, _figureMoves, _board, _figures, _dangerousCells);
	_board[1][1] = new Pawn(Vector2i(1,1), false, _startPosition, _cellSize, _figureMoves, _board, _figures, _dangerousCells);
	_board[2][1] = new Pawn(Vector2i(2,1), false, _startPosition, _cellSize, _figureMoves, _board, _figures, _dangerousCells);
	_board[3][1] = new Pawn(Vector2i(3,1), false, _startPosition, _cellSize, _figureMoves, _board, _figures, _dangerousCells);
	_board[4][1] = new Pawn(Vector2i(4,1), false, _startPosition, _cellSize, _figureMoves, _board, _figures, _dangerousCells);
	_board[5][1] = new Pawn(Vector2i(5,1), false, _startPosition, _cellSize, _figureMoves, _board, _figures, _dangerousCells);
	_board[6][1] = new Pawn(Vector2i(6,1), false, _startPosition, _cellSize, _figureMoves, _board, _figures, _dangerousCells);
	_board[7][1] = new Pawn(Vector2i(7,1), false, _startPosition, _cellSize, _figureMoves, _board, _figures, _dangerousCells);

	_board[0][0] = new Rook(Vector2i(0, 0), false, _startPosition, _cellSize, _figureMoves, _board, _figures, _dangerousCells);
	_board[7][0] = new Rook(Vector2i(7, 0), false, _startPosition, _cellSize, _figureMoves, _board, _figures, _dangerousCells);

	_board[1][0] = new Knight(Vector2i(1, 0), false, _startPosition, _cellSize, _figureMoves, _board, _figures, _dangerousCells);
	_board[6][0] = new Knight(Vector2i(6, 0), false, _startPosition, _cellSize, _figureMoves, _board, _figures, _dangerousCells);

	_board[2][0] = new Bishop(Vector2i(2, 0), false, _startPosition, _cellSize, _figureMoves, _board, _figures, _dangerousCells);
	_board[5][0] = new Bishop(Vector2i(5, 0), false, _startPosition, _cellSize, _figureMoves, _board, _figures, _dangerousCells);

	_board[3][0] = new Queen(Vector2i(3, 0), false, _startPosition, _cellSize, _figureMoves, _board, _figures, _dangerousCells);
	_blackKing = new King(Vector2i(4, 0), false, _startPosition, _cellSize, _figureMoves, _board, _figures, _dangerousCells, _stateBlack);
	_board[4][0] = _blackKing;

	//White Figures
	_board[0][6] = new Pawn(Vector2i(0, 6), true, _startPosition, _cellSize, _figureMoves, _board, _figures, _dangerousCells);
	_board[1][6] = new Pawn(Vector2i(1, 6), true, _startPosition, _cellSize, _figureMoves, _board, _figures, _dangerousCells);
	_board[2][6] = new Pawn(Vector2i(2, 6), true, _startPosition, _cellSize, _figureMoves, _board, _figures, _dangerousCells);
	_board[3][6] = new Pawn(Vector2i(3, 6), true, _startPosition, _cellSize, _figureMoves, _board, _figures, _dangerousCells);
	_board[4][6] = new Pawn(Vector2i(4, 6), true, _startPosition, _cellSize, _figureMoves, _board, _figures, _dangerousCells);
	_board[5][6] = new Pawn(Vector2i(5, 6), true, _startPosition, _cellSize, _figureMoves, _board, _figures, _dangerousCells);
	_board[6][6] = new Pawn(Vector2i(6, 6), true, _startPosition, _cellSize, _figureMoves, _board, _figures, _dangerousCells);
	_board[7][6] = new Pawn(Vector2i(7, 6), true, _startPosition, _cellSize, _figureMoves, _board, _figures, _dangerousCells);

	_board[0][7] = new Rook(Vector2i(0, 7), true, _startPosition, _cellSize, _figureMoves, _board, _figures, _dangerousCells);
	_board[7][7] = new Rook(Vector2i(7, 7), true, _startPosition, _cellSize, _figureMoves, _board, _figures, _dangerousCells);

	_board[1][7] = new Knight(Vector2i(1, 7), true, _startPosition, _cellSize, _figureMoves, _board, _figures, _dangerousCells);
	_board[6][7] = new Knight(Vector2i(6, 7), true, _startPosition, _cellSize, _figureMoves, _board, _figures, _dangerousCells);

	_board[2][7] = new Bishop(Vector2i(2, 7), true, _startPosition, _cellSize, _figureMoves, _board, _figures, _dangerousCells);
	_board[5][7] = new Bishop(Vector2i(5, 7), true, _startPosition, _cellSize, _figureMoves, _board, _figures, _dangerousCells);

	_board[3][7] = new Queen(Vector2i(3, 7), true, _startPosition, _cellSize, _figureMoves, _board, _figures, _dangerousCells);
	_whiteKing = new King(Vector2i(4, 7), true, _startPosition, _cellSize, _figureMoves, _board, _figures, _dangerousCells, _stateWhite);
	_board[4][7] = _whiteKing;
	ReCalcDangerousCells(_isWhite);
	for (Figure* figure : _figures)
		if (figure->isWhite() == _isWhite)
			figure->addMoves(&_figureMoves);

	_begin = 0;
	_end = 0;
	_stateWhite = 0;
	_stateBlack = 0;
	UpdateText();
}

void Board::undo()
{
	if (_history.size() > 0)
	{
		_history.back()->undo(_board, _startPosition, _cellSize);
		_history.pop_back();
		_isWhite = !_isWhite;
		for (Figure* figure : _figures)
			if (figure->getMovesCount())
				figure->decMovesCount();
		_figure = nullptr;
		_begin = 0;
		_end = 0;
		UpdateBoard();
	}

}

void Board::setMoveText(CentredText * moveText)
{
	_moveText = moveText;
}

void Board::setStateText(CentredText * stateText)
{
	_stateText = stateText;
}

void Board::UpdateText()
{
	_ifCanMove = true;
	if (_isWhite)
		_moveText->setString(L"White move");
	else
		_moveText->setString(L"Black move");
	if (_stateBlack == 3 || (_figureMoves.size() == 0 && _isWhite == false))
	{
		_stateText->setString(L"White won!");
		_ifCanMove = false;
	}
	else if (_stateWhite == 3 || (_figureMoves.size() == 0 && _isWhite == true))
	{
		_stateText->setString(L"Black won!");
		_ifCanMove = false;
	}
	else if (_isWhite)
	{
		if (_stateBlack == 2)
		{
			_stateText->setString(L"White won!");
			_ifCanMove = false;
		}
		else if (_stateBlack == 1 || _stateWhite == 1)
		{
			if (_stateBlack == 1 && (_stateWhite == 1 || _stateWhite == 2))
				_stateText->setString(L"Shah to black and white");
			else if (_stateWhite == 1 || _stateWhite == 2)
				_stateText->setString(L"Shah to white");
			else if (_stateBlack == 1)
				_stateText->setString(L"Shah to black");
			_ifCanMove = true;
		}
		else
		{
			_stateText->setString(L"");
			_ifCanMove = true;
		}
	}
	else
	{
		if (_stateWhite == 2)
		{
			_stateText->setString(L"Black won!");
			_ifCanMove = false;
		}
		else if (_stateBlack == 1 || _stateWhite == 1)
		{
			if ((_stateBlack == 1 || _stateBlack == 2) && _stateWhite == 1)
				_stateText->setString(L"Shah to black and white");
			else if (_stateWhite == 1)
				_stateText->setString(L"Shah to white");
			else if (_stateBlack == 1 || _stateBlack == 2)
				_stateText->setString(L"Shah to black");
			_ifCanMove = true;
		}
		else
		{
			_stateText->setString(L"");
			_ifCanMove = true;
		}
	}

}

void Board::move(Move * move)
{
	if (!_ifCanMove)
		return;
	for (Figure* figure : _figures)
		if (figure->getMovesCount())
			figure->incMovesCount();

	move->move(_board, _startPosition, _cellSize);
	_history.push_back(move);
	_isWhite = !_isWhite;
	for (Move* moves : _figureMoves)
		if (moves != move)
			delete moves;
	_figureMoves.clear();
	UpdateBoard();
}

void Board::UpdateBoard()
{
	bool whiteKing = false;
	bool blackKing = false;
	clearMoves(_figureMoves);
	ReCalcDangerousCells(_isWhite);
	for (Figure* figure : _figures)
	{
		if (figure->isWhite() == _isWhite)
			figure->addMoves(&_figureMoves);
		if (figure->getFigure() == 'K')
		{
			if (figure->isWhite())
				whiteKing = true;
			else
				blackKing = true;
		}
	}
	ReCalcDangerousCells(!_isWhite);
	if (!_isWhite)
		_whiteKing->UpdateState();
	else
		_blackKing->UpdateState();
	if (!whiteKing)
	{
		_stateWhite = 3;
		clearMoves(_figureMoves);
	}
	else if (!blackKing)
	{
		_stateBlack = 3;
		clearMoves(_figureMoves);
	}
	UpdateText();
}

void Board::draw()
{
	if (!_isActive)
		return;
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			_chessSystem->_renderWindow->draw(_rects[i][j]);
		}
	for (int i = _begin; i < _end; i++)
	{
		_greySquare.setPosition(_startPosition.x + _figureMoves[i]->getPosition().x * _cellSize.x + 2, _startPosition.y + _figureMoves[i]->getPosition().y * _cellSize.y + 2);
		_chessSystem->_renderWindow->draw(_greySquare);
	}
	if (_figure)
	{
		_redSquare.setPosition(_startPosition.x + _figure->getPosX() * _cellSize.x + 2, _startPosition.y + _figure->getPosY() * _cellSize.y + 2);
		_chessSystem->_renderWindow->draw(_redSquare);
	}
	for (Figure* figure : _figures)
			figure->draw();
}

void Board::UpdateColor()
{
	if (_chessSystem->_darkMode)
	{
		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 8; j++)
			{
				if ((i + j) % 2 == 0)
					_rects[i][j].setFillColor(Color(174, 182, 191));
				else
					_rects[i][j].setFillColor(Color(93, 109, 126));
			}
		_greySquare.setFillColor(Color(113, 125, 126));
		_redSquare.setFillColor(Color(231, 76, 60));
	}
	else
	{
		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 8; j++)
			{
				if ((i + j) % 2 == 0)
					_rects[i][j].setFillColor(Color(240, 178, 122));
				else
					_rects[i][j].setFillColor(Color(202, 111, 30));
			}
		_greySquare.setFillColor(Color(112, 123, 124));
		_redSquare.setFillColor(Color(231, 76, 60));
	}
	for (Figure* figure : _figures)
		figure->UpdateColor();
}

bool Board::CheckCoord(Vector2i position)
{
	Vector2i boardPosition((position.x - _startPosition.x) / _cellSize.x, (position.y - _startPosition.y) / _cellSize.y);
	if (boardPosition.x < 0 || boardPosition.x > 8 || boardPosition.y < 0 || boardPosition.y > 8 || position.x - _startPosition.x < 0 || position.y - _startPosition.y < 0 || !_isActive)
		return false;
	return true;
}

int Board::Edit(Vector2i position)
{
	Vector2i boardPosition((position.x - _startPosition.x) / _cellSize.x, (position.y - _startPosition.y) / _cellSize.y);
	bool choosed = true;
	if (boardPosition.x < 0 || boardPosition.x > 8 || boardPosition.y < 0 || boardPosition.y > 8 || position.x - _startPosition.x < 0 || position.y - _startPosition.y < 0 || !_isActive)
		return 1;
	if (!_ifCanMove)
		return 0;
	if (_figure)
	{
		for (int i = _begin; i<_end; i++)
		{
			if (_figureMoves[i]->getPosition() == boardPosition)
			{
				move(_figureMoves[i]);
				choosed = false;
				if (_isWithBot && _ifCanMove)
				{
					move(BotMove(_findDepth));
				}

				break;
			}
		}
		if (_figure->getPosition() == boardPosition)
			choosed = false;
		_figure = nullptr;
		_begin = 0;
		_end = 0;
	}

	if (choosed && _board[boardPosition.x][boardPosition.y] && _board[boardPosition.x][boardPosition.y]->isWhite() == _isWhite)
	{
		_figure = _board[boardPosition.x][boardPosition.y];
		_begin = _figure->getBegin();
		_end = _figure->getEnd();
	}
	return 0;
}

int Board::getWidth()
{
	return _cellSize.x * 8;
}

void Board::setWithBot(bool state)
{
	if (!_isWithBot && state && !_isWhite)
	{
		move(BotMove(_findDepth));
		_begin = 0;
		_end = 0;
		_figure = nullptr;
	}
	_isWithBot = state;

}

bool Board::isWithBot()
{
	return _isWithBot;
}

bool Board::isWhite()
{
	return _isWhite;
}

int Board::getFindDepth()
{
	return _findDepth;
}

void Board::incFindDepth()
{
	if (_findDepth < _maxFindDepth)
		_findDepth++;
	else
		_findDepth = 1;
}

void Board::Save(fstream &fs)
{
	fs << _allFigures.size() << "\n";
	for (int i = 0; i < _allFigures.size(); i++)
	{
		fs << _allFigures[i]->getFigure() << " " << _allFigures[i]->getPosX() << " " << _allFigures[i]->getPosY() << " " << _allFigures[i]->isWhite() << " " << _allFigures[i]->isOnBoard() << " " << _allFigures[i]->getMovesCount() << "\n";
	}
	fs << _history.size() << "\n";
	for (Move* move : _history)
	{
		if (typeid(*move) == typeid(SimpleMove))
		{
			SimpleMove* tmp = dynamic_cast<SimpleMove*>(move);
			fs << 1 << "\n";
			fs << tmp->getFigure()->getVectorPos() << " " << tmp->getOldPosX() << " " << tmp->getOldPosY() << " " << tmp->getNewPosX() << " " << tmp->getNewPosY() << "\n";
		}
		else if (typeid(*move) == typeid(DeleteFigure))
		{
			DeleteFigure* tmp = dynamic_cast<DeleteFigure*>(move);
			fs << 2 << "\n";
			fs << tmp->getFigure()->getVectorPos() << " " << tmp->getOldPosX() << " " << tmp->getOldPosY() << " " << tmp->getNewPosX() << " " << tmp->getNewPosY() << " " << tmp->getDeletedFigure()->getVectorPos() << "\n";
		}
		else if (typeid(*move) == typeid(NewFigure))
		{
			NewFigure* tmp = dynamic_cast<NewFigure*>(move);
			fs << 3 << "\n";
			fs << tmp->getFigure()->getVectorPos() << " " << tmp->getOldPosX() << " " << tmp->getOldPosY() << " " << tmp->getNewPosX() << " " << tmp->getNewPosY() << " " << tmp->getNewFigure()->getVectorPos() << "\n";
		}
		else if (typeid(*move) == typeid(NewDeleteFigure))
		{
			NewDeleteFigure* tmp = dynamic_cast<NewDeleteFigure*>(move);
			fs << 4 << "\n";
			fs << tmp->getFigure()->getVectorPos() << " " << tmp->getOldPosX() << " " << tmp->getOldPosY() << " " << tmp->getNewPosX() << " " << tmp->getNewPosY() << " " << tmp->getNewFigure()->getVectorPos() << " " << tmp->getDeletedFigure()->getVectorPos() << "\n";
		}
		else if (typeid(*move) == typeid(Castling))
		{
			Castling* tmp = dynamic_cast<Castling*>(move);
			fs << 5 << "\n";
			fs << tmp->getFigure()->getVectorPos() << " " << tmp->getOldPosX() << " " << tmp->getOldPosY() << " " << tmp->getNewPosX() << " " << tmp->getNewPosY() << " " << tmp->getSecondFigure()->getVectorPos() << " " << tmp->getSecondOldPosX() << " " << tmp->getSecondOldPosY() << " " << tmp->getSecondNewPosX() << " " << tmp->getSecondNewPosY() << "\n";
		}
	}
	fs << _isWithBot << " " << _findDepth << "\n";
}

void Board::Load(ifstream &fs)
{
	_figure = nullptr;
	_isWhite = true;
	_begin = 0;
	_end = 0;
	_stateWhite = 0;
	_stateBlack = 0;
	int size;
	fs >> size;
	for (int i = 0; i < size; i++)
	{
		char figureC;
		Vector2i pos;
		bool isWhite;
		bool isOnBoard;
		Figure* figure;
		unsigned long long movesCount;
		fs >> figureC >> pos.x >> pos.y >> isWhite >> isOnBoard >> movesCount;
		switch (figureC)
		{
		case 'P':
			figure = new Pawn(pos, isWhite, _startPosition, _cellSize, _figureMoves, _board, _figures, _dangerousCells);
			break;
		case 'R':
			figure = new Rook(pos, isWhite, _startPosition, _cellSize, _figureMoves, _board, _figures, _dangerousCells);
			break;
		case 'N':
			figure = new Knight(pos, isWhite, _startPosition, _cellSize, _figureMoves, _board, _figures, _dangerousCells);
			break;
		case 'B':
			figure = new Bishop(pos, isWhite, _startPosition, _cellSize, _figureMoves, _board, _figures, _dangerousCells);
			break;
		case 'Q':
			figure = new Queen(pos, isWhite, _startPosition, _cellSize, _figureMoves, _board, _figures, _dangerousCells);
			break;
		case 'K':
			if (isWhite)
			{
				_whiteKing = new King(pos, isWhite, _startPosition, _cellSize, _figureMoves, _board, _figures, _dangerousCells, _stateWhite);
				figure = _whiteKing;
			}
			else
			{
				_blackKing = new King(pos, isWhite, _startPosition, _cellSize, _figureMoves, _board, _figures, _dangerousCells, _stateBlack);
				figure = _blackKing;
			}				
			break;
		}
		if (!isOnBoard)
			_allFigures.back()->Erase();
		else
		{
			_board[pos.x][pos.y] = _allFigures.back();
		}
		_allFigures.back()->setMovesCount(movesCount);
	}
	
	int vectorPos, secondVectorPos, thirdVectorPos;
	Vector2i pos, secondPos, oldPos, secondOldPos;
	fs >> size;
	for (int i = 0; i<size; i++)
	{
		int moveType;
		fs >> moveType;
		switch (moveType)
		{
		case 1:
			fs >> vectorPos >> oldPos.x >> oldPos.y >> pos.x >> pos.y ;
			_history.push_back(new SimpleMove(_allFigures[vectorPos], pos, oldPos));
			break;
		case 2:

			fs >> vectorPos >> oldPos.x >> oldPos.y >> pos.x >> pos.y >> secondVectorPos;
			_history.push_back(new DeleteFigure(_allFigures[vectorPos], pos, _allFigures[secondVectorPos], oldPos));
			break;
		case 3:
			fs >> vectorPos >> oldPos.x >> oldPos.y >> pos.x >> pos.y >> secondVectorPos;
			_history.push_back(new NewFigure(_allFigures[vectorPos], pos, _allFigures[secondVectorPos], oldPos));
			break;
		case 4:
			fs >> vectorPos >> oldPos.x >> oldPos.y >> pos.x >> pos.y >> secondVectorPos >> thirdVectorPos;
			_history.push_back(new NewDeleteFigure(_allFigures[vectorPos], pos, _allFigures[secondVectorPos], _allFigures[thirdVectorPos], oldPos));
			break;
		case 5:
			fs >> vectorPos >> oldPos.x >> oldPos.y >> pos.x >> pos.y >> secondVectorPos >> secondOldPos.x >> secondOldPos.y >> secondPos.x >> secondPos.y;
			_history.push_back(new Castling(_allFigures[vectorPos], pos, _allFigures[secondVectorPos], secondPos, oldPos, secondOldPos));
			break;
		}
	}
	if (size % 2 == 0)
		_isWhite = true;
	else
		_isWhite = false;
	fs >> _isWithBot >> _findDepth;
	UpdateBoard();
}

Board::~Board()
{
	Clear();
}

void Board::ReCalcDangerousCells(bool isWhite)
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			_dangerousCells[i][j] = true;
	for (Figure* figure : _figures)
		if (figure->isWhite() != isWhite)
			figure->checkCells();
}

void Board::Clear()
{
	for (int i = 0; i < _figureMoves.size(); i++)
		if (_figureMoves[i])
		{
			delete _figureMoves[i];
		}
	_figureMoves.clear();

	for (Move* move : _history)
	{
		delete move;
	}
	_history.clear();
	
	for (Figure* figure : _allFigures)
		if (figure)
			delete figure;
	_figures.clear();
	_allFigures.clear();
	
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			_board[i][j] = nullptr;
}

Move* Board::BotMove(int depth) 
{	
	float bestMove = -9999;
	Move* bestMoveFound = nullptr;

	for (int i = 0; i < _figureMoves.size(); i++) 
	{
		_figureMoves[i]->move(_board, _startPosition, _cellSize);
		float value = botFindBestMove(depth - 1,  -10000, 10000, true);
		_figureMoves[i]->undo(_board, _startPosition, _cellSize);
		if (value >= bestMove) 
		{
			bestMove = value;
			bestMoveFound = _figureMoves[i];
		}
	}
	return bestMoveFound;
};

float Board::botFindBestMove(int depth, float alpha, float beta, bool isWhite) 
{
	if (depth == 0) 
	{
		return -evaluateBoard();
	}

	vector<Move*> newGameMoves;
	ReCalcDangerousCells(isWhite);
	for (Figure* figure : _figures)
		if (figure->isWhite() == isWhite)
			figure->addMoves(&newGameMoves);
	if (!isWhite) //alphaBetaMin
	{
		float bestMove = -9999;
		for (int i = 0; i < newGameMoves.size(); i++) 
		{
			newGameMoves[i]->move(_board, _startPosition, _cellSize);
			bestMove = max(bestMove, botFindBestMove(depth - 1, alpha, beta, !isWhite));
			newGameMoves[i]->undo(_board, _startPosition, _cellSize);
			alpha = max(alpha, bestMove);
			if (beta <= alpha) 
			{
				clearMoves(newGameMoves);
				return bestMove;
			}
		}
		clearMoves(newGameMoves);
		return bestMove;
	}
	else //alphaBetaMax
	{
		float bestMove = 9999;
		for (int i = 0; i < newGameMoves.size(); i++) 
		{
			newGameMoves[i]->move(_board, _startPosition, _cellSize);
			bestMove = min(bestMove, botFindBestMove(depth - 1, alpha, beta, !isWhite));
			newGameMoves[i]->undo(_board, _startPosition, _cellSize);
			beta = min(beta, bestMove);
			if (beta <= alpha) 
			{
				clearMoves(newGameMoves);
				return bestMove;
			}
		}
		clearMoves(newGameMoves);
		return bestMove;
	}
}

void Board::reverseArray(float arr1[8][8], float arr2[8][8])
{
	for (int i = 0; i<8; i++) 
	{
		for (int j = 0; j < 8; j++)
		{
			arr1[i][j] = arr2[7 - i][7 - j];
		}
	}
}

void Board::clearMoves(vector<Move*>& moves)
{
	for (Move* move : moves)
		delete move;
	moves.clear();
}

float Board::evaluateBoard() 
{
	int value = 0;
	for (int i = 0; i < 8; i++) 
	{
		for (int j = 0; j < 8; j++) 
		{
			value += getPieceValue(i, j);
		}
	}
	return value;
};

float Board::getPieceValue(int x, int y) 
{
	if (_board[x][y] == nullptr) 
	{
		return 0;
	}
	float value = 0;
	switch (_board[x][y]->getFigure())
	{
	case 'P':
		value = 10 + ((_board[x][y]->isWhite()) ? pawnEvalWhite[y][x] : pawnEvalBlack[y][x]);
		break;
	case 'R':
		value = 50 + ((_board[x][y]->isWhite()) ? rookEvalWhite[y][x] : rookEvalBlack[y][x]);
		break;
	case 'N':
		value = 30 + knightEval[y][x];
		break;
	case 'B':
		value = 30 + ((_board[x][y]->isWhite()) ? bishopEvalWhite[y][x] : bishopEvalBlack[y][x]);
		break;
	case 'Q':
		value = 90 + evalQueen[y][x];
		break;
	case 'K':
		value = 900 + ((_board[x][y]->isWhite()) ? kingEvalWhite[y][x] : kingEvalBlack[y][x]);
		break;
	}
	return (_board[x][y]->isWhite())? value : -value;
};