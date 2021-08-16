#pragma once
#include<SFML/Graphics.hpp>
#include<vector>
#include<iostream>
#include<list>
#include<fstream>
using namespace sf;
using namespace std;
class ICommand;
class Figure;
class Board;
class Move;
class Queen;
class ChessSystem
{
	/*vector<Move*>* _moves;
	Figure* (*_board)[8];
	Vector2f* _startPosition;
	Vector2f* _cellSize;*/
	static ChessSystem *pt;
	ChessSystem();
public:
	vector<Figure*>* _allFigures;
	bool _darkMode = false;
	bool _isTextureInitialized = false;
	RenderWindow* _renderWindow;
	Texture _textures[10];
	Font _font;
	ChessSystem(const ChessSystem &) = delete;
	static ChessSystem *getInstance();
	void setRenderWindow(RenderWindow& renderWindow);
	void InitializeTextures();
};

class ChessSystemPtr
{
public:
	ChessSystem *_chessSystem;
	ChessSystemPtr();
};

class ICommand : public ChessSystemPtr
{
protected:
	bool _isActive = true;
public:
	ICommand();
	virtual bool CheckCoord(Vector2i position);
	virtual int Edit(Vector2i position);
	virtual void draw() = 0;
	virtual void SetActive(bool state);
	virtual bool isActive();
	virtual void UpdateColor();
	virtual ~ICommand();
};
