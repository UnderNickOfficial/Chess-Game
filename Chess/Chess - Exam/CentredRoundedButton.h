#pragma once
#include"ChessSystem.h"
class Chess;
class CentredRoundedButton : public ICommand
{
	Text _text;
	CircleShape _circle1;
	CircleShape _circle2;
	RectangleShape _rectangle;
	int _margin;
	Vector2f _position;
	Vector2f _position1;
	Vector2f _position2;
	Chess* _curClass;
	void (Chess::*_function)();
public:
	CentredRoundedButton(const wchar_t* text, Vector2f position, int size = 0, int margin = 5);
	void setString(const wchar_t* text);
	void setSize(int size);
	void setColorText(Color color);
	void setColorButton(Color color);
	void setMargin(int margin);
	void setPosition(Vector2f position);
	void draw();
	void UpdateColor()override;
	void setFunction(Chess* curClass, void (Chess::*_function)());
	bool CheckCoord(Vector2i position)override;
	int Edit(Vector2i position)override;
	int getHeight();
private:
	void ReCalc();
};