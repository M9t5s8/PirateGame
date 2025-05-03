#include "Headers/Textures.h"
#include <iostream>

namespace Textures {
  sf::Texture playerTexture ;
  sf::Texture mapTexture;
  sf::Texture map_managerTexture;
  sf::Texture menuBackgroundTexture;
  sf::Texture backgroundTexture;
  sf::Texture Menubutton;
  sf::Texture pauseBackgroundTexture;
  sf::Texture sharkTexture;
  sf::Texture starfishTexture;
  sf::Texture crabTexture;
  sf::Texture playingBackgroundTexture;
  sf::Texture bigCloud;
  sf::Texture smallCloud;
  sf::Texture spikeTexture;
  sf::Texture waterTexture;
  sf::Texture animatedWaterTexture;

  void loadAll() {
    playerTexture.loadFromFile("Resources/player_sprites.png");
    //mapTexture.loadFromFile("Resources/level_one_data.png");
    //mapTexture.loadFromFile("Resources/level_one_data_long.png");
    mapTexture.loadFromFile("Resources/lvls/1.png");
    map_managerTexture.loadFromFile("Resources/outside_sprites.png");
    menuBackgroundTexture.loadFromFile("Resources/menu_background.png");
    backgroundTexture.loadFromFile("Resources/background_menu.png");
    Menubutton.loadFromFile("Resources/button_atlas.png");
    pauseBackgroundTexture.loadFromFile("Resources/pause_menu.png");
    sharkTexture.loadFromFile("Resources/shark_atlas.png");
    starfishTexture.loadFromFile("Resources/pinkstar_atlas.png");
    crabTexture.loadFromFile("Resources/crabby_sprite.png");
    playingBackgroundTexture.loadFromFile("Resources/playing_bg_img.png");
    bigCloud.loadFromFile("Resources/big_clouds.png");
    smallCloud.loadFromFile("Resources/small_clouds.png");
    spikeTexture.loadFromFile("Resources/trap_atlas.png");
    waterTexture.loadFromFile("Resources/water.png");
    animatedWaterTexture.loadFromFile("Resources/water_atlas_animation.png");
  }
}