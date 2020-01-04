#include <random>
#include "Asteroid.h"
#include "Definitions.h"

Asteroid::Asteroid(TextureManager& textureManager) {
    hp=1;
    angle=0;

    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> initPos(0, 3);
    std::uniform_int_distribution<int> distX(0, WINDOW_WIDTH);
    std::uniform_int_distribution<int> distY(0, WINDOW_HEIGHT);
    switch ((int)initPos(gen)){
        case 0:
            xPos = 0;
            yPos=(float)(distY(gen));
            break;
        case 1:
            xPos = (float)WINDOW_WIDTH;
            yPos=(float)(distY(gen));
            break;
        case 2:
            xPos=(float)(distX(gen));
            yPos = 0;
            break;
        case 3:
            xPos=(float)(distX(gen));
            yPos = (float)WINDOW_HEIGHT;
            break;
    }

    sprite.setTexture(textureManager.getTextureFromAtlas("rock"));
    animation = {sprite, 0, 0, ROCK_SPRITE_WIDTH, ROCK_SPRITE_HEIGTH, ROCK_SPRITESHEET, ROCK_ANIM_SPEED};

    std::uniform_int_distribution<float> distSpeedX(-4,4);
    std::uniform_int_distribution<float> distSpeedY(-4,4);


    dx = (float)(distSpeedX(gen));
    dy = (float)(distSpeedY(gen));

    type = EntityType::asteroid;
}

Asteroid::Asteroid(TextureManager &textureManager, Entity &asteroid) {
    hp=1;
    angle=0;

    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<float> distSpeedX(-3,5);
    std::uniform_int_distribution<float> distSpeedY(-3,5);


    dx = (float)(distSpeedX(gen));
    dy = (float)(distSpeedY(gen));
    sprite.setTexture(textureManager.getTextureFromAtlas("rock_small"));
    animation = {sprite, 0, 0, ROCK_SPRITE_WIDTH, ROCK_SPRITE_HEIGTH, ROCK_SPRITESHEET, ROCK_ANIM_SPEED};

    xPos=asteroid.getXPos();
    yPos=asteroid.getYPos();
    dx = (float)(distSpeedX(gen));
    dy = (float)(distSpeedY(gen));

    type = EntityType::rubble;
}

void Asteroid::updatePosition() {
    xPos += dx;
    yPos += dy;

    if(xPos>(float)WINDOW_WIDTH)
        xPos = 0;
    if(xPos<0)
        xPos = (float)WINDOW_WIDTH;

    if(yPos>(float)WINDOW_HEIGHT)
        yPos = 0;
    if(yPos<0)
        yPos = (float)WINDOW_HEIGHT;
}