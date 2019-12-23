#ifndef XENON_ANIMATION_H
#define XENON_ANIMATION_H

#include <vector>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Clock.hpp>

class Animation {
private:
    float frame;
    float animationSpeed;
    std::vector<sf::IntRect> rects;
    bool endOfAnim{};
public:
    Animation();
    Animation(sf::Sprite &sprite, int xOrigin, int yOrigin, int width, int height, int totalRects, float animationSpeed);
    void update(sf::Sprite& sprite);
    bool isEndOfAnim();
};


#endif //XENON_ANIMATION_H
