#pragma once

#include "Starfish.h"
class StarfishManager
{
private:
	Starfish starfish;
	ENEMYSTATE state;
	ENEMYDIRECTION direction;
	ENEMYANIMATION animation;
	sf::FloatRect playerRect;
	sf::FloatRect AttackRangeBounds, SearchRangeBounds;

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
	float TotalIdle, TotalPatrol;
	sf::RectangleShape attackRange;
	sf::RectangleShape searchRange;
public:

	StarfishManager(const sf::Vector2f&);
	virtual ~StarfishManager();
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
	void ResetSearch(MAP&);
	void LetRetreat();
	void Update(float, MAP&);
	void Draw(sf::RenderTarget&);
};

