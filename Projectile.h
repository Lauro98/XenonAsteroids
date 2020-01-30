#ifndef XENON_PROJECTILE_H
#define XENON_PROJECTILE_H
#include "Entity.h"
#include "TextureManager.h"
#include "Spaceship.h"
#include "Alien.h"

class Projectile: public Entity {
public:
    Projectile(TextureManager& textureManager, const sf::Sprite& shooter, bool playerShot);
    void update() override;
private:
    bool playerShot;
};

#endif