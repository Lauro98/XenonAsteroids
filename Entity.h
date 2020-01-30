#ifndef XENON_ENTITY_H
#define XENON_ENTITY_H
#include <SFML/Graphics/RenderWindow.hpp>
#include "Animation.h"
#include "TextureManager.h"

enum class EntityType {spaceship, asteroid, rubble, projectile, alien_ammo, alien};

class Entity{
public:
    virtual ~Entity() = default;
    virtual void update() = 0;
    virtual void draw(sf::RenderWindow &gameWindow);
    void terminate();
    Animation& getAnimation();
    sf::Sprite& getSprite();
    bool isAlive();
    float getAngle();
    EntityType getType();
protected:
    sf::Sprite sprite;
    float xPos, yPos;
    float dx, dy;
    float angle;
    bool alive;
    Animation animation;
    EntityType type;
};

#endif