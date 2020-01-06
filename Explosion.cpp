#include "Explosion.h"
#include "Definitions.h"

Explosion::Explosion(TextureManager& textureManager, Entity& entity) {
    dx=0;
    dy=0;
    angle = 0;
    alive=true;

    sprite.setOrigin(0,0);
    xPos = entity.getSprite().getPosition().x + ROCK_SPRITE_WIDTH*2;
    yPos = entity.getSprite().getPosition().y - ROCK_SPRITE_HEIGTH*2;
    sprite.setTexture(textureManager.getTextureFromAtlas("explosion"));
    if(entity.getType() != EntityType::spaceship)
        animation = {sprite, 0, 0, EXPLOSION_SPRITE_WIDTH, EXPLOSION_SPRITE_HEIGHT, EXPLOSION_SPRITESHEET, NORMAL_EXPLOSION_ANIM_SPEED};
    else
        animation = {sprite, 0, 0, EXPLOSION_SPRITE_WIDTH, EXPLOSION_SPRITE_HEIGHT, EXPLOSION_SPRITESHEET, SLOW_EXPLOSION_ANIM_SPEED};

}

void Explosion::update() {
    if(animation.isAnimEnded()) {
        animation = {sprite, 0, 0, 0, 0, 1, 0};
        alive = false;
    }
}