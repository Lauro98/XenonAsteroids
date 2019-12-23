#include "Explosion.h"

Explosion::Explosion(TextureManager& textureManager, Entity& entity) {
    dx=0;
    dy=0;
    angle = 0;
    hp=1;

    sprite.setOrigin(0,0);
    xPos = entity.getXPos()+100;
    yPos = entity.getYPos()-50;
    sprite.setTexture(textureManager.getTextureFromAtlas("explosion"));
    if(entity.getType() != EntityType::spaceship)
        animation = {sprite, -256, 0, 256, 256, 48, 1};
    else
        animation = {sprite, -256, 0, 256, 256, 48, 0.25};

}

void Explosion::updatePosition() {
    if(animation.isEndOfAnim()) {
        animation = {sprite, 0, 0, 0, 0, 1, 0};
        hp = 0;
    }
}