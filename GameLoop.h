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


class GameLoop: public State {
private:
    sf::Clock asteroidsGen;
    sf::Clock shootClock;
    std::vector<Entity*> entities;
    sf::Sprite background;
    GameDataRef data;
    bool gameOver;

public:
    GameLoop(GameDataRef data);

    ~GameLoop() override;

    void handleInput() override;

    void init() override ;

    void update() override ;

    void draw () override;
};


#endif
