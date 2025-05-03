#include "Headers/View.h"
#include "Headers/Global.h"

View::View(sf::RenderWindow* window, const sf::Vector2u& mapSizeInTiles)
  : m_window(window),
  x(0),
  y(0)
{
  m_view.setSize(SCREEN_WIDTH, SCREEN_HEIGHT);
  m_view.setCenter(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f);

  m_halfWidth = m_view.getSize().x / 2.0f;
  m_halfHeight = m_view.getSize().y / 2.0f;

  float mapWidth = mapSizeInTiles.x * CELL_SIZE;
  float mapHeight = mapSizeInTiles.y * CELL_SIZE;

  m_minX = m_halfWidth;
  m_maxX = mapWidth - m_halfWidth;
  m_minY = m_halfHeight;
  m_maxY = mapHeight - m_halfHeight;
}

void View::Update(const sf::Vector2f& targetPosition)
{
  x = std::clamp(targetPosition.x, m_minX, m_maxX);
  y = std::clamp(targetPosition.y, m_minY, m_maxY);
  m_view.setCenter(x, y);
  m_window->setView(m_view);
}
void View::ResetView()
{
  m_view.setCenter(m_minX, m_minY);
  m_window->setView(m_view);
}
const sf::Vector2f View::GetView() const
{
  return sf::Vector2f(x, y);
}
