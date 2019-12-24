#include <SFML/Graphics/CircleShape.hpp>
#include "Spaceship.h"
#include "cmath"
#include "ToggableShield.h"
#include "TimeShield.h"
#include "NoneShield.h"

Spaceship::Spaceship() {
}


Spaceship::Spaceship(TextureManager& textureManager, ShipType shipType) {
    sprite.setOrigin(sprite.getLocalBounds().width/2,sprite.getLocalBounds().height/2);
    xPos=((float)1280 - sprite.getLocalBounds().width)/2;
    yPos=((float)800 - sprite.getLocalBounds().height)/2;
    sprite.setPosition(xPos, yPos);
    switch(shipType){
        case lennon:
            sprite.setTexture(textureManager.getTextureFromAtlas("lennon"));
            animation = {sprite,0,0,58,79,1,0};
            fireRate = 0.4;
            maxSpeed = 10;
            accel = 0.15;
            bend = 2.0;
            break;
        case macca:
            sprite.setTexture(textureManager.getTextureFromAtlas("macca"));
            animation = {sprite, 0, 0, 36, 66, 1, 0};
            fireRate = 0.3;
            maxSpeed = 15;
            accel = 0.11;
            bend = 1.8;
            break;
        case harrison:
            sprite.setTexture(textureManager.getTextureFromAtlas("harrison"));
            animation = {sprite, 0, 0, 52, 66, 1, 0};
            fireRate = 0.5;
            maxSpeed = 13;
            accel = 0.12;
            bend = 1.5;
            break;
        case starr:
            sprite.setTexture(textureManager.getTextureFromAtlas("starr"));
            animation = {sprite, 0, 0, 32, 44, 1, 0};
            fireRate = 0.2;
            maxSpeed = 16;
            accel = 0.15;
            bend = 2.2;
            break;

    }
    boosting=false;
    shooting=false;
    hp=1;
    angle=-90;
    this->type = EntityType::spaceship;
    defenceStrategy = nullptr;
    setDefenceStrategy(none);
}

void Spaceship::updatePosition() {
    sprite.setOrigin(sprite.getLocalBounds().width/2,sprite.getLocalBounds().height/2);
    if(boosting){
        if(sprite.getTextureRect().left != sprite.getTextureRect().width) {
            animation = {sprite, sprite.getTextureRect().width, 0, sprite.getTextureRect().width,
                         sprite.getTextureRect().height, 1, 0};
        }
        dx += (float)cos(angle*radians)*accel;
        dy += (float)sin(angle*radians)*accel;
        float speed = sqrt(dx*dx + dy*dy);
        if(speed>maxSpeed){
            dx *= maxSpeed/speed;
            dy *= maxSpeed/speed;
        }
    }
    else{
        dx *= 0.98;
        dy *= 0.98;
        if(sprite.getTextureRect().left != 0) {
            animation = {sprite, 0,0,sprite.getTextureRect().width,sprite.getTextureRect().height,1,0};
        }
    }
    xPos += dx;
    yPos += dy;

    if(defenceStrategy->getType() != none && defenceStrategy->isShieldTerminated()){
        setDefenceStrategy(none);
    }

    if(xPos<0)
        xPos = 1280;
    if(xPos>1280)
        xPos=0;
    if(yPos<0)
        yPos = 800;
    if(yPos>800)
        yPos=0;
}

void Spaceship::setBoosting(bool boost) {
    boosting=boost;
}

float Spaceship::getFireRate() {
    return fireRate;
}

void Spaceship::turnRight() {
    sprite.setOrigin(sprite.getLocalBounds().width/2,sprite.getLocalBounds().height/2);
    angle += bend;
}

void Spaceship::turnLeft() {
    sprite.setOrigin(sprite.getLocalBounds().width/2,sprite.getLocalBounds().height/2);
    angle -= bend;
}

void Spaceship::setShooting(bool shooting) {
    this->shooting = shooting;
}

bool Spaceship::isShooting() {
    return shooting;
}

void Spaceship::setDefenceStrategy(DefStrategyType type) {
    delete defenceStrategy;
    switch (type){
        case none:
            defenceStrategy = new NoneShield();
            break;
        case toggableShield:
            defenceStrategy = new ToggableShield(sprite);
            break;
        case timeShield:
            defenceStrategy = new TimeShield(sprite);
    }

}

Spaceship::~Spaceship() {
    if(defenceStrategy->getType() == toggableShield || defenceStrategy->getType() == timeShield)
        delete(defenceStrategy);
}

DefenceStrategy* Spaceship::getDefenceStrategy() {
    return defenceStrategy;
}