#include "Headers/Player.h"

Player::Player()
  : currentFrame(0),
  totalTime(0),
  isFacingRight(true),
  is_onGround(false),
  isSpaceClicked(false),
  frameWidth(64),
  frameHeight(40),
  horizontal_speed(0),
  vertical_speed(0),
  playerWidth(20),
  playerHeight(26),
  isLeftClicked(false),
  isRightClicked(false),
  isAttacked(false),
  attackCompleted(true)
{
  animate = new Animation();
  playerSprite.setTexture(Textures::playerTexture);
  playerSprite.setOrigin(frameWidth / 2.f, frameHeight / 2.f);
  pos = PlayerPosition;
  playerSprite.setPosition(pos);
  playerSprite.setTextureRect(sf::IntRect(0, 0, frameWidth, frameHeight));
  playerBox.setSize(sf::Vector2f(frameWidth, frameHeight));
  playerBox.setFillColor(sf::Color::Transparent);
  playerBox.setOutlineColor(sf::Color::White);
  playerBox.setOutlineThickness(-1);
  playerHitbox.setSize(sf::Vector2f(playerWidth, playerHeight));
  playerHitbox.setFillColor(sf::Color::Transparent);
  playerHitbox.setOutlineColor(sf::Color::White);
  playerHitbox.setOutlineThickness(-1);
    

    
}
Player::~Player()
{
  delete animate;
}
sf::Vector2f Player::getPlayerPosition()
{
  return pos;
}


void Player::PlayerMovement(float deltatime)
{
  bool left = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
  bool right = sf::Keyboard::isKeyPressed(sf::Keyboard::D);

  if (left && !right)
  {
    horizontal_speed = -PLAYER_WALK_SPEED;
    if (is_onGround && !isLeftClicked && !isRightClicked && attackCompleted)
      playerstate = PLAYERSTATE::WALK;

    playerdirection = PLAYERDIRECTION::LEFT;
  }
  else if (right && !left && attackCompleted)
  {
    horizontal_speed = PLAYER_WALK_SPEED;
    if(is_onGround && !isLeftClicked && !isRightClicked && attackCompleted)
      playerstate = PLAYERSTATE::WALK;

    playerdirection = PLAYERDIRECTION::RIGHT;
  }
  else if((!left && !right && is_onGround && attackCompleted)||
    (left && right && is_onGround &&attackCompleted)
    )
  {
    horizontal_speed = 0;
    playerstate = PLAYERSTATE::IDLE;
  }
}

void Player::ChangeAnimation(int style, float deltatime)
{
  const int lines[] = { 0, 1, 2, 3, 4, 5, 6 };
  const int frames[] = { 4, 5, 2, 0, 2, 3, 7 };

  if (style == 4 || style == 5 || style == 6)
  {
    animate->setAnimation(deltatime,playerSprite, sf::Vector2f(frameWidth, frameHeight), lines[style], frames[style], 0.15f, false);
  }
  else
  {
    animate->setAnimation(deltatime,playerSprite, sf::Vector2f(frameWidth, frameHeight), lines[style], frames[style], 0.15f, true);
  }
}

void Player::verticalMovement(float deltatime)
{
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
  {
    if (is_onGround && !isSpaceClicked && attackCompleted)
    {
      vertical_speed = PLAYER_JUMP_SPEED; // Apply jump speed
      playerstate = PLAYERSTATE::JUMPUP;
      is_onGround = false;
      isSpaceClicked = true;
      pos.y += vertical_speed * deltatime * MULTIPLIER;
      
    }
  }
  else
  {
    isSpaceClicked = false;
  }
}


void Player::PlayerAttack(float deltatime)
{
  attackCompleted = animate->isFinished();
  bool leftBtn = sf::Mouse::isButtonPressed(sf::Mouse::Left);
  bool rightBtn = sf::Mouse::isButtonPressed(sf::Mouse::Right);
  if (playerstate == PLAYERSTATE::IDLE)
  {
    if (leftBtn && !rightBtn && !isRightClicked && attackCompleted && !isLeftClicked) {
      isLeftClicked = true;
      animate->reset();
      playerstate = PLAYERSTATE::ATTACK1;
    }
    else if (rightBtn && !leftBtn && !isLeftClicked && attackCompleted && !isRightClicked) {
      isRightClicked = true;
      animate->reset();
      playerstate = PLAYERSTATE::ATTACK2;
    }
  }
  if (isLeftClicked && !leftBtn && !rightBtn && attackCompleted) {
    playerstate = PLAYERSTATE::IDLE;
    isLeftClicked = false;
  }
  if (isRightClicked && !rightBtn && !leftBtn && attackCompleted) {
    playerstate = PLAYERSTATE::IDLE;
    isRightClicked = false;
  }
}


