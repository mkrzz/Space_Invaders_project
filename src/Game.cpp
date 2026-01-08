#include <SFML/Graphics.hpp>
#include "Game.h"
#include <iostream>
#include "Vector2.h"
#include "GameObject.h"
#include <SFML/Audio.hpp>

Game::Game(sf::RenderWindow& game_window)
  : window(game_window)
{
  srand(time(NULL));
}

Game::~Game()
{

}

bool Game::init()
{
  in_menu = true;

  //menu text file
  if (!space_invaders_font.loadFromFile("../Data/Fonts/Transcorner.ttf"))
  {
    std::cout << "Font did not load";
  }

  //menu text file 2
  if (!start_font.loadFromFile("../Data/Fonts/Thamire.ttf"))
  {
    std::cout << "Font did not load";
  }

  //background image file
  if (!menu_background.loadFromFile("../Data/Images/SpaceShooterRedux/Backgrounds/purple.png"))
  {
    std::cout << "Texture did not load";
  }
  
  //background image file 2 
  if (!game_background.loadFromFile("../Data/Images/SpaceShooterRedux/"
                                    "Backgrounds/darkPurple.png"))
  {
    std::cout << "Texture did not load";
  }

  //enemy texures
  if ((!red_enemy_texture.loadFromFile("../Data/Images/SpaceShooterRedux/PNG/Enemies/enemyRed3.png")) ||
      (!black_enemy_texture.loadFromFile("../Data/Images/SpaceShooterRedux/PNG/Enemies/enemyBlack1.png")) ||
          (!green_enemy_texture.loadFromFile("../Data/Images/SpaceShooterRedux/PNG/Enemies/enemyGreen2.png")) ||
      (!blue_enemy_texture.loadFromFile("../Data/Images/SpaceShooterRedux/PNG/Enemies/enemyBlue4.png")))
  {
      std::cout << "Enemy textures did not load";
  }
  
  //game background  
  sf::Vector2u gameTextureSize = game_background.getSize();
  sf::Vector2u windowSize(1080, 720);
  float gameScaleX = static_cast<float>(windowSize.x) / gameTextureSize.x;
  float gameScaleY = static_cast<float>(windowSize.y) / gameTextureSize.y;
  gameBackground.setTexture(game_background);
  gameBackground.setScale(gameScaleX, gameScaleY);

  //menu background
  sf::Vector2u menuTextureSize = menu_background.getSize();  
  float menuScaleX = static_cast<float>(windowSize.x) / menuTextureSize.x;
  float menuScaleY = static_cast<float>(windowSize.y) / menuTextureSize.y;
  menuBackground.setTexture(menu_background);
  menuBackground.setScale(menuScaleX, menuScaleY);

  //space invaders title text 
  title_text.setFont(space_invaders_font);
  title_text.setString("Space Invaders");
  title_text.setCharacterSize(80);
  title_text.setLetterSpacing(2);
  title_text.setFillColor(sf::Color::Black);
  title_text.setOutlineColor(sf::Color::Green);
  title_text.setOutlineThickness(2); 
  title_text.setPosition(
    window.getSize().x / 2 - title_text.getGlobalBounds().width / 2, 180); 

  //press enter menu font 
  start_text.setFont(start_font);
  start_text.setString("- Press enter to start -");
  start_text.setCharacterSize(50);
  start_text.setLetterSpacing(1);
  start_text.setFillColor(sf::Color::Black);
  start_text.setOutlineColor(sf::Color::Green);
  start_text.setOutlineThickness(2);    
  start_text.setPosition(
    window.getSize().x / 2 - start_text.getGlobalBounds().width / 2, 360);

  //load ship texture
  if (!ship_texture.loadFromFile("../Data/Images/SpaceShooterRedux/PNG/playerShip1_green.png"))
  {
    std::cout << "Texture did not load";
  }

  //initialise and set position of ship
  ship.initialiseSprite(
    ship_texture, "../Data/Images/SpaceShooterRedux/PNG/playerShip1_green.png");
  float shipWidth  = ship.getSprite()->getGlobalBounds().width;
  float shipHeight = ship.getSprite()->getGlobalBounds().height;
  ship.getSprite()->setPosition((1080 - shipWidth) / 2, 600);

  //bullet texture
  if (!bullet_texture.loadFromFile("../Data/Images/SpaceShooterRedux/PNG/Lasers/laserRed05.png"))
  {
    std::cout << "Bullet texture did not load" << std::endl;
  }

  // Load bullet texture
  if (!bullet_texture.loadFromFile("../Data/Images/SpaceShooterRedux/PNG/"
                                   "Lasers/laserRed05.png"))
  {
    std::cout << "Bullet texture did not load" << std::endl;
  }




  //laser sound
  if (!laserShootBuffer.loadFromFile("../Data/Sound/laserShoot.wav"))
  {
    std::cout << "Laser sound did not load!" << std::endl;
  }

  laserShootSound.setBuffer(laserShootBuffer);

  //explosion sound
  if (!alienShipBuffer.loadFromFile("../Data/Sound/explosion.wav"))
  {
    std::cout << "explosion sound did not load!" << std::endl;
  }

  //score font + positioning
  if (!score_font.loadFromFile("../Data/Fonts/Thamire.ttf"))
  {
    std::cout << "Font did not load for score display";
  }

  score_text.setFont(score_font);
  score_text.setCharacterSize(30);
  score_text.setFillColor(sf::Color::White);
  score_text.setPosition(10.f, 10.f); 

  alienExplosionSound.setBuffer(alienShipBuffer);



  //array of aliens  
  for (int i = 0; i < columns; i++)
  {
    for (int j = 0; j < rows; j++)
    {
      for (int j = 0; j < rows; j++) 
      {
        aliens[i * rows + j].getSprite()->setScale(0.6f, 0.6f);
      }


      if (j == 0)
      {
        aliens[i * rows + j].addTexture(red_enemy_texture);
      }
      else if (j == 1)
      {
        aliens[i * rows + j].addTexture(
          green_enemy_texture);
      }
      else if (j == 2) 
      {
        aliens[i * rows + j].addTexture(blue_enemy_texture);
      }
      else if (j == 3)
      {
        aliens[i * rows + j].addTexture(
          black_enemy_texture);
      }
      //alien positions
      aliens[i * rows + j].getSprite()->setPosition((i + 2.8) * 80, (j + 0.5) * 80);
    }
  }

  //array for lasers
  for (int i = 0; i < 10; ++i)
  {
    shots[i].initialiseSprite(
      bullet_texture,
      "../Data/Images/SpaceShooterRedux/PNG/Lasers/laserRed05.png");
    shots[i].getSprite()->setPosition(-100, -100); 
    shots[i].getSprite()->setScale(0.5f, 0.5f);    
  }

  
  

  return true;
}

