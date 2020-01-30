#ifndef XENON_PAUSE_H
#define XENON_PAUSE_H
#include "Game.h"
#include "Spaceship.h"
#include "Panel.h"

class Pause: public State {
public:
    explicit Pause(GameDataRef data);
    void moveUp();
    void moveDown();
    void init() override ;
    void handleInput() override;
    void update() override ;
    void draw () override;
private:
    GameDataRef data;
    sf::Sprite background;
    sf::Text text[5];
    int selectedItemIndex;
};

#endif