#pragma once

//all the necessary includes
#include <SFML/Audio.hpp>
#include<SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>
#include <vector>
#include <array>
#include <chrono>
#include <cmath>
#include <memory.h>
#include "Textures.h"




constexpr unsigned short SCREEN_HEIGHT = 448;
constexpr unsigned short SCREEN_WIDTH = 796;

constexpr unsigned char RESIZE = 2;
constexpr unsigned char CELL_SIZE = 32;


constexpr float GRAVITY = 0.6f;
constexpr float SKIN_WIDTH = 2.0f;
constexpr float MULTIPLIER = 60.0f;

//player constant
constexpr float PLAYER_WALK_SPEED = 3.0f;
constexpr float PLAYER_JUMP_SPEED = -9.0f;
constexpr float MAX_FALL_SPEED = 10.0f;
constexpr float PLAYER_ATTACK_CHARGE = 9.0f;
constexpr float PLAYER_HIT_KNOCKBACK = 3.0f;



constexpr float ENEMY_RUN_SPEED = 2.5f;
constexpr float ENEMY_WALK_SPEED = 2.0f;



constexpr float JUMP_BUFFER_TIME = 0.1f;
constexpr float COYOTE_TIME = 0.15f;


//enemy ai
namespace ENEMY_AI {
  inline constexpr int SHARK_MAX_PATROL = 6 * CELL_SIZE;
  inline constexpr int SHARK_MAX_SEARCH = 5;
  inline constexpr int ENEMY_ATTACK_RANGE = 3 * CELL_SIZE;
}





extern sf::Vector2f PlayerPosition;






template <typename T>
T clamp(T value, T min, T max)
{
  if (value < min)
    return min;
  if (value > max)
    return max;
  return value;
}

enum class CELL_TYPE
{
  EMPTY,
  FLOOR,
  DIRT,
  WATER,
  ANIWATER
};

enum class GAMESTATE
{
  PLAYING,
  MENU,
  PAUSED,
  OPTION,
  RESPAWN,
  LEVELCOMPLETE,
  QUIT
};

enum class ENEMYSTATE
{
  PATROL,
  IDLE,
  SEARCH,
  ATTACK,
  CHASE,
  RETREAT,
  HIT,
  DEAD
};
enum class ENEMYANIMATION
{
  IDLE,
  WALK,
  ATTACK,
  HIT,
  DEAD
};
enum class ENEMYDIRECTION
{
  LEFT,
  RIGHT
};
enum class PLAYERSTATE
{
  IDLE,
  WALK,
  JUMPUP,
  JUMPDOWN,
  ATTACK1,
  ATTACK2,
  HIT,
  DEAD
};
enum class PLAYERDIRECTION
{
  LEFT,
  RIGHT
};
extern GAMESTATE gamestate;


constexpr unsigned short MAP_WIDTH = SCREEN_WIDTH / CELL_SIZE;
constexpr unsigned short MAP_HEIGHT = SCREEN_HEIGHT / CELL_SIZE;

typedef std::vector<std::array<CELL_TYPE, MAP_HEIGHT>> MAP;
