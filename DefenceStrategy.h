#ifndef XENON_DEFENCESTRATEGY_H
#define XENON_DEFENCESTRATEGY_H


#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Text.hpp>

enum DefStrategyType {none, toggableShield, timeShield};

class DefenceStrategy {
protected:
    sf::Sprite shield;
    sf::Texture textureShield;
    bool visible;
    bool shieldTerminated;
    DefStrategyType type;
public:
    virtual ~DefenceStrategy() = default;
    virtual bool isVisible();
    virtual bool isShieldTerminated();
    virtual sf::Sprite& getShieldSprite();
    virtual void activateShield() = 0;
    virtual void addShield() = 0;
    virtual void draw(sf::Sprite sprite, sf::RenderWindow& renderWindow);
    virtual void impact()=0;
    DefStrategyType getType();
    virtual unsigned int getShieldLife() = 0;
    virtual void update() = 0;

};


#endif //XENON_DEFENCESTRATEGY_H
