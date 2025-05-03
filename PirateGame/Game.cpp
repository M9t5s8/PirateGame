#include "Headers/Game.h"

Game::Game(sf::RenderWindow* window)
  : window(window),
  iskeyPressed(false)
{
  window->setFramerateLimit(165);
  
  map = new Map();
  sf::Vector2u mapDetails = map->Map_Details();
  i_map = MAP(mapDetails.x);
  map->ConverttoMap(i_map);
  player = new Player();
  menu = new Menu(*window);
  view = new View(window, mapDetails);
}
Game::~Game()
{
  delete player;
  delete map;
  delete menu;
}

void Game::ChangeState()
{
  switch (gamestate)
  {
  case GAMESTATE::MENU:
  {
    gamestate = menu->getGameState();
    break;
  }
  
  case GAMESTATE::PLAYING:
  {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && !iskeyPressed)
    {
      gamestate = GAMESTATE::PAUSED;
      iskeyPressed = true;
    }
    else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
      iskeyPressed = false;
    }
    break;
  }
  
  case GAMESTATE::PAUSED:
  {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && !iskeyPressed)
    {
      gamestate = GAMESTATE::PLAYING;
      iskeyPressed = true;
    }
    else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
      iskeyPressed = false;
    }
    break;
  }
  
  default:
    break;
  }
}

sf::Vector2f Game::getMousePos()
{
  return window->mapPixelToCoords(sf::Mouse::getPosition(*window));
}

void Game::Update(float deltatime)
{
  
  this->ChangeState();
  switch (gamestate)
  {
  case GAMESTATE::MENU:
  {
    view->ResetView();
    sf::Vector2f mousePos = this->getMousePos();
    menu->MenuUpdate(deltatime, mousePos);
    break;
  }
  
  case GAMESTATE::PLAYING:
  {
    view->Update(player->getPlayerPosition());
    sf::Vector2f centerView = view->GetView();
    map->Update(deltatime, i_map, centerView);
    player->Update(deltatime, i_map);
    break;
  }
  
  case GAMESTATE::PAUSED:
  {
    view->Update(player->getPlayerPosition());
    sf::Vector2f mousePos = this->getMousePos();
    sf::Vector2f centerView = view->GetView();
    menu->PauseUpdate(deltatime, centerView, mousePos);
    break;
  }
  
  case GAMESTATE::QUIT:
  {
    window->close();
    break;
  }
  default:
    break;
  }
  
}

void Game::Draw()
{
  window->clear();
  
  switch (gamestate)
  {
  case GAMESTATE::PLAYING:
  {
    map->Draw(*window);
    player->Draw(*window);
    break;
  }
  
  case GAMESTATE::MENU:
  {
    menu->DrawMenu(*window);
    break;
  }
  
  case GAMESTATE::PAUSED:
  {
    map->Draw(*window);
    player->Draw(*window);
    menu->DrawPause(*window);
    
    break;
  }
  default:
    break;
  }
  window->display();
}
