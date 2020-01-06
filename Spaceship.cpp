#include <iostream>
#include "Spaceship.h"
#include "cmath"
#include "ToggableShield.h"
#include "TimeShield.h"
#include "NoneShield.h"
#include "Definitions.h"


Spaceship::Spaceship(TextureManager& textureManager, ShipType shipType) {
    switch(shipType){
        case lennon:
            sprite.setTexture(textureManager.getTextureFromAtlas("lennon"));
            animation = {sprite,0,0, LENNON_SPRITE_WIDTH, LENNON_SPRITE_HEIGHT,1,0};
            fireRate = LENNON_FIRE_RATE;
            maxSpeed = LENNON_MAX_SPEED;
            accel = LENNON_ACCEL;
            bend = LENNON_BEND;
            break;
        case macca:
            sprite.setTexture(textureManager.getTextureFromAtlas("macca"));
            animation = {sprite, 0, 0, MACCA_SPRITE_WIDTH, MACCA_SPRITE_HEIGHT, 1, 0};
            fireRate = MACCA_FIRE_RATE;
            maxSpeed = MACCA_MAX_SPEED;
            accel = MACCA_ACCEL;
            bend = MACCA_BEND;
            break;
        case harrison:
            sprite.setTexture(textureManager.getTextureFromAtlas("harrison"));
            animation = {sprite, 0, 0, HARRISON_SPRITE_WIDTH, HARRISON_SPRITE_HEIGHT, 1, 0};
            fireRate = HARRISON_FIRE_RATE;
            maxSpeed = HARRISON_MAX_SPEED;
            accel = HARRISON_ACCEL;
            bend = HARRISON_BEND;
            break;
        case starr:
            sprite.setTexture(textureManager.getTextureFromAtlas("starr"));
            animation = {sprite, 0, 0, STARR_SPRITE_WIDTH, STARR_SPRITE_HEIGHT, 1, 0};
            fireRate = STARR_FIRE_RATE;
            maxSpeed = STARR_MAX_SPEED;
            accel = STARR_ACCEL;
            bend = STARR_BEND;
            break;
    }
    xPos=((float)WINDOW_WIDTH - sprite.getLocalBounds().width)/2;
    yPos=((float)WINDOW_HEIGHT - sprite.getLocalBounds().height)/2;
    std::cout << xPos << ", " << yPos << std::endl;
    sprite.setPosition(xPos, yPos);
    std::cout << "position is" << sprite.getPosition().x << ", " << sprite.getPosition().y << std::endl;
    sprite.setOrigin(sprite.getLocalBounds().width/2,sprite.getLocalBounds().height/2);
    boosting=false;
    shooting=false;
    alive=true;
    angle=-90;
    shootClock.restart();
    this->type = EntityType::spaceship;
    defenceStrategy = nullptr;
    setDefenceStrategy(none);
}

Spaceship::~Spaceship() {
    if(defenceStrategy->getType() == toggableShield || defenceStrategy->getType() == timeShield)
        delete(defenceStrategy);
}

void Spaceship::update() {
    shooting = false;
    sprite.setOrigin(sprite.getLocalBounds().width/2,sprite.getLocalBounds().height/2);
    if(boosting){
        if(sprite.getTextureRect().left != sprite.getTextureRect().width) {
            animation = {sprite, sprite.getTextureRect().width, 0, sprite.getTextureRect().width,
                         sprite.getTextureRect().height, 1, 0};
        }
        dx += (float)cos(angle*RADIANS)*accel;
        dy += (float)sin(angle*RADIANS)*accel;
        float speed = sqrt(dx*dx + dy*dy);
        if(speed>maxSpeed){
            dx *= maxSpeed/speed;
            dy *= maxSpeed/speed;
        }
    }
    else{
        dx *= DECEL_FACTOR;
        dy *= DECEL_FACTOR;
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
        xPos = WINDOW_WIDTH;
    if(xPos>WINDOW_WIDTH)
        xPos=0;
    if(yPos<0)
        yPos = WINDOW_HEIGHT;
    if(yPos>WINDOW_HEIGHT)
        yPos=0;
}

void Spaceship::setBoosting(bool boost) {
    boosting=boost;
}

void Spaceship::turnRight() {
    sprite.setOrigin(sprite.getLocalBounds().width/2,sprite.getLocalBounds().height/2);
    angle += bend;
}

void Spaceship::turnLeft() {
    sprite.setOrigin(sprite.getLocalBounds().width/2,sprite.getLocalBounds().height/2);
    angle -= bend;
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

DefenceStrategy* Spaceship::getDefenceStrategy() {
    return defenceStrategy;
}

void Spaceship::shoot() {
    if(shootClock.getElapsedTime().asSeconds() >= fireRate) {
        shooting = true;
        shootClock.restart();
    }
}