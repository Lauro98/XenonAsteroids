#ifndef XENON_SPACESHIP_H
#define XENON_SPACESHIP_H

#include "Entity.h"
#include "TextureManager.h"
#include "DefenceStrategy.h"

enum ShipType {lennon, macca, harrison, starr};

class Spaceship: public Entity {
private:
    bool isBoosting;
    bool isShooting;
    float maxSpeed;
    float fireRate;
    float accel;
    float bend;
    DefenceStrategy* defenceStrategy;
public:
    Spaceship();
    Spaceship(TextureManager& textureManager, ShipType shipType);
    ~Spaceship() override;
    void updatePosition() override;
    void setBoosting(bool isBoosting);
    void setShooting(bool isShooting);
    void setDefenceStrategy(DefStrategyType type);
    DefenceStrategy* getDefenceStrategy();
    bool getShooting();
    float getFireRate();
    void turnLeft();
    void turnRight();

};


#endif //XENON_SPACESHIP_H
