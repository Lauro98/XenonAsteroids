#ifndef XENON_ASTEROID_H
#define XENON_ASTEROID_H
#include "Entity.h"
#include "TextureManager.h"

class Asteroid: public Entity {
public:
    explicit Asteroid(TextureManager& textureManager);
    Asteroid (TextureManager& textureManager, Entity& asteroid);
    void update() override;
};

#endif