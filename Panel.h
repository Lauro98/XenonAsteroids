#ifndef XENON_PANEL_H
#define XENON_PANEL_H
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "TextureManager.h"
#include "Spaceship.h"

class Panel {
public:
    Panel();
    Panel(const sf::Font& font, TextureManager& textureManager);
    void draw(sf::RenderWindow& renderWindow);
    void addPoints(int points);
    void setShieldText(unsigned int value);
    int getScore();
private:
    sf::Sprite shieldIco;
    sf::Text shieldText;
    sf::Text scoreText;
    int score;
};

#endif