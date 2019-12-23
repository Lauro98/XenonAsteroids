#ifndef XENON_TIMESHIELD_H
#define XENON_TIMESHIELD_H


#include "DefenceStrategy.h"

class TimeShield: public DefenceStrategy {
private:
    sf::Clock clock;
    unsigned int duration;
public:
    explicit TimeShield(sf::Sprite& sprite);
    void addShield() override;
    void impact() override;
    void update() override;
    void activateShield() override;
    unsigned int getShieldLife() override;

};


#endif //XENON_TIMESHIELD_H
