#include "Projectile.h"
#include <cmath>

Projectile::Projectile(TextureManager& textureManager, Spaceship& spaceship) {
    sprite.setTexture(textureManager.getTextureFromAtlas("projectile"));
    animation = {sprite, 0, 0, 32, 64, 16, 1};
    sprite.setOrigin(spaceship.getSprite().getOrigin());
    xPos = spaceship.getSprite().getLocalBounds().width/2 - sprite.getLocalBounds().width/2 + spaceship.getSprite().getPosition().x;
    yPos = abs(spaceship.getSprite().getPosition().y);
    angle = spaceship.getAngle();
    hp=1;
    type = EntityType::projectile;
}

void Projectile::updatePosition() {
    dx = (float)cos(angle*radians)*7;
    dy = (float)sin(angle*radians)*7;
    xPos += dx;
    yPos += dy;

    if((xPos < 0) || (xPos > (float)sf::VideoMode::getDesktopMode().width) || (yPos < 0) || (yPos > (float)sf::VideoMode::getDesktopMode().height))
        hp = 0;
}