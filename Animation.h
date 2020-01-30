#ifndef XENON_ANIMATION_H
#define XENON_ANIMATION_H
#include <vector>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Clock.hpp>

class Animation {
public:
    Animation() = default;
    Animation(sf::Sprite &sprite, int xOrigin, int yOrigin, int width, int height, int totalRects, float animationSpeed);
    void update(sf::Sprite& sprite);
    bool isAnimEnded();
private:
    float frame;
    float animationSpeed;
    std::vector<sf::IntRect> rects;
    bool animEnded;
};

#endif