#include<iostream>
#include <SFML/Graphics.hpp>

class Animation {
private:
  int currentFrame;
  float totalTime;
  bool isCompleted;
public:
  Animation();
  virtual ~Animation();
  void Update();
  void setAnimation(float,sf::Sprite& , sf::Vector2f ,int,int ,float , bool toLoop = true );
  bool isFinished();
  void reset();
};
