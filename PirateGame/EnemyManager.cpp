#include "Headers/EnemyManager.h"

EnemyManager::EnemyManager()
{

}
EnemyManager::~EnemyManager()
{

}
void EnemyManager::setEnemy(int greenValue, sf::Vector2f pos)
{

  switch (greenValue)
  {
  case 0:
  {
    CrabbyManager crabby(sf::Vector2f(pos.x * CELL_SIZE, pos.y * CELL_SIZE));
    CRABBY.push_back(crabby);
    break;
  }
  case 1:
  {
    SharkManager shark(sf::Vector2f(pos.x * CELL_SIZE, pos.y * CELL_SIZE));
    SHARK.push_back(shark);
    break;
  }
  case 2:
  {
    StarfishManager starfish(sf::Vector2f(pos.x * CELL_SIZE, pos.y * CELL_SIZE));
    STARFISH.push_back(starfish);
    break;
  }
  default:
    break;
  }
}


void EnemyManager::Update(float deltatime, MAP& i_map)
{
  for (auto& s : SHARK) s.Update(deltatime, i_map);
  for (auto& c : CRABBY) c.Update(deltatime, i_map);
  for (auto& s : STARFISH) s.Update(deltatime, i_map);
}

void EnemyManager::Draw(sf::RenderTarget& target)
{
	for (auto& s : SHARK) s.Draw(target);
	for (auto& c : CRABBY) c.Draw(target);
	for (auto& s : STARFISH) s.Draw(target);
}