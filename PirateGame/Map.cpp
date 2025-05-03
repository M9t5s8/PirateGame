#include "Headers/Map.h"

Map::Map()
  : mapWidth(0),
  mapHeight(0)
{
  mapSprite.setTexture(Textures::mapTexture);
  mapManagerSprites.setTexture(Textures::map_managerTexture);
  playingBgSprite.setTexture(Textures::playingBackgroundTexture);
  bigcloudSprite.setTexture(Textures::bigCloud);
  smallCloudSprite.setTexture(Textures::smallCloud);
  spikeSprite.setTexture(Textures::spikeTexture);
;
  playingBgSprite.setOrigin(playingBgSprite.getLocalBounds().width / 2.f,
    playingBgSprite.getLocalBounds().height / 2.f);
  sf::Vector2u textureSize = playingBgSprite.getTexture()->getSize();
  float scaleX = static_cast<float>(SCREEN_WIDTH) / textureSize.x;
  float scaleY = static_cast<float>(SCREEN_HEIGHT) / textureSize.y;
  playingBgSprite.setScale(scaleX, scaleY);
  enemymanager = new EnemyManager();
}
Map::~Map()
{
  delete enemymanager;
}

sf::Vector2u Map::Map_Details()
{
  return (Textures::mapTexture.getSize());
}

void Map::ConverttoMap(MAP& map)
{
  sf::Image mapImage = Textures::mapTexture.copyToImage(); // Get the image from the texture
  tileSprites.clear();   
  spikes.clear();
  waters.clear();
  waterTiles.clear();

  for (unsigned int y = 0; y < mapImage.getSize().y; ++y)
  {
    for (unsigned int x = 0; x < mapImage.getSize().x; ++x)
    {
      sf::Color pixelColor = mapImage.getPixel(x, y);
      int redValue = pixelColor.r;     
      int greenValue = pixelColor.g;
      int blueValue = pixelColor.b;

      if (redValue >= 0 && redValue <= 47)
      {
        int row = redValue % 12;
        int col = redValue / 12;

        mapManagerSprites.setTextureRect(sf::IntRect(row * CELL_SIZE, col * CELL_SIZE, CELL_SIZE, CELL_SIZE));
        mapManagerSprites.setPosition(x * CELL_SIZE, y * CELL_SIZE);
        
        tileSprites.push_back(mapManagerSprites);

        if (redValue == 11)
        {
          map[x][y] = CELL_TYPE::EMPTY;
        }
        else
        {
          map[x][y] = CELL_TYPE::FLOOR;
        }
        if (greenValue < 3)
        {
          enemymanager->setEnemy(greenValue, sf::Vector2f(x, y));
        }
        if (blueValue == 4)
        {
          spikeSprite.setPosition(x * CELL_SIZE, y * CELL_SIZE);
          spikes.push_back(spikeSprite);
        }
        if (greenValue == 100)
        {
          PlayerPosition = sf::Vector2f(x * CELL_SIZE, y * CELL_SIZE);
        }
      }
      switch (redValue)
      {
      case 48:
      {
        WaterTile tile;
        tile.sprite.setTexture(Textures::animatedWaterTexture);
        tile.sprite.setTextureRect(sf::IntRect(0, 0, WATER_FRAME_WIDTH, WATER_FRAME_HEIGHT));
        tile.sprite.setPosition(x * CELL_SIZE, y * CELL_SIZE);

        // Set offset based on position (simple example: x + y)
        tile.frameOffset = (x + y) % WATER_TOTAL_FRAMES;

        waterTiles.push_back(tile);
        map[x][y] = CELL_TYPE::ANIWATER;

        break;
      }
      case 49:
      {
        Sprite.setTexture(Textures::waterTexture);
        Sprite.setPosition(x * CELL_SIZE, y * CELL_SIZE);
        waters.push_back(Sprite);
        map[x][y] = CELL_TYPE::WATER;
        break;
      }
      default:
        break;
      }
      
      
    }
  }
}

void Map::UpdateWaterAnimation(float deltaTime)
{
  waterAnimationTimer += deltaTime;

  if (waterAnimationTimer >= WATER_FRAME_DURATION)
  {
    waterAnimationTimer = 0.0f;
    waterCurrentFrame = (waterCurrentFrame + 1) % WATER_TOTAL_FRAMES;
  }

  // Always update each tile’s frame using offset
  for (auto& tile : waterTiles)
  {
    int frame = (waterCurrentFrame + tile.frameOffset) % WATER_TOTAL_FRAMES;
    tile.sprite.setTextureRect(sf::IntRect(
      frame * WATER_FRAME_WIDTH, 0, WATER_FRAME_WIDTH, WATER_FRAME_HEIGHT
    ));
  }
}



void Map::Update(float deltatime , MAP& i_map , sf::Vector2f viewPos)
{
  playingBgSprite.setPosition(viewPos.x, viewPos.y);
  this->UpdateWaterAnimation(deltatime);
  enemymanager->Update(deltatime, i_map);
  
}
void Map::Draw(sf::RenderTarget& target)
{
  target.draw(playingBgSprite);
  
  for (auto& sprite : tileSprites)
  {
    target.draw(sprite);
  }
  for (auto& sprite : spikes)
  {
    target.draw(sprite);
  }
  for (auto& tile : waterTiles)
  {
    target.draw(tile.sprite);
  }
  for (auto& sprite : waters)
  {
    target.draw(sprite);
  }
  
  enemymanager->Draw(target);
  
}
