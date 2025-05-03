#pragma once
#include "Global.h"
#include "Collision.h"

class Enemy {
protected:
  sf::Sprite sprite;
  sf::Vector2f pos;
  float vertical_speed;
  float horizontal_speed;
  bool is_onGround;
  bool isFacingRight;
 
  sf::RectangleShape left, right;
  float totalTime;
  int currentFrame;
  int frameWidth;
  int frameHeight;
  int HitboxWidth;
  int HitboxHeight;
  bool isLeftFloor, isRightFloor;
  
  

  unsigned char horizontal_collision, vertical_collision;

public:
  ENEMYSTATE state;
  ENEMYDIRECTION direction;
  ENEMYANIMATION animation;
  bool horizontalCollided;
  
  Enemy();
  virtual ~Enemy() = default;
  virtual void LoadTexture() = 0;
  virtual void setPosition(sf::Vector2f) = 0;
  virtual void ChangeAnimation(int style, float deltatime) = 0;
  virtual void Update(float deltaTime, MAP& map) = 0;
  virtual void Draw(sf::RenderTarget& target);
 
  virtual void HorizontalMovement(float deltatime) = 0 ; 
  virtual sf::Vector2f getPosition();
  virtual bool isCollided();
  virtual ENEMYDIRECTION getDirection();

protected:
  virtual void Gravity(float deltatime);
  virtual void Collision(float deltatime, MAP& i_map);
  
  virtual void VerticalCollision(float deltatime);
  virtual void HorizontalCollision(float deltatime) ;
  virtual void Animation(int line, int totalFrame, float deltatime);
  


};


