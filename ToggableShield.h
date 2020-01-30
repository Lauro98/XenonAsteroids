 #ifndef XENON_TOGGABLESHIELD_H
#define XENON_TOGGABLESHIELD_H

#include "DefenceStrategy.h"

class ToggableShield: public DefenceStrategy {
public:
    explicit ToggableShield(sf::Sprite& sprite);
    void addShield() override;
    void impact() override;
    void update() override;
    void activateShield() override;
    unsigned int getShieldLife() override;
private:
    unsigned int hp;
};

#endif