
#ifndef SPACEINVADERS_GAME_H
#define SPACEINVADERS_GAME_H

#include <SFML/Graphics.hpp>
#include "Vector2.h"
#include "GameObject.h"
#include <SFML/Audio.hpp>

class Game
{
 public:
  Game(sf::RenderWindow& window);
  ~Game();
  bool init();
  void update(float dt);
  void render();
  void mouseClicked(sf::Event event);
  void keyPressed(sf::Event event);

 
 private:
  sf::RenderWindow& window;
  
  GameObject ship;
  GameObject aliens[32];
  GameObject shots[10];

  sf::Font space_invaders_font;
  sf::Font start_font;
  sf::Font score_font;
  sf::Text title_text;
  sf::Text start_text;
  sf::Text score_text;
  

  sf::Texture blue_enemy_texture;
  sf::Texture black_enemy_texture;
  sf::Texture green_enemy_texture;
  sf::Texture red_enemy_texture;
  
  sf::SoundBuffer laserShootBuffer;
  sf::Sound laserShootSound;
  sf::SoundBuffer alienShipBuffer;
  sf::Sound alienExplosionSound;

  sf::Texture menu_background;
  sf::Sprite menuBackground;
  sf::Texture game_background;
  sf::Sprite gameBackground;

  sf::Texture ship_texture;
  sf::Texture bullet_texture;

  //int grid_size = 25;
  int columns        = 8;
  int rows           = 4;
  int current_shot_number = 0;
  int numAliens           = rows * columns;
  int score = 0;

  float screen_width = 1080.0f;
  float screen_height = 720.0f;
  float ship_speed   = 500.0f;
  float bulletSpeed   = 500.0f;

  bool in_menu = true;
  bool reverse = false;
  bool hasWon  = false;
  bool hasLost = false;
  bool is_running;

  void updateAliens(
  GameObject aliens[], int numAliens, float deltaTime, float screenWidth);
  void updateShots(float dt); 
  bool checkCollision(const GameObject& shot, const GameObject& alien);
  bool allAliensDead();
  bool checkLossCondition();
  void renderWinMessage();
  void renderLoseMessage();
  void resetGame();
  void updateCollisions();

  
};

#endif // SPACEINVADERS_GAME_H
