#ifndef XENON_GAME_H
#define XENON_GAME_H
#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include "StateManager.h"
#include "TextureManager.h"
#include "Spaceship.h"
#include "Panel.h"
#include "SoundManager.h"
#include "GenTimer.h"

struct GameData {StateManager stateManager; TextureManager textureManager; sf::RenderWindow renderWindow;
                sf::Font font; Spaceship spaceship; Panel panel; SoundManager soundManager;};

typedef std::shared_ptr<GameData> GameDataRef;

class Game {
public:
    Game();
private:
    float dt;
    float newTime, frameTime, accumulator, currentTime;
    sf::Clock gameClock;
    GameDataRef data = std::make_shared<GameData>();
};


#endif