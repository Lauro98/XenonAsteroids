#ifndef XENON_GAMELOOP_H
#define XENON_GAMELOOP_H
#include "SFML/Graphics.hpp"
#include "TextureManager.h"
#include "Asteroid.h"
#include "Projectile.h"
#include "Spaceship.h"
#include "Explosion.h"
#include "Collision.h"
#include "Panel.h"
#include "State.h"
#include "Game.h"
#include "Definitions.h"
#include "Alien.h"

class GameLoop: public State {
public:
    explicit GameLoop(GameDataRef data);
    ~GameLoop() override;
    void handleInput() override;
    void init() override;
    void update() override;
    void draw () override;
private:
    GenTimer genTimer;
    sf::Clock gameOverTimer;
    std::vector<Entity*> entities;
    std::vector<Alien*> aliens;
    sf::Sprite background;
    GameDataRef data;
    bool gameOver;
};

#endif