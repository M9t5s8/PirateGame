#include "Headers/Animation.h"

Animation::Animation()
	:totalTime(0.0f),
	currentFrame(0),
	isCompleted(true)
{

}
Animation::~Animation()
{

}

void Animation::setAnimation(float deltatime, sf::Sprite& sprite, sf::Vector2f frameDimension, int rowIndex, int totalFrame, float frameTime, bool isLoop)
{
  if (totalFrame < 1) {
    sprite.setTextureRect(sf::IntRect(0, rowIndex * static_cast<int>(frameDimension.y),
      static_cast<int>(frameDimension.x), static_cast<int>(frameDimension.y)));
    return;
  }

  totalTime += deltatime;

  if (totalTime >= frameTime) {
    totalTime = 0.0f;
    currentFrame++;

    if (currentFrame >= totalFrame) {
      if (!isLoop) {
        currentFrame = totalFrame - 1; 
        isCompleted = true;
        return;
      }
      else {
        currentFrame = 0;
      }
    }
    else
    {
      if (!isLoop)
      {
        isCompleted = false;
      }
      else
      {
        isCompleted = true;
      }
    }
    sprite.setTextureRect(sf::IntRect(currentFrame * static_cast<int>(frameDimension.x),
      rowIndex * static_cast<int>(frameDimension.y),
      static_cast<int>(frameDimension.x), static_cast<int>(frameDimension.y)));
  }
}

void Animation::reset()
{
  currentFrame = 0;    
  totalTime = 0.0f;    
  isCompleted = false; 
}
bool Animation::isFinished()
{
	return isCompleted;
}
void Animation::Update()
{

}