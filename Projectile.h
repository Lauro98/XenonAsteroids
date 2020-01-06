#ifndef XENON_PROJECTILE_H
#define XENON_PROJECTILE_H

#include "Entity.h"
#include "TextureManager.h"
#include "Spaceship.h"


class Projectile: public Entity {
public:
    Projectile(TextureManager& textureManager, Spaceship& spaceship);
    void update() override;
};


#endif //XENON_PROJECTILE_H
