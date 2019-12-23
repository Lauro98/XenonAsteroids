#include "TimeShield.h"

TimeShield::TimeShield(sf::Sprite& sprite) {
    textureShield.loadFromFile("media/time_shield.png");
    shield.setTexture(textureShield);
    shield.setPosition(sprite.getPosition());
    shieldTerminated = false;
    visible = false;
    duration = 3;
    type=timeShield;
}

void TimeShield::impact() {
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
    duration +=2;
}

void TimeShield::activateShield() {
    if(!visible) {
        visible = true;
    }
}

unsigned int TimeShield::getShieldLife() {
    return duration;
}