void Player::Movement(float deltatime)
{
  switch (playerstate)
  {
  case PLAYERSTATE::IDLE:
    this->ChangeAnimation(0, deltatime);
    break;
  case PLAYERSTATE::WALK:
    this->ChangeAnimation(1, deltatime);
    break;
  case PLAYERSTATE::JUMPUP:
    this->ChangeAnimation(2, deltatime);
    break;
  case PLAYERSTATE::JUMPDOWN:
    this->ChangeAnimation(3, deltatime);
    break;
  case PLAYERSTATE::ATTACK1:
    this->ChangeAnimation(4, deltatime);
    break;
  case PLAYERSTATE::ATTACK2:
    this->ChangeAnimation(4, deltatime);
    if (playerdirection == PLAYERDIRECTION::LEFT)
    {
      horizontal_speed= -PLAYER_ATTACK_CHARGE;
    }
    else if (playerdirection == PLAYERDIRECTION::RIGHT)
    {
      horizontal_speed = PLAYER_ATTACK_CHARGE;
    }
    break;
  case PLAYERSTATE::HIT:
    this->ChangeAnimation(5, deltatime);
    break;
  case PLAYERSTATE::DEAD:
    this->ChangeAnimation(6, deltatime);
    break;
  default:
    break;
  }
  playerSprite.setScale(playerdirection == PLAYERDIRECTION::LEFT ? -1.f : 1.f, 1.f);
  pos.x += horizontal_speed * deltatime * MULTIPLIER;
}



void Player::Gravity(float deltatime)
{
  vertical_speed += GRAVITY * MULTIPLIER * deltatime;
  if (vertical_speed > 2.0f && !is_onGround)
    playerstate = PLAYERSTATE::JUMPDOWN;
  if (is_onGround)
    playerstate = PLAYERSTATE::IDLE;

  
}

void Player::Collision(float deltatime, MAP& i_map)
{
  const sf::FloatRect VplayerRect(
    pos.x - playerWidth / 2,
    pos.y - playerHeight / 2 - 2 * SKIN_WIDTH + (vertical_speed > 0 ? vertical_speed : 0),
    playerWidth,
    playerHeight
  );
  const sf::FloatRect HplayerRect(
    pos.x - playerWidth / 2 + horizontal_speed,
    pos.y - playerHeight / 2 - 2 * SKIN_WIDTH,
    playerWidth,
    playerHeight
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
}

void Player::VerticalCollision(float deltatime)
{
  if (0 < vertical_collision)
  {
    if (3 & vertical_collision && 12 & ~vertical_collision)
    {
      pos.y = (static_cast<int>((pos.y + vertical_speed) / CELL_SIZE)) * CELL_SIZE + playerHeight / 2 + 3 * SKIN_WIDTH;
      is_onGround = false;
    }
    else if (3 & ~vertical_collision && 12 & vertical_collision)
    {
      pos.y = (static_cast<int>((pos.y + vertical_speed) / CELL_SIZE + 1)) * CELL_SIZE - playerHeight / 2 + (3 * SKIN_WIDTH) / 2;
      is_onGround = true;
      if (attackCompleted || is_onGround)
      {
        playerstate = PLAYERSTATE::IDLE;
      }
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
void Player::HorizontalCollision(float deltatime)
{
  if (0 < horizontal_collision)
  {
    if (5 & ~horizontal_collision && 10 & horizontal_collision)
    {
      pos.x = (static_cast<int>((pos.x + horizontal_speed) / CELL_SIZE) + 1) * CELL_SIZE - playerWidth / 2 - SKIN_WIDTH;
    }
    else if (5 & horizontal_collision && 10 & ~horizontal_collision)
    {
      pos.x = (static_cast<int>((pos.x + horizontal_speed) / CELL_SIZE) * CELL_SIZE) + playerWidth / 2 + SKIN_WIDTH;
    }
    horizontal_speed = 0;
  }
}


void Player::UpdateBox()
{
  playerBox.setPosition(pos.x - frameWidth / 2.f, pos.y - frameHeight / 2.f);
  playerHitbox.setPosition(pos.x - playerWidth / 2.f, pos.y - playerHeight / 2.f - 2 * SKIN_WIDTH);
}


void Player::Update(float deltatime, MAP& i_map)
{
  this->PlayerMovement(deltatime);
  this->verticalMovement(deltatime);
  this->PlayerAttack(deltatime);
  this->Movement(deltatime);
  this->Collision(deltatime, i_map);
  PlayerPosition = pos;
  playerSprite.setPosition(pos);
  this->UpdateBox();
}

void Player::Draw(sf::RenderTarget& target)
{
  target.draw(playerSprite);
  /*target.draw(playerBox);*/
  //target.draw(playerHitbox);
}
