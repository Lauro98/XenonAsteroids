#ifndef XENON_EXPLOSION_H
#define XENON_EXPLOSION_H

#include "Entity.h"

class Explosion : public Entity{
private:
public:
    Explosion(TextureManager& textureManager, Entity& entity);
    void updatePosition() override;
};

#endif //XENON_EXPLOSION_H
