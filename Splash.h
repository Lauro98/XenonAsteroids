#ifndef XENON_SPLASH_H
#define XENON_SPLASH_H


#include "State.h"
#include "Game.h"

class Splash: public State {
private:
    GameDataRef data;
    sf::Clock clock;
    sf::Sprite background;
public:
    explicit Splash(GameDataRef data);

    void init() override ;

    void handleInput() override;

    void update() override ;

    void draw () override;
};


#endif //XENON_SPLASH_H
