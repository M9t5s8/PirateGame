#include "Headers/CrabbyManager.h"

CrabbyManager::CrabbyManager(const sf::Vector2f& pos)
{
  HomePosition = pos;

  crabby.setPosition(pos);
  idleTimer = 0.0f;
  idleSwitchTime = 2.0f + static_cast<float>(rand() % 60) / 10.f;
  state = ENEMYSTATE::IDLE;
  direction = ENEMYDIRECTION::LEFT;
  animation = ENEMYANIMATION::IDLE;
  patrolTimer = 0.0f;
  patrolDuration = 1.0f;
  fullyPatrol = 10.0f;
  fullyIdle = 10.0f;
  TotalIdle = 0.0f;
  TotalPatrol = 0.0f;
  searchTimer = 0.0f;
  searchDirectionTimer = 2.0f;
  totalSearchTime = 5.0f;
  totalSearchTimer = 0.0f;
  attackRange.setSize(sf::Vector2f(CELL_SIZE * 1.7, CELL_SIZE));
  attackRange.setOutlineColor(sf::Color::Black);
  attackRange.setFillColor(sf::Color::Transparent);
  attackRange.setOutlineThickness(-1);
  attackRange.setPosition(Position);
  attackRange.setOrigin(attackRange.getLocalBounds().width / 2, attackRange.getLocalBounds().height / 2);
  searchRange.setSize(sf::Vector2f(CELL_SIZE * 10, CELL_SIZE*3));
  searchRange.setOutlineColor(sf::Color::Black);
  searchRange.setFillColor(sf::Color::Transparent);
  searchRange.setOutlineThickness(-1);
  searchRange.setPosition(Position);
  searchRange.setOrigin(searchRange.getLocalBounds().width / 2,searchRange.getSize().y - attackRange.getLocalBounds().height / 2);

}

CrabbyManager::~CrabbyManager()
{

}
void CrabbyManager::SetPosition(sf::Vector2f position)
{
  crabby.setPosition(position);
}

