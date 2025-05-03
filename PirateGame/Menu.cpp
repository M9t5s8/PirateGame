#include "Headers/Menu.h"

Menu::Menu(sf::RenderWindow &window)
	:
	buttonWidth(140),
	buttonHeight(56)
{
	menuBackgroundSprite.setTexture(Textures::menuBackgroundTexture);
	BackgroundSprite.setTexture(Textures::backgroundTexture);
	pauseBackgroundSprite.setTexture(Textures::pauseBackgroundTexture);


	this->getBounds(menuBackgroundSprite);
	this->getBounds(BackgroundSprite);
	this->getBounds(pauseBackgroundSprite);

	menuBackgroundSprite.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	BackgroundSprite.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	

	boundary.setSize(sf::Vector2f(buttonWidth, buttonHeight * 4));
	boundary.setFillColor(sf::Color::Transparent);
	boundary.setOutlineColor(sf::Color::Black);
	boundary.setOutlineThickness(-2);
	sf::FloatRect boundartbounds = boundary.getLocalBounds();
	boundary.setOrigin(boundartbounds.width / 2.f, boundartbounds.height / 2.f);
	boundary.setPosition(SCREEN_WIDTH / 2 , SCREEN_HEIGHT / 2 + buttonHeight / 1.5);
		

	MenuPlay.setTexture(Textures::Menubutton);
	MenuOption.setTexture(Textures::Menubutton);
	MenuQuit.setTexture(Textures::Menubutton);

}

Menu::~Menu()
{

}
void Menu::getBounds(sf::Sprite& sprite)
{
	sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}
void Menu::CreateMenu(sf::Vector2f mousePos)
{  
	sf::FloatRect MenuPlayBounds = MenuPlay.getGlobalBounds();
	if (MenuPlayBounds.contains(mousePos)) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			MenuPlay.setTextureRect(sf::IntRect(2 * buttonWidth, 0, buttonWidth, buttonHeight));
			gamestate = GAMESTATE::PLAYING;
		}
		else {
			MenuPlay.setTextureRect(sf::IntRect(buttonWidth, 0, buttonWidth, buttonHeight));
		}
	}
	else {
		MenuPlay.setTextureRect(sf::IntRect(0, 0, buttonWidth, buttonHeight));
	}


	sf::FloatRect MenuOptionBounds = MenuOption.getGlobalBounds();
	if (MenuOptionBounds.contains(mousePos)) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			MenuOption.setTextureRect(sf::IntRect(2 * buttonWidth, buttonHeight, buttonWidth, buttonHeight));
			gamestate = GAMESTATE::OPTION;
		}
		else {
			MenuOption.setTextureRect(sf::IntRect(buttonWidth, buttonHeight, buttonWidth, buttonHeight));
		}
	}
	else {
		MenuOption.setTextureRect(sf::IntRect(0, buttonHeight, buttonWidth, buttonHeight));
	}



	sf::FloatRect MenuQuitBounds = MenuQuit.getGlobalBounds();
	if (MenuQuitBounds.contains(mousePos)) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			MenuQuit.setTextureRect(sf::IntRect(2 * buttonWidth, 2 * buttonHeight, buttonWidth, buttonHeight));
			gamestate = GAMESTATE::QUIT;
		}
		else {
			MenuQuit.setTextureRect(sf::IntRect(buttonWidth, 2 * buttonHeight, buttonWidth, buttonHeight));
		}
	}
	else {
		MenuQuit.setTextureRect(sf::IntRect(0, 2* buttonHeight, buttonWidth, buttonHeight));
	}

}

void Menu::CreatePause(sf::Vector2f mousePos)
{

}
void Menu::MenuPositionButtons()
{
	sf::Vector2f boundaryPos = boundary.getPosition();
	float boundaryHeight = boundary.getSize().y;
	float topPos = boundaryPos.y - boundaryHeight/2 ;
	float middlePos = boundaryPos.y - buttonHeight/2 ;
	float bottomPos = boundaryPos.y + boundaryHeight / 2 - buttonHeight;
	MenuPlay.setPosition(boundaryPos.x - buttonWidth / 2, topPos);
	MenuOption.setPosition(boundaryPos.x - buttonWidth / 2, middlePos);
	MenuQuit.setPosition(boundaryPos.x - buttonWidth / 2, bottomPos);
}

void Menu::PausePositionButtons()
{

}

GAMESTATE Menu::getGameState()
{
	return gamestate;
}




void Menu::MenuUpdate(float deltatime,sf::Vector2f mousePos)
{
	this->CreateMenu(mousePos);
	this->MenuPositionButtons();
}
void Menu::PauseUpdate(float deltatime, sf::Vector2f viewPos, sf::Vector2f mousePos)
{
	pauseBackgroundSprite.setPosition(viewPos.x, viewPos.y);
	this->CreatePause(mousePos);
	this->PausePositionButtons();
}



void Menu::DrawMenu(sf::RenderTarget& target)
{
	target.draw(BackgroundSprite);
	target.draw(menuBackgroundSprite);
	target.draw(MenuPlay);
	target.draw(MenuOption);
	target.draw(MenuQuit);
}

void Menu::DrawPause(sf::RenderTarget& target)
{
	target.draw(pauseBackgroundSprite);
}
