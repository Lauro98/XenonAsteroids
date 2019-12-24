#include <random>
#include "Asteroid.h"

Asteroid::Asteroid(TextureManager& textureManager) {
    hp=1;
    angle=0;

    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> initPos(0, 3);
    std::uniform_int_distribution<int> distX(0, 1280);
    std::uniform_int_distribution<int> distY(0, 800);
    switch ((int)initPos(gen)){
        case 0:
            xPos = 0;
            yPos=(float)(distY(gen));
            break;
        case 1:
            xPos = 1280;
            yPos=(float)(distY(gen));
            break;
        case 2:
            xPos=(float)(distX(gen));
            yPos = 0;
            break;
        case 3:
            xPos=(float)(distX(gen));
            yPos = 800;
            break;
    }

    sprite.setTexture(textureManager.getTextureFromAtlas("rock"));
    animation = {sprite, 0, 0, 64, 64, 16, 0.2};

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
    animation = {sprite, 0, 0, 64, 64, 16, 0.2};

    xPos=asteroid.getXPos();
    yPos=asteroid.getYPos();
    dx = (float)(distSpeedX(gen));
    dy = (float)(distSpeedY(gen));

    type = EntityType::rubble;
}

void Asteroid::updatePosition() {
    xPos += dx;
    yPos += dy;

    if(xPos>1280)
        xPos = 0;
    if(xPos<0)
        xPos = 1280;

    if(yPos>800)
        yPos = 0;
    if(yPos<0)
        yPos = 800;
}