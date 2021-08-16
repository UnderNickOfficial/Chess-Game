#include "CentredRoundedButton.h"


CentredRoundedButton::CentredRoundedButton(const wchar_t * text, Vector2f position, int size, int margin) : ICommand()
{
	_text.setString(text);
	_text.setCharacterSize(size);
	_text.setFont(_chessSystem->_font);
	UpdateColor();
	_margin = margin;
	_position = position;
	ReCalc();
}

void CentredRoundedButton::setString(const wchar_t * text)
{
	_text.setString(text);
	ReCalc();
}

void CentredRoundedButton::setSize(int size)
{
	_text.setCharacterSize(size);
	ReCalc();
}

void CentredRoundedButton::setColorText(Color color)
{
	_text.setFillColor(color);
}

void CentredRoundedButton::setColorButton(Color color)
{
	_circle1.setFillColor(color);
	_circle2.setFillColor(color);
	_rectangle.setFillColor(color);
}

void CentredRoundedButton::setMargin(int margin)
{
	_margin = margin;
	ReCalc();
}

void CentredRoundedButton::setPosition(Vector2f position)
{
	_position = position;
	ReCalc();
}

void CentredRoundedButton::draw()
{
	if (_isActive)
	{
		_chessSystem->_renderWindow->draw(_circle1);
		_chessSystem->_renderWindow->draw(_circle2);
		_chessSystem->_renderWindow->draw(_rectangle);
		_chessSystem->_renderWindow->draw(_text);
	}
}

void CentredRoundedButton::UpdateColor()
{
	if (_chessSystem->_darkMode)
	{
		_text.setFillColor(Color(253, 254, 254));
		_circle1.setFillColor(Color(46, 204, 113));
		_circle2.setFillColor(Color(46, 204, 113));
		_rectangle.setFillColor(Color(46, 204, 113));
	}
	else
	{
		_text.setFillColor(Color(253, 254, 254));
		_circle1.setFillColor(Color(220, 118, 51));
		_circle2.setFillColor(Color(220, 118, 51));
		_rectangle.setFillColor(Color(220, 118, 51));
	}
}

void CentredRoundedButton::setFunction(Chess* curClass, void(Chess::* function)())
{
	_curClass = curClass;
	_function = function;
}

bool CentredRoundedButton::CheckCoord(Vector2i position)
{
	if (_isActive && _position1.x <= position.x && position.x <= _position2.x && _position1.y <= position.y && position.y <= _position2.y)
		return true;
	return false;
}

int CentredRoundedButton::Edit(Vector2i position)
{
	(_curClass->*_function)();
	return 0;
}

int CentredRoundedButton::getHeight()
{
	return _rectangle.getSize().y;
}

void CentredRoundedButton::ReCalc()
{
	Vector2f size = Vector2f(_text.getLocalBounds().width, _text.getLocalBounds().height);
	float margin2 = size.y / 2 + _margin;
	_text.setPosition(_position + Vector2f(-size.x / 2, _margin - _text.getCharacterSize() / 5));
	_rectangle.setSize(size + Vector2f(0, _margin * 2));
	_rectangle.setPosition(_position - Vector2f(size.x/2, 0));
	_circle1.setRadius(margin2);
	_circle2.setRadius(margin2);
	_circle1.setPosition(_position - Vector2f(size.x / 2 + margin2, 0));
	_circle2.setPosition(_position + Vector2f(size.x / 2 - margin2, 0));
	_position1 = _position + Vector2f(-size.x / 2 - margin2, 0);
	_position2 = _position + Vector2f(size.x / 2 + margin2, margin2 * 2);
}
