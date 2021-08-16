#include "ToggleButton.h"

ToggleButton::ToggleButton(const wchar_t * text, Vector2f position, int size, int margin) : ICommand()
{
	_text.setString(text);
	_text.setCharacterSize(size);
	_text.setFont(_chessSystem->_font);
	UpdateColor();
	_margin = margin;
	_position = position;
	ReCalc();
}

void ToggleButton::setString(const wchar_t * text)
{
	_text.setString(text);
	ReCalc();
}

void ToggleButton::setSize(int size)
{
	_text.setCharacterSize(size);
	ReCalc();
}

void ToggleButton::setColorText(Color color)
{
	_text.setFillColor(color);
}

void ToggleButton::setColorButton(Color color)
{
	_circle1.setFillColor(color);
	_circle2.setFillColor(color);
	_rectangle.setFillColor(color);
}

void ToggleButton::setMargin(int margin)
{
	_margin = margin;
	ReCalc();
}

void ToggleButton::setPosition(Vector2f position)
{
	_position = position;
	ReCalc();
}

void ToggleButton::draw()
{
	if (_isActive)
	{
		_chessSystem->_renderWindow->draw(_circle1);
		_chessSystem->_renderWindow->draw(_circle2);
		_chessSystem->_renderWindow->draw(_rectangle);
		_chessSystem->_renderWindow->draw(_text);
		_chessSystem->_renderWindow->draw(_toggle);
	}
}

void ToggleButton::UpdateColor()
{
	if (_chessSystem->_darkMode)
	{
		_text.setFillColor(Color(208, 211, 212));
		_circle1.setFillColor(Color(229, 231, 233));
		_circle2.setFillColor(Color(229, 231, 233));
		_rectangle.setFillColor(Color(229, 231, 233));
		_toggle.setFillColor(Color(253, 254, 254));
		_colorButton = Color(208, 211, 212);
		_colorToggled = Color(46, 204, 113);
	}
	else
	{
		_text.setFillColor(Color(0, 0, 0));
		_circle1.setFillColor(Color(229, 231, 233));
		_circle2.setFillColor(Color(229, 231, 233));
		_rectangle.setFillColor(Color(229, 231, 233));
		_toggle.setFillColor(Color(253, 254, 254));
		_colorButton = Color(208, 211, 212);
		_colorToggled = Color(46, 204, 113);
	}
	UpdateFiguresColor();
}

void ToggleButton::setState(bool state)
{
	_state = state;
	ReCalc();
}

void ToggleButton::blockState(bool state)
{
	_blocked = state;
}

void ToggleButton::setFunction(Chess* curClass, void(Chess::* function)(bool))
{
	_curClass = curClass;
	_function = function;
}

bool ToggleButton::CheckCoord(Vector2i position)
{
	if (_isActive && _position2.x <= position.x && position.x <= _position.x && _position.y <= position.y && position.y <= _position2.y)
	{
		return true;
	}

	return false;
}

int ToggleButton::Edit(Vector2i position)
{
	if (!_blocked)
	{
		_state = !_state;
		if (_function)
			(_curClass->*_function)(_state);
		ChangeState();
	}

	return 0;
}

int ToggleButton::getHeight()
{
	return _rectangle.getSize().y;
}

void ToggleButton::ReCalc()
{
	float margin2 = _text.getLocalBounds().height/2 + _margin + _text.getCharacterSize() / 5;
	_circle1.setRadius(margin2);
	_circle2.setRadius(margin2);
	_rectangle.setSize(Vector2f(margin2 * 2, margin2 * 2));
	_text.setPosition(_position.x - _text.getLocalBounds().width - margin2 * 4 - _margin, _position.y + _text.getCharacterSize() / 5);
	_circle1.setPosition(Vector2f(_position.x - margin2*4, _position.y));
	_rectangle.setPosition(Vector2f(_position.x - margin2*3, _position.y));
	_circle2.setPosition(Vector2f(_position.x - margin2*2, _position.y));
	_toggle.setRadius(_text.getLocalBounds().height/2 + _text.getCharacterSize() / 5);
	ChangeState();
}

void ToggleButton::ChangeState()
{
	float margin2 = _text.getLocalBounds().height / 2 + _margin + _text.getCharacterSize() / 5;
	_position2 = Vector2f(_position.x - _text.getLocalBounds().width - margin2 * 4 - _margin, _position.y + margin2 * 2);
	if (_state)
		_toggle.setPosition(Vector2f(_position.x - margin2 * 2 + _margin, _position.y + _margin));
	else
		_toggle.setPosition(_position.x - margin2 * 4 + _margin, _position.y + _margin);
	UpdateFiguresColor();
}

void ToggleButton::UpdateFiguresColor()
{
	if (_state)
	{
		_circle1.setFillColor(_colorToggled);
		_rectangle.setFillColor(_colorToggled);
		_circle2.setFillColor(_colorToggled);
	}
	else
	{
		_circle1.setFillColor(_colorButton);
		_rectangle.setFillColor(_colorButton);
		_circle2.setFillColor(_colorButton);
	}
}
