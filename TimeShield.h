#ifndef XENON_TIMESHIELD_H
#define XENON_TIMESHIELD_H
#include "DefenceStrategy.h"

class TimeShield: public DefenceStrategy {
public:
    explicit TimeShield(sf::Sprite& sprite);
    void addShield() override;
    void impact() override;
    void update() override;
    void activateShield() override;
    unsigned int getShieldLife() override;
private:
    sf::Clock clock;
    int duration;
};

#endif