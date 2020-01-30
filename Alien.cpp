#include <random>
#include "Alien.h"
#include "Definitions.h"
#include "Projectile.h"

Alien::Alien(TextureManager& textureManager) {
    shootClock.restart();
    alive = true;
    angle = -90;
    type = EntityType::alien;
    sprite.setTexture(textureManager.getTextureFromAtlas("alien"));
    sprite.setOrigin((float) sprite.getLocalBounds().width / 2, (float) sprite.getLocalBounds().height / 2);
    animation = {sprite, 0, 0, ALIEN_SPRITE_WIDTH, ALIEN_SPRITE_HEIGHT, ALIEN_SPRITESHEET, ALIEN_ANIM_SPEED};
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> initialPos(0, 3);
    std::uniform_int_distribution<int> x_pos(0, WINDOW_WIDTH);
    std::uniform_int_distribution<int> y_pos(0, WINDOW_HEIGHT);
    switch ((int)initialPos(gen)){
        case 0:
            xPos = 0;
            yPos = (float)(y_pos(gen));
            break;
        case 1:
            xPos = (float)WINDOW_WIDTH;
            yPos = (float)(y_pos(gen));
            break;
        case 2:
            xPos = (float)(x_pos(gen));
            yPos = 0;
            break;
        case 3:
            xPos = (float)(x_pos(gen));
            yPos = (float)WINDOW_HEIGHT;
            break;
    }
    dx = 0;
    dy = 0;
}

void Alien::update(TextureManager& textureManager, Spaceship& spaceship, std::vector<Entity*>& entities, SoundManager& soundManager) {
    dx=0;
    dy=0;
    destination = spaceship.getSprite().getPosition();
    angle = (float)(atan2((destination.y-sprite.getPosition().y), (destination.x-sprite.getPosition().x)));
    if(fabs(destination.x - sprite.getPosition().x) > TRIGGERING_DISTANCE || fabs(destination.y - sprite.getPosition().y) > TRIGGERING_DISTANCE) {
        if (sprite.getPosition().x != destination.x && sprite.getPosition().y != destination.y) {
            dx = (float) (cos(angle) * ALIEN_ACCEL);
            dy = (float) (sin(angle) * ALIEN_ACCEL);
        }
    }
    else
        if(shootClock.getElapsedTime().asSeconds() >= ALIEN_FIRE_RATE){
            entities.emplace_back(new Projectile(textureManager, sprite, false));
            shootClock.restart();
            soundManager.playShootSound();
        }
    angle /= RADIANS;
    xPos += dx;
    yPos += dy;
}