#pragma once

#include "Crabby.h"
class CrabbyManager
{
private:
	Crabby crabby;
	ENEMYSTATE state;
	ENEMYDIRECTION direction;
	ENEMYANIMATION animation;
	sf::FloatRect playerRect;
	sf::FloatRect AttackRangeBounds,SearchRangeBounds;

	sf::Vector2f HomePosition;
	sf::Vector2f Position;
	float idleTimer;
	float idleSwitchTime;
	float patrolTimer;
	float patrolDuration;
	float fullyPatrol;
	float fullyIdle;
	float searchTimer;
	float searchDirectionTimer;
	float totalSearchTime;
	float totalSearchTimer;
	float TotalIdle, TotalPatrol;
	sf::RectangleShape attackRange;
	sf::RectangleShape searchRange;
public:

	CrabbyManager(const sf::Vector2f&);
	virtual ~CrabbyManager();
	void SetPosition(sf::Vector2f);
	void ChangeDirection(float, MAP&);
	void ExtraUpdates();
	void CheckforAttack();
	void ResetAttack();
	void ChaseLogic(MAP&);
	void SearchLogic(float);
	void CheckHome();
	void ChaseForPlayer();
	void PlayergotFar(MAP&);
	void ResetSearch(MAP& , float);
	void LetRetreat();
	void Update(float, MAP&);
	void Draw(sf::RenderTarget&);
};

