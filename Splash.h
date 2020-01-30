#ifndef XENON_SPLASH_H
#define XENON_SPLASH_H
#include "State.h"
#include "Game.h"

class Splash: public State {
public:
    explicit Splash(GameDataRef data);
    void init() override ;
    void handleInput() override;
    void update() override ;
    void draw () override;
private:
    GameDataRef data;
    sf::Clock clock;
    sf::Sprite background;
};

#endif