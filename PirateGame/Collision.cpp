#include <unordered_set> // Faster lookups
#include <algorithm>
#include <array>
#include <chrono>
#include <vector>
#include <cmath>
#include <iostream> 
#include "Headers/Collision.h"

uint16_t Collision_Check(
  const sf::FloatRect& playerRect,
  const std::vector<CELL_TYPE>& i_check_cells,
  const MAP& i_map,
  bool treat_oob_as_floor
) 
{
  // Guard clauses
  if (i_map.empty() || CELL_SIZE <= 0) return 0;

  // Convert player rect to grid cells
  int x_min = static_cast<int>(std::floor(playerRect.left / CELL_SIZE));
  int y_min = static_cast<int>(std::floor(playerRect.top / CELL_SIZE));
  int x_max = static_cast<int>(std::floor((playerRect.left + playerRect.width) / CELL_SIZE));
  int y_max = static_cast<int>(std::floor((playerRect.top + playerRect.height) / CELL_SIZE));


  // Precompute check set for O(1) lookups
  std::unordered_set<CELL_TYPE> check_set(i_check_cells.begin(), i_check_cells.end());

  uint16_t output = 0;
  for (int y = y_min; y <= y_max; ++y) {
    for (int x = x_min; x <= x_max; ++x) {
      bool is_colliding = false;
      if (0 <= x && x < i_map.size() && 0 <= y && y < i_map[0].size()) {
        is_colliding = check_set.count(i_map[x][y]);
      }
      else if (treat_oob_as_floor) {
        is_colliding = check_set.count(CELL_TYPE::FLOOR);
      }

      if (is_colliding) {
        int bitShift = (y - y_min) * 2 + (x - x_min);
        if (bitShift < 16) output |= (1 << bitShift); // Prevent overflow
      }
    }
  }
  return output;
}
bool isNoFloor(
  const sf::Vector2f checkRect,
  const MAP& i_map
)
{
  int x = static_cast<int>(checkRect.x / CELL_SIZE);
  int y = static_cast<int>(checkRect.y / CELL_SIZE);
  if (i_map[x][y] == CELL_TYPE::EMPTY)
  {
    return true;
  }
  return false;
}
bool checkCell(
  const sf::Vector2i enemy,
  const sf::Vector2i player,
  bool isLeft,
  const MAP& i_map
)
{
  int x0 = enemy.x;
  int y0 = enemy.y;
  int x1 = player.x;
  int y1 = player.y;

  if (!isLeft && player.x < enemy.x)
    return false;

  if (isLeft && player.x > enemy.x)
    return false;

  int dx = std::abs(x1 - x0);
  int dy = std::abs(y1 - y0);

  int sx = (x0 < x1) ? 1 : -1;
  int sy = (y0 < y1) ? 1 : -1;

  int err = dx - dy;

  while (true)
  {
    if (i_map[x0][y0] != CELL_TYPE::EMPTY)
    {
      return false;
    }
    if (x0 == x1 && y0 == y1)
      break;
    int e2 = 2 * err;
    if (e2 > -dy) { err -= dy; x0 += sx; }
    if (e2 < dx) { err += dx; y0 += sy; }
  }

  return true;
}