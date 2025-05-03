#pragma once
#include "Global.h"

class View
{
private:
  sf::RenderWindow* m_window;
  sf::View m_view;
  float m_halfWidth;
  float m_halfHeight;
  float m_minX, m_maxX, m_minY, m_maxY;
  float x, y;

public:
  View(sf::RenderWindow* window, const sf::Vector2u& mapSizeInTiles);

  void Update(const sf::Vector2f& targetPosition);
  void ResetView();
  const sf::Vector2f GetView() const;
};
