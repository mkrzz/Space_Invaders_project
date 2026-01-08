#include "GameObject.h"
#include <iostream>
#include "Game.h"

GameObject::GameObject() 
 {
  sprite = new sf::Sprite();
   isActive = true;
 }

GameObject::~GameObject()
 {
   delete sprite;
 }

 bool GameObject::initialiseSprite(sf::Texture& texture, std::string filename)
{
  sprite->setTexture(texture);
  return true;
}

sf::Sprite* GameObject::getSprite() const
{
  return sprite;
}

void GameObject::moveShip(float dx, float dy)
{
  sprite->move(dx, dy);
}

void GameObject::addTexture(sf::Texture& texture) 
{
  sprite->setTexture(texture);
}

Vector2 GameObject::getDirection()
{
  return direction;
}

void GameObject::setDirection(Vector2 value) 
{
  direction = value;
}


void GameObject::moveObject(Vector2 velocity)
{
  sprite->move(velocity.x, velocity.y);
}

Vector2 GameObject::getPosition() const
{
  sf::Vector2f position = sprite->getPosition();
  return Vector2(position.x, position.y); 
}