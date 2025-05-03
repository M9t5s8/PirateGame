#pragma once
#include "Enemy.h"


class Crabby : public Enemy
{
public:
  Crabby();
  ~Crabby() override = default;
  void LoadTexture() override;
  void setPosition(sf::Vector2f) override;
  void ChangeAnimation(int style, float deltatime) override;
  void HorizontalMovement(float) override;
  void Update(float deltaTime, MAP& map) override;
};





