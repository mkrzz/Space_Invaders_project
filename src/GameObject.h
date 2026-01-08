#include <SFML/Graphics.hpp>
#include "vector2.h"

#ifndef SPACEINVADERS_GAMEOBJECT_H
#define SPACEINVADERS_GAMEOBJECT_H

class GameObject
{
 public:
  GameObject();
  ~GameObject();

  bool initialiseSprite(sf::Texture& texture, std::string filename);

  sf::Sprite* getSprite() const;

  void moveObject(Vector2 velocity);

  void moveShip(float dx, float dy);

  void addTexture(sf::Texture& texture);

  Vector2 getDirection();
  Vector2 getPosition() const; 

  void setDirection(Vector2 value);

  bool isActive = true;
  
  bool destroyed = false;

  void setDestroyed(bool value)
  {
    destroyed = value; // Set the flag
  }

  bool isDestroyed() const
  {
    return destroyed; // Check if the object is destroyed
  }

  private:
  sf::Sprite* sprite;
   Vector2 direction{ 0, 0 };
};
	




#endif // SPACEINVADERS_GAMEOBJECT_H
