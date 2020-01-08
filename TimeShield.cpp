#include "TimeShield.h"
#include "Definitions.h"

TimeShield::TimeShield(sf::Sprite& sprite) {
    textureShield.loadFromFile("media/time_shield.png");
    shield.setTexture(textureShield);
    shield.setPosition(sprite.getPosition());
    shieldTerminated = false;
    visible = false;
    duration = TIME_SHIELD_BASE_DURATION;
    type=timeShield;
}

void TimeShield::impact() {
    if(duration == 0)
        duration = 0;
    else
        duration--;
}

void TimeShield::update() {
    if(clock.getElapsedTime().asSeconds() >= 1 && visible) {
        duration--;
        clock.restart();
    }
    if(duration == 0){
        visible = false;
        shieldTerminated = true;
    }
}

void TimeShield::addShield() {
    duration += ADD_TIME_SHIELD_DURATION;
}

void TimeShield::activateShield() {
    if(!visible) {
        visible = true;
    }
}

unsigned int TimeShield::getShieldLife() {
    return duration;
}