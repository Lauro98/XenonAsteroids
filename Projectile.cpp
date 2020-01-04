#include "Projectile.h"
#include "Definitions.h"
#include <cmath>

Projectile::Projectile(TextureManager& textureManager, Spaceship& spaceship) {
    sprite.setTexture(textureManager.getTextureFromAtlas("projectile"));
    animation = {sprite, 0, 0, PROJECTILE_SPRITE_WIDTH, PROJECTILE_SPRITE_HEIGHT, PROJECTILE_SPRITESHEET, PROJECTILE_ANIM_SPEED};
    sprite.setOrigin(spaceship.getSprite().getOrigin());
    xPos = spaceship.getSprite().getLocalBounds().width/2 - sprite.getLocalBounds().width/2 + spaceship.getSprite().getPosition().x;
    yPos = abs(spaceship.getSprite().getPosition().y);
    angle = spaceship.getAngle();
    hp=1;
    type = EntityType::projectile;
}

void Projectile::updatePosition() {
    dx = (float)cos(angle*RADIANS)*7;
    dy = (float)sin(angle*RADIANS)*7;
    xPos += dx;
    yPos += dy;

    if((xPos < 0) || (xPos > WINDOW_WIDTH) || (yPos < 0) || (yPos > WINDOW_HEIGHT))
        hp = 0;
}