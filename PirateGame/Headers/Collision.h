#pragma once
#include "Global.h"

// Use uint16_t instead of unsigned char for larger bitmask support
uint16_t Collision_Check(
  const sf::FloatRect& playerRect,
  const std::vector<CELL_TYPE>& i_check_cells,
  const MAP& i_map,
  bool treat_oob_as_floor = true 
);
bool isNoFloor(
  const sf::Vector2f checkRect,
  const MAP& i_map
);
bool checkCell(
  const sf::Vector2i enemy,
  const sf::Vector2i player,
  bool isLeft,
  const MAP& i_map
);