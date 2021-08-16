#include "RoundedButton.h"
#include"Chess.h"
using namespace std;

int main()
{
	RenderWindow window(VideoMode(616, 734), "Chess", sf::Style::Close | sf::Style::Titlebar);
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);
	ContextSettings settings;
	settings.antialiasingLevel = 8;
	Image icon;
	icon.loadFromFile("images/icon.png");
	window.setIcon(96, 96, icon.getPixelsPtr());

	ChessSystemPtr chessSystem;
	chessSystem._chessSystem->setRenderWindow(window);
	Vector2f startPosition(20, 20);
	Vector2f scale(1, 1);
	Chess chess(startPosition, scale);

	
	while (window.isOpen())
	{
		Vector2i pos = Mouse::getPosition(window);
		Event events;
		if (chessSystem._chessSystem->_darkMode)
			window.clear(Color(40, 55, 71));
		else
			window.clear(Color(253, 254, 254));
		while (window.pollEvent(events))
		{
			if (events.type == Event::Closed)
				window.close();
			if (events.type == Event::MouseButtonPressed)
			{
				if (events.key.code == Mouse::Left)
				{
					if (chess.CheckCoord(pos))
						chess.Edit(pos);
				}
			}
		}
		chess.draw();
		window.display();
	}
}
