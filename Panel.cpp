#include <iostream>
#include "Panel.h"

Panel::Panel() {

}

Panel::Panel(const sf::Font& font, TextureManager& textureManager) {
    shieldIco.setOrigin(0,0);
    shieldIco.setTexture(textureManager.getTextureFromAtlas("shieldIco"));
    shieldIco.setPosition(1050,10);

    shieldText.setOrigin(0,0);
    shieldText.setPosition(shieldIco.getPosition().x+50,11);
    shieldText.setFont(font);
    shieldText.setFillColor(sf::Color::White);
    shieldText.setCharacterSize(43);
    shieldText.setString("0");

    scoreText.setOrigin(0,0);
    scoreText.setPosition(50,10);
    scoreText.setFont(font);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setCharacterSize(50);
    score = 0;
    addPoints(0);
}

void Panel::addPoints(int points) {
    if(points < 0 && abs(points) > score)
        score = 0;
    else
        score += points;
    std::string string = std::to_string(score);
    scoreText.setString(string);
}

void Panel::draw(sf::RenderWindow &renderWindow) {
    renderWindow.draw(scoreText);
    renderWindow.draw(shieldIco);
    renderWindow.draw(shieldText);
}

    int Panel::getScore() {
    return score;
}

void Panel::setShieldText(unsigned int value) {
    std::string string = std::to_string(value);
    shieldText.setString(string);
}