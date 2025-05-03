#include "Headers/Global.h"
#include "Headers/Game.h"
#include "Headers/Textures.h"


int main()
{
  
  sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH * RESIZE, SCREEN_HEIGHT * RESIZE), "Pirate Game");
  Textures::loadAll();
  Game game(&window);
  float deltatime;
  sf::Clock clock;





  while (window.isOpen())
  {
    deltatime = clock.restart().asSeconds();
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
        window.close();
    } 

    game.Update(deltatime);
    game.Draw();
  }
  return 0;
}
