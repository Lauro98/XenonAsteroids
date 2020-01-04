#include "DefenceStrategy.h"


bool DefenceStrategy::isVisible() {
    return visible;
}

sf::Sprite &DefenceStrategy::getShieldSprite() {
    return shield;
}

void DefenceStrategy::draw(sf::Sprite sprite, sf::RenderWindow &renderWindow) {
    shield.setPosition(sprite.getPosition().x - shield.getLocalBounds().width/2, sprite.getPosition().y - shield.getLocalBounds().height/2);
    renderWindow.draw(shield);
}

DefStrategyType DefenceStrategy::getType() {
    return type;
}

bool DefenceStrategy::isShieldTerminated() {
    return shieldTerminated;
}
