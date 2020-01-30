#ifndef XENON_SELECTSPACESHIP_H
#define XENON_SELECTSPACESHIP_H
#include "Game.h"
#include "State.h"
#include "Spaceship.h"

class SelectSpaceShip: public State {
public:
    explicit SelectSpaceShip(GameDataRef data);
    void moveLeft();
    void moveRight();
    void init() override ;
    void handleInput() override;
    void update() override ;
    void draw () override;
private:
    GameDataRef data;
    sf::Sprite background;
    sf::Sprite ship[4];
    sf::Text name[4];
    int selectedItemIndex;
};

#endif