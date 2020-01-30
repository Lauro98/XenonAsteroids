#include "Projectile.h"
#include "Definitions.h"
#include <cmath>

Projectile::Projectile(TextureManager& textureManager, const sf::Sprite& shooter, bool playerShot) {
    this->playerShot = playerShot;
    if(playerShot) {
        sprite.setTexture(textureManager.getTextureFromAtlas("projectile"));
        animation = {sprite, 0, 0, PROJECTILE_SPRITE_WIDTH, PROJECTILE_SPRITE_HEIGHT, PROJECTILE_SPRITESHEET, PROJECTILE_ANIM_SPEED};
        type = EntityType::projectile;
    }
    else {
        sprite.setTexture(textureManager.getTextureFromAtlas("alien_ammo"));
        animation = {sprite, 0, 0, ALIEN_PROJECTILE_SPRITE_WIDTH, ALIEN_PROJECTILE_SPRITE_HEIGHT, ALIEN_PROJECTILE_SPRITESHEET, ALIEN_PROJECTILE_ANIM_SPEED};
        type = EntityType::alien_ammo;
    }
    sprite.setOrigin((float)sprite.getLocalBounds().width/2, (float)sprite.getLocalBounds().height/2);
    xPos = shooter.getPosition().x;
    yPos = shooter.getPosition().y;
    dx = 0;
    dy = 0;
    angle = shooter.getRotation()-90;
    alive = true;
}

void Projectile::update() {
    animation.update(sprite);
    if(playerShot) {
        dx = (float) cos(angle * RADIANS) * PROJECTILE_SPEED;
        dy = (float) sin(angle * RADIANS) * PROJECTILE_SPEED;
    }
    else{
        dx = (float) cos(angle * RADIANS) * ALIEN_PROJECTILE_SPEED;
        dy = (float) sin(angle * RADIANS) * ALIEN_PROJECTILE_SPEED;
    }
    xPos += dx;
    yPos += dy;
    if((xPos < 0) || (xPos > WINDOW_WIDTH) || (yPos < 0) || (yPos > WINDOW_HEIGHT))
        alive = false;
}