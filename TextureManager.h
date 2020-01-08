#ifndef XENON_TEXTUREMANAGER_H
#define XENON_TEXTUREMANAGER_H

#include <string>
#include <SFML/Graphics/Texture.hpp>
#include <map>

class TextureManager {
private:
    std::map<std::string, sf::Texture> textureAtlas;
    void loadTexture(const std::string &name, const std::string &filePath);
public:
    TextureManager();
    sf::Texture &getTextureFromAtlas(const std::string &name);
};


#endif //XENON_TEXTUREMANAGER_H
