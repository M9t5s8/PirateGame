#pragma once
#include "Global.h"
#include "Collision.h"
#include "Textures.h"
#include "Animation.h"

class Player
{
private:
  Animation* animate;
  sf::Sprite playerSprite;
  sf::RectangleShape playerHitbox, playerBox;
  sf::Font font;
  sf::Text text, debugText;
  int currentFrame;
  float totalTime;
  float horizontal_speed;
  float vertical_speed;
  int frameWidth;
  int frameHeight;
  bool isFacingRight;
  bool is_onGround;
  bool isSpaceClicked;
  bool isLeftClicked, isRightClicked, isAttacked, attackCompleted;
  sf::Vector2f pos;
  unsigned char horizontal_collision, vertical_collision;
  int playerWidth;
  int playerHeight;
  float jumpBufferTimer = 0.f;
  float coyoteTimer = 0.f;
  PLAYERSTATE playerstate;
  PLAYERDIRECTION playerdirection;

public:
  Player();
  virtual ~Player();
  void ChangeAnimation(int, float);
  void PlayerMovement(float);
  void verticalMovement(float);
  sf::Vector2f getPlayerPosition();
  void UpdateBox();
  void Collision(float, MAP&);
  void PlayerAttack(float);
  void VerticalCollision(float);
  void HorizontalCollision(float);
  void Movement(float);
  void Gravity(float);
  void Update(float, MAP&);
  void Draw(sf::RenderTarget&);
};
