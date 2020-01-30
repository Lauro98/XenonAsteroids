#ifndef XENON_SETTINGS_H
#define XENON_SETTINGS_H
#include "State.h"
#include "Game.h"

class Settings: public State {
public:
    explicit Settings(GameDataRef dataRef);
    void moveUp();
    void moveDown();
    void init() override;
    void handleInput() override;
    void update() override;
    void draw () override;
private:
    GameDataRef data;
    sf::Sprite background;
    sf::Text text[4];
    int selectedItemIndex;
    bool viewingCommands;
};

#endif