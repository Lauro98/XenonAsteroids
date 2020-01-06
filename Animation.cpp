#include "Animation.h"

Animation::Animation(sf::Sprite &sprite, int xOrigin, int yOrigin, int width, int height, int totalRects, float animationSpeed) {
    animEnded = false;
    this->animationSpeed=animationSpeed;
    frame=0;

    for(int i=0; i<totalRects; i++)
        rects.emplace_back(xOrigin+i*width, yOrigin, width, height);

    sprite.setTextureRect(rects.at(0));
}

void Animation::update(sf::Sprite& sprite) {
    frame += animationSpeed;
    if (frame >= rects.size()) {
        frame -= rects.size();
        animEnded = true;
    }
    else
        animEnded = false;
    sprite.setTextureRect(rects.at((int)frame));
}

bool Animation::isAnimEnded() {
    return animEnded;
}
