#pragma once
#include"Global.h"
#include "Textures.h"
class Menu
{
private:

	sf::Sprite MenuPlay , MenuOption , MenuQuit;
	sf::Sprite menuBackgroundSprite;
	sf::Sprite BackgroundSprite;
	sf::Sprite pauseBackgroundSprite;
	sf::RenderWindow* window;
	int buttonWidth;
	int buttonHeight;
	sf::RectangleShape boundary;

public:
	Menu(sf::RenderWindow &);
	virtual ~Menu();
	void getBounds(sf::Sprite&);
	void CreatePause(sf::Vector2f );
	void CreateMenu(sf::Vector2f);
	void MenuPositionButtons();
	void PausePositionButtons();
	GAMESTATE getGameState();
	void MenuUpdate(float , sf::Vector2f);
	void PauseUpdate(float, sf::Vector2f, sf::Vector2f);
	void DrawMenu(sf::RenderTarget&);
	void DrawPause(sf::RenderTarget&);
};

