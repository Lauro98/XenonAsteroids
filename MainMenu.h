#ifndef XENON_MAINMENU_H
#define XENON_MAINMENU_H

#include "State.h"
#include "Game.h"
#include <SFML/Graphics.hpp>

class MainMenu: public State {
private:
    GameDataRef data;
    sf::Sprite background;
    sf::Text text[3];
    int selectedItemIndex;

public:
    explicit MainMenu(GameDataRef data);

    void moveUp();

    void moveDown();

    void init() override ;

    void handleInput() override;

    void update() override ;

    void draw () override;
};


#endif //XENON_MAINMENU_H
