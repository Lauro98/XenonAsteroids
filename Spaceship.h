#ifndef XENON_SPACESHIP_H
#define XENON_SPACESHIP_H
#include "Entity.h"
#include "TextureManager.h"
#include "DefenceStrategy.h"

enum ShipType {lennon, macca, harrison, starr};

class Spaceship: public Entity {
public:
    Spaceship() = default;
    Spaceship(TextureManager& textureManager, ShipType shipType);
    ~Spaceship() override;
    void update() override;
    void setBoosting(bool boosting);
    void shoot();
    void setDefenceStrategy(DefStrategyType type);
    DefenceStrategy* getDefenceStrategy();
    bool isShooting();
    void turnLeft();
    void turnRight();
private:
    bool boosting;
    bool shooting;
    float maxSpeed;
    float fireRate;
    float accel;
    float bend;
    sf::Clock shootClock;
    DefenceStrategy* defenceStrategy;
};

#endif