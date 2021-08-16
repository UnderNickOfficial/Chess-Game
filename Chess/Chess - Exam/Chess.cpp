#include "Chess.h"


Chess::Chess(Vector2f startPosition, Vector2f scale) : ICommand()
{
	int buttonHeight;
	int boardWidth;
	_startPosition = startPosition;
	_scale = scale;

	_newGame = new RoundedButton(L"New Game", _startPosition, 20, 10);
	_objects.push_back(_newGame);
	buttonHeight = _newGame->getHeight();

	_board = new Board(Vector2f(_startPosition.x, _startPosition.y + buttonHeight * 2 + 40), Vector2f(64 * _scale.x + 8, 64 * _scale.y + 8), "resources/save.txt");
	_objects.push_back(_board);
	_newGame->setFunction(this, &Chess::NewGame);
	boardWidth = _board->getWidth();

	_undo = new RoundedButton(L"Undo", Vector2f(_startPosition.x, _startPosition.y + buttonHeight + 20), 20, 10);
	_objects.push_back(_undo);
	_undo->setFunction(this, &Chess::undo);

	_darkMode = new ToggleButton(L"Dark Mode", Vector2f(_startPosition.x + boardWidth, _startPosition.y), 20, 5);
	_objects.push_back(_darkMode);
	_darkMode->setFunction(this, &Chess::DarkMode);

	_withBot = new ToggleButton(L"With Bot", Vector2f(_startPosition.x + boardWidth, _startPosition.y + buttonHeight + 20), 20, 5);
	_objects.push_back(_withBot);
	_withBot->setFunction(this, &Chess::WithBot);
	//_withBot->blockState(true);

	_moveText = new CentredText(L"Black move", Vector2f(_startPosition.x + _board->getWidth()/2, _startPosition.y), 20, 10);
	_objects.push_back(_moveText);

	_stateText = new CentredText(L"", Vector2f(_startPosition.x + _board->getWidth() / 2, _startPosition.y + buttonHeight + 20), 20, 10);
	_objects.push_back(_stateText);

	_authorName = new CentredText(L"Created by Nikita Fursa", Vector2f(_startPosition.x + _board->getWidth() / 2, _startPosition.y + buttonHeight * 2 + 35 + _board->getWidth()), 20, 10);
	_objects.push_back(_authorName);
	_findDepth = new CentredRoundedButton(L"Complexity: 1", Vector2f(_startPosition.x + _board->getWidth() / 2, _startPosition.y), 20, 10);
	_objects.push_back(_findDepth);
	_findDepth->SetActive(false);
	_findDepth->setFunction(this, &Chess::IncFindDepth);

	_board->setMoveText(_moveText);
	_board->setStateText(_stateText);
	ifstream fs;
	fs.open("resources/save.bin", ios::binary);
	if (fs.is_open())
	{
		_board->Load(fs);
		fs >> _chessSystem->_darkMode;
		DarkMode(_chessSystem->_darkMode);
		if (_board->isWithBot())
		{
			_withBot->setState(_board->isWithBot());
			_findDepth->SetActive(true);
		}
		if (_chessSystem->_darkMode)
		{
			_darkMode->setState(true);
		}
		fs.close();
	}
	else
		_board->NewGame();
	UpdateFindDepth();
}

bool Chess::CheckCoord(Vector2i position)
{
	for (int i = 0; i < _objects.size(); i++)
	{
		if (_objects[i]->CheckCoord(position))
		{
			_lastObject = i;
			return true;
		}
	}
	return false;
}

int Chess::Edit(Vector2i position)
{
	return _objects[_lastObject]->Edit(position);
}

void Chess::draw()
{
	for (ICommand* object : _objects)
		object->draw();
}

Chess::~Chess()
{
	fstream fs;
	fs.open("resources/save.bin", ios::out | ios::binary);
	if (fs.is_open())
	{
		_board->Save(fs);
		fs << _chessSystem->_darkMode << "\n";
		fs.close();
	}
	for (ICommand* object : _objects)
		delete object;
}

void Chess::NewGame()
{
	_board->NewGame();
}

void Chess::undo()
{
	_board->undo();
	if (_board->isWithBot() && !_board->isWhite())
		_board->undo();
}

void Chess::DarkMode(bool state)
{
	_chessSystem->_darkMode = state;
	for (ICommand* object : _objects)
		object->UpdateColor();
}

void Chess::WithBot(bool state)
{
	if (state)
		_findDepth->SetActive(true);
	else
		_findDepth->SetActive(false);
	_board->setWithBot(state);
}

void Chess::UpdateFindDepth()
{
	wchar_t tmp[20]{};
	wcscpy_s(tmp, L"Complexity: ");
	wchar_t tmp2[11];
	_itow_s(_board->getFindDepth(), tmp2, 10);
	wcscat_s(tmp, tmp2);
	_findDepth->setString(tmp);
}

void Chess::IncFindDepth()
{
	_board->incFindDepth();
	UpdateFindDepth();
}
