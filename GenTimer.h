#ifndef XENON_GENTIMER_H
#define XENON_GENTIMER_H
#include <SFML/System/Clock.hpp>

struct Cronometer {
    sf::Clock clock;
    float time;
    Cronometer(){ time = 0; }
};

class GenTimer {
public:
    void init();
    void update();
    float getAlienGenTime();
    float getAsteroidGenTime();
    void resetAlienGen();
    void resetAsteroidGen();
private:
    Cronometer alienGen;
    Cronometer asteroidGen;
};


#endif
