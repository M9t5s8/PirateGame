#include "Headers/Enemy.h"

Enemy::Enemy()
  : frameWidth(0),
  frameHeight(0),
  currentFrame(0),
  totalTime(0),
  HitboxWidth(0),
  HitboxHeight(0), 
  vertical_speed(0),
  horizontal_speed(0),
  is_onGround(false),
  isFacingRight(false),
  vertical_collision(0),
  horizontal_collision(0),
  horizontalCollided(false),
  isLeftFloor(false),
  isRightFloor(false)
{
  sprite.setTexture(Textures::crabTexture); 
  sprite.setOrigin(frameWidth / 2.f, frameHeight / 2.f);
  sprite.setTextureRect(sf::IntRect(0, 0, frameWidth, frameHeight));
  //animate = new Animation();

}



void Enemy::Gravity(float deltatime)
{
  vertical_speed += GRAVITY * MULTIPLIER * deltatime;
}

void Enemy::Collision(float deltatime, MAP& i_map)
{
  const sf::FloatRect VplayerRect(
    pos.x - HitboxWidth / 2,
    pos.y - HitboxHeight / 2 + (vertical_speed > 0 ? vertical_speed : 0),
    HitboxWidth,
    HitboxHeight
  );

  const sf::FloatRect HplayerRect(
    pos.x - HitboxWidth / 2 + horizontal_speed,
    pos.y - HitboxHeight / 2 - SKIN_WIDTH,
    HitboxWidth,
    HitboxHeight
  );

  const std::vector<CELL_TYPE> check_cells = { CELL_TYPE::FLOOR };
  vertical_collision = Collision_Check(VplayerRect, check_cells, i_map, true);
  horizontal_collision = Collision_Check(HplayerRect, check_cells, i_map, true);

  if (vertical_collision == horizontal_collision && vertical_collision != 0)
  {
    if (abs(vertical_speed) > abs(horizontal_speed))
    {
      this->VerticalCollision(deltatime);
    }
    else
    {
      this->HorizontalCollision(deltatime);
    }
  }
  else
  {
    this->VerticalCollision(deltatime);
    this->HorizontalCollision(deltatime);
  }
  const sf::Vector2f LFloorCheck(pos.x - HitboxWidth / 2 + horizontal_speed, pos.y + HitboxHeight);
  const sf::Vector2f RFloorCheck(pos.x + HitboxWidth / 2 + horizontal_speed, pos.y + HitboxHeight);
  if (isNoFloor(LFloorCheck, i_map))
  {
      horizontalCollided = true;
  }
  if (isNoFloor(RFloorCheck, i_map))
  {
      horizontalCollided = true;
  }
}

void Enemy::VerticalCollision(float deltatime)
{
  if (0 < vertical_collision)
  {
    if (3 & vertical_collision && 12 & ~vertical_collision)
    {
      pos.y = (static_cast<int>((pos.y + vertical_speed) / CELL_SIZE)) * CELL_SIZE + HitboxHeight / 2 + SKIN_WIDTH;
      is_onGround = false;
    }
    else if (3 & ~vertical_collision && 12 & vertical_collision)
    {
      pos.y = (static_cast<int>((pos.y + vertical_speed) / CELL_SIZE + 1)) * CELL_SIZE - HitboxHeight / 2 - SKIN_WIDTH / 1.5;
    }
    vertical_speed = 0;
    pos.x = pos.x;
  }
  else
  {
    is_onGround = false;
    this->Gravity(deltatime);
    pos.y += vertical_speed * deltatime * MULTIPLIER;
  }
}

void Enemy::HorizontalCollision(float deltatime)
{
  if (0 < horizontal_collision)
  {
    if (5 & ~horizontal_collision && 10 & horizontal_collision)
    {
      pos.x = (static_cast<int>((pos.x + horizontal_speed) / CELL_SIZE) + 1) * CELL_SIZE - HitboxWidth / 2 - SKIN_WIDTH;
      if (state == ENEMYSTATE::IDLE || state == ENEMYSTATE::PATROL)
        direction = ENEMYDIRECTION::RIGHT;

      horizontalCollided = true;
    }
    else if (5 & horizontal_collision && 10 & ~horizontal_collision)
    {
      pos.x = (static_cast<int>((pos.x + horizontal_speed) / CELL_SIZE) * CELL_SIZE) + HitboxWidth / 2 + SKIN_WIDTH;
      if (state == ENEMYSTATE::IDLE || state == ENEMYSTATE::PATROL)
        direction = ENEMYDIRECTION::LEFT;

      horizontalCollided = true;
    }
    horizontal_speed = 0;
    
  }
}



bool Enemy::isCollided()
{
  return horizontalCollided;
}
ENEMYDIRECTION Enemy::getDirection()
{
  return direction;
}


void Enemy::Animation(int line, int totalFrame, float deltatime)
{
  if (totalFrame <= 1)
  {
    currentFrame = 0;
    sprite.setTextureRect(sf::IntRect(0, line * frameHeight, frameWidth, frameHeight));
    return;
  }

  float frameTime = 0.15f;
  totalTime += deltatime;

  if (totalTime >= frameTime)
  {
    currentFrame = (currentFrame + 1) % totalFrame;
    sprite.setTextureRect(sf::IntRect(currentFrame * frameWidth, line * frameHeight, frameWidth, frameHeight));
    totalTime = 0;
  }
}

void Enemy::setPosition(sf::Vector2f position)
{
  sprite.setPosition(position);
}
sf::Vector2f Enemy::getPosition()
{
  return sprite.getPosition();
}

void Enemy::Update(float deltatime, MAP& i_map)
{
  this->Collision(deltatime, i_map);
  this->ChangeAnimation(0, deltatime);
  sprite.setPosition(pos);
}

void Enemy::Draw(sf::RenderTarget& target)
{
  target.draw(sprite);
}

