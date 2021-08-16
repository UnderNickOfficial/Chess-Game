#pragma once
#include"ChessSystem.h"
class Chess;
class CentredText : public ICommand
{
	Text _text;
	int _margin;
	Vector2f _position;
public:
	CentredText(const wchar_t* text, Vector2f position, int size = 0, int margin = 5);
	void setString(const wchar_t* text);
	void setSize(int size);
	void setColorText(Color color);
	void setMargin(int margin);
	void setPosition(Vector2f position);
	void draw();
	void UpdateColor()override;
private:
	void ReCalc();
};