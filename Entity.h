#ifndef XENON_ENTITY_H
#define XENON_ENTITY_H

#include <SFML/Graphics/RenderWindow.hpp>
#include "Animation.h"
#include "TextureManager.h"



enum class EntityType {spaceship, asteroid, rubble, projectile};

class Entity{
protected:
    sf::Sprite sprite;
    float xPos, yPos;
    float dx, dy;
    float angle;
    unsigned int hp;
    Animation animation;
    EntityType type;
public:
    virtual ~Entity() = default;
    virtual void updatePosition() = 0;
    void draw(sf::RenderWindow &gameWindow);
    void setHp(unsigned int hp);
    Animation& getAnimation();
    sf::Sprite& getSprite();
    unsigned int getHp();
    float getXPos();
    float getYPos();
    float getAngle();
    EntityType getType();
};


#endif