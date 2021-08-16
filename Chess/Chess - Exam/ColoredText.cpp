#include "ColoredText.h"

CentredText::CentredText(const wchar_t * text, Vector2f position, int size, int margin) : ICommand()
{
	_text.setString(text);
	_text.setCharacterSize(size);
	_text.setFont(_chessSystem->_font);
	UpdateColor();
	_margin = margin;
	_position = position;
	ReCalc();
}

void CentredText::setString(const wchar_t * text)
{
	_text.setString(text);
	ReCalc();
}

void CentredText::setSize(int size)
{
	_text.setCharacterSize(size);
	ReCalc();
}

void CentredText::setColorText(Color color)
{
	_text.setFillColor(color);
}

void CentredText::setMargin(int margin)
{
	_margin = margin;
	ReCalc();
}

void CentredText::setPosition(Vector2f position)
{
	_position = position;
	ReCalc();
}

void CentredText::draw()
{
	if (_isActive)
	{
		_chessSystem->_renderWindow->draw(_text);
	}
}

void CentredText::UpdateColor()
{
	if (_chessSystem->_darkMode)
	{
		_text.setFillColor(Color(208, 211, 212));
	}
	else
	{
		_text.setFillColor(Color(0, 0, 0));
	}
}

void CentredText::ReCalc()
{
	Vector2f size = Vector2f(_text.getLocalBounds().width, _text.getLocalBounds().height);
	_text.setPosition(Vector2f(_position.x - size.x / 2, _position.y + _margin - _text.getCharacterSize() / 5));
}
