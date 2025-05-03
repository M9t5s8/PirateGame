#pragma once
#include "Enemy.h"


class Shark : public Enemy
{
public:
  Shark();
  ~Shark() override = default;

  void LoadTexture() override;
  void setPosition(sf::Vector2f) override;
  void HorizontalMovement(float) override;
  void ChangeAnimation(int style, float deltatime) override;
  void Update(float deltaTime, MAP& map) override;
};


