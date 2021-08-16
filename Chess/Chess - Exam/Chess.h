#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include"Board.h"
#include"RoundedButton.h"
#include"CentredRoundedButton.h"
#include"ToggleButton.h"
class Chess : public ICommand
{
	Vector2f _startPosition;
	Vector2f _scale;
	Board* _board;
	RoundedButton* _newGame;
	RoundedButton* _undo;
	CentredRoundedButton* _findDepth;
	ToggleButton* _darkMode;
	ToggleButton* _withBot;
	CentredText* _moveText;
	CentredText* _stateText;
	CentredText* _authorName;
	vector<ICommand*> _objects;
	int _lastObject;
public:
	Chess(Vector2f startPosition, Vector2f scale);
	bool CheckCoord(Vector2i position)override;
	int Edit(Vector2i position)override;
	void draw()override;
	~Chess();
private:
	void NewGame();
	void undo();
	void DarkMode(bool state);
	void WithBot(bool state);
	void UpdateFindDepth();
	void IncFindDepth();
};