void Game::update(float dt)
{
  if (!is_running)
  {
    return;
  }

  sf::Vector2 shipPos = ship.getSprite()->getPosition();

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
  {
    if (shipPos.x > 0)
    {
      ship.moveShip(-ship_speed * dt, 0);
    }
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
  {
    if (shipPos.x < screen_width - ship.getSprite()->getGlobalBounds().width)
    {
      ship.moveShip(ship_speed * dt, 0);
    }
  }

  updateAliens(aliens, 32, dt, screen_width);
  
  updateShots(dt);
  
  updateCollisions();

  //checks if player is hit, sets game to not running
  if (hasWon || hasLost)
  {
    is_running = false;
    return;
  }
  if (allAliensDead())
  {
    hasWon = true;
    is_running = false;
    return;
  }
  if (checkLossCondition())
  {
    hasLost = true;
    is_running = false;
    return;
  }

}



void Game::updateShots(float dt)
{
  for (int i = 0; i < 10; ++i)
  {
    if (!shots[i].isActive)
      continue; 

    // Move shot upwards
    Vector2 velocity = shots[i].getDirection() * bulletSpeed * dt;
    shots[i].moveObject(velocity);

    // If shot moves off the top of the screen
    if (shots[i].getPosition().y < 0)
    {
      shots[i].isActive = false;
    }

  }

  
}

//Updates collision detections on aliens and lasers + handles explosion sound
void Game::updateCollisions()
{
  for (int i = 0; i < 10; ++i)
  {
    if (!shots[i].isActive)
      continue;

    for (int j = 0; j < 32; ++j)
    {
      if (!aliens[j].isActive)
        continue;

      if (checkCollision(shots[i], aliens[j]))
      {
        //explosion sound
        alienExplosionSound.play();
        score += 50;
        shots[i].isActive  = false;
        aliens[j].isActive = false;
        shots[i].getSprite()->setPosition(-100, -100);
        aliens[j].getSprite()->setPosition(-100, -100);
        break;
      }
    }
  }
}


void Game::render()
{
    if (in_menu)
    {
      window.draw(menuBackground);
      window.draw(title_text);
      window.draw(start_text);  
    }

    else
    {
      window.draw(gameBackground);
      window.draw(*ship.getSprite());

      for (int i = 0; i < 32; i++)
      {
        if (aliens[i].isActive) 
        {
          window.draw(*aliens[i].getSprite());
        }
      }

      window.draw(score_text);
    }

    for (int i = 0; i < 10; ++i)
    {
      if (shots[i].getSprite()->getPosition().y >= 0) 
      {
        window.draw(*shots[i].getSprite());
      }
    }
    //win message
    if (hasWon)
    {
      renderWinMessage();
    }
    //lose message
    else if (hasLost)
    {
      renderLoseMessage();
    }

    //render score to screen
    score_text.setString("Score: " + std::to_string(score));
    
}

void Game::mouseClicked(sf::Event event)
{
  //get the click position
  sf::Vector2i click = sf::Mouse::getPosition(window);


}

void Game::keyPressed(sf::Event event)
{
    if (event.key.code == sf::Keyboard::Enter)
    {
      if (in_menu || hasWon || hasLost)
        {
          resetGame();
        }
    }

    // Fire a bullet
    if (event.key.code == sf::Keyboard::Space) 
    {
        //laser sound
        laserShootSound.play();

      // Get the next shot in the array
      GameObject& bullet = shots[current_shot_number];

      //set the position of the bullet above the ship
      sf::Vector2f shipPos = ship.getSprite()->getPosition();
      bullet.getSprite()->setPosition(
        shipPos.x + ship.getSprite()->getGlobalBounds().width / 2 -
          bullet.getSprite()->getGlobalBounds().width / 2,
        shipPos.y - 10);

      //make the bullet visible
      bullet.getSprite()->setColor(sf::Color::White); 

      // Set bullet's direction to move upwards
      bullet.setDirection(Vector2(0, -1));

      bullet.isActive     = true;

      current_shot_number = (current_shot_number + 1) % 10; 
    }
}

void Game::updateAliens(
  GameObject aliens[], int numAliens, float deltaTime, float screenWidth)
{
    //alien direction
  static Vector2 direction(1.f, 0.f); 
  
  // Alien speed
  float speed = 175.f;                 

  bool hitEdge = false;

  // Check if active alien hits the edge of the screen
  for (int i = 0; i < numAliens; i++)
  {
    if (!aliens[i].isActive)
      continue; 

    float alienRight = aliens[i].getSprite()->getPosition().x +
                       aliens[i].getSprite()->getGlobalBounds().width;
    float alienLeft = aliens[i].getSprite()->getPosition().x;

    if (
      (direction.x > 0 && alienRight >= screenWidth) ||
      (direction.x < 0 && alienLeft <= 0))
    {
      hitEdge = true;
      break; 
    }
  }

  // If any alien hits the edge, reverse direction and move all aliens down
  if (hitEdge)
  {
    // Reverse horizontal direction
    direction.x *= -1;  
    // Move aliens down
    direction.y = 10.f; 
  }
  else
  {
    direction.y = 0.f; 
  }

  // Move all active aliens
  for (int i = 0; i < numAliens; i++)
  {
    if (!aliens[i].isActive)
      continue; 

    Vector2 movement = direction * (speed * deltaTime);
    aliens[i].moveShip(movement.x, movement.y); 
  }
}

//check if alien and laser collide based on bounding boxes
bool Game::checkCollision(const GameObject& shot, const GameObject& alien)
{
  //get bounding boxes
  sf::FloatRect shotBounds  = shot.getSprite()->getGlobalBounds();
  sf::FloatRect alienBounds = alien.getSprite()->getGlobalBounds();
  
  //collision check - checking if the lasers bounding box collides with the aliens bounding box
  return (
    shotBounds.left < alienBounds.left + alienBounds.width &&
    shotBounds.left + shotBounds.width > alienBounds.left &&
    shotBounds.top < alienBounds.top + alienBounds.height &&
    shotBounds.top + shotBounds.height > alienBounds.top);
}

// destroy aliens
bool Game::allAliensDead()
{
  for (int i = 0; i < 32; ++i)
  {
    if (aliens[i].isActive)
    {
      return false; 
    }
  }
  
  return true; 
}

//checks if alien ship hits player
bool Game::checkLossCondition()
{
  for (int i = 0; i < 32; ++i)
  {
    if (aliens[i].isActive && checkCollision(aliens[i], ship))
    {
      is_running = false;
      hasLost = true;
      return true; 
    }
  }
  return false;
}

//win message function
void Game::renderWinMessage()
{
  sf::Text winText;
  winText.setFont(start_font);
  winText.setString("You Win! Press Enter to Play Again");
  winText.setCharacterSize(50);
  winText.setFillColor(sf::Color::Green);
  winText.setPosition(
    window.getSize().x / 2 - winText.getGlobalBounds().width / 2,
    window.getSize().y / 2);
  window.draw(winText);
}

//lose message function
void Game::renderLoseMessage()
{
  sf::Text loseText;
  loseText.setFont(start_font);
  loseText.setString("You Lose! Press Enter to Try Again");
  loseText.setCharacterSize(50);
  loseText.setFillColor(sf::Color::Red);
  loseText.setPosition(
    window.getSize().x / 2 - loseText.getGlobalBounds().width / 2,
    window.getSize().y / 2);
  window.draw(loseText);
}


void Game::resetGame()
{
  // Reset all game objects 
  hasWon  = false;
  hasLost = false;
  in_menu = false;
  is_running = true;
  score      = 0;

  // Reset positions
  ship.getSprite()->setPosition(
    (1080 - ship.getSprite()->getGlobalBounds().width) / 2, 600);

  // Reset aliens and bullets
  for (int i = 0; i < 32; ++i)
  {
    aliens[i].isActive = true;
    
    //resets aliens into grid position
    float x = (i % 8) * 105 + 50; 
    float y = (i / 8) * 60 + 50; 
    aliens[i].getSprite()->setPosition(x, y);
  }
  for (int i = 0; i < 10; ++i)
  {
    shots[i].isActive = false;
    shots[i].getSprite()->setPosition(-100, -100);
  }
}

