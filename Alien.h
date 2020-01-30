#ifndef XENON_ALIEN_H
#define XENON_ALIEN_H
#include "Entity.h"
#include "Spaceship.h"
#include "SoundManager.h"

class Alien: public Entity {
public:
    explicit Alien(TextureManager& textureManager);
    void update() override {};
    void update(TextureManager& textureManager, Spaceship& spaceship, std::vector<Entity*>& entities, SoundManager& soundManager);
private:
    sf::Vector2f destination;
    sf::Clock shootClock;
};

#endif