void CrabbyManager::ChangeDirection(float deltatime , MAP& i_map)
{
  Position = crabby.getPosition();
  

  switch (state)
  {
  case ENEMYSTATE::PATROL:
  {
    TotalPatrol += deltatime;
    patrolTimer += deltatime;
    if (patrolTimer >= patrolDuration) {
      patrolTimer = 0.f;
      animation = ENEMYANIMATION::IDLE;
      state = ENEMYSTATE::IDLE;
    }
    this->SearchLogic(deltatime);
    this->CheckHome();
    std::cout << "Patrol" << std::endl;
    break;
  }
  case ENEMYSTATE::IDLE:
  {
    idleTimer += deltatime;
    TotalIdle += deltatime;
    if (idleTimer >= idleSwitchTime) {
      direction = (rand() % 2 == 0) ? ENEMYDIRECTION::LEFT : ENEMYDIRECTION::RIGHT;
      idleTimer = 0.f;
      idleSwitchTime = 2.0f + static_cast<float>(rand() % 30) / 10.f;
      animation = ENEMYANIMATION::WALK;
      state = ENEMYSTATE::PATROL;
      patrolTimer = 0.f;
      patrolDuration = 1.f + static_cast<float>(rand() % 40) / 10.f;
    }
    this->SearchLogic(deltatime);
    this->CheckHome();
    std::cout << "Idle" << std::endl;
    break;
  }
  case ENEMYSTATE::SEARCH:
  {
    this->SearchLogic(deltatime);
    this->ChaseLogic(i_map);
    this->ResetSearch(i_map , deltatime);
    std::cout << "Search" << std::endl;
    break;
  }
  case ENEMYSTATE::CHASE:
  {
    this->ChaseForPlayer();
    this->CheckforAttack();
    this->PlayergotFar(i_map);
    std::cout << "Chase" << std::endl;
    break;
  }
  case ENEMYSTATE::ATTACK:
  {
    this->ResetAttack();
    this->ChaseForPlayer();
    this->CheckforAttack();
    std::cout << "Attack" << std::endl;
    break;
  }
  case ENEMYSTATE::RETREAT:
  {
    this->LetRetreat();
    std::cout << "Retreat" << std::endl;
    break;
  }
  case ENEMYSTATE::HIT:
    break;
  case ENEMYSTATE::DEAD:
    break;
  default:
    break;
  }
}
void CrabbyManager::CheckHome()
{
  if (Position.x > HomePosition.x + ENEMY_AI::SHARK_MAX_PATROL)
  {
    direction = ENEMYDIRECTION::LEFT;
  }
  else if (Position.x < HomePosition.x - ENEMY_AI::SHARK_MAX_PATROL)
  {
    direction = ENEMYDIRECTION::RIGHT;
  }
}
void CrabbyManager::SearchLogic(float deltatime)
{
  if (SearchRangeBounds.intersects(playerRect))
  {
    animation = ENEMYANIMATION::IDLE;
    state = ENEMYSTATE::SEARCH;
    searchTimer += deltatime;
    if (searchTimer >= searchDirectionTimer)
    {
      direction = ( direction == ENEMYDIRECTION::RIGHT) ? ENEMYDIRECTION::LEFT : ENEMYDIRECTION::RIGHT;
      searchTimer = 0.0f;

    }
  }
}
void CrabbyManager::CheckforAttack()
{
  if (AttackRangeBounds.intersects(playerRect))
  {
    state = ENEMYSTATE::ATTACK;
    animation = ENEMYANIMATION::ATTACK;
  }
}
void CrabbyManager::ResetAttack()
{
  if (!AttackRangeBounds.intersects(playerRect))
  {
    state = ENEMYSTATE::IDLE;
    animation = ENEMYANIMATION::IDLE;
  }
}
void CrabbyManager::ChaseLogic(MAP& i_map)
{
  sf::Vector2i enemyCell(
    static_cast<int>(Position.x) / CELL_SIZE,
    static_cast<int>(Position.y) / CELL_SIZE
  );
  sf::Vector2i playerCell(
    static_cast<int>(PlayerPosition.x) / CELL_SIZE,
    static_cast<int>(PlayerPosition.y) / CELL_SIZE
  );
  bool isLeft = (direction == ENEMYDIRECTION::LEFT);
  if (SearchRangeBounds.intersects(playerRect) && checkCell(enemyCell, playerCell, isLeft, i_map))
  {
    state = ENEMYSTATE::CHASE;
    animation = ENEMYANIMATION::IDLE;
  }
}
void CrabbyManager::ResetSearch(MAP& i_map , float deltatime)
{
  sf::Vector2i enemyCell(
    static_cast<int>(Position.x) / CELL_SIZE,
    static_cast<int>(Position.y) / CELL_SIZE
  );
  sf::Vector2i playerCell(
    static_cast<int>(PlayerPosition.x) / CELL_SIZE,
    static_cast<int>(PlayerPosition.y) / CELL_SIZE
  );
  bool isLeft = (direction == ENEMYDIRECTION::LEFT);
  totalSearchTimer += deltatime;
  if (!SearchRangeBounds.intersects(playerRect) || (!checkCell(enemyCell, playerCell, isLeft, i_map) && totalSearchTimer >= totalSearchTime))
  {
    totalSearchTimer = 0.0f;
    state = ENEMYSTATE::IDLE;
    animation = ENEMYANIMATION::IDLE;
  }
}
void CrabbyManager::ChaseForPlayer()
{
  if ((Position.x > PlayerPosition.x))
  {
    direction = ENEMYDIRECTION::LEFT;
  }
  else
  {
    direction = ENEMYDIRECTION::RIGHT;
  }
  animation = ENEMYANIMATION::WALK;
}
void CrabbyManager::PlayergotFar(MAP& i_map)
{
    if (SearchRangeBounds.intersects(playerRect))
    {
      if (crabby.isCollided())
      {
        animation = ENEMYANIMATION::IDLE;
      }
      if ((Position.x > PlayerPosition.x) && crabby.isCollided())
      {
        direction = ENEMYDIRECTION::LEFT;
      }
      else if((Position.x > PlayerPosition.x) && crabby.isCollided())
      {
        direction = ENEMYDIRECTION::RIGHT;
      }
      
    }
    else
    {
      if (crabby.isCollided())
      {
        state = ENEMYSTATE::RETREAT;
      }
    }
}
void CrabbyManager::LetRetreat()
{
  if ((Position.x > HomePosition.x))
  {
    direction = ENEMYDIRECTION::LEFT;
  }
  else
  {
    direction = ENEMYDIRECTION::RIGHT;
  }
  animation = ENEMYANIMATION::WALK;
  if (static_cast<int>( Position.x / CELL_SIZE) == static_cast<int>(HomePosition.x / CELL_SIZE))
  {
    animation = ENEMYANIMATION::IDLE;
    state = ENEMYSTATE::IDLE;
  }
}






void CrabbyManager::ExtraUpdates()
{
  attackRange.setPosition(crabby.getPosition());
  searchRange.setPosition(crabby.getPosition());
  playerRect = sf::FloatRect(PlayerPosition.x - 10, PlayerPosition.y - 13, 20, 26);
  AttackRangeBounds = attackRange.getGlobalBounds();
  SearchRangeBounds = searchRange.getGlobalBounds();
}



void CrabbyManager::Update(float deltatime, MAP& i_map)
{
  this->ExtraUpdates();
  this->ChangeDirection(deltatime , i_map);
  crabby.state = state;
  crabby.animation = animation;
  if (crabby.isCollided())
  {
    direction = (direction == ENEMYDIRECTION::LEFT) ? ENEMYDIRECTION::RIGHT : ENEMYDIRECTION::LEFT;
    crabby.horizontalCollided = false;
  }
  crabby.direction = direction;
  crabby.Update(deltatime, i_map);
}
void CrabbyManager::Draw(sf::RenderTarget& target)
{
  crabby.Draw(target);
  target.draw(attackRange);
  target.draw(searchRange);
}