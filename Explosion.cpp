#include "Explosion.h"
#include "Definitions.h"

Explosion::Explosion(TextureManager& textureManager, Entity& entity) {
    dx=0;
    dy=0;
    angle = 0;
    hp=1;

    sprite.setOrigin(0,0);
    xPos = entity.getXPos()+ROCK_SPRITE_WIDTH*2;
    yPos = entity.getYPos()-ROCK_SPRITE_HEIGTH*2;
    sprite.setTexture(textureManager.getTextureFromAtlas("explosion"));
    if(entity.getType() != EntityType::spaceship)
        animation = {sprite, -EXPLOSION_SPRITE_WIDTH, 0, EXPLOSION_SPRITE_WIDTH, EXPLOSION_SPRITE_HEIGHT, EXPLOSION_SPRITESHEET, NORMAL_EXPLOSION_ANIM_SPEED};
    else
        animation = {sprite, -EXPLOSION_SPRITE_WIDTH, 0, EXPLOSION_SPRITE_WIDTH, EXPLOSION_SPRITE_HEIGHT, EXPLOSION_SPRITESHEET, SLOW_EXPLOSION_ANIM_SPEED};

}

void Explosion::updatePosition() {
    if(animation.isEndOfAnim()) {
        animation = {sprite, 0, 0, 0, 0, 1, 0};
        hp = 0;
    }
}