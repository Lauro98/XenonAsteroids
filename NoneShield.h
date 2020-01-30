#ifndef XENON_NONESHIELD_H
#define XENON_NONESHIELD_H
#include "DefenceStrategy.h"

class NoneShield: public DefenceStrategy{
public:
    NoneShield();
    void addShield() override;
    void impact() override;
    void update() override ;
    void activateShield() override;
    unsigned int getShieldLife() override;
};

#endif