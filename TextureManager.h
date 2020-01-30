#ifndef XENON_TEXTUREMANAGER_H
#define XENON_TEXTUREMANAGER_H
#include <string>
#include <SFML/Graphics/Texture.hpp>
#include <map>

class TextureManager {
public:
    TextureManager();
    sf::Texture &getTextureFromAtlas(const std::string &name);
private:
    std::map<std::string, sf::Texture> textureAtlas;
    void loadTexture(const std::string &name, const std::string &filePath);
};

#endif