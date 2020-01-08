#include "Explosion.h"
#include "Definitions.h"

Explosion::Explosion(TextureManager& textureManager, Entity& entity) {
    dx = 0;
    dy = 0;
    angle = -90;
    alive = true;
    xPos = entity.getSprite().getPosition().x;
    yPos = entity.getSprite().getPosition().y;
    sprite.setPosition(xPos, yPos);
    sprite.setTexture(textureManager.getTextureFromAtlas("explosion"));
    if(entity.getType() != EntityType::spaceship)
        animation = {sprite, 0, 0, EXPLOSION_SPRITE_WIDTH, EXPLOSION_SPRITE_HEIGHT, EXPLOSION_SPRITESHEET, NORMAL_EXPLOSION_ANIM_SPEED};
    else
        animation = {sprite, 0, 0, EXPLOSION_SPRITE_WIDTH, EXPLOSION_SPRITE_HEIGHT, EXPLOSION_SPRITESHEET, SLOW_EXPLOSION_ANIM_SPEED};

}

void Explosion::update() {
    animation.update(sprite);
    if(animation.isAnimEnded()) {
        animation = {sprite, 0, 0, 0, 0, 1, 0};
        alive = false;
    }
}