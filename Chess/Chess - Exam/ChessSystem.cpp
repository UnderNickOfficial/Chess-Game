#include "ChessSystem.h"

ICommand::ICommand() :ChessSystemPtr()
{
}

bool ICommand::CheckCoord(Vector2i position)
{
	return false;
}

int ICommand::Edit(Vector2i position)
{
	return 0;
}

void ICommand::SetActive(bool state)
{
	_isActive = state;
}

bool ICommand::isActive()
{
	return _isActive;
}

void ICommand::UpdateColor()
{
}

ICommand::~ICommand()
{
}

ChessSystem *ChessSystem::pt = nullptr;

ChessSystem::ChessSystem()
{
	InitializeTextures();
}

ChessSystem * ChessSystem::getInstance()
{
	if (pt == nullptr)
		pt = new ChessSystem();
	return pt;
}

void ChessSystem::setRenderWindow(RenderWindow & renderWindow)
{
	_renderWindow = &renderWindow;
}

void ChessSystem::InitializeTextures()
{
	if (!_font.loadFromFile("fonts/Hero-Bold.ttf"))
	{
	}
	if (!_textures[0].loadFromFile("images/pawn.png"))
	{
	}
	if (!_textures[1].loadFromFile("images/rook.png"))
	{
	}
	if (!_textures[2].loadFromFile("images/knight.png"))
	{
	}
	if (!_textures[3].loadFromFile("images/bishop.png"))
	{
	}
	if (!_textures[4].loadFromFile("images/queen.png"))
	{
	}
	if (!_textures[5].loadFromFile("images/king.png"))
	{
	}
	for (int i = 0; i < 10; i++)
		_textures[0].setSmooth(true);
}

ChessSystemPtr::ChessSystemPtr()
{
	_chessSystem = ChessSystem::getInstance();
}

