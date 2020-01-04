#ifndef XENON_GAME_H
#define XENON_GAME_H

#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include "StateManager.h"
#include "TextureManager.h"
#include "Spaceship.h"
#include "Panel.h"


struct GameData {StateManager stateManager; TextureManager textureManager; sf::RenderWindow renderWindow;
                sf::Font font; Spaceship spaceship; Panel panel;};

typedef std::shared_ptr<GameData> GameDataRef;

class Game {
private:
    float dt;
    sf::Clock gameClock;
    GameDataRef data = std::make_shared<GameData>();
public:
    Game();

    void run();

};


#endif //XENON_GAME_H
