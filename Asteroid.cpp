#include <random>
#include "Asteroid.h"

Asteroid::Asteroid(TextureManager& textureManager) {
    hp=1;
    angle=0;

    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::uniform_int_distribution<int> distX(0, sf::VideoMode::getDesktopMode().width);
    std::uniform_int_distribution<int> distY(0, sf::VideoMode::getDesktopMode().height);
    std::uniform_int_distribution<int> distSpeed(-4,4);


    sprite.setTexture(textureManager.getTextureFromAtlas("rock"));
    animation = {sprite, 0, 0, 64, 64, 16, 0.2};

    xPos=(float)(distX(gen));
    yPos=(float)(distY(gen));
    dx = (float)(distSpeed(gen));
    dy = (float)(distSpeed(gen));

    type = EntityType::asteroid;
}

Asteroid::Asteroid(TextureManager &textureManager, Entity &asteroid) {
    hp=1;
    angle=0;

    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distSpeed(-3,5);

    sprite.setTexture(textureManager.getTextureFromAtlas("rock_small"));
    animation = {sprite, 0, 0, 64, 64, 16, 0.2};

    xPos=asteroid.getXPos();
    yPos=asteroid.getYPos();
    dx = (float)(distSpeed(gen));
    dy = (float)(distSpeed(gen));

    type = EntityType::rubble;
}

void Asteroid::updatePosition() {
    xPos += dx;
    yPos += dy;

    if(xPos>(float)sf::VideoMode::getDesktopMode().width)
        xPos = 0;
    if(xPos<0)
        xPos = (float)sf::VideoMode::getDesktopMode().width;

    if(yPos>(float)sf::VideoMode::getDesktopMode().height)
        yPos = 0;
    if(yPos<0)
        yPos = (float)sf::VideoMode::getDesktopMode().height;
}