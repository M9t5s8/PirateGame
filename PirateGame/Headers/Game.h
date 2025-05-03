#pragma once
#include "Map.h"
#include "View.h"
#include "Menu.h"
#include "Player.h"
class Game
{
private:
  sf::RenderWindow* window;
  Map* map;
  View* view;
  Menu* menu;
  Player* player;
  MAP i_map;
  bool iskeyPressed;
public:
  Game(sf::RenderWindow*);
  virtual ~Game();
  void ChangeState();
  sf::Vector2f getMousePos();
  void Update(float);
  void Draw();
};


