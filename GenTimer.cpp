#include "GenTimer.h"

void GenTimer::init() {
    alienGen.clock.restart();
    alienGen.time = 0;
    asteroidGen.clock.restart();
    asteroidGen.time = 0;
}

void GenTimer::update() {
    alienGen.time = alienGen.clock.getElapsedTime().asSeconds();
    asteroidGen.time = asteroidGen.clock.getElapsedTime().asSeconds();
}

float GenTimer::getAlienGenTime() {
    return alienGen.time;
}

float GenTimer::getAsteroidGenTime() {
    return asteroidGen.time;
}

void GenTimer::resetAlienGen() {
    alienGen.time = 0;
    alienGen.clock.restart();
}

void GenTimer::resetAsteroidGen() {
    asteroidGen.time = 0;
    asteroidGen.clock.restart();
}
