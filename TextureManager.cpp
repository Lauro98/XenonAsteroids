#include <iostream>
#include "TextureManager.h"

TextureManager::TextureManager() {
    loadTexture("background", "media/background.jpg");
    loadTexture("commands", "media/commands.png");
    loadTexture("explosion", "media/explosion.png");
    loadTexture("game_over", "media/GameOver.png");
    loadTexture("harrison", "media/harrison.png");
    loadTexture("lennon", "media/lennon.png");
    loadTexture("macca", "media/macca.png");
    loadTexture("menu", "media/menu.jpg");
    loadTexture("pause", "media/pause.png");
    loadTexture("projectile","media/projectile.png");
    loadTexture("rock", "media/rock.png");
    loadTexture("rock_small", "media/rock_small.png");
    loadTexture("settings", "media/settings.png");
    loadTexture("shieldIco", "media/shield_ico.png");
    loadTexture("splash", "media/splash.png");
    loadTexture("starr", "media/starr.png");
}

void TextureManager::loadTexture(const std::string &name, const std::string &filePath) {
    sf::Texture tempTex;
    if(!tempTex.loadFromFile(filePath))
        std::cout << "error: can't open file at " << filePath << std::endl;
    textureAtlas[name] = tempTex;
}

sf::Texture &TextureManager::getTextureFromAtlas(const std::string &name) {
    return textureAtlas.at(name);
}