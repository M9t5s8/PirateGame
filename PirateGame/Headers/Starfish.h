#pragma once
#include "Enemy.h"


class Starfish: public Enemy
{
public:
  Starfish();
  ~Starfish() override = default;

  void LoadTexture() override;
  void setPosition(sf::Vector2f) override;
  void ChangeAnimation(int style, float deltatime) override;
  void HorizontalMovement(float) override;
  void Update(float deltaTime, MAP& map) override;
};


