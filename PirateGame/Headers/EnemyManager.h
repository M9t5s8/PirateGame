#pragma once
#include "Global.h"
#include "CrabbyManager.h"
#include "StarfishManager.h"
#include "SharkManager.h"
class EnemyManager
{
private:
	
	std::vector<SharkManager> SHARK;
	std::vector<CrabbyManager> CRABBY;
	std::vector<StarfishManager> STARFISH;
public:
	EnemyManager();
	virtual ~EnemyManager();
	void setEnemy(int greenValue, sf::Vector2f pos);
	void Update(float deltatime , MAP&);
	void Draw(sf::RenderTarget&);
};