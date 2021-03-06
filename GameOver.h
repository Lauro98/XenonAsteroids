#ifndef XENON_GAMEOVER_H
#define XENON_GAMEOVER_H
#include "State.h"
#include "Game.h"

class GameOver: public State {
public:
    explicit GameOver(GameDataRef data);
    void moveUp();
    void moveDown();
    void init() override ;
    void handleInput() override;
    void update() override ;
    void draw () override;
private:
    GameDataRef data;
    sf::Sprite background;
    sf::Font font;
    sf::Text text[2];
    int selectedItemIndex;
    sf::Clock clock;
};

#endif