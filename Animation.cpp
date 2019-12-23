#include "Animation.h"

Animation::Animation(sf::Sprite &sprite, int xOrigin, int yOrigin, int width, int height, int totalRects, float animationSpeed) {
    endOfAnim = false;
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
        endOfAnim = true;
    }
    else
        endOfAnim = false;
    sprite.setTextureRect(rects.at((int)frame));
}

Animation::Animation() {

}

bool Animation::isEndOfAnim() {
    return endOfAnim;
}
