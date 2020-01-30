#ifndef XENON_EXPLOSION_H
#define XENON_EXPLOSION_H
#include "Entity.h"

class Explosion : public Entity{
public:
    Explosion(TextureManager& textureManager, Entity& entity);
    void update() override;
};

#endif