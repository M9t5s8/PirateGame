#include "Headers/Starfish.h"

Starfish::Starfish() {
  frameWidth = 34;
  frameHeight = 30;
  HitboxWidth = 18;
  HitboxHeight = 20;

  pos = { 350, 250 };
  vertical_speed = 0;
  horizontal_speed = 0;
  isFacingRight = false;
  state = ENEMYSTATE::IDLE;

  LoadTexture();

  sprite.setOrigin(frameWidth / 2.f, frameHeight / 2.f);
  sprite.setPosition(pos);
}

void Starfish::setPosition(sf::Vector2f position)
{
  pos.x = position.x + HitboxWidth / 2;
  pos.y = position.y + HitboxHeight / 2;
  sprite.setPosition(pos);
}

void Starfish::LoadTexture() {
  sprite.setTexture(Textures::starfishTexture);
  sprite.setTextureRect(sf::IntRect(0, 0, frameWidth, frameHeight));
}

void Starfish::ChangeAnimation(int style, float deltatime) {
  int line = 0;
  int totalFrame = 1;
  switch (style) {
  case 0: line = 0; totalFrame = 7; break;
  case 1: line = 1; totalFrame = 5; break;
  case 2: line = 2; totalFrame = 6; break;
  case 3: line = 3; totalFrame = 3; break;
  case 4: line = 4; totalFrame = 4; break;
  }
  Animation(line, totalFrame, deltatime);
}




void Starfish::HorizontalMovement(float deltatime)
{

  switch (animation)
  {
  case ENEMYANIMATION::WALK:
    switch (direction)
    {
    case ENEMYDIRECTION::LEFT:
      if (state == ENEMYSTATE::CHASE || state == ENEMYSTATE::RETREAT)
        horizontal_speed = -ENEMY_RUN_SPEED;
      else
        horizontal_speed = -ENEMY_WALK_SPEED;
      this->ChangeAnimation(1, deltatime); // 1 = Walk
      break;

    case ENEMYDIRECTION::RIGHT:
      if (state == ENEMYSTATE::CHASE || state == ENEMYSTATE::RETREAT)
        horizontal_speed = ENEMY_RUN_SPEED;
      else
        horizontal_speed = ENEMY_WALK_SPEED;
      this->ChangeAnimation(1, deltatime); // 1 = Walk
      break;

    default:
      break;
    }
    break;

  case ENEMYANIMATION::IDLE:
    horizontal_speed = 0;
    this->ChangeAnimation(0, deltatime); // 0 = Idle
    break;

  case ENEMYANIMATION::ATTACK:
    horizontal_speed = 0;
    this->ChangeAnimation(2, deltatime); // 2 = Attack
    break;

  case ENEMYANIMATION::HIT:
    this->ChangeAnimation(3, deltatime); // 3 = Hit
    break;

  case ENEMYANIMATION::DEAD:
    this->ChangeAnimation(4, deltatime); // 4 = Dead
    break;

  default:
    std::cerr << "Unknown enemy animation state!" << std::endl;
    break;
  }

  sprite.setScale(direction == ENEMYDIRECTION::RIGHT ? -1.f : 1.f, 1.f);
  pos.x += horizontal_speed * deltatime * MULTIPLIER;
}














void Starfish::Update(float deltaTime, MAP& map) {
  this->HorizontalMovement(deltaTime);
  this->Gravity(deltaTime);
  this->Collision(deltaTime, map);
  sprite.setPosition(pos);

}
