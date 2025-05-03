#pragma once
#include "Global.h"
#include "EnemyManager.h"
#include "Textures.h"

class Map
{
private:
	sf::Sprite mapSprite, mapManagerSprites,playingBgSprite;
	sf::Sprite bigcloudSprite,smallCloudSprite;
	sf::Sprite spikeSprite;
	sf::Sprite Sprite;
	sf::RectangleShape shape;
	int mapWidth, mapHeight;
	std::vector<sf::Sprite> tileSprites;
	std::vector<sf::Sprite> spikes;
	std::vector<sf::Sprite> waters;
	EnemyManager* enemymanager;
	struct WaterTile {
		sf::Sprite sprite;
		int frameOffset;
	};
	std::vector<WaterTile> waterTiles;


	float waterAnimationTimer = 0.0f;
	int waterCurrentFrame = 0;

	const float WATER_FRAME_DURATION = 0.25f;
	const int WATER_TOTAL_FRAMES = 4;
	const int WATER_FRAME_WIDTH = 32;
	const int WATER_FRAME_HEIGHT = 32;


public:
	Map();
	virtual ~Map();
	sf::Vector2u Map_Details();
	void ConverttoMap(MAP&);
	void Update(float, MAP& , sf::Vector2f);
	void UpdateWaterAnimation(float);
	void Draw(sf::RenderTarget&);
};

