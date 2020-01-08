#include "ToggableShield.h"

ToggableShield::ToggableShield(sf::Sprite& sprite) {
    textureShield.loadFromFile("media/toggable_shield.png");
    shield.setTexture(textureShield);
    shield.setPosition(sprite.getPosition());
    visible = false;
    shieldTerminated = false;
    hp = 0;
    addShield();
    type = toggableShield;
}

void ToggableShield::impact() {
    visible = false;
    hp--;
}

void ToggableShield::update() {
    if(hp == 0)
        shieldTerminated = true;
}

void ToggableShield::addShield() {
    hp++;
}

void ToggableShield::activateShield() {
    visible = !visible;
}

unsigned int ToggableShield::getShieldLife() {
    return hp;
}