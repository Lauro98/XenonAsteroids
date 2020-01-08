#include "Entity.h"

void Entity::draw(sf::RenderWindow &gameWindow) {
    sprite.setOrigin(sprite.getLocalBounds().width/2,sprite.getLocalBounds().height/2);
    sprite.setPosition(xPos, yPos);
    sprite.setRotation(angle+90);
    gameWindow.draw(sprite);
}

Animation &Entity::getAnimation() {
    return animation;
}

sf::Sprite &Entity::getSprite() {
    return sprite;
}

float Entity::getAngle() {
    return angle;
}

EntityType Entity::getType() {
    return type;
}

bool Entity::isAlive() {
    return alive;
}

void Entity::terminate() {
    alive = false;
}