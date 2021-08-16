#include "RoundedButton.h"

RoundedButton::RoundedButton(const wchar_t * text, Vector2f position, int size, int margin) : ICommand()
{
	_text.setString(text);
	_text.setCharacterSize(size);
	_text.setFont(_chessSystem->_font);
	UpdateColor();
	_margin = margin;
	_position = position;
	ReCalc();
}

void RoundedButton::setString(const wchar_t * text)
{
	_text.setString(text);
	ReCalc();
}

void RoundedButton::setSize(int size)
{
	_text.setCharacterSize(size);
	ReCalc();
}

void RoundedButton::setColorText(Color color)
{
	_text.setFillColor(color);
}

void RoundedButton::setColorButton(Color color)
{
	_circle1.setFillColor(color);
	_circle2.setFillColor(color);
	_rectangle.setFillColor(color);
}

void RoundedButton::setMargin(int margin)
{
	_margin = margin;
	ReCalc();
}

void RoundedButton::setPosition(Vector2f position)
{
	_position = position;
	ReCalc();
}

void RoundedButton::draw()
{
	if (_isActive)
	{
		_chessSystem->_renderWindow->draw(_circle1);
		_chessSystem->_renderWindow->draw(_circle2);
		_chessSystem->_renderWindow->draw(_rectangle);
		_chessSystem->_renderWindow->draw(_text);
	}
}

void RoundedButton::UpdateColor()
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

void RoundedButton::setFunction(Chess* curClass, void(Chess::* function)())
{
	_curClass = curClass;
	_function = function;
}

bool RoundedButton::CheckCoord(Vector2i position)
{
	if (_isActive && _position.x <= position.x && position.x <= _position2.x && _position.y <= position.y && position.y <= _position2.y)
		return true;
	return false;
}

int RoundedButton::Edit(Vector2i position)
{
	(_curClass->*_function)();
	return 0;
}

int RoundedButton::getHeight()
{
	return _rectangle.getSize().y;
}

void RoundedButton::ReCalc()
{
	Vector2f size = Vector2f(_text.getLocalBounds().width, _text.getLocalBounds().height);
	float margin2 = size.y / 2 + _margin;
	_text.setPosition(_position + Vector2f(margin2, _margin - _text.getCharacterSize() / 5));
	_rectangle.setSize(size + Vector2f(0, _margin * 2));
	_rectangle.setPosition(_position + Vector2f(margin2, 0));
	_circle1.setRadius(margin2);
	_circle2.setRadius(margin2);
	_circle1.setPosition(_position);
	_circle2.setPosition(_position + Vector2f(size.x, 0));
	_position2 = _position + Vector2f(size.x + margin2 * 2, margin2 * 2);
}
