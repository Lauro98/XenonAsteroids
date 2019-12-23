#include <iostream>
#include <utility>
#include "Entity.h"

void Entity::draw(sf::RenderWindow &gameWindow) {
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

unsigned int Entity::getHp() {
    return hp;
}

float Entity::getXPos() {
    return xPos;
}

float Entity::getYPos() {
    return yPos;
}

void Entity::setHp(unsigned int hitPoint) {
    if(hitPoint>1){
        std::cout << "error: max hp allowed is 1 while it received "<< hitPoint << "as input." << std::endl;
        std::cout << "error will be handled assigning 1 to hp." << std::endl;
    }
    else
        hp=hitPoint;
}

float Entity::getAngle() {
    return angle;
}

EntityType Entity::getType() {
    return type;
}

Entity::~Entity() {

}
